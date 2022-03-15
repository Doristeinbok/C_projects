#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stdlib.h>

typedef struct Vector Vector_t;


/* Create new vector */
extern Vector_t *VectorCreate(size_t initial_capacity, size_t type_size);

/* Delete the vector */
extern void VectorDestroy(Vector_t *vector);

/* Add a new element to the end of the vector */
extern void VectorPushBack(Vector_t *vector, const void* element);

/* Remove element from the vector*/
extern void VectorPopBack(Vector_t *vector);

/* Get access to an element */
extern void* VectorGetAccessToElement(Vector_t *vector, size_t idx);

/* Reallocates memory to store num elements*/
extern void VectorReserve(Vector_t *vector, size_t num);

/* Return number of elements */
extern size_t VectorSize(Vector_t *vector);

/* Return capacity */
extern size_t VectorCapacity(Vector_t *vector);

#endif
