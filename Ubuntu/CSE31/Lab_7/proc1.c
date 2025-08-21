#include <stdio.h>

int SUM(int x, int y){
    return x + y;
}

int main(){
    int m = 10, n = 5, sum;
    sum = SUM(m,n);
    printf("%d\n", sum);

    return 0;
}