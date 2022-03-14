#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h>


typedef enum { BIT_ON = 1, BIT_OFF = 0 } bitstate_t;

/* typedef to create a single unit to work with as an array - long isn't portable, need a different option*/
#ifdef ARCH32
/* can be supported only under c99 */
typedef unsigned long long bitarray_t;
#else
typedef unsigned long bitarray_t;
#endif


/* Sets all bits to 1 */
extern bitarray_t BitArraySetAll();

/* Sets all bits in arr to 0 */
extern bitarray_t BitArrayResetAll();

/* Set chosen bit to 1 */
extern bitarray_t BitArraySetOn(bitarray_t array, size_t idx); 

/* Set chosen bit to 0 */
extern bitarray_t BitArraySetOff(bitarray_t array, size_t idx);

/* Set chosen bit to value chosen */
extern bitarray_t BitArraySetBit(bitarray_t array, size_t idx, bitstate_t value);

/* What is the value of chosen bit? */
extern size_t BitArrayGetValue(bitarray_t array, size_t idx);

/* Toggles all bits */
extern bitarray_t BitArrayFlip(bitarray_t array);

/* Mirror bits in array */
extern bitarray_t BitArrayMirror(bitarray_t array);

/* Counts how many bits are on */
extern size_t BitArrayCountOn(bitarray_t array);

/* Counts how many bits are off */
extern size_t BitArrayCountOff(bitarray_t array);

/* Rotate array to the right by n steps */
extern bitarray_t BitArrayRotR(bitarray_t array, size_t steps);

/* Rotate array to the left by n steps */
extern bitarray_t BitArrayRotL(bitarray_t array, size_t steps);

/* copy to string */
extern char *BitArrayToString(bitarray_t array, char *dest);

/* Toggle bit */
extern bitarray_t BitArrayToggleBit(bitarray_t array, size_t idx);

/* count on bits using lookup table */
size_t BitArrayCountOnLut(bitarray_t array);

/* mirror using lookup table */
size_t BitArrayMirrorOnLut(bitarray_t array);

#endif

