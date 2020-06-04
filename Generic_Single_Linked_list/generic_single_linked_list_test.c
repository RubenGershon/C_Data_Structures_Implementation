/*******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Single Linked List testing
* 						  DATE: 2020
*******************************************************************************/

#include <stdio.h> 		/* printf               */
#include <stdlib.h> 	/* malloc realloc	    */
#include "generic_single_linked_list.h"

#define RED           "\x1b[31m"
#define GREEN        "\x1B[32m"
#define RESET        "\x1b[0m"
#define PSUCCESS printf(GREEN"SUCCESS\n"RESET)
#define PFAIL printf(RED"FAIL\n"RESET)
#define SUCCESS 1
#define FAIL 0

/**********************************[ STRUCT ]**********************************/

typedef struct Person
{
	char m_name[25];
	float m_age;
}Person;

/*******************************[ TESTS FUNCTIONS ]****************************/

static int TestCreateWithCompare();
static int TestCreateNoCompare();
static int TestInsertNullList();
static int TestInsertNullData();
static int TestInsertByDefault();
static int TestInsertByOrderNoCmp();
static int TestInsertSorted1();
static int TestInsertWrongOp1();
static int TestInsertWrongOp2();
static int TestInsertWrongOp3();
static int TestInsertBefore();
static int TestInsertAfter();
static int TestRemoveWrongArgs1();
static int TestRemoveWrongArgs2();
static int TestRemoveWrongArgs3();
static int TestRemoveWrongArgs4();
static int TestRemoveOneElmt1();
static int TestRemoveOneElmt2();
static int TestRemoveCurrent();
static int TestRemoveAfter();






/*****************************[ HELPERS FUNCTIONS ]****************************/

int CompareInts(void const *a_compareTo, void const *a_toInsert);
static void PrintStatus(int arg, char *str);
/*static int VectorPrintInts(void *_element, size_t _index, void *_context);
static int VectorPrintStruct(void *_element, size_t _index, void *_context);*/

/***********************************[ MAIN ]***********************************/

int main(void)
{
    printf("\n");
	PrintStatus(TestCreateWithCompare(), "Create: With Compare.");
	PrintStatus(TestCreateNoCompare(), "Create: No Compare.");
	printf("\n");
	PrintStatus(TestInsertNullList(), "Insert: NULL list.");
	PrintStatus(TestInsertNullData(), "Insert: NULL Data.");
	PrintStatus(TestInsertByDefault(), "Insert: By Default, insert at the end.");
	PrintStatus(TestInsertByOrderNoCmp(), "Insert: By order with no compare fct.");
	PrintStatus(TestInsertSorted1(), "Insert: By order.");
	PrintStatus(TestInsertWrongOp1(), "Insert: wrong input operation (op).");
	PrintStatus(TestInsertWrongOp2(), "Insert: wrong input operation (op).");
	PrintStatus(TestInsertWrongOp3(), "Insert: wrong input operation (op).");
	PrintStatus(TestInsertBefore(), "Insert: Before.");
	PrintStatus(TestInsertAfter(), "Insert: After.");
	printf("\n");
	PrintStatus(TestRemoveWrongArgs1(), "Remove: wrong input.");
	PrintStatus(TestRemoveWrongArgs2(), "Remove: wrong input.");
	PrintStatus(TestRemoveWrongArgs3(), "Remove: wrong input.");
	PrintStatus(TestRemoveWrongArgs4(), "Remove: wrong input.");
	PrintStatus(TestRemoveOneElmt1(), "Remove Current: 1 element in the list.");
	PrintStatus(TestRemoveOneElmt2(), "Remove After: 1 element in the list.");
	PrintStatus(TestRemoveCurrent(), "Remove Current: Normal use.");
	PrintStatus(TestRemoveAfter(), "Remove After: Normal use.");



    return (0);
}

/*******************************[ TESTS CREATE ]*******************************/


static int TestCreateWithCompare()
{
	Sll_t *newList = SLLCreate(CompareInts);
	if (NULL != newList)
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}


