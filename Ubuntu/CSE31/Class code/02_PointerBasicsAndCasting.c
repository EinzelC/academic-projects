#include <stdio.h>

/* Title: Demo code for CSE 031 Lecture 04 (Spring 2025)
 * Author: Santosh Chandrasekhar
 * 
 * This program produces 4 warnings during compilation, but will run despite the warnings.
 */

int main() {
	
	int *ptr, x = 3;
	printf("Size of ptr: %lu\n\n", sizeof(ptr));
	//printf("*ptr before allocation: %d\n", *ptr); // Unexpected behavior. Can cause segmentation fault.
	
	ptr = &x; // ptr now points to x.
	printf("x = %d\n", x); // Value of x.
	printf("&x = %p\n", &x); // Address of x.
	printf("*ptr = %d\n", *ptr); // Getting the value of x by dereferencing the pointer to x.
	printf("ptr = %p\n", ptr); // Value stored in pointer (address of x).
	
	*ptr = 5; // Manipulating value of x using the pointer. Same as x = 5; 
	printf("*ptr = %d\n", *ptr); // Getting the new value of x by dereferencing the pointer to x.
	printf("x = %d\n", x); // Verify that x's value indeed changed to 5.

	printf("&ptr = %p\n", &ptr); // Pointers themselves have an address!
	int **z = &ptr; // Double pointers can point to pointers.
	printf("z = %p\n", z); // Getting the address of ptr.
	printf("*z = %p\n", *z); // Getting the address stored in ptr.
	printf("**z = %d\n", **z); // Getting the value of x by dereferencing the double pointer.
	printf("\n");

	float f = 1.2f; 
	float *fptr = &f; // A float pointer is only meant to point to a float data type 
	printf("*fptr (pointing to a float) = %.2f\n", *fptr); // The .2 in the %.2f is forcing the output to contain 2 digits after the decimal point.
	char chr = 'A';
	fptr = &chr; // Float pointer can be made to point to a char variable, but this will produce a warning 
	printf("*fptr (pointing to a char) = %c\n", *fptr); // Meaningless 
	char *cptr = &chr;
	printf("*cptr (pointing to a char) = %c\n", *cptr); // Expected behavior
	
	void *vptr; // A void pointer can be made to point to anything.
	vptr = &f; // Here a void pointer is made to point to a float
	//printf("*vptr (pointing to a float) = %.2f\n", *vptr); // Wrong way to dereference a void pointer. Will cause compilation error.
	printf("*vptr (pointing to a float) = %.2f\n", *((float *)vptr)); // Need to first cast a void pointer to a float pointer before dereferencing it as a float
	vptr = &chr; // Here a void pointer is made to point to a char
	printf("*vptr (pointing to a char) = %c\n", *((char *)vptr)); // Here we need to cast the same void pointer to a char pointer before dereferencing it as a char
	printf("\n");

	int num = 1000;
	int *p1 = num; // Meaningless (your code should not have access to address 1000 or 0x3e8 in hex). Will produce a warning due to incompatible types.
	printf("p1 = %p\n", p1); // Should print 0x3e8, which is 1000 in hex
	//printf("*p1 = %d\n", *p1); // Will cause segmentation fault at runtime.
	
	int *p2 = (int *) num; // Meaningless again. Will produce a warning due to incompatible types.
	printf("p2 = %p\n", p2);  // Should print 0x3e8, which is 1000 in hex
	//printf("*p2 = %d\n", *p2); // Will cause segmentation fault at runtime.
	
	int *p3;
	printf("\np3 = %p\n", p3); // Unexpected behavior. Might print 0x0 or some random address.
    *p3 = 5; // Unexpected behavior. Can cause segmentation fault.
    printf("*p3 = %d\n", *p3); // Unexpected behavior. Can cause segmentation fault or print 5.

	return 0;
}
