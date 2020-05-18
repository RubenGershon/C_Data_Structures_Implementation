/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Stack Implementation File
* 						  DATE: 2020
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>      /* malloc  */
#include "generic_stack.h"

#define FALSE 0
#define TRUE 1

/******************************************************************************/

struct Stack
{
    void **m_stack;
    Stack_t* m_minStack;
    Compare_t m_cmp;
    size_t m_capacity;  /* Max N of items that can fit into the stack. */  
    size_t m_nItems;    /* N items currently present in the Stack.     */
    int m_isFirstVisit;
};


/***********************************[ CREATE ]*********************************/

Stack_t* StackCreate(size_t a_capacity, Compare_t a_cmp)
{
    Stack_t* newStack = NULL;

    if (0 == a_capacity)
    {
        return NULL;
    }

    newStack = (Stack_t*)malloc(sizeof(Stack_t));
    if (NULL == newStack)
    {
        return NULL;
    }

    newStack->m_minStack = NULL;

    newStack->m_stack = (void**)calloc(sizeof(void*), a_capacity);
    if (NULL == newStack->m_stack)
    {
        free(newStack);
        return NULL;
    }

    /* If the user provided a_cmp, we can implement a minStack utility */
    if (NULL != a_cmp)
    {
        newStack->m_minStack = (Stack_t*)malloc(sizeof(Stack_t));
        if (NULL == newStack->m_minStack)
        {
            free(newStack->m_stack);
            free(newStack);
            return NULL;
        }

        newStack->m_minStack->m_stack = (void**)calloc(sizeof(void*), a_capacity);
        if (NULL == newStack->m_minStack->m_stack)
        {
            free(newStack->m_stack);
            free(newStack->m_minStack->m_stack);
            free(newStack);
            return NULL;
        }
        newStack->m_minStack->m_nItems = 0;
    }    

    newStack->m_cmp = a_cmp;
    newStack->m_capacity = a_capacity;
    newStack->m_nItems = 0;
    newStack->m_isFirstVisit = TRUE;

    return newStack;
}


/**********************************[ DESTROY ]*********************************/


void StackDestroy(Stack_t* a_stack, DestroyFunc_t a_destroy)
{
    size_t i = 0;
    if (NULL == a_stack)
    {
        return;
    }

    if (NULL != a_destroy)
    {
        for (i = 0; i < a_stack->m_nItems; ++i)
        {
            a_destroy(a_stack->m_stack[i]);
        }
    }

    free(a_stack->m_stack);
    if (NULL != a_stack->m_minStack)
    {
        free(a_stack->m_minStack->m_stack);
    }    
    free(a_stack);
}    


/***********************************[ PUSH ]***********************************/

Status_t StackPush(Stack_t* a_stack, void const* a_item)
{
    void *tempItem = NULL;
    if (NULL == a_stack)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (IsFull(a_stack))
    {
        return ERR_OVERFLOW;
    }

    a_stack->m_stack[a_stack->m_nItems] = (void*)a_item;
    a_stack->m_nItems++;

    /* We enter here if we have a minStack */
    if (NULL != a_stack->m_minStack)
    {
        if (FALSE == a_stack->m_isFirstVisit)
        {
            StackTop(a_stack->m_minStack, &tempItem);
            if (TRUE == a_stack->m_cmp(tempItem, a_item))
            {
                a_stack->m_minStack->m_stack[a_stack->m_minStack->m_nItems] = (void*)a_item;
                a_stack->m_minStack->m_nItems++;
            }
        }
        else
        {
            a_stack->m_minStack->m_stack[a_stack->m_minStack->m_nItems] = (void*)a_item;
            a_stack->m_isFirstVisit = FALSE;
            a_stack->m_minStack->m_nItems++;
        }
    }       

    return ERR_OK;
}


/************************************[ POP ]***********************************/


Status_t StackPop(Stack_t* a_stack, void **a_item)
{
    void *tempItem1 = NULL;
    void *tempItem2 = NULL;
    if (NULL == a_stack)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (IsEmpty(a_stack))
    {
        return ERR_UNDERFLOW;
    }

    StackTop(a_stack->m_minStack, &tempItem1);
    StackTop(a_stack, &tempItem2);
    if ( (NULL != a_stack->m_minStack) && (tempItem1 == tempItem2) )
    {
        a_stack->m_minStack->m_nItems--;
    }
    
    if (NULL != a_item)
    {
        *a_item = a_stack->m_stack[a_stack->m_nItems - 1];
    }    
    a_stack->m_nItems--;

    return ERR_OK;
}

/************************************[ TOP ]***********************************/


Status_t StackTop(Stack_t const* a_stack, void **a_item)
{
    if ( (NULL == a_stack) || (NULL == a_item))
    {
        return ERR_NOT_INITIALIZED;;
    }

    if (IsEmpty(a_stack))
    {
        return ERR_UNDERFLOW;
    }

    *a_item =  a_stack->m_stack[a_stack->m_nItems - 1]; 

    return ERR_OK;
}


/************************************[ MIN ]***********************************/


Status_t StackMin(Stack_t const* a_stack, void **a_item)
{
    if ( (NULL == a_stack) || (NULL == a_stack->m_minStack) || (NULL == a_item))
    {
        return ERR_NOT_INITIALIZED;;
    }

    if (IsEmpty(a_stack))
    {
        return ERR_UNDERFLOW;
    }

    StackTop(a_stack->m_minStack, a_item);

    return ERR_OK;  
}


/****************************[ SIZE & EMPTY & FULL ]***************************/


int StackSize(Stack_t const* a_stack)
{
    if (NULL == a_stack)
    {
        return -1;
    }

    return a_stack->m_nItems;
}

int IsEmpty(Stack_t const* a_stack)
{
    if (NULL == a_stack)
    {
        return -1;
    }

    return (0 == a_stack->m_nItems);
}

int IsFull(Stack_t const* a_stack)
{
    if (NULL == a_stack)
    {
        return -1;
    }

    return (a_stack->m_nItems == a_stack->m_capacity);
}



/**********************************[ PRINT ]***********************************/

void StackPrint(Stack_t const* a_stack, PrintFunc_t a_printf)
{
    size_t i = 0;
    if ( (NULL == a_stack) || (NULL == a_printf))
    {
        return;
    }
    
    printf("\nSTACK\n");
    for (i = 0; i < a_stack->m_nItems; ++i)
    {
        a_printf(a_stack->m_stack[i]);
    }
    printf("\n");

    if (NULL != a_stack->m_minStack)
    {
        printf("\nMIN-STACK\n");
        for (i = 0; i < a_stack->m_minStack->m_nItems; ++i)
        {
            a_printf(a_stack->m_minStack->m_stack[i]);
        }
        printf("\n");
    }
}

