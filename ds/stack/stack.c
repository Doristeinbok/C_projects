#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <assert.h>

struct Stack
{
	int capacity;
	int top;
	void **array;
};


/*Return a new stack*/
Stack_t *StackCreate(size_t capacity)
{
	Stack_t *new_stack = (Stack_t*)malloc(sizeof(Stack_t));
	if(NULL == new_stack)
	{
		return NULL;
	}
	
	new_stack->top = 0;
	new_stack->capacity = capacity;
	new_stack->array = (void**)malloc(new_stack->capacity * sizeof(void*));
	if(NULL == new_stack->array)
	{
		return NULL;
	}
	return new_stack;
}


/*Delete the stack */
void StackDestroy(Stack_t *stack)
{
	assert(stack);

	free(stack->array);
	free(stack);
}


/*Add a new element to the top of the stack */
void StackPush(Stack_t *stack, void *new_element)
{
	assert(stack);

	if(stack->top == stack->capacity)
	{
		printf("Stack is full\n");
		return;
	}

	stack->array[stack->top] = new_element;
	++stack->top;
}


/*Remove the last element */
void StackPop(Stack_t *stack)
{
	assert(stack && !StackIsEmpty(stack));

	--stack->top;
}


/*Return the value of the last element */
void* StackPeek(Stack_t *stack)
{
	assert(stack);

	return stack->array[stack->top - 1];
}


/*Check if the array is empty, Return 0 or 1*/
int StackIsEmpty(Stack_t *stack)
{
	assert(stack);

	return (0 == stack->top);
}


/*Return how many elements are used*/
size_t StackSize(Stack_t *stack)
{
	assert(stack);

	return stack->top;

}


/*Check the capacity, Return the capacity*/
size_t StackCapacity(Stack_t *stack)
{
	assert(stack);

	return stack->capacity;
}

/* Print stack */
void PrintStack(Stack_t *stack)
{
	size_t i = 0;
	size_t size = stack->top;
	for(; i < size ; ++i)
	{
		printf("%d\n", *(int*)stack->array[i]);
	}
}