#include <stdlib.h>/* malloc */
#include <assert.h>
#include "heap.h"
#include "dynamic_vector.h"

struct Heap
{
    cmp_func_t compare;
    const void *param;
    Vector_t *vector;
};

static void HeapifyDownFrom(heap_t *heap, size_t from);
static size_t LeftChild(size_t i);
static size_t RightChild(size_t i);
static size_t GetParent(size_t i);
static void SwapPointersInArray(void *element1, void *element2);
static void HeapifyUp(heap_t *heap);
static size_t GetFirstChild(heap_t *heap, size_t current);

heap_t *HeapCreate(cmp_func_t compare, const void *param)
{
    heap_t *heap = NULL;

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (!heap)
    {
        return NULL;
    }

    heap->compare = compare;
    heap->param = param;

    heap->vector = VectorCreate(1, sizeof(void *));
    /* check and free */
    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    VectorDestroy(heap->vector);
    free(heap);
}

/* returns 0 if success, 1 if failed*/
int HeapPush(heap_t *heap, const void *data)
{
    assert(heap);

    VectorPushBack(heap->vector, &data);
    HeapifyUp(heap);
    /* check if the size is changed */
    return 0;
}

void HeapPop(heap_t *heap)
{
    assert(heap);
    if (HeapIsEmpty(heap))
    {
        return;
    }
    SwapPointersInArray(VectorGetAccessToElement(heap->vector, 0),
                        VectorGetAccessToElement(heap->vector, HeapSize(heap) - 1));
    VectorPopBack(heap->vector);
    if (HeapIsEmpty(heap))
    {
        return;
    }
    HeapifyDownFrom(heap, 0);
}

void *HeapPeek(heap_t *heap)
{
    assert(heap);

    return (void *)*(size_t *)VectorGetAccessToElement(heap->vector, 0);
}

/* 1 if empty, 0 if not*/
int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return 0 == HeapSize(heap);
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return VectorSize(heap->vector);
}

void *HeapRemove(heap_t *heap, const void *data, is_match_func_t is_match)
{
    size_t i;
    assert(heap && is_match);
    for (i = 0; i < HeapSize(heap); ++i)
    {
        if (0 == is_match((void *)*(size_t *)VectorGetAccessToElement(heap->vector, i), data))
        {
            SwapPointersInArray(VectorGetAccessToElement(heap->vector, i),
                                VectorGetAccessToElement(heap->vector, HeapSize(heap) - 1));
            VectorPopBack(heap->vector);
            if (HeapSize(heap) > 0)
            {
                HeapifyDownFrom(heap, i);
            }
            return (void *)data;
        }
    }
    return NULL;
}

void *HeapFind(const heap_t *heap, const void *data, is_match_func_t is_match)
{
    size_t i = 0;
    assert(heap);
    for (i = 0; i < HeapSize(heap); ++i)
    {
        if (0 == is_match((void *)*(size_t *)VectorGetAccessToElement(heap->vector, i), data))
        {
            return (void *)data;
        }
    }
    return NULL;
}

static size_t LeftChild(size_t i)
{
    return 2 * i + 1;
}

static size_t RightChild(size_t i)
{
    return 2 * i + 2;
}

static size_t GetParent(size_t i)
{
    if (0 == i)
    {
        return 0;
    }
    return (i - 1) / 2;
}

static void HeapifyUp(heap_t *heap)
{
    size_t current;

    current = HeapSize(heap) - 1;

    for (; 0 != current; current = GetParent(current))
    {
        if (heap->compare((void *)*(size_t *)VectorGetAccessToElement(heap->vector, current),
                          (void *)*(size_t *)VectorGetAccessToElement(heap->vector, GetParent(current)),
                          heap->param) < 0)
        {
            SwapPointersInArray(VectorGetAccessToElement(heap->vector, current),
                                VectorGetAccessToElement(heap->vector, GetParent(current)));
        }
        else
        {
            return;
        }
    }
}

static void HeapifyDownFrom(heap_t *heap, size_t from)
{
    size_t current;
    size_t next_child;
    current = from;

    while (0 != GetFirstChild(heap, current))
    {
        next_child = GetFirstChild(heap, current);
        if (heap->compare((void *)*(size_t *)VectorGetAccessToElement(heap->vector, current),
                          (void *)*(size_t *)VectorGetAccessToElement(heap->vector, next_child),
                          heap->param) > 0)
        {

            SwapPointersInArray(VectorGetAccessToElement(heap->vector, current),
                                VectorGetAccessToElement(heap->vector, next_child));
            current = next_child;
        }
        else
        {
            return;
        }
    }
}

static size_t GetFirstChild(heap_t *heap, size_t current)
{
    if (LeftChild(current) > HeapSize(heap) - 1 && RightChild(current) > HeapSize(heap) - 1)
    {
        return 0;
    }
    else
    {
        if (LeftChild(current) > HeapSize(heap) - 1)
        {
            return RightChild(current);
        }
        else if (RightChild(current) > HeapSize(heap) - 1)
        {
            return LeftChild(current);
        }
    }

    return heap->compare((void *)*(size_t *)VectorGetAccessToElement(heap->vector, LeftChild(current)),
                         (void *)*(size_t *)VectorGetAccessToElement(heap->vector, RightChild(current)), heap->param) <= 0
               ? LeftChild(current)
               : RightChild(current);
}

static void SwapPointersInArray(void *element1, void *element2)
{
    size_t tmp = *(size_t *)element1;
    *(size_t *)element1 = *(size_t *)element2;
    *(size_t *)element2 = tmp;
}
