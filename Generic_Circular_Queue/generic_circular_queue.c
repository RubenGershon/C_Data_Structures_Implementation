/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Circular Queue Implementation File
* 						  DATE: 2020
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>      /* malloc  */
#include "generic_circular_queue.h"

#define FALSE 0
#define TRUE 1

/******************************************************************************/

struct Queue
{
	void **m_items;
	size_t m_capacity;  /* Max N of items that can fit into the queue */
	size_t m_head;
	size_t m_tail;
	size_t m_nItems;    /* N items currently present in the queue.    */
};


/***********************************[ CREATE ]*********************************/

Queue_t *QueueCreate(size_t a_capacity)
{
	Queue_t *queue = NULL;

	if (0 == a_capacity)
	{
		return (NULL);
	}

    queue = (Queue_t *)malloc(sizeof(Queue_t));
    if (NULL == queue)
    {
        return (NULL);
    }

    queue->m_items = (void **)calloc( sizeof(void *), a_capacity);
    if (NULL == queue->m_items)
    {
        free(queue);
        return (NULL);
    }

    queue->m_capacity = a_capacity;
    queue->m_head = 0;
    queue->m_tail = 0;
    queue->m_nItems = 0;

    return (queue);
}


/**********************************[ DESTROY ]*********************************/


void QueueDestroy(Queue_t **a_queue, DestroyFunc_t a_destroy)
{
	size_t i = 0;
	if ( (NULL != *a_queue) || (NULL != a_queue) )
	{
		return;
	}

	if (NULL != a_destroy)
	{
		for (i = 0; i < (*a_queue)->m_nItems; ++i)
		{
			a_destroy((*a_queue)->m_items[i]);
		}
	}

	free((*a_queue)->m_items);
	free(*a_queue);
	*a_queue = NULL;

    return;
}


/*********************************[ ENQUEUE ]**********************************/


Status_t QueueEnqueue(Queue_t *a_queue, void const *a_item)
{
    if (NULL == a_queue)
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (QueueIsFull(a_queue)) 
	{
		return (ERR_OVERFLOW);
    }
	
	a_queue->m_items[a_queue->m_tail] = (void*)a_item;
	a_queue->m_tail = ((a_queue->m_tail + 1) % a_queue->m_capacity);
	a_queue->m_nItems += 1;

    return (ERR_OK);
}


/**********************************[ DEQUEUE ]*********************************/


Status_t QueueDequeue(Queue_t *a_queue, void **a_pItem)
{
	if (NULL == a_queue)
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (QueueIsEmpty(a_queue)) 
	{
		return (ERR_UNDERFLOW);
    }
	
	if (NULL != a_pItem)
	{
		*a_pItem = a_queue->m_items[a_queue->m_head];
	}

	a_queue->m_head = ((a_queue->m_head + 1) % a_queue->m_capacity);
	a_queue->m_nItems -= 1;

    return (ERR_OK);
}



/*********************************[ UTILITIES ]********************************/


int QueueCapacity(Queue_t const *a_queue)
{
    if (NULL == a_queue)
    {
        return (-1);
    }
    
    return a_queue->m_capacity;
}


int QueueSize(Queue_t const *a_queue)
{
    if (NULL == a_queue)
    {
        return (-1);
    }

    return a_queue->m_nItems;
}

int QueueIsEmpty(Queue_t const *a_queue)
{
	if (NULL == a_queue)
    {
        return (-1);
    }

	return (0 == a_queue->m_nItems);
}

int QueueIsFull(Queue_t const *a_queue)
{
	if (NULL == a_queue)
    {
        return (-1);
    }

	return (a_queue->m_capacity == a_queue->m_nItems);
}


/**********************************[ FOREACH ]*********************************/


size_t QueueForEach(Queue_t const *a_queue, OperationFunc_t a_action, void *a_context)
{
	size_t i = 0;
    if ((NULL == a_queue) || (NULL == a_action) )
    {
        return (0);
    }

    for (i = 0; i < a_queue->m_nItems; ++i)
    {
       if (0 == a_action(a_queue->m_items[(a_queue->m_head + i)
                                        % a_queue->m_capacity], i, a_context))
       {
			++i;
           break;
       }
    }

    return (i);
}