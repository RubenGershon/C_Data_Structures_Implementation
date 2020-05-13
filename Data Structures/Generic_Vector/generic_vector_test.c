/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: GenericVector testing
* 						  DATE: 22-07-2019
*******************************************************************************/

#include <stdio.h> 		/* printf               */
#include <stdlib.h> 	/* malloc realloc	    */

#include "generic_vector.h"

#define SUCCESS 0
#define FAIL 1

/**********************************[ STRUCT ]**********************************/

typedef struct Person
{
	char m_name[25];
	float m_age;
}Person;

/*******************************[ TESTS FUNCTIONS ]****************************/

static int TestCreateNormalUse();
static int TestCreateBothParamsZero();
static int TestCreateSizeZero();
static int TestCreateMaxSize();

static int TestAddNullVector();
static int TestAddNormalUse();
static int TestAddUntilFull();
static int TestAddResizeZero();
static int TestAddResize1();

static int TestRemoveNullVector();
static int TestRemoveNullItem();
static int TestRemoveEmptyVector();
static int TestRemoveNormalUse();
static int TestRemoveNormalUse2();

static int TestGetNullVector();
static int TestGetNullItem();
static int TestGetBadIndex();
static int TestGetNormalUse();

static int TestSetNullVector();
static int TestSetNullItem();
static int TestSetBadIndex();
static int TestSetNormalUse();


static void TestForEachPrintInt();
static void TestForEachPrintstruct();

/*****************************[ HELPERS FUNCTIONS ]****************************/

static void PrintStatus(int arg1, int arg2, char *str);
static int HCheck(int arg1, int arg2, int param);
static int VectorPrintInts(void *_element, size_t _index, void *_context);
static int VectorPrintStruct(void *_element, size_t _index, void *_context);

/***********************************[ MAIN ]***********************************/

int main(void)
{
    printf("\n");
	PrintStatus(TestCreateNormalUse(), SUCCESS, "Create: Normal use");
	PrintStatus(TestCreateBothParamsZero(), SUCCESS, "Create: both param 0");
	PrintStatus(TestCreateSizeZero(), SUCCESS, "Create: size 0");
	PrintStatus(TestCreateMaxSize(), SUCCESS, "Create: Max size");
	printf("\n");

	PrintStatus(TestAddNullVector(), SUCCESS, "Add: Null Vector");
	PrintStatus(TestAddNormalUse(), SUCCESS, "Add: Normal Use");
	PrintStatus(TestAddUntilFull(), SUCCESS, "Add: Until Vector Full");
	PrintStatus(TestAddResizeZero(), SUCCESS, "Add: Resize 0");
	PrintStatus(TestAddResize1(), SUCCESS, "Add: Normal Resize 1");
	printf("\n");

	PrintStatus(TestRemoveNullVector(), SUCCESS, "Remove: Null Vector");
	PrintStatus(TestRemoveNullItem(), SUCCESS, "Remove: Null item");
	PrintStatus(TestRemoveEmptyVector(), SUCCESS, "Remove: Empty Vector");
	PrintStatus(TestRemoveNormalUse(), SUCCESS, "Remove: Normal Use");
	PrintStatus(TestRemoveNormalUse2(), SUCCESS, "Remove: Normal Use 2");
	printf("\n");


	PrintStatus(TestGetNullVector(), SUCCESS, "Get: Null Vector");
	PrintStatus(TestGetNullItem(), SUCCESS, "Get: Null item");
	PrintStatus(TestGetBadIndex(), SUCCESS, "Get: Wrong Index");
	PrintStatus(TestGetNormalUse(), SUCCESS, "Get: Normal Use");
	printf("\n");

	PrintStatus(TestSetNullVector(), SUCCESS, "Set: Null Vector");
	PrintStatus(TestSetNullItem(), SUCCESS, "Set: Null item");
	PrintStatus(TestSetBadIndex(), SUCCESS, "Set: Wrong Index");
	PrintStatus(TestSetNormalUse(), SUCCESS, "Set: Normal Use");
	printf("\n");

	printf("\n");

	TestForEachPrintInt();
	TestForEachPrintstruct();

    return (0);
}

/********************************TESTS CREATE*********************************/