static int TestCreateNoCompare()
{
	Sll_t *newList = SLLCreate(NULL);
	if (NULL != newList)
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}


/********************************[ TESTS INSERT ]******************************/


static int TestInsertNullList()
{
	int n = 1;
	if (NULL == SLLInsert(NULL, (void*)&n, NULL, EMPTY))
	{
		return SUCCESS;
	}
	return FAIL;
}


static int TestInsertNullData()
{
	Sll_t *newList = SLLCreate(NULL);

	if (NULL == SLLInsert(newList, NULL, NULL, EMPTY))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}


static int TestInsertByDefault()
{
	Sll_t *newList = SLLCreate(NULL);
	Iterator_t *it = NULL;
	int n1 = 1;
	int n2 = 2;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	SLLInsert(newList, (void*)&n2, NULL, EMPTY);
	it = IteratorBegin(newList);

	if ( (NULL != it) && (1 == *((int*)IteratorGet(it))) )
	{
		if ( (NULL != it) && (2 == *((int*)IteratorGet(IteratorNext(it)))) )
		{
			SLLDestroy(newList, NULL);
			return SUCCESS;
		}	
	}
	return FAIL;
}


static int TestInsertByOrderNoCmp()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 11;
	
	if ( NULL == SLLInsert(newList, (void*)&n1, NULL, SORTED) )
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;		
	}
	return FAIL;
}

static int TestInsertSorted1()
{
	Sll_t *newList = SLLCreate(CompareInts);
	Iterator_t *it = NULL;
	int n1 = 11;
	int n2 = 1;
	int n3 = 4;

	SLLInsert(newList, (void*)&n1, NULL, SORTED);
	SLLInsert(newList, (void*)&n2, NULL, SORTED);
	SLLInsert(newList, (void*)&n3, NULL, SORTED);

	it = IteratorBegin(newList);
	if ( 1 == *((int*)IteratorGet(it)) ) 
	{
		it = IteratorNext(it);
		if (4 == *((int*)IteratorGet(it)) )
		{
			it = IteratorNext(it);
			if (11 == *((int*)IteratorGet(it)) )
			{
				SLLDestroy(newList, NULL);
				return SUCCESS;
			}	
		}		
	}
	return FAIL;
}

static int TestInsertWrongOp1()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;
	int n2 = 2;
	
	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	if ( NULL == SLLInsert(newList, (void*)&n2, IteratorBegin(newList), EMPTY) )
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;		
	}
	return FAIL;
}

static int TestInsertWrongOp2()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;
	int n2 = 2;
	
	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	if ( NULL == SLLInsert(newList, (void*)&n2, IteratorBegin(newList), SORTED) )
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;		
	}
	return FAIL;
}

static int TestInsertWrongOp3()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;
	
	if ( NULL == SLLInsert(newList, (void*)&n1, NULL, AFTER) )
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;		
	}
	return FAIL;
}

static int TestInsertBefore()
{
	Sll_t *newList = SLLCreate(NULL);
	Iterator_t *it = NULL;
	int n1 = 1;
	int n2 = 2;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	it = IteratorBegin(newList);
	SLLInsert(newList, (void*)&n2, it, BEFORE);
	
	if ( 2 == *((int*)IteratorGet(IteratorBegin(newList)) ))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;	
	}
	return FAIL;
}


static int TestInsertAfter()
{
	Sll_t *newList = SLLCreate(NULL);
	Iterator_t *it = NULL;
	int n1 = 1;
	int n2 = 2;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	it = IteratorBegin(newList);
	SLLInsert(newList, (void*)&n2, it, AFTER);
	
	if ( 1 == *((int*)IteratorGet(IteratorBegin(newList)) ))
	{
		if (2 == *((int*)IteratorGet(IteratorNext(it))) )
		SLLDestroy(newList, NULL);
		return SUCCESS;	
	}
	return FAIL;
}





