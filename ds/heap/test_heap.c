#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "heap.h"

static int CompareInt(const void *n1, const void *n2, const void *param);
static void test1();
static void test2();
static void test3();
static void test4();

static int MatchInt(const void *n1, const void *param);

int main()
{
	test1();
	test3();
	test2();
	test4();
	return 0;
}

static void test4()
{
	heap_t *heap = NULL;
	int b[100];
	size_t i;
	srand(0);
	heap = HeapCreate(CompareInt, NULL);

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();

		HeapPush(heap, &b[i]);
	}

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		if (b[i] != *(int *)HeapFind(heap, &b[i], MatchInt))
		{
			printf("fail in %d\n", __LINE__);
		}
	}

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		if (b[i] != *(int *)HeapRemove(heap, &b[i], MatchInt))
		{
			printf("fail in %d\n", __LINE__);
		}
	}
	HeapDestroy(heap);
}

static void test2()
{
	heap_t *heap = NULL;
	int b[100];
	size_t i;
	int min = 0;
	int temp = 1;
	srand(0);
	heap = HeapCreate(CompareInt, NULL);

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();
		if (0 == i)
		{
			min = b[0];
		}
		else if (b[i] < min)
		{
			min = b[i];
		}
		HeapPush(heap, &b[i]);
	}

	if (min != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}
	HeapPush(heap, &temp);
	if (temp != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}
	HeapPop(heap);

	if (min != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	for (i = 0; i < HeapSize(heap); ++i)
	{
		if (min > *(int *)HeapPeek(heap))
		{
			printf("fail in %d\n", __LINE__);
		}
		min = *(int *)HeapPeek(heap);

		HeapPop(heap);
	}

	HeapDestroy(heap);
}

static void test1()
{
	heap_t *heap = NULL;
	int test = 50;
	int test2 = 30;

	heap = HeapCreate(CompareInt, NULL);

	if (!HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (0 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapPush(heap, &test);

	if (test != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (1 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapPush(heap, &test2);

	if (test2 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (2 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (test != *(int *)HeapRemove(heap, &test, MatchInt))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (test2 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (1 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapDestroy(heap);
}

static void test3()
{
	heap_t *heap = NULL;
	int test2 = 30;
	int test1 = 50;
	int test3 = 0;
	int test4 = 4;
	int test5 = 7;
	int test6 = 9;
	int test7 = 70;
	int test8 = 1;

	heap = HeapCreate(CompareInt, NULL);
	HeapPush(heap, &test1);
	HeapPush(heap, &test2);
	HeapPush(heap, &test3);
	HeapPush(heap, &test4);
	HeapPush(heap, &test5);
	HeapPush(heap, &test6);
	HeapPush(heap, &test7);
	HeapPush(heap, &test8);

	if (0 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}
	HeapPop(heap);
	if (1 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}
	HeapDestroy(heap);
}

static int MatchInt(const void *n1, const void *param)
{
	return *(int *)n1 - *(int *)param;
}

static int CompareInt(const void *n1, const void *n2, const void *param)
{
	(void)param;
	return *(int *)n1 - *(int *)n2;
}
