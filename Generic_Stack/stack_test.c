

#include <stdio.h> 		/* printf                                       */
#include <stdlib.h> 	/* malloc realloc 								*/

#include "stack.h"

/**********************************DEFINE*************************************/

#define RED           "\x1b[31m"
#define GREEN        "\x1B[32m"
#define RESET        "\x1b[0m"

#define PSUCCESS printf(GREEN"SUCCESS\n"RESET)
#define PFAIL printf(RED"FAIL\n"RESET)
#define SUCCESS 1
#define FAIL 0

/************************************MAIN*************************************/

static int Test1();


/*******************************HELPERS FUNCTIONS**************************/

static void PrintStatus(int arg1, int arg2, char *str);
int Compare(const void* a_item1, const void* a_item2);


/************************************MAIN*************************************/


int main(void)
{
	printf("\n");
	PrintStatus(Test1(), SUCCESS, "Test1: Normal use");


	return (0);
}

/*********************************TESTS INIT*******************************/

static int Test1()
{
    int n1 = 20;
    int n2 = 12;
    int n3 = 3;
    int n4 = 2;

    int* p1 = &n1;
    int* p2 = &n2;
    int* p3 = &n3;
    int* p4 = &n4;

    Stack_t* mystack = StackCreate(4, Compare);
    StackPush(mystack, p1);
    StackPush(mystack, p2);
    StackPush(mystack, p3);
    StackPush(mystack, p4);
    StackPop(mystack, NULL);
    StackPop(mystack, NULL);
    StackPop(mystack, NULL);
    StackPop(mystack, NULL);




    Print(mystack);
    PrintMin(mystack);

    printf("The Minimum is: %d\n ", *(int*)StackMin(mystack));
    StackDestroy(mystack, NULL);

    return SUCCESS;
}




/*******************************HELPERS FUNCTIONS***************************/

int Compare(const void* a_item1, const void* a_item2)
{
    if (*(int*)a_item2 <= *(int*)a_item1)
    {
        return 1;
    }
    return 0;
}


static void PrintStatus(int arg1, int arg2, char *str)
{
	if (arg1 == arg2)
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

