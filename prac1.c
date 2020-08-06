/**************************************************************************
 *
 * File: prac1.c
 * Author: Kurt Burdick
 *
 * Created: 3/16/2020
 * modified: 3/30/2020
 *
 * Purpose: Understand basic file compression using bit shifting and masks
 *	The progam will...
 *	- take decimal integers input from the user and pack them into
 *	unsigned int(s) in order to demand less space for the storage of
 *	all the integers. And will also unpack them to return the original
 * 	values that the user input. This will be completed by understanding
 * 	file compression techniques, bit shifting, and masks in C.
 *
 * Algorithm:
 *	a) Ask user to enter 16 decimal integers, less than 256.
 *	b) Store ints in a dynamically allocated array.
 *	c) Pack each number into an unsigned integer.
 *	d) If the user input more than four numbers, add the decimal ints
 *		into multiple unsigned ints.
 *	e) Reverse the integer packing to return the original integers,
 *		from the unsigned ints that were created.
 *	f) Print the packed integers and the corresponding decimal int for
 *		each packed integer.
 *	g) Repeat the above process until the user quits.
 *
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE 	 sizeof(CHAR_BIT)
#define LOWDIGIT 15
#define DIG 	 20

#define CHAR 	'0'
#define OFFSET 	'7'

#define HIGHINT 255
#define LOWINT 	0

#define UPPER 16
#define LOWER 1

#define CONT1 'y'
#define CONT2 'Y'


// forward declaraing other functions
unsigned int pack(int *arrIn, unsigned int storeInt);
void unpack(unsigned int unpackInt);

/****************************************************************
 *
 * Description: This function converts integers to hexadecimal notaion
 *	without using standard library, or printf format specifiers
 *
 * Input:
 *	- register int x - a decimal format integer
 *
 * Output:
 *	- output to console in the form of putchar with coverted
 *		hexadecimal output
 *
 * Variables:
 *	int i - to increment array of chars.
 *
 *	char s[] - array of characters to output hexadecimal string
 *
 *
 * Constants:
 * 	constants used to define character conversion, and offsets,
 *	for the hexadecimal values 1 - 9, and A - F, using ascii
 *	character conversion.
 *
 ****************************************************************/
void printHex(register int x)
{

	register int i = 0;

	char s[DIG];

	// add minus sign if int is negative
	if( x < 0)
	{
		x = -x;
	}

	do{

		// hex 9 - 10 number to letter transition
		if( (x & LOWDIGIT) <= 9)
		{
			s[i++] = (( x & LOWDIGIT) + CHAR);
		}

		if( (x & LOWDIGIT) >= 10)
		{
			s[i++] = ((x & LOWDIGIT) + OFFSET);
		}


	}while ( (x >>= 4) > 0);


	do{
		putchar(s[--i]);

	}while (i > 0);

	putchar('\n');
}



