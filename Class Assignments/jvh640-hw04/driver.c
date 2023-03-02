#include <stdio.h>
#include <stdlib.h>
#include "set.h"

void UserInputSet(setADT S, char *name);
void UserOperation(setADT A, setADT B);
void HandleResults(setADT A, setADT B, setADT C);

void main(){
    setADT A = setNew(), B = setNew();
    
    UserInputSet(A, "A");
    UserInputSet(B, "B");
    UserOperation(A, B);
    setFree(A);
    setFree(B);
}

void UserInputSet(setADT S, char *name){ //Handles User Input
    int userEntry = 0, entryNum = 1;
    
    printf("\nPlease enter positive integers for set %s. Enter -1 when this set is complete.\n", name);
    printf("---------------------------------------------------------------------------------------\n");
    do{
        printf("Set %s - Entry %d\n> ", name, entryNum);
        scanf(" %d", &userEntry);
        if(userEntry >= 0)
            entryNum = (setInsertElementSorted(S, userEntry) + 1);
        else if(userEntry == -1){
            printf("---------------------------------------------------------------------------------------\n");
            printf("Set %s entry complete!\n", name);
            printf("---------------------------------------------------------------------------------------\n");
        }
        else
            printf("Error: Please enter a integer value of 0 or higher. If entry of set is complete enter -1.\n");
   }while(userEntry != -1);
}

void UserOperation(setADT A, setADT B){ //Handles Operation selection and processes
    setADT C;
    char userSelection;
    
    do{
        printf("---------------------------------------------------------------------------------------\n");
        printf("Select set operation:\n");
        printf("U - Union, I - Intersection, D - Difference, Q - Quit\n> ");
        scanf(" %c", &userSelection);
        
        switch(toupper(userSelection)){
            case 'U' :
                C = setUnion(A, B);
                HandleResults(A, B, C);
                break;
            case 'I' :
                C = setIntersection(A, B);
                HandleResults(A, B, C);
                break;
            case 'D' :
                C = setDifference(A, B);
                HandleResults(A, B, C);
                break;
            case 'Q' :
                printf("Quitting...\n");
                break;
            default :
                printf("\nError: Invalid Entry.\n\n");
        }
            
    }while(toupper(userSelection) != 'Q');
}

void HandleResults(setADT A, setADT B, setADT C){  // Prints results of chosen operation  
    setPrint(A, "A");
    setPrint(B, "B");
    setPrint(C, "C");
    printf("\nThere are %d elements in set C\n", setCardinality(C));
    setFree(C);
}