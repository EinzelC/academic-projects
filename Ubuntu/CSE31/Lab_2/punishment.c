#include <stdio.h>
int main(){

    int inputOne = 0;
    int inputTwo = 0;
    int One = 1;
    int Two = 1;
    int i;

    printf("Enter the repetition count for the punishment phrase: ");
    while(One){
        
        scanf("%d", &inputOne);
        if(inputOne <= 0){
            printf("You entered an invalid value for the repetition count! Please re-enter: ");
        } else {
            One = 0;
        }
    }
    
    printf("\nEnter the line where you want to insert the typo: ");
    while(Two){
        scanf("%d", &inputTwo);
        if(inputTwo <=0 || inputTwo > inputOne){
            printf("You entered an invalid value for the typo placement! Please re-enter: ");
        } else {
            Two = 0;
        }
    }
    
    printf("\n");
    for(i = 1; i <= inputOne; i++){
        if(i == inputTwo){
            printf("Cading wiht is C avesone!\n");
        } else {
            printf("Coding with C is awesome!\n");
        }
    }

return 0;
}