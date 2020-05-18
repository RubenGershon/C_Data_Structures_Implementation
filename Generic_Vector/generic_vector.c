/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: GenericVector implementation file
* 						  DATE: 22-07-2019
*******************************************************************************/

#include <stdio.h> 		/* printf            */
#include <stdlib.h> 	/* malloc realloc    */
#include "generic_vector.h"

/*********************************[ MACROS ]***********************************/

#define MAGIC_NUM 0xBEEFBEEF

/*********************************[ STRUCTS ]**********************************/

struct Vector
{
	size_t m_magic_num;
    void **m_items;
    size_t  m_original_capacity;   /* original num of items that can fit in the vector)*/
    size_t  m_curr_capacity;  /* curr max num of items that can fit in the vector)*/
    size_t  m_numb_of_items;  /* actual number of items                      */
    size_t  m_block_size;      /* the chunk size to be allocated when no space*/
};

/*****************************[ STATICS FUNCTIONS ]****************************/

static Status_t VectorResize(Vector_t *_vector);


/******************************[ CREATE - DESTROY ]****************************/

Vector_t* VectorCreate(size_t a_initialCapacity, size_t a_blockSize)
{
	Vector_t *vector = NULL;

	if ( (0 == a_initialCapacity) && (0 == a_blockSize) )
	{
		return (NULL);
	}

    vector = (Vector_t *)malloc(sizeof(Vector_t));
    if(NULL == vector)
    {
        return (NULL);
    }

    vector->m_items = (void **)calloc(sizeof(void *) , (a_initialCapacity));
    if (NULL == vector->m_items)
    {
        free(vector);
        return (NULL);
    }

	vector->m_magic_num = MAGIC_NUM;
    vector->m_original_capacity = a_initialCapacity;
    vector->m_curr_capacity = a_initialCapacity;
    vector->m_numb_of_items = 0;
    vector->m_block_size = a_blockSize;

    return (vector);
}

void VectorDestroy(Vector_t **a_vector, void (*a_elementDestroy)(void *a_item))
{
	size_t i = 0;
	if ((!*a_vector) || (!a_vector) || (MAGIC_NUM != (*a_vector)->m_magic_num))
	{
		return;
	}

	if (NULL != a_elementDestroy)
	{
		for (i = 0; i < (*a_vector)->m_numb_of_items; ++i)
		{
			a_elementDestroy((*a_vector)->m_items[i]);
		}
	}
	
	(*a_vector)->m_magic_num = 0xDEADBEEF;
	free((*a_vector)->m_items);
	free(*a_vector);
	*a_vector = NULL;
}

/**********************************[ PUSH ]************************************/


Status_t VectorPushBack(Vector_t *a_vector, void *a_item)
{
	Status_t return_status = ERR_OK;
    if ((NULL == a_vector) || (NULL == a_item))
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (a_vector->m_curr_capacity == a_vector->m_numb_of_items) 
	{
		if (0 != a_vector->m_block_size)
		{
    		return_status = VectorResize(a_vector);
		}
		else
		{
			return (ERR_OVERFLOW);
		}
    }

	if (ERR_OK == return_status)
	{
		a_vector->m_items[a_vector->m_numb_of_items] = a_item;
		a_vector->m_numb_of_items += 1;
	}
       
    return (return_status);
}

/************************************[ POP ]***********************************/


Status_t VectorPopBack(Vector_t  *a_vector, void **a_pValue)
{
	 if (NULL == a_vector)
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (0 == a_vector->m_numb_of_items)
    {
        return (ERR_UNDERFLOW);
    }

	if (NULL != a_pValue)
	{
		*a_pValue = a_vector->m_items[a_vector->m_numb_of_items - 1];
	}

	a_vector->m_numb_of_items -= 1;

    return (ERR_OK);
}

/***********************************[ GET ]************************************/


Status_t VectorGet(Vector_t const *a_vector, size_t a_index, void **a_pValue)
{
	 if ( (NULL == a_vector) || (NULL == a_pValue) )
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (a_index >= a_vector->m_numb_of_items)
    {
        return (ERR_WRONG_INDEX);
    }

    *a_pValue = a_vector->m_items[a_index];

    return (ERR_OK);
}


/************************************[ SET ]***********************************/


Status_t VectorSet(Vector_t *a_vector, size_t a_index, void *a_value)
{
    if ( (NULL == a_vector) || (NULL == a_value) )
    {
        return (ERR_NOT_INITIALIZED);
    }

    if (a_index >= a_vector->m_numb_of_items)
    {
        return (ERR_WRONG_INDEX);
    }

    a_vector->m_items[a_index] = a_value;

    return (ERR_OK);
}

/*****************************[ GET SIZE / GET CAPACITY ]**********************/

size_t VectorGetSize(Vector_t const *a_vector)
{
	if (NULL == a_vector)
    {
        return (0);
    }

	return (a_vector->m_numb_of_items);
}


size_t VectorGetCapacity(Vector_t const *a_vector)
{
	if (NULL == a_vector)
    {
        return (0);
    }

	return (a_vector->m_curr_capacity);
}

/*********************************[ FOR EACH ]*********************************/

size_t VectorForEach(Vector_t const *a_vector, VectorElementAction a_action, void *a_context)
{
    size_t i = 0;
    if ( (NULL == a_vector) || (NULL == a_action) )
    {
        return (0);
    }

    for (i = 0; i < a_vector->m_numb_of_items; ++i)
    {
       if (0 == a_action(a_vector->m_items[i], i, a_context))
       {
			++i;
           break;
       }
    }

    return (i);
}

/*****************************[ STATICS FUNCTIONS ]****************************/


static Status_t VectorResize(Vector_t *a_vector)
{
    void **temporary = (void **)realloc(a_vector->m_items,
                	(sizeof(void *) * (a_vector->m_curr_capacity + a_vector->m_block_size)));

    if (NULL == temporary)
    {
        return (ERR_REALLOCATION_FAILED);
    }

    a_vector->m_items = temporary;
    a_vector->m_curr_capacity += a_vector->m_block_size;

    return (ERR_OK);
}

