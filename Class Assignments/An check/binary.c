/*
* Name:  An Chau
* ID: Oyf420
*
* 
* 
*/

#include <stdlib.h>
#include <stdio.h> 
#include "binary.h"


void create(Tree *tree){ //creates binary tree
	tree->count = 0;
	tree->sum =0;
	tree->root = NULL;
}

void insert(Tree *tree, int number){ //inserts a value into the tree
	Node *tmp, *prev, *cp;
	
	tree->count+=1;
	printf("size: %d \n", tree->count);
	tree->sum += number;
	tmp = (Node *)malloc(sizeof(Node));
	tmp->key = number;
	tmp->right = tmp->left = 0;
	
	if(! tree->root){
		tree->root = tmp;
		
	}else{
		cp = tree->root;
		while(cp){
			prev = cp;
			if(number < cp->key){
				cp = cp->left;
			}else{
				cp = cp->right;
			}
		}
		if(number < prev->key){
			prev->left = tmp;
		}else{
			prev->right = tmp;
		}
	}
}

void search(Tree *tree, int number){//searches through the tree to find a number
	int match = 0;
	Node *cp = tree->root;

	while(cp){
		if(cp->key == number){
			printf("Found! \n");
			match=1;
			break;
		}else{
			if(number < cp->key){
				cp = cp->left;
			}else{
				cp = cp->right;
			}
		}
			
	}
	if(match==0){
	printf("Not found\n");
}
}

void deleteNode(Node **nodeAdress){//deletes the node that contains the number that was chosen
	Node *prev, *cp = *nodeAdress;
	
	if(! (*nodeAdress)->left){
		
		*nodeAdress = (*nodeAdress)->right;
	}else if(! (*nodeAdress)->right){
		
		*nodeAdress = (*nodeAdress)->left;
	}else{
		cp = (*nodeAdress)->left;
		
		if(! cp->right){
			(*nodeAdress)->key = cp->key;
			(*nodeAdress)->left = cp->left;
		}else{
			do{
				prev = cp;
				cp = cp->right;
			}while(cp->right);
			 (*nodeAdress)->key = cp->key;
			 prev->right = cp->left;
			 
		}
		
	}
	free(cp);
}

void deleteTree(Tree *tree, int number){//is passed the address of the tree and passed the number to be deleted
	int match= 0;
	Node *prev = NULL, *cp = tree->root;
	
	
	while(!match && cp){
		
		
		prev = cp;
		if(number < cp->key){
			cp = cp->left;
		} else{
			cp = cp->right;
		}
		
		
		match = number == cp->key;
	}
	
	//If the number is found, it decreases tree size and then calls the function to delete the node
	if(match){
		tree->count-=1;
		tree->sum -= number;
		
		if(! prev){
			deleteNode(& tree->root);
		}else{
			if(number < prev->key){
				deleteNode(& prev->left);
			}else{
				deleteNode(& prev->right);
			}
		}
	}
}

void inNode(Node *node){//prints the values of the tree in inorder
	if(node){
		inNode(node->left);
		printf("%d ", node->key);
		inNode(node->right);
	}
}

void inTree(Tree *tree){//Is passed the address of the tree and then calls the function to print inorder
	inNode(tree->root);
	printf("\n");
}

void preNode(Node *node){//prints the values of the tree in preorder
	if(node){
		printf("%d ", node->key);
		preNode(node->left);
		preNode(node->right);
	}
}

void preTree(Tree *tree){//Is passed the address of the tree and then calls the function to print in preorder
	preNode(tree->root);
}

void postNode(Node *node){//prints the values of the tree in postorder
	if(node){
		postNode(node->left);
		postNode(node->right);
		printf("%d ", node->key);
	}
}

void postTree(Tree *tree){//Is passed the address of the tree and then calls the function to print in postorder
	postNode(tree->root);
	printf("\n");
}

void level(Tree *tree){//Is passed the address of the tree to print values in level order
	Node *tmp, *queue[100];
	int size = 0;
	int take = 0;
	
	if(tree->root){
		queue[size++] = tree->root;
		
		while(size > take){
			
			
			tmp = queue[take++];
			printf("%d ", tmp->key);
			if(tmp->left != NULL){
				queue[size++] = tmp->left;
			}
			if(tmp->right != NULL){
				queue[size++] = tmp->right;
				
				
			}
		}
	}
	printf("\n");
}

void max(Tree *tree){//prints the highest value in the tree
	Node *cp;
	if(tree->root){
		cp = tree->root;
		while(cp->right){
			cp = cp->right;
		}
		printf("The highest value is %d\n", cp->key);
	}
}

void min(Tree *tree){//prints the lowest value in the tree
	Node *cp;
	if(tree->root){
		cp = tree->root;
		while(cp->left){
			cp = cp->left;
		}
		printf("The lowest value is %d\n", cp->key);
	}
}

int heightNode(Node *node){//calculates the height of the tree and then returns it
	if(!node){
		return 0;
	}
	int a = heightNode(node->left);
	int b = heightNode(node->right);
	return (a > b) ? 1+a : 1+b;
}

void heightTree(Tree *tree){//prints the height of the tree
	printf("The height of the tree is %d\n", heightNode(tree->root));
}

void count(Tree *tree){//prints the amount of nodes
	printf("The tree size is %d\n", tree->count);
}

void sum(Tree *tree){//prints the sum of the values in the nodes
	printf("The tree sum is %d\n", tree->sum);
}



