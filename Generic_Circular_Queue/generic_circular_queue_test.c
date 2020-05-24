/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Circular Queue Test File
* 						  DATE: 2020
******************************************************************************/

#include <stdio.h> 		/* printf                                       */
#include <stdlib.h> 	/* malloc realloc 								*/

#include "generic_circular_queue.h"

/*********************************[ DEFINE ]***********************************/

#define RED           "\x1b[31m"
#define GREEN        "\x1B[32m"
#define RESET        "\x1b[0m"

#define PSUCCESS printf(GREEN"SUCCESS\n"RESET)
#define PFAIL printf(RED"FAIL\n"RESET)
#define SUCCESS 1
#define FAIL 0

/***********************************[ MAIN ]***********************************/

static int TestCreateNormalUse();
static int TestCreateSizeZero();
static int TestCreateMaxSize();

static int TestEnqueueNullQueue();
static int TestEnqueueFullQueue();
static int TestEnqueueNormalUse();
static int TestEnqueueUntilFull();
static int TestEnqueueValuesInserted();

static int TestDequeueNullQueue();
static int TestDequeueNullItem();
static int TestDequeueEmptyQueue();
static int TestDequeueNormalUse();
static int TestDequeueFullQueue();

static int TestIsFullNullQueue();
static int TestIsFullQueue();
static int TestIsFullNotFullQueue();

static int TestIsEmptyNullQueue();
static int TestIsEmptyQueue();
static int TestNotEmptyQueue();

static int TestFull1();
static int TestFull2();

static void TestForEachPrintInt();


/******************************[ HELPERS FUNCTIONS ]***************************/

static int HEnqueueFunction(Queue_t *queue, const size_t iterations);
static int HDeQueueFunction(Queue_t *queue, const size_t iterations);
static int HCheck(int arg1, int arg2);
static void PrintStatus(int arg, char *str);
static int QueuePrintInts(void const *a_element, size_t a_index, void *a_context);

/***********************************[ MAIN ]***********************************/


int main(void)
{
	printf("\n");
	PrintStatus(TestCreateNormalUse(), "Create: Normal use");
	PrintStatus(TestCreateSizeZero(), "Create: size 0");
	PrintStatus(TestCreateMaxSize(), "Create: Max size");
	printf("\n");

	PrintStatus(TestEnqueueNullQueue(), "Enqueue: Null Queue");
	PrintStatus(TestEnqueueFullQueue(), "Enqueue: Full Queue");
	PrintStatus(TestEnqueueValuesInserted(), "Enqueue: Check Values Inserted");
	PrintStatus(TestEnqueueNormalUse(), "Enqueue: Normal Use");
	PrintStatus(TestEnqueueUntilFull(), "Enqueue: Until Queue Full");
	printf("\n");

	PrintStatus(TestDequeueNullQueue(), "Dequeue: Null Queue");
	PrintStatus(TestDequeueNullItem(),  "Dequeue: Null item");
	PrintStatus(TestDequeueEmptyQueue(),"Dequeue: Empty Queue");
	PrintStatus(TestDequeueNormalUse(), "Dequeue: Normal Use");
	PrintStatus(TestDequeueFullQueue(), "Dequeue: Full Dequeue");
	printf("\n");
 
	PrintStatus(TestIsFullNullQueue(), "IsFull: Null Queue");
	PrintStatus(TestIsFullQueue(), "IsFull: Full Queue");
	PrintStatus(TestIsFullNotFullQueue(), "IsFull: Not Full Queue");
	printf("\n");

	PrintStatus(TestIsEmptyNullQueue(), "IsEmpty: Null Queue");
	PrintStatus(TestIsEmptyQueue(), "IsEmpty: Empty Queue");
	PrintStatus(TestNotEmptyQueue(), "IsEmpty: Not Empty Queue");
	printf("\n");

	PrintStatus(TestFull1(), "TestFull: Test full functions 1");
	PrintStatus(TestFull2(), "TestFull: Test full functions 2");
	printf("\n");

	TestForEachPrintInt();

    return (ERR_OK);
}

/***********************************[ TESTS ]**********************************/

static int TestCreateNormalUse()
{
	Queue_t *queue = QueueCreate(4);
	
	if (NULL != queue)
	{
		QueueDestroy(&queue, NULL);
		return (SUCCESS);
	}
	return (FAIL);        
}

static int TestCreateSizeZero()
{
	Queue_t *queue = QueueCreate(0);
	
	if (NULL == queue)
	{
		QueueDestroy(&queue, NULL);
		return (SUCCESS);
	}
	return (FAIL);        
}

static int TestCreateMaxSize()
{
	Queue_t *queue = QueueCreate(0xFFFFFFFFFFFFFFFF + 1);
	
	if (NULL == queue)
	{
		return (SUCCESS);
	}
	
	QueueDestroy(&queue, NULL);
	return (FAIL);        
}


