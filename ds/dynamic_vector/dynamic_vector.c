#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dynamic_vector.h"


struct Vector
{
    size_t capacity;
    size_t size;
	void *items;
	size_t type_size;
};



Vector_t *VectorCreate(size_t initial_capacity, size_t type_size)
{
	Vector_t *new_vector = NULL;
	new_vector = (Vector_t*)malloc(sizeof(Vector_t));
	if(NULL == new_vector)
	{
		return NULL;
	}
	new_vector->capacity = initial_capacity;
    new_vector->size = 0;
    new_vector->type_size = type_size;
    new_vector->items = malloc(new_vector->capacity * new_vector->type_size);

    return new_vector;
}


void VectorDestroy(Vector_t *vector)
{
	free(vector->items);
	free(vector);
}


/* Add a new element to the end of the vector */

void VectorPushBack(Vector_t *vector, const void* element)
{
	assert(vector);
	if(vector->size == vector->capacity)
	{
		VectorReserve(vector, 2 * vector->capacity);
	}

	memcpy((char*)vector->items + vector->type_size * vector->size, element, vector->type_size);
	++vector->size;	
}


void VectorPopBack(Vector_t *vector)
{
	assert(vector && vector->size);

	if(vector->size > 0)
	{
		--vector->size;
	}

	if(vector->size < vector->capacity / 3)
	{
		VectorReserve(vector, vector->capacity / 2);
	}
}


size_t VectorSize(Vector_t *vector)
{
	assert(vector);

	return vector->size;
}


size_t VectorCapacity(Vector_t *vector)
{
	assert(vector);

	return vector->capacity;
}

/* Get access to an element */
void* VectorGetAccessToElement(Vector_t *vector, size_t idx)
{
	assert(vector);

	if(idx > vector->size || vector->size == 0)
	{
		return NULL;
	}

	return (void*)((char*)vector->items + idx * vector->type_size);
}

/* Reallocates memory to store num elements*/

void VectorReserve(Vector_t *vector, size_t num)
{
	void *temp = NULL;
	assert(vector);

	temp = realloc(vector->items, num * vector->size);
	if(NULL == temp)
	{
		return;
	}
	vector->items = temp;
	vector->capacity = num;	
}

