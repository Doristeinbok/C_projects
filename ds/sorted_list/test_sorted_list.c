#include <stdio.h>

#include "sorted_list.h"



int IsLower(const void *new_elem, const void *curr_elem, const void *param);
int PrintList(void *data, void *param);
int match_func(void *data, void *param);


void test1(void);
void test2(void);



int main()
{
    test1();
    test2();
    return 0;
}



/************************************/



void test1(void)
{
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    int num_4 = 4;
    action_func_t print = PrintList;
    sorted_list_t *new_list = SortedListCreate(IsLower, &num_1);
    sorted_list_iter_t iter = SortedListBegin(new_list);
    SortedListInsert(new_list, &num_3);
    SortedListInsert(new_list, &num_2);
    SortedListInsert(new_list, &num_1);
    SortedListInsert(new_list, &num_4);

    printf("*******************test 1*******************\n");
    SortedListForEach(SortedListBegin(new_list), SortedListEnd(new_list), print, &num_1);
    printf("NULL\n");

    if(1 != *(int*)SortedListIterGetData(SortedListBegin(new_list)))
    {
        printf("error in line %d\n", __LINE__);
    }

    SortedListRemove(SortedListBegin(new_list));
    if(2 != *(int*)SortedListIterGetData(SortedListBegin(new_list)))
    {
        printf("error in line %d\n", __LINE__);
    }
    
    iter = SortedListFind(SortedListBegin(new_list), SortedListEnd(new_list), &num_3);
    if(3 != *(int*)SortedListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }

    iter = SortedListFind(SortedListBegin(new_list), SortedListEnd(new_list), &num_1);
    if(NULL != SortedListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }

    SortedListForEach(SortedListBegin(new_list), SortedListEnd(new_list), print, &num_1);
    printf("NULL\n");


    iter = SortedListFindIf(SortedListBegin(new_list), SortedListEnd(new_list), match_func, &num_1);
    if(2 != *(int*)SortedListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }


    SortedListDestroy(new_list);
}



/************************************/



void test2(void)
{
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    int num_4 = 4;
    int num_5 = 5;
    int num_6 = 6;
    int num_7 = 7;
    int num_8 = 8;

    action_func_t print = PrintList;
    sorted_list_t *new_list = SortedListCreate(IsLower, &num_1);
    sorted_list_t *list_to_merge = SortedListCreate(IsLower, &num_1);

    SortedListInsert(new_list, &num_6);
    SortedListInsert(new_list, &num_4);
    SortedListInsert(new_list, &num_8);
    SortedListInsert(new_list, &num_1);

    SortedListForEach(SortedListBegin(new_list), SortedListEnd(new_list), print, &num_1);
    printf("NULL\n");

    SortedListInsert(list_to_merge, &num_2);
    SortedListInsert(list_to_merge, &num_7);
    SortedListInsert(list_to_merge, &num_3);
    SortedListInsert(list_to_merge, &num_5);

    printf("*******************test 2*******************\n");
    SortedListForEach(SortedListBegin(list_to_merge), SortedListEnd(list_to_merge), print, &num_1);
    printf("NULL\n");

    new_list = SortListMerge(new_list, list_to_merge);
    SortedListForEach(SortedListBegin(new_list), SortedListEnd(new_list), print, &num_1);
    printf("NULL\n");


    SortedListDestroy(new_list);
    SortedListDestroy(list_to_merge);
}



/************************************/



int IsLower(const void *new_elem, const void *curr_elem, const void *param)
{
    (void)param;
    return *(int*)new_elem < *(int*)curr_elem;
}


int PrintList(void *data, void *param)
{
    (void)param;
    printf("%d -> ", *(int*)data);
    return 0;
}


int match_func(void *data, void *param)
{
    if(*(int*)data > *(int*)param)
    {
        return 1;
    }

    else if(*(int*)data < *(int*)param)
    {
        return -1;
    }

    else
    {
        return 0;
    }
}




