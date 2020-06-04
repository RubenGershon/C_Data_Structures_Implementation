/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: generic iterator header
* 						  DATE: 2020
*******************************************************************************/

#ifndef GENERIC_ITERATOR_H_
#define GENERIC_ITERATOR_H_

typedef struct Itrt Iterator_t;

/** @brief Get iterator to the container beginning.
 *  @brief Time complexity: O(1).    
 *  @param[in] a_container - container to return begin iterator from.
 *  @return An iterator pointing at the container's beginning.
 *  @warning if the container is empty, iterator point at the end.*/
Iterator_t *IteratorBegin(void const* a_container);


/** @brief Get iterator to the container end.
 *  @brief Time complexity: best O(1), worst O(n);    
 *  @param[in] a_container - container to return end iterator from.
 *  @return an iterator pointing at the void's end.
 *  @warning .*/
/*Iterator_t *IteratorEnd(const void *a_container);*/


/** @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro.*/
/*int IteratorEquals(Iterator_t const *_a, Iterator_t const *_b);*/


/** @brief Get iterator to the next element from a given iterator.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to go next from.
 *  @return an iterator pointing at the next item in the container.
 *  @warning if *a_itr is end iterator it will be returned as-is.*/
/*Iterator_t *IteratorNext(Iterator_t *a_itr);*/


/** @brief Get iterator to the prev element from a given iterator.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to go prev from.
 *  @return an iterator pointing at the prev item in the container.
 *  @warning if *a_itr is begin iterator it will be returned as-is.*/
/*Iterator_t *IteratorPrev(Iterator_t *a_itr);*/


/** @brief Get data from the container item the iterator is pointing to.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to get data from.
 *  @return The data or NULL if pointing to the end.*/
void *IteratorGet(Iterator_t const *a_itr, GetFunct_t a_fct);



/** @brief Set data from the container item the iterator is pointing to.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to set data from.
 *  @param[in] *a_element - ptr to element to set. Cannot be NULL.
 *  @return The data or NULL if pointing to the end.*/
/*void IteratorSet(Iterator_t *a_itr, void *a_element);*/


/** @brief Inserts a new node before node the iterator is pointing at
 *  @param _itr : An element, Cannot be NULL.
 * @return an iterator pointing at the element inserted or NULL on error.
Iterator_t* Iterator_t*IteratorInsertBefore(Iterator_t* _itr, void *_element);

** @brief Removes the node the iterator is pointing at.
 * @params _itr : A void iterator, return if Tail.
 * @return the removed data.
void *Iterator_t*IteratorRemove(Iterator_t* _itr);*/

#endif