/********************************[ TESTS REMOVE ]******************************/

static int TestRemoveWrongArgs1()
{
	if (ERR_BAD_ARGS == SLLRemove(NULL, NULL, NULL, EMPTY))
	{
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveWrongArgs2()
{
	Sll_t *newList = SLLCreate(NULL);
	if (ERR_BAD_ARGS == SLLRemove(newList, NULL, NULL, EMPTY))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveWrongArgs3()
{
	Sll_t *newList = SLLCreate(NULL);

	if (ERR_BAD_ARGS == SLLRemove(newList, NULL, IteratorBegin(newList), CURRENT))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveWrongArgs4()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;
	int n2 = 2;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	SLLInsert(newList, (void*)&n2, NULL, EMPTY);

	if (ERR_BAD_ARGS == SLLRemove(newList, NULL, IteratorBegin(newList), EMPTY))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveOneElmt1()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	if (ERR_LAST == SLLRemove(newList, NULL, IteratorBegin(newList), CURRENT))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveOneElmt2()
{
	Sll_t *newList = SLLCreate(NULL);
	int n1 = 1;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	if (ERR_LAST == SLLRemove(newList, NULL, IteratorBegin(newList), AFTER))
	{
		SLLDestroy(newList, NULL);
		return SUCCESS;
	}
	return FAIL;
}

static int TestRemoveCurrent()
{
	Sll_t *newList = SLLCreate(NULL);
	Iterator_t *it = NULL;
	int n1 = 1;
	int n2 = 2;
	int n3 = 3;
	int *ptr = NULL;
	int status;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	SLLInsert(newList, (void*)&n2, NULL, EMPTY);
	SLLInsert(newList, (void*)&n3, NULL, EMPTY);
	it = IteratorBegin(newList);

	status = SLLRemove(newList, (void **)&ptr, it, CURRENT);
	if (ERR_SUCCESS == status)
	{
		if (1 == *ptr && 2 == *((int*)IteratorGet(IteratorBegin(newList))))
		{
			SLLDestroy(newList, NULL);
			return SUCCESS;
		}	
	}
	return FAIL;
}


static int TestRemoveAfter()
{
	Sll_t *newList = SLLCreate(NULL);
	Iterator_t *it = NULL;
	int n1 = 1;
	int n2 = 2;
	int n3 = 3;
	int *ptr = NULL;

	SLLInsert(newList, (void*)&n1, NULL, EMPTY);
	SLLInsert(newList, (void*)&n2, NULL, EMPTY);
	SLLInsert(newList, (void*)&n3, NULL, EMPTY);
	it = IteratorBegin(newList);
	if (ERR_SUCCESS == SLLRemove(newList, (void **)&ptr, it, AFTER))
	{
		if (2 == *ptr && 1 == *((int*)IteratorGet(IteratorBegin(newList))))
		{
			SLLDestroy(newList, NULL);
			return SUCCESS;
		}	
	}
	return FAIL;
}


/**********************************FOR EACH***********************************/




/*******************************HELPERS FUNCTIONS****************************/

static void PrintStatus(int arg, char *str)
{
	if (arg == 1)
	{
        printf("%s : ", str);
		PSUCCESS;
	}
    else
    {
        printf("%s : ", str);
    	PFAIL;
    }
}

int CompareInts(void const *a_compareTo, void const *a_toInsert)
{
    if (*(int*)a_toInsert <= *(int*)a_compareTo)
    {
        return 1;
    }
    return 0;
}


/********************************FUNCTION POINTERS***************************/

/* static int VectorPrintInts(void *_element, size_t _index, void *_context)
{
	(void)(_index);
	(void)(_context);
	printf("%d,",*(int *)_element);
	return 1;
}

static int VectorPrintStruct(void *_element, size_t _index, void *_context)
{
	(void)(_index);
	(void)(_context);
	printf("%s,",((Person *)_element)->m_name);
	printf("%f,",((Person *)_element)->m_age);
	printf("\n");
	return 1;
}*/