static int TestCreateNormalUse()
{
	Vector_t *vector = VectorCreate(4, 2);
	
	if (NULL != vector)
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
    {
		return (FAIL);        
    }
}

static int TestCreateBothParamsZero()
{
	Vector_t *vector = VectorCreate(0, 0);
	
	if (NULL == vector)
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
    {
		VectorDestroy(&vector, NULL);
		return (FAIL);        
    }
}

static int TestCreateSizeZero()
{
	Vector_t *vector = VectorCreate(0, 2);
	
	if (NULL != vector)
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
    {
		VectorDestroy(&vector, NULL);
		return (FAIL);        
    }
}

static int TestCreateMaxSize()
{
	Vector_t *vector = VectorCreate(0xFFFFFFFFFFFFFFFF + 1, 0);
	
	if (NULL == vector)
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
    {
		VectorDestroy(&vector, NULL);
		return (FAIL);        
    }
}

/*********************************TESTS ADD***********************************/

static int TestAddNullVector()
{
	int return_status = 0;
	int item = 1;
    Vector_t *vector = NULL;

	return_status = VectorPushBack(vector, &item);

	return (HCheck(ERR_NOT_INITIALIZED, return_status,0));
}

static int TestAddNormalUse()
{
	int pitem = 0;
	int *item = &pitem;
	int data = 101;
    Vector_t *vector = VectorCreate(10, 0);

	if ((ERR_OK == VectorPushBack(vector, &data)) && (ERR_OK == VectorGet(vector, 0, (void **)&item)) 
		&& (1  == VectorGetSize(vector)))
	{
		if (101 == *(int *)item)
		{
			VectorDestroy(&vector, NULL);
			return (SUCCESS);
		}
	}

	VectorDestroy(&vector, NULL);
	return (FAIL);
}

static int TestAddUntilFull()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

    Vector_t *vector = VectorCreate(5, 0);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);
	VectorPushBack(vector, &data4);

	if (5 == VectorGetSize(vector))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestAddResizeZero()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

    Vector_t *vector = VectorCreate(4, 0);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);
	

	if (ERR_OVERFLOW == VectorPushBack(vector, &data4))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestAddResize1()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

    Vector_t *vector = VectorCreate(4, 2);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);
	

	if (ERR_OK == VectorPushBack(vector, &data4))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

/*********************************TESTS REMOVE*****************************/

static int TestRemoveNullVector()
{
	int return_status = 0;
	return_status = VectorPopBack(NULL, NULL);

	return (HCheck(ERR_NOT_INITIALIZED, return_status,0));
}

static int TestRemoveNullItem()
{
	Vector_t *vector = VectorCreate(10, 0);
	int return_status = 0;
	int *item = NULL;
	int data = 11;

	VectorPushBack(vector, &data);
	return_status = VectorPopBack(vector ,(void **)&item);
	VectorDestroy(&vector, NULL);
	
	if ((ERR_OK == return_status) && (0 == VectorGetSize(vector)))
	{
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestRemoveEmptyVector()
{
	int return_status = 0;
	int *item = NULL;
	Vector_t *vector = VectorCreate(10, 0);

	return_status = VectorPopBack(vector, (void **)&item);
	VectorDestroy(&vector, NULL);

	return (HCheck(ERR_UNDERFLOW, return_status,0));
}

static int TestRemoveNormalUse()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int *item = NULL;
	int *item1 = NULL;
	int *item2 = NULL;
	int *item3 = NULL;

    Vector_t *vector = VectorCreate(4, 0);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);

	VectorPopBack(vector, (void **)&item);
	VectorPopBack(vector, (void **)&item1);
	VectorPopBack(vector, (void **)&item2);
	VectorPopBack(vector, (void **)&item3);

	
	if (0 == VectorGetSize(vector))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestRemoveNormalUse2()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int *item = NULL;

    Vector_t *vector = VectorCreate(4, 0);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);

	VectorPopBack(vector, (void **)&item);

	
	if ((3 == VectorGetSize(vector)) && (*item == 3))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

/*********************************TESTS GET*******************************/

static int TestGetNullVector()
{
	int return_status = 0;
	return_status = VectorGet(NULL, 0,  NULL);

	return (HCheck(ERR_NOT_INITIALIZED, return_status,0));
}

