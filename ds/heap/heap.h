#ifndef __HEAP_H__
#define __HEAP_H__
#include <stddef.h> /*for size_t*/

typedef int (*cmp_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*is_match_func_t)(const void *curr_item, const void *param);

typedef struct Heap heap_t;

extern heap_t *HeapCreate(cmp_func_t compare, const void *param);

extern void HeapDestroy(heap_t *heap);

/* returns 0 if success, 1 if failed*/
extern int HeapPush(heap_t *heap, const void *data);

extern void HeapPop(heap_t *heap);

extern void *HeapPeek(heap_t *heap);

/* 1 if empty, 0 if not*/
extern int HeapIsEmpty(const heap_t *heap);

extern size_t HeapSize(const heap_t *heap);

extern void *HeapRemove(heap_t *heap, const void *data, is_match_func_t is_match);

extern void *HeapFind(const heap_t *heap, const void *data, is_match_func_t is_match);

#endif
