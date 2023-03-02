#ifndef _binary_h
#define _binary_h

typedef struct node{
	int key;
	struct node *right;
	struct node *left;
}Node;

typedef struct tree{
	int count;
	int sum;
	Node *root;
	
}Tree;

void create(Tree *tree);
void insert(Tree *tree, int number);
void search(Tree *tree, int number);
void deleteTree(Tree *tree, int number);
void inTree(Tree *tree);
void preTree(Tree *tree);
void postTree(Tree *tree);
void levelorder(Tree *tree);
void max(Tree *tree);
void min(Tree *tree);
void heightTree(Tree *tree);
int heightNode(Node *node);
void count(Tree *tree);
void sum(Tree *tree);

#endif