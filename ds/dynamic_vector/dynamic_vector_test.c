#include <stdio.h>
#include "dynamic_vector.h"
#include <string.h>

static void test0();
void test1();
void test2();
void test3();

int main()
{
    test0();
    test1();
    test2();
    test3(); 
    return 0;
}

static void test0()
{
    Vector_t *vector = VectorCreate(1, sizeof(int));
    int a = 5;
    int b = 10;
    VectorPushBack(vector, &a);
    VectorPushBack(vector, &b);
    if (!(5 == *(int *)VectorGetAccessToElement(vector, 0)))
    {
        printf("fail in %d\n", __LINE__);
    }
    if (!(10 == *(int *)VectorGetAccessToElement(vector, 1)))
    {
        printf("fail in %d\n", __LINE__);
    }
    VectorDestroy(vector);
}

void test1()
{
    Vector_t *vector = VectorCreate(10, sizeof(int));
    int a = 4;
    int b = 50;
    int c = -23;

    VectorPushBack(vector, &a);
    if (!(4 == *(int *)VectorGetAccessToElement(vector, 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(10 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(1 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &b);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(50 == *(int *)VectorGetAccessToElement(vector, 1)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &c);

    if (!(3 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(-23 == *(int *)VectorGetAccessToElement(vector, 2)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(50 == *(int *)VectorGetAccessToElement(vector, 1)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(4 == *(int *)VectorGetAccessToElement(vector, 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 5);

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &c);

    if (!(-23 == *(int *)VectorGetAccessToElement(vector, 2)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 100);

    if (!(100 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);


    if (!(50 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorDestroy(vector);
}

void test2()
{
    Vector_t *vector = VectorCreate(10, sizeof(long));
    long a = 4;
    long b = 50;
    long c = -23;

    VectorPushBack(vector, &a);
    if (!(4 == *(long *)VectorGetAccessToElement(vector, 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(10 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(1 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &b);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(50 == *(long *)VectorGetAccessToElement(vector, 1)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &c);

    if (!(3 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(-23 == *(long *)VectorGetAccessToElement(vector, 2)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(50 == *(long *)VectorGetAccessToElement(vector, 1)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(4 == *(long *)VectorGetAccessToElement(vector, 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 5);

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, &c);

    if (!(-23 == *(long *)VectorGetAccessToElement(vector, 2)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 100);

    if (!(100 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);


    if (!(50 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorDestroy(vector);
}

void test3()
{
    Vector_t *vector = VectorCreate(10, 20);
    char *a = NULL;
    char *b = NULL;
    char *c = NULL;

    a = (char *)calloc(20, sizeof(char));
    if (!a)
    {
        return;
    }
    strcpy(a, "Hello world!");

    b = (char *)calloc(20, sizeof(char));
    if (!b)
    {
        return;
    }
    strcpy(b, "Dumbeldore");
    c = (char *)calloc(20, sizeof(char));
    if (!c)
    {
        return;
    }
    strcpy(c, "Harry Potter");

    VectorPushBack(vector, a);
    if (!((strncmp((char *)VectorGetAccessToElement(vector, 0), "Hello world!", 12) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(10 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(1 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, b);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!((strncmp((char *)VectorGetAccessToElement(vector, 1), "Dumbeldore", 10) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, c);

    if (!(3 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!((strncmp((char *)VectorGetAccessToElement(vector, 2), "Harry Potter", 12) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!((strncmp((char *)VectorGetAccessToElement(vector, 1), "Dumbeldore", 10) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!((strncmp((char *)VectorGetAccessToElement(vector, 0), "Hello world!", 12) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 5);

    if (!(5 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPushBack(vector, c);

    if (!((strncmp((char *)VectorGetAccessToElement(vector, 2), "Harry Potter", 12) == 0)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorReserve(vector, 100);

    if (!(100 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    VectorPopBack(vector);

    if (!(50 == VectorCapacity(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(2 == VectorSize(vector)))
    {
        printf("fail in %d\n", __LINE__);
    }

    free(a);
    a = NULL;
    free(b);
    b = NULL;
    free(c);
    c = NULL;
    VectorDestroy(vector);
}
