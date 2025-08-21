#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Title: Demo code for CSE 031 Lecture 07 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

#ifndef SIZE
#define SIZE 20 
#endif

//const int SIZE = 20; //You may also use this instead of the macro declaration

int main() {
	int i = 0;
	
	int *ar, br[SIZE]; // SIZE = 20
	ar = (int *) malloc(SIZE * sizeof(int));
	printf("size of int: %lu\n", sizeof(int));
	printf("size of ar[]: %lu, size of br[]: %lu\n", sizeof(ar), sizeof(br)); 
	
	printf("ar[] (malloc): ");
	for(i = 0; i < SIZE; i++) printf("%d ", ar[i]); // Though this prints 0, it is NOT initialized (this is a misconception).
													// Code below with pointer k demonstrates this fact.
	printf("\n");
	printf("br[] (array): ");
	for(i = 0; i < SIZE; i++) printf("%d ", br[i]); // Should print junk values (not initialized)
	
	printf("\n\n");

	int *arr = (int*) malloc(SIZE * sizeof(int)); 
	for(i = 0; i < SIZE; ++i) arr[i] = i + 1; // Initialize arr
	printf("arr[] (malloc): ");
	for(i = 0; i < SIZE; i++) printf("%d ", arr[i]); // Print arr's contents
	printf("\n");
	
    free(arr); // Release and free the memory pointed by arr
    //free(arr); // Uncomment at your own risk. This should cause a runtime error

    int x = 11; // arr is not destroyed after freeing. It is just a pointer, so it can now be made to point to something else
    arr = &x; 
    printf("arr: %d\n", arr[0]);  // Or use *arr, or *(arr + 0) instead of arr[0]

    int* k = (int*) malloc(SIZE * sizeof(int)); // Dynamically allocate memory to another pointer
    // memset(k, 0, SIZE*sizeof(int)); // One way to initialize dynamically allocated array k to all 0's besides using a for-loop
    printf("k[] (re-malloc): ");
    for(i = 0; i < SIZE; i++) printf("%d ", k[i]);	// Might see "left-over" values that were initialized in line 33 (unless you
    												// uncomment line 46)
	printf("\n");
	
	return 0;
}