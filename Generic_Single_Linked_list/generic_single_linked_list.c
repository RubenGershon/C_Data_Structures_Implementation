/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Single Linked List implementation file
* 						  DATE: 2020
*******************************************************************************/

#include <stdio.h> 		/* printf            */
#include <stdlib.h> 	/* malloc realloc    */
#include "generic_single_linked_list.h"

/*********************************[ MACROS ]***********************************/

/*********************************[ STRUCTS ]**********************************/

typedef struct node Node_t;
struct node
{
    void *m_data;
    Node_t *m_next;
};

struct Sll
{
    Node_t *m_head;       /* Pointer to the head (start) of the Sll. */
    Node_t *m_last_node;  /* Pointer to the last node of the Sll. */
    CmpFunc_t m_compare;
};

/*****************************[ STATICS FUNCTIONS ]****************************/

/** @brief Dynamically create a new vector object of given capacity.  
 *  @param[in] a_initialCapacity - n of elements that can be stored initially.
 *  @param[in] a_blockSize - the vector will grow or shrink  by this size. 
 *  @return Vector * - on success / NULL on fail.
 *  @warning if a_blockSize is 0 the vector will be of fixed size. 
 *  @warning if both params are zero function will return NULL. */
static Node_t *SLLCreateNode(void const* a_data);

static Node_t *SLLInsertAfter(Node_t *a_where, Node_t *a_node);
static Node_t *SLLInsertBefore(Node_t *a_where, Node_t *a_node);
static Node_t *SLLRemoveAfter(Node_t *node);
static Node_t *SLLRemoveCurrent(Node_t *node);

static void SwapData(Node_t *where, Node_t *node);
static Node_t *FlipRec(Node_t *head);




/*****************************[ CREATE & DESTROY ]*****************************/


Sll_t *SLLCreate(CmpFunc_t a_compare)
{
    Sll_t *newList = (Sll_t*)calloc(1, sizeof(Sll_t));
    if (NULL == newList)
    {
        return NULL;
    }

    newList->m_compare = a_compare;
    return newList;
}


void SLLDestroy(Sll_t *a_sll, DestroyFunc_t a_destroyer)
{
    Node_t* curr_node = NULL;
    Node_t* next_node = NULL;
    if (NULL == a_sll)
    {
        return;
    }

    curr_node = a_sll->m_head;

    while(NULL != curr_node)
    {
        next_node = curr_node->m_next;
        if (NULL != a_destroyer)
        {
            a_destroyer(curr_node->m_data);
        }
        free(curr_node);
        curr_node = next_node;
    }
    free(a_sll);
}


/**********************************[ INSERT ]**********************************/



Iterator_t *SLLInsert(Sll_t *a_sll, void const* a_data, Iterator_t *a_itr, Op_t a_op)
{
    Node_t *newNode = NULL;
    Iterator_t *it = NULL;

    if ( (NULL == a_sll || NULL == a_data) || (a_itr != NULL && EMPTY == a_op)
    || (a_itr != NULL && (a_op != BEFORE && a_op != AFTER)) 
    || (a_itr != NULL && a_op == SORTED)
    || (a_itr == NULL && (a_op != SORTED && a_op != EMPTY)) 
    || (a_itr == NULL && a_op == SORTED && NULL == a_sll->m_compare) )
    {
        return NULL;
    }

    newNode = SLLCreateNode(a_data);
    if (NULL == newNode)
    {
        return NULL;
    }

    if (a_sll->m_head == NULL)
    {
        a_sll->m_head = newNode;
        a_sll->m_last_node = newNode;
        return (Iterator_t *)a_sll->m_head;
    }

    /* if no position specified, and a_op != SORTED insert last */
    if ( (NULL == a_itr) && (EMPTY == a_op) )
    {
        a_sll->m_last_node->m_next = newNode;
        a_sll->m_last_node = newNode;
    }
    else if( (NULL == a_itr) && (a_op == SORTED) )
    {
        SLLForEach(a_sll, (int (*) (void *,void *))a_sll->m_compare, (void*)a_data, &it);
        SLLInsertBefore((Node_t *)it, newNode);
    }
    else /* Insert AFTER/BEFORE given Iterator */
    {
        if (a_op == AFTER)
        {
            SLLInsertAfter((Node_t *)a_itr, newNode);
        }
        else
        {
            SLLInsertBefore((Node_t *)a_itr, newNode);
        }  
    }

    return (Iterator_t *)newNode;
}

static Node_t *SLLCreateNode(void const *a_data)
{
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if (NULL == newNode)
    {
        return NULL;
    }

    newNode->m_data = (void *)a_data;
    newNode->m_next = NULL;

    return newNode;
}

static Node_t *SLLInsertAfter(Node_t *a_where, Node_t *a_node)
{
    a_node->m_next = a_where->m_next;
    a_where->m_next = a_node;
    return a_node;
}


static Node_t *SLLInsertBefore(Node_t *a_where, Node_t *a_node)
{
    SLLInsertAfter(a_where, a_node);
    SwapData(a_where, a_node);
    return a_where;
}



