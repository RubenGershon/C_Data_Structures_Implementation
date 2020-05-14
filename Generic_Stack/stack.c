
#include <stdlib.h>      /* malloc  */
#include <assert.h>     /* assert   */
#include "stack.h"

/******************************************************************************/

struct Stack
{
    const void **m_stack;
    Stack_t* m_minStack;
    Compare_t m_cmp;
    size_t m_capacity;
    size_t m_nItems;
    int m_isFirstVisit;
};


/***********************************[ CREATE ]*********************************/

Stack_t* StackCreate(size_t a_capacity, Compare_t a_cmp)
{
    Stack_t* myStack = NULL;


    if ( (0 == a_capacity) || (NULL == a_cmp))
    {
        return NULL;
    }

    myStack = (Stack_t*)malloc(sizeof(Stack_t)*1);
    if (NULL == myStack)
    {
        return NULL;
    }

    myStack->m_minStack = (Stack_t*)malloc(sizeof(Stack_t)*1);

    myStack->m_stack = (const void**)calloc(sizeof(void*), a_capacity);
    if (NULL == myStack->m_stack)
    {
        free(myStack);
        return NULL;
    }

    myStack->m_minStack->m_stack = (const void**)calloc(sizeof(void*), a_capacity);
    if (NULL == myStack->m_minStack->m_stack)
    {
        free(myStack->m_stack);
        free(myStack->m_minStack->m_stack);
        free(myStack);
        return NULL;
    }

    myStack->m_cmp = a_cmp;

    myStack->m_capacity = a_capacity;

    myStack->m_nItems = 0;
    myStack->m_minStack->m_nItems = 0;

    myStack->m_isFirstVisit = 1;

    return myStack;
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
    free(a_stack->m_minStack->m_stack);
    free(a_stack);
}    

/***********************************[ PUSH ]***********************************/

Result_t StackPush(Stack_t* a_stack, const void* a_item)
{
    if (NULL == a_stack)
    {
        return UNINITIALIZED;
    }

    if (a_stack->m_nItems == a_stack->m_capacity)
    {
        return OVERFLOW;
    }

    a_stack->m_stack[a_stack->m_nItems] = a_item;
    a_stack->m_nItems++;

    if (0 == a_stack->m_isFirstVisit)
    {
        if (1 == a_stack->m_cmp(StackTop(a_stack->m_minStack), a_item))
        {
            a_stack->m_minStack->m_stack[a_stack->m_minStack->m_nItems] = a_item;
            a_stack->m_minStack->m_nItems++;
        }
    }
    else
    {
        a_stack->m_minStack->m_stack[a_stack->m_minStack->m_nItems] = a_item;
        a_stack->m_isFirstVisit = 0;
        a_stack->m_minStack->m_nItems++;
    }

    return OK;
}

/************************************[ POP ]***********************************/

Result_t StackPop(Stack_t* a_stack, const void* a_item)
{
    if (NULL == a_stack)
    {
        return UNINITIALIZED;
    }

    if (a_stack->m_nItems == 0)
    {
        return UNDERFLOW;
    }

    if (StackTop(a_stack->m_minStack) == StackTop(a_stack))
    {
        a_stack->m_minStack->m_nItems--;
    }
    
    if (NULL != a_item)
    {
        a_item = a_stack->m_stack[a_stack->m_nItems - 1];
    }    
    a_stack->m_nItems--;


    return OK;
}

/************************************[ POP ]***********************************/

const void* StackTop(Stack_t* a_stack)
{
    if (NULL == a_stack || a_stack->m_nItems == 0)
    {
        return NULL;
    }

    return a_stack->m_stack[a_stack->m_nItems - 1]; 
}


/************************************[ MIN ]***********************************/

const void* StackMin(Stack_t* a_stack)
{
    if (NULL == a_stack || a_stack->m_minStack->m_nItems == 0)
    {
        return NULL;
    }

    return StackTop(a_stack->m_minStack); 
}



/**********************************[ PRINT ]***********************************/

void Print(Stack_t* a_stack)
{
    size_t i = 0;
    printf("\nSTACK\n");
    for (i = 0; i < a_stack->m_nItems; ++i)
    {
        printf("%d,", *(int*)a_stack->m_stack[i]);
    }
    printf("\n");
}

void PrintMin(Stack_t* a_stack)
{
    size_t i = 0;
    printf("\nMIN STACK\n");
    for (i = 0; i < a_stack->m_minStack->m_nItems; ++i)
    {
        printf("%d,", *(int*)a_stack->m_minStack->m_stack[i]);
    }
    printf("\n");
}



/******************************[ INSERT BEFORE ]*******************************/



/*******************************[ REMOVE AFTER ]*******************************/




/*********************************[ COUNT ]************************************/




