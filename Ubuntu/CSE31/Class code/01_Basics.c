#include <stdio.h>
#include <stdbool.h>

/* Title: Demo code for CSE 031 Lecture 02 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

int main(int argc, char *argv[]) {

	printf("argc = %d\n", argc); // Prints the number of command line arguments (including the executable)
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d] = %s\n", i, argv[i]); // Should print the command line arguments
	}		
	
	printf("\n");

	FILE *pfile;
    int i;
    unsigned char ch;
    pfile = fopen(argv[1], "r"); // Filename should be passed as a command line argument
    							 // (otherwise this will cause a segmentation fault)
    
    for (i=0; ; i++) {
        if (fscanf(pfile, "%c", &ch) == EOF) break;
        printf("%c", ch);
    }
    
    fclose (pfile); 

	printf("\n\n");

	if(-46)	// Any non-zero value is treated as true
		printf("Hello!\n");

	bool bvar = true; // This datatype requires the use of stdbool.h
	printf("Boolean variable bvar = %d\n\n", bvar); // Should print 1 (or 0 if bvar = false)

	char c = 'a';
	int  x = 34;
	int  y[4];
	long z;
	printf("sizeof(c)    = %lu\n", sizeof(c));		// %d - int, %c - char, %lu - long unsigned, etc.
	printf("sizeof(char) = %lu\n", sizeof(char));	// For a full list of format specifiers
	printf("sizeof(x)    = %lu\n", sizeof(x));		// see https://www.cplusplus.com/reference/cstdio/printf/
	printf("sizeof(int)  = %lu\n", sizeof(int));
	printf("sizeof(y)    = %lu\n", sizeof(y));
	printf("sizeof(7.2)  = %lu\n", sizeof(7.2f));

	printf("sizeof(long) = %lu\n", sizeof(long));
	return 0;
}
