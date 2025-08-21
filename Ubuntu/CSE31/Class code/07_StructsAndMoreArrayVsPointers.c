#include <stdio.h>
#include <stdlib.h>

/* Title: Demo code for CSE 031 Lecture 08 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

// A structure with 4 members
struct myStruct1 {
    char c1;
    short s;
    int i;
    char c2;
};

// Another structure with the same 4 members but in a different order
typedef struct myStruct2 {
    char c1;
    char c2;
    short s;
    int i;
} myStruct2;

struct __attribute__((__packed__)) myStruct3 { // To compress the structure (not recommended)
	char x;
	int y;
};

int main() {
	typedef int AnIntegerVariable; // typedef allows us to rename (create an alias for) datatypes for convenience
	AnIntegerVariable myint = 8;
	printf("myint: %d\n\n", myint);

	// See https://en.wikipedia.org/wiki/Data_structure_alignment for explanation of outputs below
	printf("Size of myStruct1: %lu\n", sizeof(struct myStruct1)); 
	printf("Size of myStruct2: %lu\n\n", sizeof(myStruct2)); 
	

	typedef struct myStruct3 point;
	point p; // or struct myStruct3 p;
	p.x = 'a';
	p.y = 1;

	point q = p; // q and p are two difference struct variables and contents of p are copied over to q

	printf("p.x: %c, p.y: %d\n", p.x, p.y);
	printf("q.x: %c, q.y: %d\n", q.x, q.y);
	
	q.x = 'b'; // Should not affect contents of p
	q.y = 2;

	printf("\n");
	printf("p.x: %c, p.y: %d\n", p.x, p.y);
	printf("q.x: %c, q.y: %d\n", q.x, q.y); 

	printf("\n");

	// Code to demonstrate difference between pointers and arrays
	int *p1, *p2, y;
	int c[4];
	p1 = (int *) malloc (sizeof(int));
	p2 = &y;
	*p1 = 1; // p1[0] would also work here
	printf("*p1: %u, p1: %p, &p1: %p\n", *p1, p1, &p1);
	*p2 = 2; // p2[0] would also work here
	printf("*p2: %u, p2: %p, &p2: %p\n", *p2, p2, &p2);
	*c = 3; // c[0] would also work here
	printf("*c: %u, c: %p, &c: %p\n", *c, c, &c); // Address of c is same as value of c

	return 0;
}