/**********************************[ REMOVE ]**********************************/


Status_t SLLRemove(Sll_t *a_sll, void **a_data, Iterator_t *a_itr, Op_t a_op)
{
    Node_t *removed = NULL;
    if ( (NULL == a_sll) || (NULL == a_itr) || (a_op != CURRENT && a_op != AFTER) ) 
    {
        return ERR_BAD_ARGS;
    }

    if (a_sll->m_last_node == (Node_t*)a_itr)
    {
        return ERR_LAST;
    }

    /* Check if we remove the last node of the list, if yes, need update.*/
    if (a_sll->m_last_node == (Node_t*)IteratorNext(a_itr))
    {
        a_sll->m_last_node = (Node_t*)a_itr;
    }

    if (CURRENT == a_op)
    {
        removed = SLLRemoveCurrent((Node_t*)a_itr);
    }
    else if ( NULL != IteratorNext(a_itr) )
    {
        removed = SLLRemoveAfter((Node_t*)a_itr);
    }
    
    if (NULL != a_data)
    {
        *a_data = removed->m_data;
    }
    
    free(removed);
    return ERR_SUCCESS;
}


static Node_t *SLLRemoveAfter(Node_t *a_node)
{
    Node_t* toReturn = NULL;

    toReturn = a_node->m_next;
    a_node->m_next = toReturn->m_next;
    toReturn->m_next = NULL;
    return toReturn; 
}


static Node_t *SLLRemoveCurrent(Node_t *a_node)
{
    SwapData(a_node, a_node->m_next);
    return SLLRemoveAfter(a_node);
}



/******************************[ EMPTY & COUNT ]*******************************/

int SLLIsEmpty(Sll_t const *a_sll)
{
    if (NULL == a_sll)
    {
        return -1;
    }
    return (a_sll->m_head == NULL);
}

int SLLCount(Sll_t const *a_sll)
{
    size_t count = 0;
    Node_t* runner = NULL;

    if (NULL == a_sll)
    {
        return -1;
    }

    runner = a_sll->m_head;
    while (NULL != runner)
    {
        ++count;
        runner = runner->m_next;
    }

    return count;
}

/********************************[ FOR EACH ]**********************************/

Status_t SLLForEach(Sll_t *a_sll, actionFunc_t a_action, void *a_param, Iterator_t **a_itr)
{
    Node_t *runner = NULL;

    if ( (NULL == a_sll) || (NULL == a_action) )
    {
        return ERR_BAD_ARGS;
    }

    runner = a_sll->m_head;
    while (NULL != runner)
    {
        if (0 != a_action(runner->m_data, a_param))
        {
            if (NULL != a_itr)
            {
                *a_itr = (Iterator_t*)runner;
            }    
            return ERR_STOP;
        }   
        runner = runner->m_next;
    }

    return ERR_SUCCESS;
}


/**********************************[ FIND ]************************************/


Iterator_t *SLLFind(Sll_t const *a_sll, void const *a_toFind, FindFunc_t a_finder)
{
    Iterator_t *it = NULL;

    if ( (NULL == a_sll) || (NULL == a_finder) || (NULL == a_toFind) )
    {
        return NULL;
    }
    SLLForEach((Sll_t*)a_sll, (int (*) (void *,void *))a_sll->m_compare, (void*)a_toFind, &it);

    return it;
}


Iterator_t *SLLFindMiddle(Sll_t const *a_sll)
{
   Node_t *fastPtr = NULL;
   Node_t *slowPtr = NULL;

   if ( (NULL == a_sll) || (NULL == a_sll->m_head) )
   {
        return NULL;
   }    

    fastPtr = a_sll->m_head;
    slowPtr = a_sll->m_head;

    while ( (NULL != fastPtr) && (NULL != fastPtr->m_next) )
    {                                                                                     
        fastPtr = fastPtr->m_next->m_next;
        slowPtr = slowPtr->m_next;
    }    

    return (Iterator_t *)slowPtr;
}


/**********************************[ FLIP ]************************************/


Iterator_t *SLLFlip(Sll_t *a_sll)
{
    Node_t* prevN = NULL;
    Node_t* currN = NULL;
    Node_t* nextN = NULL;

    if (NULL == a_sll || NULL == a_sll->m_head)
    {
        return NULL;
    }

    prevN = a_sll->m_head;
    nextN = a_sll->m_head->m_next;
    a_sll->m_head->m_next = NULL;
    while(nextN != NULL)
    {
        currN = nextN;
        nextN = nextN->m_next;
        currN->m_next = prevN;
        prevN = currN;    
    }

    return (Iterator_t *)currN;
}

Iterator_t *SLLFlipRec(Sll_t *a_sll)
{
    if (NULL == a_sll || NULL == a_sll->m_head)
    {
        return NULL;
    }

    return (Iterator_t *)FlipRec(a_sll->m_head);
}

