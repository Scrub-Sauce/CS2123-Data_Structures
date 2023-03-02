/******* Now we can simply implement driver.c  ****************/ 
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
main()
{
    int i, tmp;
    listADT X, Y, Z;
    X = NewList();
    Y = NewList();
    
    for(i=0; i<6; i++){ //Takes user input for the linked list values
        printf("Please enter an Integer: ");
        scanf("%d", &tmp);
        
        list_insert_sorted(X, tmp);
        list_insert_unsorted(Y, tmp);
    }
    
    printf("\nList X: "); //Prints sorted List of user entered values
    list_print_values(X);
    printf("\nList Y: "); //Prints unsorted List of user entered values
    list_print_values(Y);
    
    printf("\nList X's "); //Prints average of sorted list
    list_average(X);
    printf("\nList Y's "); //Prints average of unsorted list
    list_average(Y);
    
    printf("Please enter an integer to be removed from the list: "); //Ask's user which value should be deleted if encountered.
    scanf("%d", &tmp);
    
    list_delete_by_value(X, tmp); //Deletes user specified value from sorted list.
    printf("\nList X: ");
    list_print_values(X); //Prints sorted List of user entered values
    
    list_delete_by_value(Y, tmp);//Deletes user specified value from unsorted list.
    printf("\nList Y: ");
    list_print_values(Y); //Prints unsorted list of user entered values
    
    printf("\nList X's ");
    list_average(X); //Prints average of sorted list
    printf("\nList Y's ");
    list_average(Y); //Prints average of unsorted list
    
    Z = list_n_copy(X, 3); //Creates new list from list specified using the first n specified in the list
    printf("\nList Z: ");
    list_print_values(Z); //Prints of new List of user entered values
    printf("\nList Z's ");
    list_average(Z); 
    
    //Free's all lists
    FreeListElements(X); //Frees elements in X
    free(X);
    FreeListElements(Y); //Frees elements in Y
    free(Y);
    FreeListElements(Z); //Frees elements in Z
    free(Z);
}