static int TestGetNullItem()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data = 11;

	VectorPushBack(vector, &data);
	
	if (ERR_NOT_INITIALIZED == VectorGet(vector, 0,  NULL))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestGetBadIndex()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data = 11;
	void *item = NULL;

	VectorPushBack(vector, &data);
	
	if (ERR_WRONG_INDEX == VectorGet(vector, 1,  &item))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestGetNormalUse()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data1 = 11;
	int data2 = 22;
	void *item = NULL;

	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);

	if (ERR_OK == VectorGet(vector, 1,  &item))
	{
		if (22 == *(int *)item)
		{
			VectorDestroy(&vector, NULL);
			return (SUCCESS);
		}	
	}
	
	return (FAIL);
}

/*********************************TESTS SET*******************************/

static int TestSetNullVector()
{
	int return_status = 0;
	return_status = VectorSet(NULL, 0,  NULL);

	return (HCheck(ERR_NOT_INITIALIZED, return_status,0));
}

static int TestSetNullItem()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data = 11;

	VectorPushBack(vector, &data);
	
	if (ERR_NOT_INITIALIZED == VectorSet(vector, 0,  NULL))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestSetBadIndex()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data = 11;
	int item = 5;

	VectorPushBack(vector, &data);
	
	if (ERR_WRONG_INDEX == VectorSet(vector, 1,  (void *)&item))
	{
		VectorDestroy(&vector, NULL);
		return (SUCCESS);
	}
	else
	{
		return (FAIL);
	}
}

static int TestSetNormalUse()
{
	Vector_t *vector = VectorCreate(10, 0);
	int data1 = 11;
	int data2 = 22;
	int item = 555;
	void *return_item = NULL;

	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);

	if (ERR_OK == VectorSet(vector, 1,  (void *)&item))
	{
		VectorGet(vector, 1,  &return_item);
		
		if (555 == *(int *)return_item)
		{
			VectorDestroy(&vector, NULL);
			return (SUCCESS);
		}	
	}
	
	return (FAIL);
}	
	

	

/**********************************FOR EACH***********************************/

static void TestForEachPrintInt()
{
	VectorElementAction funct_t = VectorPrintInts;
	int data = 0;
	int data1 = 1;
	int data2 = 25;
	int data3 = 3;

    Vector_t *vector = VectorCreate(4, 0);

	VectorPushBack(vector, &data);
	VectorPushBack(vector, &data1);
	VectorPushBack(vector, &data2);
	VectorPushBack(vector, &data3);

	printf("TEST VECTOR FOR EACH - PRINT INT\n");
	VectorForEach(vector, funct_t, NULL);
	printf("\n");

	VectorDestroy(&vector, NULL);
}

static void TestForEachPrintstruct()
{
	int (*ptr)(void *, size_t , void *) = VectorPrintStruct;
	Person person = {"riri", 1.1};
	Person person1 = {"fifi", 2.2};
	Person person2 = {"loulou", 3.3};
	Person person3 = {"donald", 4.4};

    Vector_t *vector = VectorCreate(4, 0);

	VectorPushBack(vector, &person);
	VectorPushBack(vector, &person1);
	VectorPushBack(vector, &person2);
	VectorPushBack(vector, &person3);

	printf("TEST VECTOR FOR EACH - PRINT STRUCT\n");
	VectorForEach(vector, ptr, NULL);
	printf("\n");


	VectorDestroy(&vector, NULL);
}




/*******************************HELPERS FUNCTIONS****************************/

static int HCheck(int arg1, int arg2, int param)
{
	if (param == 0)
	{
		return (arg1 == arg2) ? (SUCCESS): (FAIL);
	}

	else
	{
		return (arg1 != arg2) ? (SUCCESS): (FAIL);
	}
}


static void PrintStatus(int arg1, int arg2, char *str)
{
	if (arg1 == arg2)
	{
		printf("%s : SUCCESS\n", str);
	}
	else
	{
		printf("%s : FAIL\n", str);
	}	
}

/********************************FUNCTION POINTERS***************************/

static int VectorPrintInts(void *_element, size_t _index, void *_context)
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
}
