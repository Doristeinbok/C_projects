#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

typedef struct Stack Stack_t;


/*Return a new stack*/
extern Stack_t *StackCreate(size_t capacity);

/*Delete the stack */
extern void StackDestroy(Stack_t *stack);

/*Add a new element to the top of the stack */
extern void StackPush(Stack_t *stack, void* new_element);

/*Remove the last element */
extern void StackPop(Stack_t *stack);

/*Return the value of the last element */
extern void* StackPeek(Stack_t *stack);

/*Check if the array is empty, Return 0 or 1*/
extern int StackIsEmpty(Stack_t *stack);

/*Return how many elements are used*/
extern size_t StackSize(Stack_t *stack);

/*Check the capacity, Return the capacity*/
extern size_t StackCapacity(Stack_t *stack);

/* Print stack */
extern void PrintStack(Stack_t *stack);


#endif

