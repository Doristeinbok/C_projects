#include <stdio.h>

#include "bst.h"


int is_bigger(const void *new_elem, const void *curr_elem, const void *param)
{
    (void)param;
    if (*(int*)new_elem > *(int*)curr_elem)
    {
        return 1;
    }
    else if (*(int*)new_elem < *(int*)curr_elem)
    {
        return -1;
    }
    return 0;
}

int PrintRange(void *data, const void *param)
{
    (void)param;
    printf("%d   ", *(int*)data);
    return 0;
}


int main()
{
    int num_30 = 30;
    int num_20 = 20;
    int num_40 = 40;
    int num_50 = 50;
    int num_10 = 10;
    int num_25 = 25;


    bst_t *new_bst = BstCreate(is_bigger, NULL);  
    
    bst_iter_t iter_30 = BstInsert(new_bst, &num_30);
    bst_iter_t iter_20 = BstInsert(new_bst, &num_20);
    bst_iter_t iter_40 = BstInsert(new_bst, &num_40);

    printf("size = %lu\n", BstSize(new_bst)); 
    BstForEach(iter_20, iter_40, PrintRange, "1");
 
    BstDestroy(new_bst);
    


    return 0;
}
