#include <stdio.h>
#include "bit_array.h"


bitarray_t BitArraySetAll()
{
	bitarray_t arr = 1LU; 
	arr <<= 63;
	return (arr | (arr - 1LU));
}


bitarray_t BitArrayResetAll()
{
	return 0;
}


bitarray_t BitArraySetOn(bitarray_t array, size_t idx)
{
	bitarray_t arr_bit_on = (1LU << idx);
	return (arr_bit_on | array);
}


bitarray_t BitArraySetOff(bitarray_t array, size_t idx)
{
	if((array >> idx) & 1LU)
		{
		    return(array ^(1LU << idx));
		}
		return array;
}


bitarray_t BitArraySetBit(bitarray_t array, size_t idx, bitstate_t value)
{
	if(((array >> idx)&1LU) != value)
	{
		return(array ^(1LU << idx));
	}
	return array;
}


size_t BitArrayGetValue(bitarray_t array, size_t idx)
{
	bitarray_t mark_idx = 1LU << idx;
	return !!(array & mark_idx);
}


bitarray_t BitArrayFlip(bitarray_t array)
{
	bitarray_t flip_arr = ~array;
	return flip_arr; 
}

bitarray_t BitArrayMirror(bitarray_t array)
{
	bitarray_t reverse_array = array;
  	size_t count = 63;
	array >>= 1; 
	while(array)
	{
	   reverse_array <<= 1;       
	   reverse_array |= array & 1;
	   array >>= 1;
	   count--;
	}
	reverse_array <<= count;
	return reverse_array;
}
 

bitarray_t BitArrayRotR(bitarray_t array, size_t steps)
{
	return (array >> steps)|(array << (64 - steps));
}


bitarray_t BitArrayRotL(bitarray_t array, size_t steps)
{
	return (array << steps)|(array >> (64 - steps));
}


size_t BitArrayCountOn(bitarray_t array)
{
	size_t count = 0;
	while(array)
	{
		count += array & 1LU;
		array >>= 1LU;
	}
	return count;
}


size_t BitArrayCountOff(bitarray_t array)
{
	size_t count = 0;
	while(array)
	{
		count += (array & 1LU) ^ 1LU;
		array >>= 1LU;
	}
	return count;
}


char *BitArrayToString(bitarray_t array, char *dest)
{
	size_t i = 0;
    for(; i < 64LU; ++i)
    {
    	dest[63LU - i] = '0' + (1LU & array >> i);
    }
    return dest;
}


bitarray_t BitArrayToggleBit(bitarray_t array, size_t idx)
{
	return (array ^ (1LU << idx));
}





