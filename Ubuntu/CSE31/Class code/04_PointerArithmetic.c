#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

/* Title: Demo code for CSE 031 Lecture 05 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

int main() {

	int i; 
	int a[5];
	for (i = 0; i < 5; ++i) *(a + i) = 2 * i; // Initialize array
	int *p = a;

	printf("Elements of p[] and their addresses: \n");
	for (i = 0; i < 5; ++i) printf("%d @ %p\n", *(p + i), (p + i)); 
	printf("\n");
	
	int x;
	int *q = p; // Remember where p points to at the start (we'll be resetting p later)
	
	// See Slide 11 of Lecture 05 for meaning of what these commands do.
	x = *(p + 1); printf("x = *(p + 1): %-5d \t p: %p\n", x, p); 
	x = *p + 1; printf("x = *p + 1: %-5d \t p: %p\n", x, p);
	x = (*p)++; printf("x = (*p)++: %-5d \t p: %p\n", x, p);	// x = *p; *p = *p + 1;
															// Changes content of array at index 0
	x = *p++; printf("x = *p++: %-5d \t p: %p\n", x, p); // x = *p; p = p + 1;
	x = *(p++); printf("x = *(p++): %-5d \t p: %p\n", x, p); // x = *p; p = p + 1;
	x = *(p)++; printf("x = *(p)++: %-5d \t p: %p\n", x, p); // x = *p; p = p + 1;
	x = *++p; printf("x = *++p: %-5d \t p: %p\n", x, p); // p = p + 1; x = *p; 
	x = ++*p; printf("x = ++*p: %-5d \t p: %p\n", x, p); // *p = *p + 1; x = *p;
														// Changes content of array at index 3 
	p = q;	// Reset p to point to the beginning
	printf("\nContents of p[]: ");
	for (i = 0; i < 5; ++i) printf("%d ", *(p + i));
	printf("\n");

	return 0;
}
