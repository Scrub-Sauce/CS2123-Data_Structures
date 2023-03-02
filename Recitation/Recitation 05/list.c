/******************************* list.c ***********************/
#include <stdlib.h>
#include <stdio.h> 
#include "list.h"

typedef struct point {
   listElementT x; 
   struct point *next;
} myDataT;

struct listCDT {
	myDataT *start; // myDataT *header;
	myDataT *end;   // myDataT *foother;
};

listADT NewList()
{
   listADT tmp;
   tmp = (listADT) malloc(sizeof(struct listCDT)); // New(listADT);

   if (tmp==NULL) return NULL;                  

   tmp->start = tmp->end = NULL;
   return tmp;
}

void list_insert_sorted(listADT a, int val)
{
    myDataT *b, *prev, *curr;

    b = (myDataT *) malloc(sizeof(myDataT)); 
    if (b==NULL) return;
        b->x = val;   
        b->next = NULL;

        prev = NULL;
        curr = a->start; 
        while(curr) {
            if (curr->x >= b->x ) break;
                prev = curr;
                curr = curr->next;
        }
        if(prev == NULL) {
            b->next = a->start;
            a->start = b;
        } else{ 
            b->next = prev->next;
            prev->next = b;
        }
        if (b->next == NULL) {
	       a->end = b;
        }
}

void list_insert_unsorted(listADT a, int val) 
// add val the end of the link list
{ 
    myDataT *b;

    b = (myDataT *) malloc(sizeof(myDataT)); 
    if (b==NULL) return;
        b->x = val;   
        b->next = NULL;

    if(a->start == NULL) {
        a->start = b;
    } else{ 
        a->end->next = b;   
    }
    a->end = b;
}

void list_print_values(listADT a){ //Loop prints the values of list
    myDataT *curr = a->start;
    
    while(curr != NULL){  
        printf("%d ", curr->x);
        curr = curr->next;
    } 
    printf("\n");
}

void list_average(listADT a){ //Initializes calculation variables and finds the average of the list
    myDataT *curr = a->start;
    int count = 0, sum = 0, avg = 0;
    
    while(curr != NULL){
        sum += curr->x;
        count++;
        curr = curr->next;
    }
    avg = sum / count;
    
    printf("Average = %d\n", avg);
}

void list_delete_by_value(listADT a, listElementT b){ //while the list is still going the loop checks if the list has the value specified when called
    myDataT *curr, *prev, *tmp;
    curr = a->start;
    prev = curr;
    while(curr!=NULL){
        if(curr == a->start){
            if(curr->x == b){
                tmp = curr->next;
                free(curr);
                a->start = tmp;
                curr = tmp;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }else{
            if(curr->x == b){
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }else{
                prev = curr;
                curr = curr->next;
            }  
        }
    } 
}

listADT list_n_copy(listADT a, int b){ //creatures a new list and copies the first b numbers from the a list into a new list designated Z.
    listADT Z;
    myDataT *curr;
    int i, c;
    
    Z = NewList();
    curr = a->start;
    
    for(i=0; i<b; i++){
        c = curr->x;
        list_insert_sorted(Z, c);
        curr = curr->next;
    }
    return Z;
}

void FreeListElements(listADT a){
    myDataT *curr, *prev;
    curr = a->start;
    prev = curr;
    
    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    if(curr->next == NULL)
        free(curr);
}




