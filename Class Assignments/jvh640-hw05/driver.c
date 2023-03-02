#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void main() {
	treeADT tree = treeNew();
	char userInput;
    int userNum;
    
    do{
        printf("Please Choose an Operation you'd like to perform:\n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("Options - Insert: I, Find: F, Delete: D, Max: W, Min: X, Height: H, Count: C, Sum: S, Quit: Q\n");
        printf("List Option - Inorder: V, Preorder: B, Postorder: T, Level order: K.\n");
        printf("> ");
        scanf(" %c", &userInput);
        
        switch(toupper(userInput)){ //Switch for user option
            case 'I':
                printf("Please list integers to be entered. Enter -1 to stop.\n");
                do{
                    printf("> ");
                    scanf(" %d", &userNum);
                    if(userNum != -1)
                        insert(tree, userNum);
                }while(userNum != -1);
                break;
            case 'F':
                printf("Enter an Integer to be found: ");
                scanf(" %d", &userNum);
                if(find(tree, userNum))
				    printf("Your number was found.\n");
                else
				    printf("Your number was not found\n");
                break;
            case 'D':
                printf("Enter an Integer to be deleted: ");
                scanf(" %d", &userNum);
                del(tree, userNum);
                break;
            case 'W':
                printf("The maximum value of the tree is: %d\n", max(tree));
                break;
            case 'X':
                printf("The minimum value of the tree is: %d\n", min(tree));
                break;
            case 'H':
                printf("The height of the tree is: %d\n", height(tree, NULL, 0));
                break;
            case 'C':
                printf("The number of elements in the tree is: %d\n", count(tree));
                break;
            case 'S':
                printf("The sum of all elements in the tree is: %d\n", sum(tree));
                break;
            case 'V':
                inorder(tree, NULL, 0);
                printf("\n");
                break;
            case 'B':
                preorder(tree, NULL, 0);
                printf("\n");
                break;
            case 'T':
                postorder(tree, NULL, 0);
                printf("\n");
                break;
            case 'K':
                levelorder(tree);
                break;
            case 'Q':
                ClearTree(tree);
                exit(0);
                break;
            default:
                printf("---------------------------------------------------------------------------------------\n");
                printf("Error: Invalid Entry\n");
                printf("---------------------------------------------------------------------------------------\n");
                break;
        }
    }while(userInput != 'Q');
}