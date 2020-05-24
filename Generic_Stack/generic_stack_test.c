/******************************************************************************
* 						  PROGRAMMER: RUBEN GERSHON
* 						  FILE: Generic Stack Test File
* 						  DATE: 2020
******************************************************************************/

#include <stdio.h> 		/* printf                                       */
#include <stdlib.h> 	/* malloc realloc 								*/

#include "generic_stack.h"

/*********************************[ DEFINE ]***********************************/

#define RED           "\x1b[31m"
#define GREEN        "\x1B[32m"
#define RESET        "\x1b[0m"

#define PSUCCESS printf(GREEN"SUCCESS\n"RESET)
#define PFAIL printf(RED"FAIL\n"RESET)
#define SUCCESS 1
#define FAIL 0

/***********************************[ MAIN ]***********************************/

static int Test_Create_1();
static int Test_Create_2();
static int Test_Create_3();
static int Test_Push_1();
static int Test_Push_2();
static int Test_Push_3();
static int Test_Push_4();
static int Test_Pop_1();
static int Test_Pop_2();
static int Test_Pop_3();
static int Test_Pop_4();
static int Test_Top_1();
static int Test_Top_2();
static int Test_Top_3();
static int Test_Top_4();
static int Test_Min_1();
static int Test_Min_2();
static int Test_Min_3();
static int Test_Min_4();
static int Test_Min_5();
static int Test_Visual_1();

/******************************[ HELPERS FUNCTIONS ]***************************/

static void PrintStatus(int arg, char *str);
void PrintInts(void const* a_item);
int CompareInts(const void* a_item1, const void* a_item2);
static Status_t FillHelper1(Stack_t *a_newStack, int *a_arr);


/***********************************[ MAIN ]***********************************/


int main(void)
{
	printf("\n");
	PrintStatus(Test_Create_1(), "Test_Create_1: Zero Capacity");
	PrintStatus(Test_Create_2(), "Test_Create_2: Capacity & NULL cmp");
	PrintStatus(Test_Create_3(), "Test_Create_3: Capacity & cmp");
	PrintStatus(Test_Push_1(), "Test_Push_1: Null ptr");
	PrintStatus(Test_Push_2(), "Test_Push_2: Normal use");
	PrintStatus(Test_Push_3(), "Test_Push_3: Overflow");
	PrintStatus(Test_Push_4(), "Test_Push_4: Null item");
    PrintStatus(Test_Pop_1(), "Test_Pop_1: Null ptr");
	PrintStatus(Test_Pop_2(), "Test_Pop_2: Normal use");
	PrintStatus(Test_Pop_3(), "Test_Pop_3: Underflow");
	PrintStatus(Test_Pop_4(), "Test_Pop_4: With return Item");
    PrintStatus(Test_Top_1(), "Test_Top_1: Null ptr");
	PrintStatus(Test_Top_2(), "Test_Top_2: Null item");
	PrintStatus(Test_Top_3(), "Test_Top_3: Normal Use");
	PrintStatus(Test_Top_4(), "Test_Top_4: Underflow");
    PrintStatus(Test_Min_1(), "Test_Min_1: Null stack");
	PrintStatus(Test_Min_2(), "Test_Min_2: Null item");
	PrintStatus(Test_Min_3(), "Test_Min_3: Null compare");
	PrintStatus(Test_Min_4(), "Test_Min_4: Normal Use");
	PrintStatus(Test_Min_5(), "Test_Min_5: Normal Use after a pop");
	PrintStatus(Test_Visual_1(), "Test_Visual_1: Normal Use");





	return (0);
}

/***********************************[ TESTS ]**********************************/

static int Test_Create_1()
{
    if (NULL == StackCreate(0, NULL))
    {
        return SUCCESS;
    }
    return FAIL;
}

static int Test_Create_2()
{
    Stack_t *newStack = StackCreate(10, NULL); 
    if (NULL != newStack)
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }
    return FAIL;
}

static int Test_Create_3()
{
    Stack_t *newStack = StackCreate(10, CompareInts); 
    if (NULL != newStack)
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }
    return FAIL;
}

static int Test_Push_1()
{
    if (ERR_NOT_INITIALIZED ==  StackPush(NULL, NULL))
    {
        return SUCCESS;
    } 
    return FAIL;
}


