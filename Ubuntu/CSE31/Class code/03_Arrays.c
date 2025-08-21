#include <stdio.h>

/* Title: Demo code for CSE 031 Lecture 05 (Spring 2025)
 * Author: Santosh Chandrasekhar
 *
 * This program produces a warning during compilation, but will run despite the warning.
 */

// Demonstrate how returning a locally declared array (or pointer) is problematic
char *getStr() { 
	char string[32]; // A locally declared array that we will attempt to return to main().
	//string = "I am fascinated by pointers!";	// Uncomment to observe error. This type of assignment cannot be done in C.
												// This is because string is a read-only pointer.
	printf("Enter your string: ");
	//scanf("%s", string); // Uncomment this line and comment next line to observe behavior. scanf only captures user input 
						   // till a whitespace (rest remains in stdin buffer)
	fgets(string, sizeof(string), stdin); // Captures string with whitespaces included
	printf("You entered: %s\n", string);
	return string;
}

// Demonstrate use of a pointer as an array
int strLen(char *s) { // Or you may use char s[] as the parameter
    int n = 0;
    while (s[n] != 0) n++; // Although s is a pointer, you may treat it as an array (of chars)
    return n;
}

int main() {
	char *string;
	//string = getStr(); // Problematic as the returned string no longer exists 
						 // due to the stack frame being popped. May cause a Segmentation fault. 
	string = "Hello, how are you?";
	printf("string: %s\n", string);
	int len = strLen(string);
	printf("Length of string: %d\n\n", len);

	const int AR_SIZE = 10; // Single source of truth. Good programming practice (but often not followed).
	int ar[AR_SIZE]; // Cannot assume array elements will be initializd to 0. Printing content should produce junk.
	printf("Size of array: %lu\n", sizeof(ar)); // Size of ar = AR_SIZE * sizeof(int)
	printf("Contents of ar (using [] and pointer deferencing): \n");
	for (int i = 0; i < AR_SIZE; ++i) { 
		// In the command below, %11d reserves a space of 11 digits to print each number that are all right-aligned.
		// You may change it to left alignment by changing it to %-11d
		printf("ar[%d]: %11d \t *(ar + %d): %11d\n", i, ar[i], i, *(ar + i)); // ar is nothing but a read-only pointer 
																			  // to the start of the array.	Since ar is 
																			  // not initialized, all elements will be junk.
	}

	//Demonstrate that C does not check array bounds. 
	printf("\nContents of ar (using [] and pointer deferencing) exceeding its defined length: \n");
	for (int i = 0; i < 20; ++i) { // Accessing 20 elements even though ar is defined with 10
		printf("ar[%d]: %11d \t *(ar + %d): %11d\n", i, ar[i], i, *(ar + i));
	}
	printf("\n");

	//ar = &AR_SIZE; // This will cause a compilation error since ar is a read-only pointer to the first array element
		
	// Demonstrate that one address past the end of array is always a valid address.
	int br[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, *p, *q, sum = 0;
	p = &br[0];		// Pointer to beginning of array
	q = &br[10];	// One address past the end of array is guaranteed to be valid
	while (p != q)		// Traverse array till the two pointers meet
		sum += *p++;	// Equivalent to sum = sum + *p; followed by p = p + 1;
	printf("Sum of elements of br = %d\n", sum);

	printf("\n");
	// Demonstrate that incrementing a pointer by 1 automatically increments the address stored in the pointer by the correct 
	// number of bytes (as per the datatype of variable being pointed to). E.g., if a pointer p points to an int, adding one 
	// increments the address stored in p by 4 as integers are 4 bytes.
	double cr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Each element is now 8-bytes
	for (int i = 0; i < AR_SIZE; ++i) // Initialize ar[]
		ar[i] = i + 1; 
	printf("Elements of ar (an int array) and cr (a double array) with their addresses: \n");
	for (int i = 0; i < AR_SIZE; ++i) { 
		printf("%d, %p\t", *(ar + i), (ar + i));	// addition of i is actually i*4
		printf("%.2f, %p\n", *(cr + i), (cr + i));	// addition of i is actually i*8
	}

	return 0;
}