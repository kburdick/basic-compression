/**************************************************************************
 *
 * File: compress.c
 * Author: Kurt Burdick
 *
 * Purpose: Extra functions for practicum 1
 *	- the packing a unpacking of 4 integers into one int, and vice
 *	versa is done with these functions.
 *
 * - Required to have two separate files that compile together for the
 *	practicum.
 *
 *************************************************************************/


#include <stdio.h>

// define bit shift sizes for int packing/unpacking
#define SHIFT8  8
#define SHIFT16 16
#define SHIFT24 24


/************************************
 *
 * Description: This function packs 4 integers into a single int
 *
 * Input:
 *	arrIn - the array filled with regular ints that will populate the
 *		unsigned packed integer.
 *
 *	storeInt - the integer that will contain all four integers when the
 * 		function returns.
 *
 * Output:
 *	storeInt - one unsigned integer value
 *
 * Variables:
 *	int *tempPtr - keeps track of the position in the input array
 *
 ************************************/
unsigned int pack(int *arrIn, unsigned int storeInt){

	int *tempPtr = arrIn;

	*tempPtr = *tempPtr << SHIFT24;
	storeInt = *tempPtr | storeInt;
	tempPtr++;

	*tempPtr = *tempPtr << SHIFT16;
	storeInt = *tempPtr | storeInt;
	tempPtr++;

	*tempPtr = *tempPtr << SHIFT8;
	storeInt = *tempPtr | storeInt;
	tempPtr++;

	storeInt = *tempPtr | storeInt;

	return storeInt;
}



/*****************************************
 *
 * Description: This function unpacks previously packed unsigned integers
 * 	into their original input values
 *
 * Input:
 *	unpackInt - the unsigned integer to unpack into 4 integer values
 *
 * Output:
 *	print the four original decimal numbers as they were entered
 *		before compression took place.
 *
 * Variables:
 *	int result - the resulting decimal integer
 *
 *	int mask - a bit mask to filter out unwanted values when
 *		bit shifting for the original decimal integers
 *
 ****************************************/
void unpack(unsigned int unpackInt){

	int result = 0;
	int mask = 0xFF;

	result = mask & (unpackInt >> SHIFT24);
	printf("val1: %d\n", result);

	result = mask & (unpackInt >> SHIFT16);
	printf("val2: %d\n", result);

	result = mask & (unpackInt >> SHIFT8);
	printf("val3: %d\n", result);

	result = mask & unpackInt;
	printf("val4: %d\n", result);

}
