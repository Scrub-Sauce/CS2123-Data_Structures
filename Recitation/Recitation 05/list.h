#ifndef _list_h_
#define _list_h_

typedef int listElementT; // base type int can be changed to char, double or any other type 
typedef struct listCDT *listADT; // listADT is a pointer type!

listADT NewList();
void list_insert_sorted(listADT a, listElementT val); 
void list_insert_unsorted(listADT a, listElementT val); 
     // just add val to end of the list
void list_print_values(listADT a);
void list_average(listADT a);
void list_delete_by_value(listADT a, int b);
listADT list_n_copy(listADT a, int b);
void FreeListElements(listADT a);
#endif 