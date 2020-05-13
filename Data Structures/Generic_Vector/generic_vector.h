/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Vector header
* 						  DATE: 22-07-2019
******************************************************************************/

/** @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand. */ 

#ifndef GENERIC_VECTOR_H_
#define GENERIC_VECTOR_H_

#include "Status.h"
#include <stddef.h>  /* size_t */

/**********************************TYPEDEFS***********************************/

typedef struct Vector Vector_t;
typedef int	(*VectorElementAction)(void *a_element, size_t a_index, void *a_context);

/*****************************************************************************/


/** @brief Dynamically create a new vector object of given capacity.  
 *  @param[in] a_initialCapacity - n of elements that can be stored initially.
 *  @param[in] a_blockSize - the vector will grow or shrink  by this size. 
 *  @return Vector * - on success / NULL on fail.
 *  @warning if a_blockSize is 0 the vector will be of fixed size. 
 *  @warning if both params are zero function will return NULL. */
Vector_t *VectorCreate(size_t a_initialCapacity, size_t a_blockSize);


/** @brief Dynamically deallocate a previously allocated vector  
 *  @param[in] a_vector - Vector to be deallocated.
 *  @params[in]a _elementDestroy : A function pointer to be used to destroy
 *  all elements in the vector or a null if no such destroy is required. */
void VectorDestroy(Vector_t **a_vector, void (*a_elementDestroy)(void *a_item));


/** @brief Add an Item to the back of the Vector.  
 *  @param[in] a_vector - Vector to append integer to.
 *  @param[in] a_item - Item to add.
 *  @retval ERR_NOT_INITIALIZED if pointer is NULL.
 *  @retval ERR_REALLOCATION_FAILED if realloc failed.
 *  @retval ERR_OVERFLOW if _blockSize = 0. 
 *  @retval ERR_OK on success. */
Status_t VectorPushBack(Vector_t *a_vector, void *a_item);


/** @brief Delete an Element from the back of the Vector.  
 *  @param[in] a_vector - Vector to delete integer from.
 *  @param[out] a_pValue - ** that will receive deleted item value. Can be NULL.
 *  @retval ERR_NOT_INITIALIZED if pointer is NULL. 
 *  @retval VERR_OK on success. 
 *  @retval ERR_UNDERFLOW if vector is empty. */
Status_t VectorPopBack(Vector_t  *a_vector, void **a_pValue);


/** @brief Get value of item at specific index from the the Vector 
 *  @param[in] a_vector - Vector to use.
 *  @param[in] a_index - index of item to get value from.
 *  @param[out] a_pValue - pointer to variable that will receive the item value.
 *  @retval ERR_NOT_INITIALIZED if one of the pointer is NULL.
 *  @retval ERR_WRONG_INDEX if Bad Index. 
 *  @retval VECTOR_SUCCESS on success. */
Status_t VectorGet(Vector_t const* a_vector, size_t a_index, void **a_pValue);


/** @brief Set an item at specific index to a new value.
 *  @param[in] a_vector - Vector to use.
 *  @param[in] a_index - index of an existing item.
 *  @param[in] a_value - new value to set.
 *  @retval ERR_NOT_INITIALIZED if one of the pointer is NULL.
 *  @retval ERR_WRONG_INDEX if Bad Index. 
 *  @retval VECTOR_SUCCESS on success.*/
Status_t VectorSet(Vector_t *a_vector, size_t a_index, void *a_value);


/** @brief Get the number of actual items currently in the vector.
 *  @param[in] a_vector - Vector to use.
 *  @return  number of items on success 0 if vector is empty or invalid. */
size_t VectorGetSize(Vector_t const *a_vector);


/** @brief Get the current capacity of the  vector.
 *  @param[in] a_vector - Vector to use.
 *  @return  capacity of vector	. */
size_t VectorGetCapacity(Vector_t const *a_vector);


/** @brief Iterate over all elements in the vector.
 *  @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 *  @param[in] a_vector - vector to iterate over.
 *  @param[in] a_action - User provided function pointer to be invoked for each element
 *  @param[in] a_context - User provided context, will be sent to _action
 *  @returns number of times the user functions was invoked
 * equivallent to:
 *      for (i = 1; i < Vector_Size(v); ++i)
		{
 *             Vector_Get(v, i, &elem);
 *             if(_action(elem, i, _context) == 0)
 *				break;	
 *      }
 *		return i;
 */                                         
size_t VectorForEach(Vector_t const *a_vector, VectorElementAction a_action, void *a_context);



#endif          /* GenericVector s*/




