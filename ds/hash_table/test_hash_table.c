#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"


static int IsEqual(void *curr_data, void *requested_data);
static size_t HashFunc(const void *new_elem);
int Print(void *data, void *param);


int main()
{
    hash_t *new_hash = NULL;
    size_t size_of_index = 10;
    size_t size_to_check = 0;
    int num = 1;
    char *one = "one";
    char *two = "two";
    char *three = "three";
    char *four = "four";

    new_hash = HashCreate(HashFunc, IsEqual, size_of_index, &num);

    printf("HashIsEmpty should return 1 = %d\n", HashIsEmpty(new_hash)) ;

    HashInsert(new_hash, one);
    HashInsert(new_hash, two);
    HashInsert(new_hash, three); 
    HashInsert(new_hash, four); 

    printf("size = %lu\n", HashSize(new_hash));  

    HashRemove(new_hash, three);

    printf("size = %lu\n", HashSize(new_hash));  

    printf("HashIsEmpty should return 0 = %d\n", HashIsEmpty(new_hash)) ;

    printf("find returned: %s\n", (char*)HashFind(new_hash, two));

    HashForEach(new_hash, Print, &num); 


    HashDestroy(new_hash);


    return 0;
}



/* --------------------helper functions--------------------------  */



int IsEqual(void *curr_data, void *requested_data)
{
    return !strcmp(curr_data, requested_data);
}


static size_t HashFunc(const void *new_elem)
{
	size_t res = 0;
	char *str = (char *)new_elem;
	while (*str)
	{
		res += (size_t)*str;
		++str;
	}
	return res;
}


int Print(void *data, void *param)
{
	(void)param;
	printf("%s, ", (char*)data);
	return 0;    
}
