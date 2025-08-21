#include <stdio.h>
#include <stdlib.h>

 int main() {
	int num;
	int *ptr;
	int **handle;

	num = 14;
	ptr = (int *) malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **) malloc(1 * sizeof(int *));
	*handle = ptr;

	// Print variables and their addresses
    printf("Address of num: %p, Value of num: %d\n", (void *)&num, num);
    printf("Address of ptr: %p, Value of ptr: %p\n", (void *)&ptr, (void *)ptr);
    printf("Address of handle: %p, Value of handle: %p\n", (void *)&handle, (void *)handle);

    printf("Value pointed to by ptr: %d\n", *ptr);

    printf("Value pointed to by handle: %p\n", (void *)*handle);

    printf("Value pointed to by the pointer stored in handle: %d\n", **handle);

    free(ptr);
    free(handle);

	return 0;
} 

