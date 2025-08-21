#include <stdio.h>

/* Title: Demo code for CSE 031 Lecture 09 (Spring 2025)
 * Author: Santosh Chandrasekhar
 */

int size = 25; // A global initialized variable

int counter1() {
    int i = 0; // Local variable will only exist while this 
               // function is executing (ceases to exist after 
               // it returns)
    return i++; // Post-increment (i is incremented AFTER the function returns)
}

int counter2() {
    static int j = 0; // Static variables exist through the lifetime of a program.
                      // Just like a global variable (but scope is limited to counter2)
    size++; // Demonstrate change to global variable from anywhere
    return j++; // j will be incremented after function returns due to post-increment
}

int main(void) {

    printf("size = %d\n", size);    // Printing the global variable 

    for (int k = 0; k < 20; ++k) {
        printf("%d ", counter1()); // Should print all 0's
    }
    printf("\n");

    for (int k = 0; k < 20; ++k) {
        printf("%d ", counter2());  // Should print 0...19 (value of counter2()'s local
                                    // j is "remembered" between calls)
    }
    
    printf("\n");    
    printf("size = %d\n", size); // Printing the global variable again
                                 // after being incremented inside counter2
    
    //printf("j = %d\n", j); // This will cause a compilation error as the static 
                             // variable j inside counter2 is out of scope

    return 0;

}