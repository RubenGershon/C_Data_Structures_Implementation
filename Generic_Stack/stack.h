#ifndef __SLL_H__
#define __SLL_H__

#include <stdio.h>
#include<stddef.h> /* size_t */

typedef enum Result{OK, UNINITIALIZED, OVERFLOW, UNDERFLOW} Result_t;
typedef struct Stack Stack_t;

typedef int (*DestroyFunc_t)(const void* a_item);
typedef int (*Compare_t)(const void* a_item1, const void* a_item2);


Stack_t* StackCreate(size_t a_capacity, Compare_t a_cmp);
void StackDestroy(Stack_t* a_stack, DestroyFunc_t a_destroy);
Result_t StackPush(Stack_t* a_stack, const void* a_item);
Result_t StackPop(Stack_t* a_stack, const void* a_item);
const void* StackTop(Stack_t* a_stack);
void Print(Stack_t* a_stack);
void PrintMin(Stack_t* a_stack);
const void* StackMin(Stack_t* a_stack);


#endif
