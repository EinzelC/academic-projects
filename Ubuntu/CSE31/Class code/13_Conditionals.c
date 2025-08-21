#include <stdio.h>
#include <stdbool.h>

/* Title: Demo code for CSE 031 Lecture 18 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

int main(int argc, char *argv[]) {
	int i = 0, j = 0, f, g = 2000, char = 4500;

	printf("Please enter a number: ");
	scanf("%d", &i);
	printf("Please enter a number: ");
	scanf("%d", &j);

	if  (i == j) goto L1;
		f = g - h;
		goto L2;
L1:	f = g + h;
L2:	printf("f (= g + h if i == j, = g - h otherwise): %d\n", f);
	return 0;
}



