#include <stdio.h>

#include "doubly_linked_list.h"


int PrintList(void *data, void *param);
int IsEqual(void *data, void *param);

void test1(void);
void test2(void);


int main()
{
    test1();
    test2();
    return 0;
}


void test1(void)
{
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    int num_4 = 4;
    int num_5 = 5;
    action_func_t action_func = PrintList;

    dlist_t *new_list = DListCreate();
    dlist_iter_t iter = DListBegin(new_list);
    DListInsert(iter, &num_1);
    DListInsert(iter, &num_2);
    DListInsert(iter, &num_3);
    DListInsert(iter, &num_4);

    DListForEach(DListBegin(new_list), DListEnd(new_list), action_func, &num_1);
    printf("NULL\n");

    if(4 != DListCount(new_list))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(1 != *(int*)DListIterGetData(DListBegin(new_list)))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(2 != *(int*)DListIterGetData(DListIterNext(DListBegin(new_list))))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(4 != *(int*)DListIterGetData(DListIterPrev(DListEnd(new_list))))
    {
        printf("error in line %d\n", __LINE__);
    }

    iter = DListIterNext(DListIterNext(DListBegin(new_list))); 
    iter = DListInsert(iter, &num_5);
    if(5 != *(int*)DListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }

    if(5 != DListCount(new_list))
    {
        printf("error in line %d\n", __LINE__);
    }

    DListRemove(iter);
    iter = DListIterNext(DListIterNext(DListBegin(new_list)));
    if(3 != *(int*)DListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }

    DListDestroy(new_list);

}



/**************************************************/


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
    
    action_func_t action_func = PrintList;
    match_func_t match_func = IsEqual;

    dlist_t *new_list = DListCreate();
    dlist_t *list_splice = DListCreate();
    dlist_iter_t iter = DListBegin(new_list);
    dlist_iter_t iter_splice = DListBegin(list_splice);

    DListInsert(iter, &num_1);
    DListInsert(iter, &num_2);
    DListInsert(iter, &num_3);
    DListInsert(iter, &num_4);

    DListInsert(iter_splice, &num_5);
    DListInsert(iter_splice, &num_6);
    DListInsert(iter_splice, &num_7);
    DListInsert(iter_splice, &num_8);


    DListForEach(DListBegin(new_list), DListEnd(new_list), action_func, &num_1);
    printf("NULL\n");

    iter = DListFind(DListBegin(new_list), DListEnd(new_list), match_func, &num_4);
    if(4 != *(int*)DListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }

    iter = DListFind(DListBegin(new_list), DListEnd(new_list), match_func, &num_2);
    if(2 != *(int*)DListIterGetData(iter))
    {
        printf("error in line %d\n", __LINE__);
    }


    /******************************* splice *******************************/    


    iter = DListIterNext(DListBegin(new_list));
    iter_splice = DListBegin(list_splice);
    DListSplice(iter, iter_splice, DListEnd(list_splice));

    DListForEach(DListBegin(new_list), DListEnd(new_list), action_func, &num_1);
    printf("NULL\n");
    


    DListDestroy(new_list);
    DListDestroy(list_splice);
}



/**************************************************/



int PrintList(void *data, void *param)
{
    (void)param;
    printf("%d -> ", *(int*)data);
    return 0;
}


int IsEqual(void *data, void *param)
{
    return *(int*)data == *(int*)param;
}