static int Test_Push_2()
{
    int arr[10];
    Stack_t *newStack = StackCreate(10, NULL);
    if (ERR_OK != FillHelper1(newStack, arr))
    {
        StackDestroy(newStack, NULL);
        return FAIL;
    }

    if (10 == StackSize(newStack))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }
    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Push_3()
{
    int arr[10];
    int item = 3;
    Stack_t *newStack = StackCreate(10, NULL);
    FillHelper1(newStack, arr);

    if (ERR_OVERFLOW == StackPush(newStack, &item) && 10 == StackSize(newStack))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Push_4()
{
    Stack_t *newStack = StackCreate(10, NULL);

    if (ERR_OK == StackPush(newStack, NULL) && 1 == StackSize(newStack))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Pop_1()
{
    if (ERR_NOT_INITIALIZED ==  StackPop(NULL, NULL))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Pop_2()
{
    int arr[10];
    Stack_t *newStack = StackCreate(10, NULL);
    FillHelper1(newStack, arr);
    StackPop(newStack, NULL);
   
    if (9 == StackSize(newStack))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }
    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Pop_3()
{
    int item = 3;
    Stack_t *newStack = StackCreate(10, NULL);
    StackPush(newStack, &item);

    if ( (ERR_OK == StackPop(newStack, NULL)) && 
                    (ERR_UNDERFLOW == StackPop(newStack, NULL)) )
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Pop_4()
{
    int item1 = 3;
    int item2 = 6;
    int *ptr = NULL;
    Stack_t *newStack = StackCreate(10, NULL);
    StackPush(newStack, &item1);
    StackPush(newStack, &item2);

    if ( (2 == StackSize(newStack)) && (ERR_OK == StackPop(newStack, (void*)&ptr)) && 
    (*ptr == 6) &&  (1 == StackSize(newStack)))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}


static int Test_Top_1()
{
    int *ptr = NULL;
    if (ERR_NOT_INITIALIZED ==  StackTop(NULL, (void*)&ptr))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Top_2()
{
    Stack_t *newStack = StackCreate(10, NULL);
    if (ERR_NOT_INITIALIZED ==  StackTop(newStack, NULL))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Top_3()
{
    int item1 = 3;
    int item2 = 6;
    int *ptr = NULL;
    Stack_t *newStack = StackCreate(10, NULL);
    StackPush(newStack, &item1);
    StackPush(newStack, &item2);

    if ( (2 == StackSize(newStack)) && (ERR_OK == StackTop(newStack, (void*)&ptr)) && 
    (*ptr == 6) && (2 == StackSize(newStack)))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Top_4()
{
    int item = 3;
    Stack_t *newStack = StackCreate(10, NULL);
    int *ptr = NULL;
    StackPush(newStack, &item);

    if ( (ERR_OK == StackPop(newStack, NULL)) && 
                    (ERR_UNDERFLOW == StackTop(newStack, (void*)&ptr)) )
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Min_1()
{
    int *ptr = NULL;
    if (ERR_NOT_INITIALIZED ==  StackMin(NULL, (void*)&ptr))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Min_2()
{
    Stack_t *newStack = StackCreate(10, CompareInts);
    if (ERR_NOT_INITIALIZED ==  StackMin(newStack, NULL))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Min_3()
{
    int *ptr = NULL;
    Stack_t *newStack = StackCreate(10, NULL);
    if (ERR_NOT_INITIALIZED ==  StackMin(newStack, (void*)&ptr))
    {
        return SUCCESS;
    } 
    return FAIL;
}

static int Test_Min_4()
{
    int arr[10];
    int *ptr = NULL;
    Stack_t *newStack = StackCreate(10, CompareInts);
    FillHelper1(newStack, arr);
    
    if ((ERR_OK == StackMin(newStack, (void*)&ptr)) && (*ptr == 2))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}

static int Test_Min_5()
{
    int arr[10];
    int *ptr = NULL;
    Stack_t *newStack = StackCreate(10, CompareInts);
    FillHelper1(newStack, arr);
    StackPop(newStack, NULL);
    
    if ((ERR_OK == StackMin(newStack, (void*)&ptr)) && (*ptr == 3))
    {
        StackDestroy(newStack, NULL);
        return SUCCESS;
    }

    StackDestroy(newStack, NULL);
    return FAIL;
}


static int Test_Visual_1()
{
    int arr[10];
    Stack_t *newStack = StackCreate(10, CompareInts);
    FillHelper1(newStack, arr);
   
    StackPrint(newStack, PrintInts);
    
    StackDestroy(newStack, NULL);
    return SUCCESS;
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

void PrintInts(void const* a_item)
{
    printf("%d, ", *(int*)a_item);
}

static Status_t FillHelper1(Stack_t *a_newStack, int *a_arr)
{
    size_t i = 0;
    Status_t status = 0;
    int arr[10] = {3,7,4,11,8,33,30,5,44,2};
    for (i = 0; i < 10; ++i)
    {
       a_arr[i] = arr[i];
    }

    for (i = 0; i < 10; ++i)
    {
        status = StackPush(a_newStack, &a_arr[i]);
        if (ERR_OK != status)
        {
            return status;
        }
    }
    return status;
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

