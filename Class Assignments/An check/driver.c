#include <stdlib.h>
#include <stdio.h>
#include "binary.h"
#include <string.h>

void commands();

int main(){
	Tree tree;
	char ch[1];
	int num;
	create(&tree);
	
	
	
	while(ch[0]!='Q'){
	num =0;
	
	printf("\n");
	commands();
	
	scanf("%s", ch);
	
	
	 switch (toupper(ch[0])) {
      case 'A': printf("Enter numbers to insert. Enter -1 when done. \n");
               while(num!=-1){
			    scanf("%d", &num);
			    if(num!=-1){
		      	insert(&tree, num);
		      }
		      }
		      	break;
		      	
	  case 'B': printf("Enter number to search in tree\n");      	
                scanf("%d", &num);
		      	search(&tree, num);
		      	break;
		      	
	  case 'C': printf("Enter number to delete from the tree\n");      	
                scanf("%d", &num);
		      	deleteTree(&tree, num);
		      	break;
		      	
      case 'D': inTree(&tree);
	             break;
	             
	  case 'E': preTree(&tree);
	             break;      
				 
	  case 'F': postTree(&tree);
	             break;
		
	  case 'G': level(&tree);
	             break;		 			     
				 
	   case 'H': max(&tree);
	            break;          
      
	   case 'I': min(&tree);
	            break;  
				
	  case 'J': heightTree(&tree);
	            break;	
				
	  case 'K': count(&tree);
	            break;	
				
	  case 'L': sum(&tree);
	            break;						      
     
      case 'Q': exit(0);
      
      default:  printf("Illegal command\n"); break;
    }
}
	
	
	
	
	
	

}

//Displays the list of commands
void commands(){
	printf("Choose a command by typing in a letter\n");
	printf("A: Insert value\n");
	printf("B: Search for a value in the tree\n");
	printf("C: Delete a value in the tree\n");
	printf("D: Display values in the tree inorder\n");
	printf("E: Display values in the tree preorder\n");
	printf("F: Display values in the tree postorder\n");
	printf("G: Display values in the tree levelorder\n");
	printf("H: Display highest value in tree\n");
	printf("I: Display lowest value in tree\n");
	printf("J: Display height of the tree\n");
	printf("K: Display the amount of values in tree\n");
	printf("L: Display the sum of all values in tree\n");
	printf("Q: Exit program\n");
	printf("\n");
}
