/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Single Linked List header
* 						  DATE: 2020
*******************************************************************************/

#ifndef GENERIC_SINGLE_LINKED_LIST_H_
#define GENERIC_SINGLE_LINKED_LIST_H_

#include "Status.h"
#include <stddef.h>  /* size_t */

#define TRUE 1
#define FALSE 0

/*********************************[ TYPEDEFS ]*********************************/

typedef struct Itrt Iterator_t;
typedef struct Sll Sll_t;
typedef int (*actionFunc_t)(void* a_data, void* a_param);
typedef int (*CmpFunc_t)(void const *a_compareTo, void const *a_toInsert);
typedef int (*FindFunc_t)(void const *a_compareTo, void const *a_toFind);
typedef void (*DestroyFunc_t)(void* a_toDestroy);

/************************************[ API ]***********************************/


/** @brief Dynamically create an empty Generic Single Linked List.
 * 	@param[in] *a_compare - a compare function allowing to insert elements in 
 * 	a specific order. Can be NULL but SORTED option will not be allowed.  
 *  @return Pointer to the new list on success / NULL on fail.*/
Sll_t *SLLCreate(CmpFunc_t a_compare);


/** @brief Destroy a Generic Single Linked List.
 * 	@param[in] *a_sll - list to destroy.
 *  @param[in] *a_destroyer - destroy function. Can be NULL.*/
void SLLDestroy(Sll_t *a_sll, DestroyFunc_t a_destroyer);


/** @brief Insert a new element in the list. The New element can be inserted:
 *      - By default at the end of the list. Time complexity: O(1)
 *      - Before or after the provided iterator. Time complexity: O(1)
 *      - Sorted In order. Time complexity: Best O(1), Worst O(n).
 *  @param[in] *a_sll - list to insert to. Can't be NULL.
 *  @param[in] *a_data - ptr to data to insert. Can't be NULL.
 *  @param[in] *a_itr - iterator pointing to a specific node. Can be NULL.
 *  @param[in] a_op - Operation to exe: EMPTY/BEFORE/AFTER/SORTED.
 *  @return An iterator pointing at the inserted element. NULL if fail.
 *  @brief If a_itr is NULL and a_op input is EMPTY, SLLInsert will 
 *  insert by default after the last element of the list.
 *  @brief If a_itr is NULL and a_op choice is SORTED, SLLInsert will insert 
 * 	in order via the use of the compare function provided at SLLCreate.
 *  @brief If a_itr is provided, SLLInsert will insert BEFORE or AFTER the  
 * 	node pointed by a_itr depending on the a_op option choice.
 * 	@warning If a_itr is provided but a_op is != BEFORE/AFTER, return NULL.
 *  @warning if a_itr is NULL and SORTED option is selected but no CmpFunc_t 
 *  was provided at SLLcreate, return NULL.
 * 	@warning if a_itr is provided AND SORTED option is selected,
 * 	or if a_itr is NULL AND BEFORE/AFTER option is selected, return NULL.*/
Iterator_t *SLLInsert(Sll_t *a_sll, void const* a_data, Iterator_t *a_itr, Op_t a_op);


/** @brief Remove an element from the list at or after the provided iterator.
 *  Time complexity: O(1)
 *  @param[in] *a_sll - list to remove from. Can't be NULL.
 *  @param[in] **a_data - ** to removed data. Can be NULL.
 *  @param[in] *a_itr - iterator. Can't be NULL.
 *  @param[in] a_op - Operation to execute: CURRENT/AFTER.
 *  @return SUCCESS on successful removal, ERR_BAD_ARGS if bad inputs, ERR_LAST
 *  if last element or only 1 lement on the list.
 *  @brief SLLRemove will remove BEFORE or AFTER the  
 * 	node pointed by a_itr depending on the a_op option choice.
 * 	@warning If a_op is != CURRENT/AFTER, return ERR_BAD_ARGS.
 * 	@warning If List is empty, a_itr will be NULL so it will not work.
 * 	@warning If only one element is left in the List or if a_itr points to the 
 * last element: not possible to remove it. return ERR_LAST.*/
Status_t SLLRemove(Sll_t *a_sll, void **a_data, Iterator_t *a_itr, Op_t a_op);


