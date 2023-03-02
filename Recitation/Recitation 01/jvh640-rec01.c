#include <stdio.h>
#include <stdlib.h>

void PrintOneDigit(int d);
void PrintTeenDigit(int d);
void PrintTenDigit(int d);

void main(){
    int num; //Initializes the user entered Number
    int d6, d5, d4, d3, d2, d1; // Initializes the seperation of digits
    int isRunning = 1, notValid = 1; // Creates boolean values for while loops 
    printf("\nEnter numbers in for conversion. If complete, enter a negative value to end the program.\n\n");
    while(isRunning == 1){ // Creates running loop.
        while(notValid == 1){ // Creates nester valid user entry loop.
            printf("Enter Number : ");
            scanf("%d", &num);  // User Entry
            if(num > 999999)  // Invalid Error
                printf("ERROR: Invalid Entry - Please enter an integer between 0 - 999,999.\n\n");
            else if(num < 0){ // Exits program on negative entry
                printf("\nProgram Complete\n");
                exit(0);
            } else // Valid entry continues.
                notValid = 0; 
        }
        ++notValid; //Increments notValid for Next entry cycle
        d6 = (num % 1000000) / 100000;  // Finds the value of the Hundred Thousandth Digit
        d5 = (num % 100000) / 10000; // Finds the value of the Ten Thousandth Digit
        d4 = (num % 10000) / 1000; // Finds the value of the Thousandth Digit
        d3 = (num % 1000) / 100; // Finds the value of the Hrundredth Digit
        d2 = (num % 100) / 10; // Finds the value of the Tenth Digit
        d1 = num %10; // Finds the value of the Single Digit
        if (d6 > 0){
            PrintOneDigit(d6);
            printf("hundred ");
        }
        if(d5 != 0 && d5 != 1)
            PrintTenDigit(d5);
        if(d5 == 1)
            PrintTeenDigit(d4);
        if(d4 != 0 && d5 != 1)
            PrintOneDigit(d4);
        if(num > 999)
            printf("thousand ");
        if(d3 > 0){
            PrintOneDigit(d3);
            printf("hundred ");
        }
        if(d2 !=0 && d2 !=1)
            PrintTenDigit(d2);
        if(d2 == 1)
            PrintTeenDigit(d1);
        if(d2 != 1 && d1 != 0)
            PrintOneDigit(d1);
        if(num == 0)
            printf("zero");
        printf("\n");                
    }
}

void PrintOneDigit(int d){
     char *single[10] = {"zero ", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine "};
    printf("%s", single[d]);
}

void PrintTenDigit(int d){
      char *tens[10] = {" ", " ", "twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "seventy ", "eighty ", "nienty "};
        printf("%s", tens[d]);
}

void PrintTeenDigit(int d){
    char *teens[10] = {"ten ", "elevin ", "twelve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen "};
        printf("%s", teens[d]);
}