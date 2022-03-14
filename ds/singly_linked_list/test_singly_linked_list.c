#include <stdio.h>

#include "singly_linked_list.h"


int PrintList(void *data, void *param);
int IsEqual(const void *data, void *param);


void test(void);

int main()
{
    test();
    return 0;
}



/**************************************************/



void test(void)
{
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    int num_4 = 4;
    action_func_t print = PrintList;
    match_func_t match_func = IsEqual;

    slist_t *new_list = SListCreate();
    slist_iter_t iter = SListBegin(new_list);
    slist_iter_t iter_test = SListBegin(new_list);


    /* insert 4 integers */


    SListInsert(iter, &num_4);
    SListInsert(iter, &num_3);
    SListInsert(iter, &num_2);
    SListInsert(iter, &num_1);

    if(4 != SListCount(new_list))
    {
        printf("error in line %d\n", __LINE__);
    }

    iter_test = SListBegin(new_list);
    
    if(1 != *(int*)SListIterGetData(iter_test))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(1 != SListIterIsEqual(iter_test, SListBegin(new_list)))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(0 != SListIterIsEqual(iter_test, SListIterNext(SListBegin(new_list))))
    {
        printf("error in line %d\n", __LINE__);
    }

    SListForEach(SListBegin(new_list), SListEnd(new_list), print, &num_1);
    printf("NULL\n");


    /* remove 2*/


    SListRemove(SListIterNext(iter_test));

    if(3 != SListCount(new_list))
    {
        printf("error in line %d\n", __LINE__);
    }
    SListForEach(SListBegin(new_list), SListEnd(new_list), print, &num_1);
    printf("NULL\n");


    iter_test = SListFind(SListBegin(new_list), SListEnd(new_list), match_func, &num_3);
    if(3 != *(int*)SListIterGetData(iter_test))
    {
        printf("error in line %d\n", __LINE__);
    }

    iter_test = SListFind(SListBegin(new_list), SListEnd(new_list), match_func, &num_2);
    if(NULL != SListIterGetData(iter_test))
    {
        printf("error in line %d\n", __LINE__);
    }

    SListDestroy(new_list);
}



/****************************************************/



int PrintList(void *data, void *param)
{
    (void)param;
    printf("%d -> ", *(int*)data);
    return 1;
}


int IsEqual(const void *data, void *param)
{
    return *(int*)data == *(int*)param;
}








