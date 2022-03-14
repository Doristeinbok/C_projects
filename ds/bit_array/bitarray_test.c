#include <stdio.h>
#include "bit_array.h"


int main() {

	if(BitArraySetAll() != 0xFFFFFFFFFFFFFFFF)
	{
		long ans = (long)BitArraySetAll();
		printf("BitArraySetAll has failed!\n");
		printf("returns %ld\n\n", ans);
	};
	
	if(BitArrayResetAll() != 0)
	{
		printf("BitArrayResetAll has failed!\n");
	};
	
	if(BitArraySetOn(9,1) != 11)
	{
		printf("BitArraySetOn has failed!\n");
	};
	
	if(BitArraySetOff(9,3) != 1)
	{
		printf("BitArraySetOff has failed!\n");
	};
	
	if(BitArraySetBit(9,1,1) != 11)
	{
		printf("BitArraySetBit has failed!\n");
	};
	
	
	if(BitArrayGetValue(9,3) != 1)
	{
		printf("BitArrayGetValue has failed!\n");
	};
	
	
	if(BitArrayFlip(9) != 18446744073709551606LU)
	{
		printf("BitArrayFlip has failed!\n");
	};
	
	
	if(BitArrayMirror(128) != 72057594037927936)
	{
		printf("BitArrayMirror has failed!\n");
	};
	
	
	/* test for BitArraySetAll */
	
	if(BitArraySetOff(9,3) != 1)
	{
		printf("BitArraySetOff has failed!\n");
	};
	
	return 0;
}