static int TestEnqueueNullQueue()
{
	int return_status = 0;
	int data = 1;
    Queue_t *queue = NULL;

	return_status = QueueEnqueue(queue, &data);

	return (HCheck(ERR_NOT_INITIALIZED, return_status));
}

static int TestEnqueueFullQueue()
{
    Queue_t *queue = QueueCreate(10);	
	int return_status = 0;
	int data = 1;

	if (10 == HEnqueueFunction(queue, 10))
	{
		return_status = QueueEnqueue(queue, &data);
	}

	QueueDestroy(&queue, NULL);
	return (HCheck(ERR_OVERFLOW, return_status));
}

static int TestEnqueueValuesInserted()
{
	Queue_t *queue = QueueCreate(10);
	int item1 = 0;
	int item2 = 0;
	int item3 = 0;
	int *ptr1 = &item1;
	int *ptr2 = &item2;
	int *ptr3 = &item3;
	int data = 111;
	int data2 = 222;
	int data3 = 333;	

	QueueEnqueue(queue, &data);
	QueueEnqueue(queue, &data2);
	QueueEnqueue(queue, &data3);

	QueueDequeue(queue, (void **)&ptr1);
	QueueDequeue(queue, (void **)&ptr2);
	QueueDequeue(queue, (void **)&ptr3);

	if (*ptr1 == 111 && *ptr2 == 222 && *ptr3 == 333)
	{
		return (SUCCESS);
	}

	QueueDestroy(&queue, NULL);
	return (FAIL);
}


static int TestEnqueueNormalUse()
{
    Queue_t *queue = QueueCreate(10);	
	int return_status = 0;
	int data = 1;

	if (1 == QueueIsEmpty(queue))
	{
		return_status = QueueEnqueue(queue, &data);
		if (ERR_OK == return_status && 0 == QueueIsEmpty(queue))
		{
			QueueDestroy(&queue, NULL);
			return (SUCCESS);
		}
	}

	QueueDestroy(&queue, NULL);
	return (FAIL);
}

static int TestEnqueueUntilFull()
{
	Queue_t *queue = QueueCreate(10);	

	if (10 == HEnqueueFunction(queue, 10))
	{
		QueueDestroy(&queue, NULL);
		return (SUCCESS);
	}
	else
	{
		QueueDestroy(&queue, NULL);
		return (FAIL);
	}
}


static int TestDequeueNullQueue()
{
	int return_status = 0;
	int item = 0;
	int *ptr = &item;
    Queue_t *queue = NULL;

	return_status = QueueDequeue(queue, (void **)&ptr);

	return (HCheck(ERR_NOT_INITIALIZED, return_status));
}

static int TestDequeueNullItem()
{
    Queue_t *queue = QueueCreate(10);	
	int return_status = 0;
	int data = 0;

	QueueEnqueue(queue, &data);
	return_status = QueueDequeue(queue, NULL);

	QueueDestroy(&queue, NULL);
	return (HCheck(ERR_OK, return_status));
}


static int TestDequeueEmptyQueue()
{
    Queue_t *queue = QueueCreate(10);	
	int return_status = 0;
	int *ptr = NULL;

	return_status = QueueDequeue(queue, (void **)&ptr);

	QueueDestroy(&queue, NULL);
	return (HCheck(ERR_UNDERFLOW, return_status));
}


static int TestDequeueNormalUse()
{
    Queue_t *queue = QueueCreate(10);	
	int return_status = 0;
	int *ptr = NULL;
	int data = 101;

	if (1 == QueueIsEmpty(queue))
	{
		QueueEnqueue(queue, &data);
		return_status = QueueDequeue(queue, (void **)&ptr);
		if ((ERR_OK == return_status) && (1 == QueueIsEmpty(queue)) && (101 == *ptr))
		{
			QueueDestroy(&queue, NULL);
			return (SUCCESS);
		}
	}

	QueueDestroy(&queue, NULL);
	return (FAIL);
}

static int TestDequeueFullQueue()
{
	Queue_t *queue = QueueCreate(10);	

	HEnqueueFunction(queue, 10);
	if (10 == HDeQueueFunction(queue, 10))
	{
		if (1 == QueueIsEmpty(queue))
		{
			QueueDestroy(&queue, NULL);
			return (SUCCESS);
		}	
	}
	
	QueueDestroy(&queue, NULL);
	return (FAIL);
}


static int TestIsFullNullQueue()
{
	int return_status = 0;

	return_status = QueueIsFull(NULL);

	return (HCheck(-1, return_status));
}

static int TestIsFullQueue()
{
	Queue_t *queue = QueueCreate(3);
	int return_status = -10;

	HEnqueueFunction(queue, 3);
	return_status = QueueIsFull(queue);
	QueueDestroy(&queue, NULL);

	return (HCheck(1, return_status));
}

