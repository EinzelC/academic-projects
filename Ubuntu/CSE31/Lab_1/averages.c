#include <stdio.h>
#include <string.h>

int sumOfDigits(int number) {
    int sum = 0;
    if(number < 0){
        number *= -1;
    }
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

void suffix(int d){
    int lastDigit;
    if(d < 0){
        d *= -1;
    }
    lastDigit = d % 10;
    if(lastDigit == 1){
        printf("st");
    }else if(lastDigit == 2){
        printf("nd");
    }else if(lastDigit == 3){
        printf("rd");
    }else{
        printf("th");
    }
}

int main(){
    int input[50];
    int even[50];
    int odd[50];
    int putin = 1;
    int index = 0;

    int e = 0;
    int o = 0;

    while(putin){
        printf("Enter the %d", index+1);
        suffix(index+1);
        printf(" Value: ");
        scanf("%d", &input[index]);
        if(input[index] == 0){
            putin = 0;
        }else{index++;}
        
    }

    int added = 0;
    for(int i = 0; i < index-1; i++){
        added = sumOfDigits(input[i]);
        if(added % 2 == 0){
            even[e] = input[i];
            e++;
        } else {
            odd[o] = input[i];
            o++;
        }

    }

    float average = 0;
    for(int i = 0; i < e; i++){
        average += even[i];
    }
    printf("Average of input values whose digits sum up to an even number: %.2f\n", average/(e));

    average = 0;
    for(int i = 0; i < o; i++){
        average += odd[i];
    }
    printf("Average of input values whose digits sum up to an odd number: %.2f\n", average/(o));
return 0;
}