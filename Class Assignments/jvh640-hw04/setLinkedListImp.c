#include <stdio.h>
#include <stdlib.h>
#include "set.h"

typedef struct point {
   setElementT x; 
   struct point *next;
} setDataT;

struct setCDT {
	setDataT *start; 
	setDataT *end;   
    int elementCount;
};

setADT setNew(){
    setADT newSet;
    newSet = (setADT) malloc(sizeof(struct setCDT));
    if(newSet == NULL){
        printf("\nError: Unable to allocate memory for set.\n");
        exit(0);
    }
    newSet->start = newSet->end = NULL;
    newSet->elementCount = 0;
    return newSet;
} 

void setFree(setADT S){
    setDataT *current, *delete;
    
    if(S->start != NULL){
        current = S->start;
    
        while(current->next != NULL){
            delete = current;
            current = current->next;
            free(delete);
        }
        if(current->next == NULL)
            free(current);
    }
    free(S);
}

int setInsertElementSorted(setADT S, int E){
    setDataT *current, *previous, *newDataT;
    int inSet = MultipleCheck(S, E);
    
    if(inSet == 0){
        newDataT = (setDataT *) malloc(sizeof(setDataT));
        if(newDataT == NULL){
            printf("\nError: Unable to allocate memory for new element.\n");
            exit(0);
        }
    
        newDataT->x = E;
        newDataT->next = NULL;
    
        previous = NULL;
        current = S->start;
    
        while(current){
            if(current->x >= newDataT->x)
                break;
            previous = current;
            current = current->next;
        }
        if(previous == NULL) {
            newDataT->next = S->start;
            S->start = newDataT;
        }else{
            newDataT->next = previous->next;
            previous->next = newDataT;
        }
        if(newDataT->next == NULL)
            S->end = newDataT;
    
        S->elementCount += 1;
    }
    
    return S->elementCount;
} 

setADT setUnion (setADT A, setADT B){
    setADT C = setNew();
    setDataT *current = A->start;
    
    while(current){
        setInsertElementSorted(C, current->x);
        current = current->next;
    }
    
    current = B->start;
    
    while(current){
        setInsertElementSorted(C, current->x);
        current = current->next;
    }
    
    return C;
}

setADT setIntersection (setADT A, setADT B){
    setADT C = setNew();
    setDataT *currentA, *currentB;
    
    currentA = A->start;
    while(currentA){
        currentB = B->start;
        while(currentB){
            if(currentA->x == currentB->x){
                setInsertElementSorted(C, currentA->x);
            }            
            currentB = currentB->next;
        }
        currentA = currentA->next;
    }
    return C;
}

setADT setDifference(setADT A, setADT B){
    setADT C = setNew();
    setDataT *currentA, *currentB;
    int i, j, match;
    
    currentA = A->start;
    for(i = 0; i < A->elementCount; i++){
        match  = 0;
        currentB = B->start;
        for(j = 0; j < B->elementCount; j++){
            if(currentA->x == currentB->x){
                match = 1;
            }
            currentB = currentB->next;
        }
        if(match == 0){
            setInsertElementSorted(C, currentA->x);
        }
        currentA = currentA->next;
    }
    return C;
}

int setCardinality(setADT S){
    int numElements = S->elementCount;
    return numElements;
}

void setPrint(setADT S, char *name){
    setDataT *current;
    if(S->elementCount != 0){
        current = S->start;    
        printf("Set %s: {", name);
        while(current->next != NULL){
            printf("%d, ", current->x);
            current = current->next;
        }
        printf("%d}\n", current->x);
    }else{
        printf("\nThis operation is not applicable to these sets.\n");
    }
}

int MultipleCheck(setADT S, int E){ // Checks for Duplicates in set
    setDataT *current = S->start;
    
    while(current){
        if(current->x == E){
            return 1;
        }
        current = current->next;
    }
    return 0;
}