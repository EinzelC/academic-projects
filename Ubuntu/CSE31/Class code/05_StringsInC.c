#include <stdio.h>
#include <string.h>

/* Title: Demo code for CSE 031 Lecture 06 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

int main() {
	int i;

	char* str;	// Most common way of creating a string
	str = "abc";
	printf("str: %s, length of str: %lu\n", str, strlen(str));

	// Using arrays to create strings to demonstrate the importance of the null terminating 
	// charater (can do the same with pointers too).
	static char s1[4];	// To store a 3-character string, create an array of size 4, not 3, to have space 
						// for the null terminating character
	s1[0] = 'b';
	s1[1] = 'c'; 
	s1[2] = 'd';
	s1[3] = '\0';	// Store the null terminating character at the last location (without this, you may see 
					// odd printing behavior as shown with s2)
	printf("s1: %s, length of s1: %lu\n", s1, strlen(s1));	
	
	s1[1] = '\0'; // This will cut the string to just 'b' even though s1[2] ='d' 
	printf("s1: %s, length of s1: %lu\n", s1, strlen(s1));	

	char s2[3]; // Intentionally done to demonstrate what happens when we forget the null terminating character
	s2[0] = 'b';
	s2[1] = 'c'; 
	s2[2] = 'd'; // Notice now that we did not place \0 in the end
	printf("s2: %s, length of s2: %lu\n", s2, strlen(s2)); // Should see odd things printed (sometimes) 

	printf("\n");
	printf("Charaters and their locations for string str: \n");
	for(i = 0; i < 4; i++)
		printf("character: %c \t at address: %p\n", str[i], str + i); // Or use *(str + i) instead of str[i]
	printf("\n");

	return 0;
}
