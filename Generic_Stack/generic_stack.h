/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Stack header
* 						  DATE: 2020
******************************************************************************/

#ifndef GENERIC_STACK_H_
#define GENERIC_STACK_H_

#include "Status.h"
#include <stddef.h>  /* size_t */

/*********************************[ TYPEDEFS ]*********************************/

typedef struct Stack Stack_t;
typedef int (*DestroyFunc_t)(void const* a_item);
typedef void (*PrintFunc_t)(void const* a_item);
typedef int (*Compare_t)(void const* a_item1, void const* a_item2);


/************************************[ API ]***********************************/


/** @brief Dynamically create a new stack object of given capacity.
 *  @param[in] a_capacity - n of elements that can be stored initially.
 *  @param[in] a_cmp - Pointer to a compare function. a_cmp should return 
 *  1(TRUE) if a_item1 => a_item2 or 0(FALSE) else. 
 *  @return Vector * - on success / NULL on fail.
 *  @warning if a_capacity is 0 StackCreate return NULL. 
 *  @warning if a_cmp is NULL, the stack will not implement StackMin API. */
Stack_t* StackCreate(size_t a_capacity, Compare_t a_cmp);


/** @brief Dynamically deallocate a previously allocated stack  
 *  @param[in] a_stack - Stack to be deallocated.
 *  @param[in]a _destroy : A function pointer to be used to destroy
 *  all elements in the stack or a null if no such destroy is required. */
void StackDestroy(Stack_t* a_stack, DestroyFunc_t a_destroy);


/** @brief Push an Item into the stack.
 *  @brief Time Complexity : O(1).   
 *  @param[in] a_stack - Stack to push item to.
 *  @param[in] a_item - Item to add.
 *  @retval ERR_NOT_INITIALIZED if a_stack is NULL.
 *  @retval ERR_OVERFLOW if stack is full. 
 *  @retval ERR_OK on success. */
Status_t StackPush(Stack_t* a_stack, void const* a_item);


/** @brief Pop an Element from the back of the Stack.
 *  @brief Time Complexity : O(1).     
 *  @param[in] a_stack - Stack to pop item from.
 *  @param[out] a_item - ** that will receive deleted item.Can be NULL.
 *  @retval ERR_NOT_INITIALIZED if pointer is NULL. 
 *  @retval ERR_UNDERFLOW if Stack is empty.
 *  @retval ERR_OK on success. */
Status_t StackPop(Stack_t* a_stack, void **a_item);


/** @brief Retreive the last pushed item of the Stack.
 *  @brief Time Complexity : O(1).  
 *  @param[in] a_stack - Stack to top the item from.
 *  @param[out] a_item - ** that will receive the toped item.
 *  @retval ERR_NOT_INITIALIZED if a_stack or a_item are NULL. 
 *  @retval ERR_UNDERFLOW if Stack is empty.
 *  @retval ERR_OK on success. */
Status_t StackTop(Stack_t const* a_stack, void **a_item);


/** @brief Retreive the Minimum element (by its value) of the Stack.
 *  @brief Time Complexity : O(1), Space Complexity: O(n).  
 *  @param[in] a_stack.
 *  @param[out] a_item - ** that will receive the item.
 *  @retval ERR_NOT_INITIALIZED if a_stack or a_item are NULL or see @warning. 
 *  @retval ERR_UNDERFLOW if Stack is empty.
 *  @retval ERR_OK on success.
 *  @warning if a_cmp was not provided at StackCreate, 
 *  StackMin retval is NULL.*/ 
Status_t StackMin(Stack_t const* a_stack, void **a_item);


/** @brief Return the number of elements presents in the Stack.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_stack - Stack.
 *  @retval -1 if a_stack is NULL. 
 *  @retval n elements on Success. */
int StackSize(Stack_t const* a_stack);


/** @brief Check if the Stack is empty or not.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_stack - Stack.
 *  @retval -1 if a_stack is NULL. 
 *  @retval 1 if Stack is empty.
 *  @retval 0 if Stack not empty. */
int IsEmpty(Stack_t const* a_stack);


/** @brief Check if the Stack is full or not.
 *  @brief Time Complexity : O(1).    
 *  @param[in] a_stack - Stack.
 *  @retval -1 if a_stack is NULL. 
 *  @retval 1 if Stack is full.
 *  @retval 0 if Stack not full. */
int IsFull(Stack_t const* a_stack);


/** @brief Print function.
 *  @param[in] a_stack - Stack to print.
 *  @param[in] a_print - * to a print function. Cannot be NULL.
 *  @retval Nothing happen if one of the pointers is NULL. 
 *  @retval Print stack on Success, also print Min Stack if there is one.*/
void StackPrint(Stack_t const* a_stack, PrintFunc_t a_printf);


#endif
