#include <stdio.h>
#include <stdbool.h>

/* Title: Demo code for CSE 031 Lecture 20 (Spring 2024)
 * Author: Santosh Chandrasekhar
 */

int fib(int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return 1;
	return (fib(n - 1) + fib(n - 2));
}

int main(int argc, char *argv[]) {
	printf("%d\n", fib(10));
	return 0;
}