// main execution of the data compression program
int main()
{

	// define variables
	int *arr1, input, *temp, *temp2, *temp3, *temp4, *temp5, *tmpPtr;;
	unsigned int packTest1, packTest2, packTest3, packTest4;

	// while loop character
	char contChar = 'y';

	while(contChar == 'y' || contChar == 'Y'){


		printf("Enter the number of integers to compress (1 - 16): \n");
		scanf(" %d", &input);

		// error checking
		if(input < LOWER || input > UPPER)
		{
			fprintf(stderr, "invalid input range.\n");
			exit(1);
		}

		// create dynamic integer array
		arr1 = (int *)malloc(UPPER * SIZE);
		tmpPtr = arr1;

		for(int i = 0; i < UPPER; i++){
			*tmpPtr = 0;
			tmpPtr++;
		}

		temp = arr1;
		temp2 = arr1;
		temp3 = arr1;
		temp4 = arr1;
		temp5 = arr1;

		printf("\nEnter the decimal numbers to compress: \n");

		int i = 0;
		int test;

		while(i < input)
		{

			scanf(" %d", &test);
			printf("\n");

			if(test >= LOWINT && test <= HIGHINT)
			{
				*temp = test;
				temp++;
				i++;
			}
			else
			{
				printf("enter a value from 0 - 255, inclusive\n");
			}
		}

		// print the ints in the new array to make sure input is correct
		for(int j = 0; j < input; j++)
		{
			printf("arr[%d] : %d\n", j, *temp5);
			temp5++;
		}


		// variable that lets us know how many times we have to call the unpack function for unsigned ints made
		int packedInts = 0;

		packTest1 = 0;
		packTest2 = 0;
		packTest3 = 0;
		packTest4 = 0;

		printf("\n Packing integers to save space...\n");
		printf(" (four ints are packed into one)\n");

		// pack integers lcgic
		if(input <= 4)
		{
			packTest1 = pack(arr1, packTest1);

			printf("\n");

			printf("int1, int form: %d\nhex1, hex form: ", packTest1);
			printHex(packTest1);

			packedInts = 1;
		}

		else if(input <= 8 && input >= 5)
		{

			// update pointer for next int
			for(int i = 0; i < 4; i++){
				temp2++;
			}

			// call integer packing functions
			packTest1 = pack(arr1, packTest1);
			packTest2 = pack(temp2, packTest2);

			printf("\n");

			printf("int1, int form: %d\nhex1, hex form: ", packTest1);
			printHex(packTest1);

			printf("\n");

			printf("int2, int form: %d\nhex2, hex form: ", packTest2);
			printHex(packTest2);

			printf("\n");

			// set packed int number
			packedInts = 2;

			// set temp pointer back to arr1
			temp2 = arr1;
		}

		else if(input <= 12 && input >= 9)
		{

			for(int i = 0; i < 4; i++){
				temp2++;
			}
			for(int j = 0; j < 8; j++){
				temp3++;
			}

			packTest1 = pack(arr1, packTest1);
			packTest2 = pack(temp2, packTest2);
			packTest3 = pack(temp3, packTest3);

			printf("\n");

			printf("int1, int form: %d\nhex1, hex form: ", packTest1);
			printHex(packTest1);

			printf("\n");

			printf("int2, int form: %d\nhex2, hex form: ", packTest2);
			printHex(packTest2);

			printf("\n");

			printf("int3, int form: %d\nhex3, hex form: ", packTest3);
			printHex(packTest3);

			printf("\n");

			// set packed in number
			packedInts = 3;

			// reset temp pointers
			temp2 = arr1;
			temp3 = arr1;
		}

		else if(input >= 13 && input <= 16)
		{
			for(int i = 0; i < 4; i++){
				temp2++;
			}
			for(int j = 0; j < 8; j++){
				temp3++;
			}
			for(int k = 0; k < 12; k++){
				temp4++;
			}

			// call pack int function
			packTest1 = pack(arr1, packTest1);
			packTest2 = pack(temp2, packTest2);
			packTest3 = pack(temp3, packTest3);
			packTest4 = pack(temp4, packTest4);

			printf("\n");

			printf("int1, int form: %d\nhex1, hex form: ", packTest1);
			printHex(packTest1);

			printf("\n");

			printf("int2, int form: %d\nhex2, hex form: ", packTest2);
			printHex(packTest2);

			printf("\n");

			printf("int3, int form: %d\nhex3, hex form: ", packTest3);
			printHex(packTest3);

			printf("\n");

			printf("int4, int form: %d\nhex4, hex form: ", packTest4);
			printHex(packTest4);

			printf("\n");

			// set packed ints number
			packedInts = 4;

			//reset temp pointers
			temp2 = arr1;
			temp3 = arr1;
			temp4 = arr1;
		}


		printf("\n unpacking storage integers...\n");

		// unpacking storage integer logic
		if(packedInts == 1)
		{
			unpack(packTest1);
		}
		if(packedInts == 2)
		{
			unpack(packTest1);
			printf("\n");
			unpack(packTest2);
		}
		if(packedInts == 3)
		{
			unpack(packTest1);
			printf("\n");
			unpack(packTest2);
			printf("\n");
			unpack(packTest3);
		}
		if(packedInts == 4)
		{
			unpack(packTest1);
			printf("\n");
			unpack(packTest2);
			printf("\n");
			unpack(packTest3);
			printf("\n");
			unpack(packTest4);
		}

		// free allocated memory for the array
		free(arr1);

		// main while loop prompt
		printf("\nPlease enter %c or %c to continue, or another char to exit:\n", CONT1, CONT2);
		scanf(" %c", &contChar);

		printf("\n");
	}


	return 0;
}
