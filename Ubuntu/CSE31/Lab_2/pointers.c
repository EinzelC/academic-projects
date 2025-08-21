#include <stdio.h>

int main() {
    int x, y, *px, *py, *arrp;
    int arr[10];

    x = 0;
    y = 0;
    px = &x;
    py = &y; 

    for (int i = 0; i < 10; i++) {
        arr[i] = i + 1;  
    }

    printf("Value of x: %d\n", x);
    printf("Value of y: %d\n", y);
    printf("Address of x: %p\n", (void*)&x);
    printf("Address of y: %p\n", (void*)&y);
    printf("Value of px (address of x): %p\n", (void*)px);
    printf("Value of py (address of y): %p\n", (void*)py);
    printf("Value pointed to by px: %d\n", *px);
    printf("Value pointed to by py: %d\n", *py);
    for (int i = 0; i < 10; i++) {
        printf("arr[%d] = %d\n", i, *(arr+i));
    }
    printf("Value of arr (address of arr[0] = %d): %p\n", arr[0], (void*)arr);
    
    return 0;
}