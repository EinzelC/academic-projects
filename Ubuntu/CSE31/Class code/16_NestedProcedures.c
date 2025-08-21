#include <stdio.h>
#include <stdbool.h>

/* Title: Demo code for CSE 031 Lecture 20 (Spring 2024)
 * Author: Santosh Chandrasekhar
 */

int bar(int a, int b) {
	return a * b;
}

int foo(int x, int y) {
	return bar(x, x + y) + y;
}

int main(int argc, char *argv[]) {
	int x = 0, y = 0;
	printf("Please enter a number: ");
	scanf("%d", &x);
	printf("Please enter a number: ");
	scanf("%d", &y);
	printf("%d\n", foo(x, y));
	return 0;
}

