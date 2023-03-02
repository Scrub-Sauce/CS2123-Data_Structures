#include <stdio.h>
#include <stdlib.h>
#include "random.h"

void StoreSecret(int secret, int s_a[]);
int CheckSecret(int secret, int s_a[], int numValidity);
int CompareDigits(int s_a[], int a_a[]);
void PrintResults(int in_place, int out_of_place, int not_exist);

#define MAX_TURNS 40

void main(){
    int secret, s_a[4], i, numValidity, ans, a_a[4];
    
    Randomize();
    do{ // loop to generate valid number
        numValidity = 0; //used to check if secret is valid
        
        secret = RandomInteger(1000, 9999); //Generates Random number
        StoreSecret(secret, s_a);
        numValidity = CheckSecret(secret, s_a, numValidity);
    }while(numValidity == 1);
    for(i = 1; i <= MAX_TURNS; i++){ //Loop for counting player turns
        do{ // loop to take in valid player entry
            numValidity = 0; //used to check if ans is valid
            
            printf("Turn #%d - Please enter a number between 1000-9999\n", i);
            scanf(" %d", &ans); // Player Input
            StoreSecret(ans, a_a);
            numValidity = CheckSecret(ans, a_a, numValidity);
            if(numValidity == 1){
                printf("Invalid Entry.\n");
            }
        }while(numValidity == 1);
        CompareDigits(s_a, a_a);
    }
    printf("-------------Game Over-------------\n");
}


void StoreSecret(int secret, int s_a[]){ // Stores the secret or ans variable into s_a or a_a
    s_a[0] = (secret % 10000) / 1000; 
    s_a[1] = (secret % 1000) / 100; 
    s_a[2] = (secret % 100) / 10; 
    s_a[3] = secret % 10;
}

int CheckSecret(int secret, int s_a[], int numValidity){ // Checks the validity of s_a and a_a
    int i, j;
    
    for(i = 0; i < 4; i++){
        for(j = i+1; j < 4; j++){
            if(s_a[i] == s_a[j]){
                numValidity = 1;
            }
        }
    }
    return (numValidity);
}

int CompareDigits(int s_a[], int a_a[]){ //Compares the value of s_a and a_a and counts whats inplace doesnt exist or out of place   
    int i, j, in_place = 0, out_of_place = 0, not_exist = 4, checked;
    
    for(i = 0; i < 4; i++){
        checked = 0;
        if(s_a[i] == a_a[i]){
            in_place++;
            not_exist--;
            checked = 1;
        }
        for(j = 0; j < 4; j++){
            if(checked == 0){
                if(s_a[i] == a_a[j]){
                    out_of_place++;
                    not_exist--;
                }
            }
        }
    }
   PrintResults(in_place, out_of_place, not_exist);
}

void PrintResults(int in_place, int out_of_place, int not_exist){ //Prints the results of the CompareDigits() function
    if(in_place == 4){
        printf("-------------You Win-------------\n");
        exit(0);
    }
    if(in_place == 1){
        printf("%d digit is in place\n", in_place);
    }else if(in_place > 1 || in_place < 1 && in_place != 4){
        printf("%d digits are in place\n", in_place);
    }
    if(out_of_place == 1){
        printf("%d digit is out place\n", out_of_place);
    }else if(out_of_place > 1 || out_of_place < 1){
        printf("%d digits are out place\n", out_of_place);
    }
    if(not_exist == 1){
        printf("%d digit does not exist\n", not_exist);
    }else if(not_exist > 1 || not_exist < 1){
        printf("%d digits do not exist\n", not_exist);
    } 
}