static int TestIsFullNotFullQueue()
{
	Queue_t *queue = QueueCreate(10);
	int return_status = -10;

	return_status = QueueIsFull(queue);
	QueueDestroy(&queue, NULL);

	return (HCheck(0, return_status));
}


static int TestIsEmptyNullQueue()
{
	int return_status = 0;

	return_status = QueueIsEmpty(NULL);

	return (HCheck(-1, return_status));
}

static int TestIsEmptyQueue()
{
	Queue_t *queue = QueueCreate(10);
	int return_status = -10;

	return_status = QueueIsEmpty(queue);
	
	QueueDestroy(&queue, NULL);
	return (HCheck(1, return_status));
}

static int TestNotEmptyQueue()
{
	Queue_t *queue = QueueCreate(10);
	int return_status = -10;
	int data = 1;

	QueueEnqueue(queue, &data);
	return_status = QueueIsEmpty(queue);
	
	QueueDestroy(&queue, NULL);
	return (HCheck(0, return_status));
}


static int TestFull1()
{
	Queue_t *queue = QueueCreate(10);
	int data = 11;
	int data2 = 999;

	if (1 != QueueIsEmpty(queue))
	{
		return (FAIL);
	}

	if (10 != HEnqueueFunction(queue, 10))
	{
		return (FAIL);
	}

	if (1 != QueueIsFull(queue))
	{
		return (FAIL);
	}

	if (ERR_OVERFLOW != QueueEnqueue(queue, &data))
	{
		return (FAIL);
	}

	if (10 != HDeQueueFunction(queue, 10))
	{
		return (FAIL);
	}

	if (ERR_OK != QueueEnqueue(queue, &data2))
	{
		return (FAIL);
	}

	if (9 != HEnqueueFunction(queue, 10))
	{
		return (FAIL);
	}

	QueueDestroy(&queue, NULL);
	return (SUCCESS);
}

static int TestFull2()
{
	Queue_t *queue = QueueCreate(10);

	if (1 != QueueIsEmpty(queue))
	{
		return (FAIL);
	}

	if (7 != HEnqueueFunction(queue, 7))
	{
		return (FAIL);
	}

	if (1 == QueueIsFull(queue))
	{
		return (FAIL);
	}

	if (4 != HDeQueueFunction(queue, 4))
	{
		return (FAIL);
	}

	if (7 != HEnqueueFunction(queue, 7))
	{
		return (FAIL);
	}

	QueueDestroy(&queue, NULL);
	return (SUCCESS);
}


/******************************[ HELPERS FUNCTIONS ]***************************/

int CompareInts(void const* a_item1, void const* a_item2)
{
    if (*(int*)a_item2 <= *(int*)a_item1)
    {
        return 1;
    }
    return 0;
}


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

static int HEnqueueFunction(Queue_t *queue, const size_t iterations)
{
	size_t i = 0;
	int count = 0;
	int return_status = 0;
	int *items = (int *)malloc(sizeof(int) * iterations);

	for (i = 0; i < iterations; ++i)
	{
		items[i] = i;
	}

	for (i = 0; i < iterations; ++i)
	{
		return_status = QueueEnqueue(queue, &items[i]);
		if (ERR_OK == return_status)
		{
			++count;
		}
	}
	return (count);
}

static int HDeQueueFunction(Queue_t *queue, const size_t iterations)
{
	size_t i = 0;
	int count = 0;
	int return_status = 0;

	for (i = 0; i < iterations; ++i)
	{
		return_status = QueueDequeue(queue, NULL);
		if (ERR_OK == return_status)
		{
			++count;
		}
	}
	return (count);
}


static int HCheck(int arg1, int arg2)
{
	return (arg1 == arg2) ? (SUCCESS): (FAIL);
}


/***********************************TEST FOR EACH***************************/

static void TestForEachPrintInt()
{
	int data = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 6;

    Queue_t *queue = QueueCreate(7);

	QueueEnqueue(queue, &data);
	QueueEnqueue(queue, &data1);
	QueueEnqueue(queue, &data2);
	QueueEnqueue(queue, &data3);
	QueueEnqueue(queue, &data4);
	QueueEnqueue(queue, &data5);
	QueueEnqueue(queue, &data6);

	QueueDequeue(queue, NULL);
	QueueDequeue(queue, NULL);
	QueueDequeue(queue, NULL);

	QueueEnqueue(queue, &data);
	QueueEnqueue(queue, &data1);

	printf("TEST QUEUE FOR EACH - PRINT INT\n");
	QueueForEach(queue, QueuePrintInts, NULL);
	printf("\n");

	QueueDestroy(&queue, NULL);
}

/********************************FUNCTION POINTERS****************************/

static int QueuePrintInts(void const *a_element, size_t a_index, void *a_context)
{
	(void)(a_index);
	(void)(a_context);
	printf("%d,",*(int *)a_element);
	return 1;
}