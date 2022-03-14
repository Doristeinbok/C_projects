#include <stdio.h>

#include "stack.h"


struct Stack 
{
	int capacity;
	int top;
	void **array;
};


void test(void);


int main() 
{
	test();
	return 0;
}



/*******************************************************/



void test(void)
{
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int capacity = 5;

	Stack_t *new_stack = StackCreate(capacity);

	if (5 != StackCapacity(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}	

	if (1 != StackIsEmpty(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}

	StackPush(new_stack, &num4);
	if (1 != StackSize(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}

	StackPush(new_stack, &num5);
	if (2 != StackSize(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}

	StackPush(new_stack, &num6);
	if (3 != StackSize(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}

	if (6 != *(int*)StackPeek(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}
	
	StackPop(new_stack); 
	if (2 != StackSize(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}

	if (5 != *(int*)StackPeek(new_stack))
	{
		printf("error in line %d\n", __LINE__);
	}	

	StackDestroy(new_stack);
}