/** @brief Runs over the list and implement an action function provided by the 
 *  user until it either arrives to the end of the list, or action function 
 *  returns a non-zero value.
 *  @param[in] *a_sll - list to iterate on. Can't be NULL.
 *  @param[in] *a_action - action function that will act on each node.
 *  Can't be NULL.
 *  @param[in] *a_param - Parameter that will be passed to action function.
 *  Can be NULL.
 *  @param[in] *a_itr -If a non-zero value is returned from acton function,
 *  a_itr point to the element where the action function failed. Can be NULL.
 *  @return Action Function returns 0 for success and continuing to following
 *  item, return any other value to trigger stop-running.
 *  @return SLLForEach return ERR_BAD_ARGS if bad input, return ERR_SUCCESS if 
 *  iteration go over the whole list, return ERR_STOP if stopped. */
Status_t SLLForEach(Sll_t *a_sll, actionFunc_t a_action, void *a_param, Iterator_t **a_itr);


/** @brief Searches the List to find a specified element using a matching
 *  function provided by user. Best: O(1), Worst O(n).
 *  @param[in] *a_sll - list to iterate on. Can't be NULL.
 *  @param[in] *a_toFind - * to the element to be found in the List.
 *  Can't be NULL.
 *  @param[in] *a_finder - * to FindFunc_t function. Cannot be NULL.
 *  @return Returns the pointer to the element, if found.
 *  Returns NULL if element not found.*/
Iterator_t *SLLFind(Sll_t const *a_sll, void const *a_toFind, FindFunc_t a_finder);


/** @brief Search for the middle of the list. Best: O(1), Worst O(n).
 *  @param[in] *a_sll - list to check on. Can't be NULL.
 *  @return Iterator to the middle, NULL if NULL input or empty list.*/
Iterator_t *SLLFindMiddle(Sll_t const *a_sll);


/** @brief Tell if the list is Empty or not.Time complexity: O(1)
 *  @param[in] *a_sll - list to check on. Can't be NULL.
 *  @return TRUE if empty, FALSE if not, -1 if NULL input.*/
int SLLIsEmpty(Sll_t const *a_sll);


/** @brief Count the number of elements in the list.Time complexity: O(n)
 *  @param[in] *a_sll - list to count on. Can't be NULL.
 *  @return count on success, -1 if NULL input.*/
int SLLCount(Sll_t const *a_sll);


/** @brief Check if there is a loop. Time complexity: Best O(1), Worst O(n).
 *  @param[in] *a_sll - list to count on. Can't be NULL.
 *  @return TRUE if loop, FALSE if not, -1 if NULL input.*/
int SLLHasLoop(Sll_t const *a_sll);


/** @brief If there is one, find the intersection and return iterator to where 
 *  the intersection occurs. Average O(n).
 *  @param[in] *a_sll1 - list1. Can't be NULL.
 *  @param[in] *a_sll2 - list2. Can't be NULL.
 *  @return Iterator to intersection if there is, NULL if no intersection.*/
Iterator_t *SLLFindIntersection(Sll_t const *a_sll1, Sll_t const *a_sll2);

Iterator_t *SLLFlip(Sll_t *a_sll);

Iterator_t *SLLFlipRec(Sll_t *a_sll);

/*node_t* SLLSwapNodes(node_t *head, void *data1, void *data2, cmpFunc_t compare);*/


/*********************************[ ITERATORS ]********************************/

/** @brief Get iterator to the list beginning.
 *  @brief Time complexity: O(1).    
 *  @param[in] a_sll - list to return begin iterator from.
 *  @return An iterator pointing at the list beginning.
 *  @warning if the container is empty, iterator is NULL.*/
Iterator_t *IteratorBegin(Sll_t const *a_sll);


/** @brief Get iterator to the list end.
 *  @brief Time complexity: O(1).    
 *  @param[in] a_sll - list to return end iterator from.
 *  @return An iterator pointing at the list end.
 *  @warning if the container is empty, iterator is NULL.*/
Iterator_t *IteratorEnd(Sll_t const *a_sll);


/** @brief Get iterator to the next element from a given iterator.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to go next from.
 *  @return an iterator pointing at the next item in the list.
 *  @warning if *a_itr is end iterator it will return NULL.*/
Iterator_t *IteratorNext(Iterator_t *a_itr);


/** @brief Get data from the item the iterator is pointing to.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to get data from.
 *  @return The data or NULL if a_itr is NULL.*/
void *IteratorGet(Iterator_t const *a_itr);


/** @brief Set data from the item the iterator is pointing to.
 *  @brief Time complexity: O(1);    
 *  @param[in] *a_itr - ptr to iterator to Set data.
 *  @param[in] *a_element - ptr to the element to set.
 *  @return void pointer to previous data on success, NULL on fail.*/
void *IteratorSet(Iterator_t *a_itr, void const *a_element);


#endif          /* Generic Single Linked List */




