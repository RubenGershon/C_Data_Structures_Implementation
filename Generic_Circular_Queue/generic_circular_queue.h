/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Circular Queue header
* 						  DATE: 2020
*******************************************************************************/

#ifndef GENERIC_CIRCULAR_QUEUE_H_
#define GENERIC_CIRCULAR_QUEUE_H_

#include "Status.h"
#include <stddef.h>  /* size_t */

/*********************************[ TYPEDEFS ]*********************************/

typedef struct Queue Queue_t;
typedef int	(*OperationFunc_t)(void const *a_element, size_t a_idx, void *a_context);
typedef void (*DestroyFunc_t)(void *a_item);


/************************************[ API ]***********************************/


/** @brief Dynamically create a Queue of specific size according to user input.
 *  @brief Average time complexity : O(n).
 *  @param[in] a_capacity - n of elements that can be stored initially.
 *  @return Queue_t * - on success / NULL on fail.
 *  @warning if a_capacity is 0 StackCreate return NULL. */
Queue_t *QueueCreate(size_t a_capacity);


/** @brief Dynamically deallocate a previously allocated queue.
 *  @brief  Best time complexity : O(1). Worst time complexity : O(n).
 *  @param[in] a_queue - pointer to pointer the queue to destroy..
 *  @param[in]a _destroy : A function pointer to be used to destroy
 *  all elements in the stack or a null if no such destroy is required. */
void QueueDestroy(Queue_t **a_queue, DestroyFunc_t a_destroy);


/** @brief Add one element to the queue.
 *  @brief Time Complexity : O(1).   
 *  @param[in] a_queue : pointer to the queue. Cannot be NULL.
 *  @param[in] a_item - Item to add.
 *  @retval ERR_NOT_INITIALIZED if a_queue is NULL.
 *  @retval ERR_OVERFLOW if queue is full. 
 *  @retval ERR_OK on success. */
Status_t QueueEnqueue(Queue_t *a_queue, void const *a_item);


/** @brief Remove one element from the queue.
 *  @brief Time Complexity : O(1).   
 *  @param[in] a_queue : pointer to the queue. Cannot be NULL.
 *  @param[in] a_item - return the removed element. Can be NULL..
 *  @retval ERR_NOT_INITIALIZED if a_queue is NULL.
 *  @retval ERR_UNDERFLOW if queue is empty. 
 *  @retval ERR_OK on success. */
Status_t QueueDequeue(Queue_t *a_queue, void **a_pItem);


/** @brief Return the capacity of the Queue.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_queue - Queue.
 *  @retval -1 if a_Queue is NULL. 
 *  @retval capacity on Success. */
int QueueCapacity(Queue_t const *a_queue);


/** @brief Return the number of elements presents in the Queue.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_queue - Queue.
 *  @retval -1 if a_Queue is NULL. 
 *  @retval n elements on Success. */
int QueueSize(Queue_t const *a_queue);


/** @brief Check if the queue is empty.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_queue - pointer to the queue.
 *  @retval -1 if a_queue is NULL. 
 *  @retval 1 if queue is empty.
 *  @retval 0 if queue not empty. */
int QueueIsEmpty(Queue_t const *a_queue);


/** @brief Check if the queue is full.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_queue - pointer to the queue.
 *  @retval -1 if a_queue is NULL. 
 *  @retval 1 if queue is full.
 *  @retval 0 if queue not full. */
int QueueIsFull(Queue_t const *a_queue);


/** @brief Iterate over all elements in the queue.
 *  @details The user-provided a_action function is called for each element
 *          if a_action return a zero for an element the iteration will stop.  
 * @param[in] a_queue - queue to iterate over.
 * @param[in] a_action - User-provided function* to be invoked for each element.
 * @param[in] a_context - User-provided context, will be sent to a_action
 * @returns number of times the user function was invoked. */
size_t QueueForEach(Queue_t const *a_queue, OperationFunc_t a_action, void *a_context);


#endif
