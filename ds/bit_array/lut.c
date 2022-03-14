#include <stdio.h>
#include "bit_array.h"


static const unsigned char COUNT_TABLE[16] =
    {
    0, 1, 1, 2,
    1, 2, 2, 3,
    1, 2, 2, 3,
    2, 3, 3, 4
    };


static const unsigned char MIRROR_TABLE[16] =
    {
    0x0, 0x8, 0x4, 0xC,
    0x2, 0xA, 0x6, 0xE,
    0x1, 0x9, 0x5, 0xD,
    0x3, 0xB, 0x7, 0xF 
    };
    
    
size_t BitArrayCountOnLut(bitarray_t array)
{
    size_t i = 0;
    size_t count = 0;

    for(; i < 64; i +=4)
    {
        count += COUNT_TABLE[(array >> i) & 0xF];
    }
    return count;
}


size_t BitArrayMirrorOnLut(bitarray_t array)
{
    size_t i = 0;
    size_t mirror = 0;

    for(; i < 64; i +=4)
    {
    	mirror <<= 4;
        mirror |= MIRROR_TABLE[(array >> i) & 0xF];
    }
    return mirror;
}

