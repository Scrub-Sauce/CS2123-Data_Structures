//lib.h is the .h file that contain all the prototypes and struct that will be used in main.c

#ifndef _tree_h
#define _tree_h

typedef struct node{
    int key;
    struct node *right;
    struct node *left;
}NodeDataT;

typedef struct treeCDT *treeADT;

treeADT treeNew();    //creates the tree dynamically 
void insert(treeADT tree, int number);  //inserts new integers to the tree
int find(treeADT tree, int number);   //find a certain int in the tree
void del(treeADT tree, int number);   //deletes a certain int fro the tree
void inorder(treeADT tree, NodeDataT *cp, int n);   //lists the tree in order
void preorder(treeADT tree, NodeDataT *cp, int n);  //lists the tree pre odrer 
void postorder(treeADT tree, NodeDataT *cp, int n); // lists the tree postorder
void levelorder(treeADT tree);    //lists the tree in level order 
int max(treeADT tree);    // gets the biggest int in the tree
int min(treeADT tree);    //gets the smallest int in the tree
int height(treeADT tree, NodeDataT *cp, int n); //gets the height of the tree
int count(treeADT tree);  //gets the count of the tree
int sum(treeADT tree);    //gets the sum of all ints in the tree
void ClearTree(treeADT tree); //free's all nodes then clears tree

#endif