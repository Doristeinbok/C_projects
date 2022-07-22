#include <stdio.h>

#include "avl.h"


static int CompFunc(const void *elem_1, const void *elem_2, const void *param)
{
	int a = *(int *)elem_1;
	int b = *(int *)elem_2;

	(void)param;

	if (a < b)
	{
		return -1;
	}
	else if (a == b)
	{
		return 0;
	}
	return 1;
}

int Print(void *data, const void *param)
{
    (void)param;
    if(data)
    {
        printf("%d  ", *(int*)data);
        return 0;
    }
    return 1;
}


int main()
{
    int num = 1;

    int num_30 = 30;
    int num_10 = 10;
    int num_50 = 50;
    int num_40 = 40;
    int num_60 = 60;
    int num_20 = 20;
    int num_5 = 5;
    int num_7 = 7;
    int num_6 = 6;

    avl_t *new_avl = AvlCreate(CompFunc, &num);
    AvlInsert(new_avl, &num_40); 
    AvlInsert(new_avl, &num_20); 
    AvlInsert(new_avl, &num_50);
    AvlInsert(new_avl, &num_30);
    AvlInsert(new_avl, &num_10);
    AvlInsert(new_avl, &num_60); 
    AvlInsert(new_avl, &num_5); 
    AvlInsert(new_avl, &num_7); 
    AvlInsert(new_avl, &num_6); 
    AvlFind(new_avl, &num_40);
    AvlFind(new_avl, &num_7);
    AvlFind(new_avl, &num_30);
    AvlFind(new_avl, &num_20); 
    
    printf("height = %lu\n", AvlHeight(new_avl));

    AvlForEach(new_avl, Print, &num, IN_ORDER);

    AvlRemove(new_avl, &num_20); 
    printf("\n");
    AvlForEach(new_avl, Print, &num, IN_ORDER);
    printf("\n");


    AvlDestroy(new_avl);

    printf("\n");
    AvlForEach(new_avl, Print, &num, IN_ORDER); 
/* 
    printf("\n");

    AvlForEach(new_avl, Print, &num, IN_ORDER);

    AvlRemove(new_avl, &num_30); 
    printf("\n");
    AvlForEach(new_avl, Print, &num, IN_ORDER);
    printf("\n"); */


/* 



 /* 

    printf("pre-order printing\n");
    AvlForEach(new_avl, Print, &num, PRE_ORDER);
    printf("\n");

    printf("post-order printing\n");
    AvlForEach(new_avl, Print, &num, POST_ORDER);
    printf("\n");

    printf("new_avl size is: %lu\n", AvlSize(new_avl));
  */

    /* printf("height = %lu\n", AvlHeight(new_avl)); */

    /* printf("AvlFind(new_avl, &num_1) = %d", *(int*)AvlFind(new_avl, &num_1)); */

    return 0;
}