static Node_t *FlipRec(Node_t *a_node)
{
    Node_t* newHead = NULL;
    if (NULL == a_node->m_next)
    {
        return a_node;
    }

    newHead = FlipRec(a_node->m_next);

    a_node->m_next->m_next = a_node;
    a_node->m_next = NULL;
    return newHead;
}


/******************************[ FIND INTERSECTION ]***************************/

Iterator_t *SLLFindIntersection(Sll_t const *a_sll1, Sll_t const *a_sll2)
{
    size_t head1_length = 0;
    size_t head2_length = 0;
    size_t delta = 0;
    Node_t *long_list = NULL;
    Node_t *short_list = NULL;
    
    if ( (NULL == a_sll1) || (NULL == a_sll2) )
    {
        return NULL;
    }
      
      head1_length = SLLCount(a_sll1);
      head2_length = SLLCount(a_sll2);
      
      if (head1_length >= head2_length)
      {
            long_list = a_sll1->m_head;
            short_list = a_sll2->m_head;
            delta = head1_length - head2_length;
      }
      else
      {
            long_list = a_sll2->m_head;
            short_list = a_sll1->m_head;
            delta = head2_length - head1_length;
      }
      
      while (0 != delta)
      {
            long_list = long_list->m_next;
            --delta;
      }
      
      while (NULL != long_list && long_list->m_next != short_list->m_next)
      {
            long_list = long_list->m_next;
            short_list = short_list->m_next;    
      }
      
    return ((long_list->m_next == short_list->m_next) ? 
                                (Iterator_t *)(long_list->m_next) : (NULL));
}

/**********************************[ HAS LOOP ]********************************/

int SLLHasLoop(Sll_t const *a_sll)
{
    Node_t const *slow_runner = NULL;
    Node_t const *fast_runner =  NULL;
    
    if (NULL == a_sll)
    {
        return -1;
    }
    
    slow_runner = a_sll->m_head->m_next;
    if (NULL == slow_runner)
    {
       return (0); 
    }
    
    fast_runner =  a_sll->m_head->m_next->m_next;
    
    while (slow_runner != fast_runner && NULL != fast_runner)
    {
        slow_runner = slow_runner->m_next;
        fast_runner = fast_runner->m_next;
        
        if (NULL != fast_runner)
        {
            fast_runner = fast_runner->m_next;
        }
    }
    
     return (NULL != fast_runner);
}     

/*******************************[ SWAP 2 NODES ]*******************************/


/*node_t* SLLSwapNodes(node_t *head, void *data1, void *data2, cmpFunc_t compare)
{
    node_t *node1 = head;
    node_t *node2 = head;
    node_t *node1Prev = head;
    node_t *node2Prev = head;
    node_t *temp = NULL;

    if ( (NULL == head) || (NULL == data1) || (NULL == data2) || (NULL == compare) )
    {
        return NULL;
    }

    while ( (node1 != NULL) && (1 != compare(node1->data, data1)) )
    {
        node1Prev = node1;
        node1 = node1->next;
    }

    while ( (node2 != NULL) && (1 != compare(node2->data, data2)) )
    {
        node2Prev = node2;
        node2 = node2->next;
    }

    if ( (NULL == node1) || (NULL == node2) )
    {
        return NULL; 
    }

    if (node1->next == node2)
    {
        node1->next = node2->next;
        node2->next = node1;
        if (node1 != node1Prev)
        {
            node1Prev->next = node2;
            return head;
        }
        else
        {
            return node2;
        }
    }
    else
    {
        temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        if (node1 != node1Prev)
        {
            node1Prev->next = node2;
            return head;
        }
        else
        {
            node2Prev->next = node1;
            return node2;
        }
    }
}*/



/*******************************[ STATIC SWAP ]********************************/


static void SwapData(Node_t *where, Node_t *node)
{
    void* temp = where->m_data;
    where->m_data = node->m_data;
    node->m_data = temp;
}

/**********************************[ ITERATORS ]*******************************/



Iterator_t *IteratorBegin(Sll_t const *a_sll)
{
    return (Iterator_t*)(a_sll->m_head);
}

Iterator_t *IteratorEnd(Sll_t const *a_sll)
{
    return (Iterator_t*)(a_sll->m_last_node);
}

Iterator_t *IteratorNext(Iterator_t *a_itr)
{
    if (NULL == a_itr)
    {
        return (a_itr);
    }

	return ((Iterator_t *) ((Node_t *)a_itr)->m_next);
}

void *IteratorGet(Iterator_t const *a_itr)
{
    if (NULL == a_itr)
    {
        return NULL;
    }
	return (Iterator_t*)((Node_t*)a_itr)->m_data; 
}

void *IteratorSet(Iterator_t *a_itr, void const *a_element)
{
    void *toReturn = NULL;
	if ( (NULL == a_itr) || (NULL == a_element) )
	{
		return NULL;
	}

    toReturn = ((Node_t *)a_itr)->m_data;
    ((Node_t *)a_itr)->m_data = (void*)a_element;

    return toReturn;
}
