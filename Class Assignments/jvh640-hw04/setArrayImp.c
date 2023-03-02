#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define MAX_SIZE 100

typedef struct point{
    setElementT x;
}setDataT;

struct setCDT{
    setDataT array[MAX_SIZE];
    int elementCount;
};

setADT setNew(){
    setADT newSet;
    
    newSet = (setADT) malloc(sizeof(struct setCDT));
    if(newSet == NULL){
        printf("\nError: Unable to allocate memory for set.\n");
        exit(0);
    }
    newSet->elementCount = 0;
    
    return newSet;
}

void setFree(setADT S){
    free(S);
}

int setInsertElementSorted(setADT S, int E){
    int i, j, a, tmp;
    
    if(S->elementCount == 0){
        S->array[0].x = E;
        S->elementCount++;
        return S->elementCount;
    }
    
    if(S->elementCount != 0){
        for(i = 0; i < S->elementCount; i++){
            if(E == S->array[i].x){
                return 0;
            }
        }
        S->array[S->elementCount].x = E;
        
        for(i = 0; i <= S->elementCount-2; i++){
            a = i;
            for(j = a + 1; j <= S->elementCount-1; j++){
                if(S->array[j].x < S->array[a].x)
                    a = j;
                tmp = S->array[i].x;
                S->array[i].x = S->array[a].x;
                S->array[a].x = tmp;
            }
        }
        S->elementCount += 1;
        return S->elementCount;
    }
    
}
    
 

setADT setUnion (setADT A, setADT B){
    int i;
    setADT C = setNew(); 
    
    for(i = 0; i < A->elementCount; i++){
        setInsertElementSorted(C, A->array[i].x);
    }
    for(i = 0; i < B->elementCount; i++){
        setInsertElementSorted(C, B->array[i].x);
    }
    return C;
}

setADT setIntersection (setADT A, setADT B){
    int i, j;
    setADT C = setNew();
    
    for(i = 0; i < A->elementCount; i++){
        for(j = 0; j < A->elementCount; j++){
            if(A->array[i].x == B->array[j].x){
                setInsertElementSorted(C, A->array[i].x);
            }
        }
    }
    return C;
}

setADT setDifference(setADT A, setADT B){
    int i, j, match;
    setADT C = setNew();
    
    for(i = 0; i < A->elementCount; i++){
        match = 0;
        for(j = 0; j < A->elementCount; j++){
            if(A->array[i].x == B->array[j].x){
                match = 1;
            }
        }
        if(match == 0)
            setInsertElementSorted(C, A->array[i].x);
    }
    return C;
}

int setCardinality(setADT S){
        return S->elementCount;
}

void setPrint(setADT S, char *name){
    int i;
    
    if(S->elementCount != 0){    
        printf("Set %s: {", name);
        for(i = 0; i < S->elementCount-1; i++){
            printf("%d, ", S->array[i].x);
        }
        printf("%d}\n", S->array[S->elementCount-1].x);
    }else{
        printf("\nThis operation is not applicable to these sets.\n");
    }
}