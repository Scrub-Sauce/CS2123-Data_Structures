#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct treeCDT{
	int size;
	int sum;
	NodeDataT *root;
};

treeADT treeNew(){
    treeADT newTree;
    newTree = (treeADT) malloc(sizeof(struct treeCDT));
    if(newTree == NULL){
        printf("\nError: Unable to allocate memory for set.\n");
        exit(0);
    }
	newTree->size = newTree->sum = 0;
	newTree->root = NULL;
    return newTree;
}

void insert(treeADT tree, int number){
	NodeDataT *temp, *pre, *cur;
	
	tree->size++;
	tree->sum += number;
	temp = (NodeDataT *)malloc(sizeof(NodeDataT));
	temp->key = number;
	temp->right = temp->left = 0;
	
	if(! tree->root){
		tree->root = temp;
		
	}else{
		cur = tree->root;
		while(cur){
			pre = cur;
			if(number < cur->key){
				cur = cur->left;
			}else{
				cur = cur->right;
			}
		}
		if(number < pre->key){
			pre->left = temp;
		}else{
			pre->right = temp;
		}
	}
}

int find(treeADT tree, int number){
	int found = 0;
	NodeDataT *cur;
	cur = tree->root;
	while(cur){
		if(cur->key == number){
			found = 1;
			break;
		}else{
			if(number < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}		
	}
	return found;
}

void deleteNode(NodeDataT **nodeAdress){
	NodeDataT *pre, *cur;
	cur = *nodeAdress;
	if(! (*nodeAdress)->left){
		*nodeAdress = (*nodeAdress)->right;
	}else if(! (*nodeAdress)->right){
		*nodeAdress = (*nodeAdress)->left;
	}else{
		cur = (*nodeAdress)->left;
		if(! cur->right){
			(*nodeAdress)->key = cur->key;
			(*nodeAdress)->left = cur->left;
		}else{
			do{
				pre = cur;
				cur = cur->right;
			}while(cur->right);
			 (*nodeAdress)->key = cur->key;
			 pre->right = cur->left;
		}
		
	}
	free(cur);
}

void del(treeADT tree, int number){
	int found = 0;
	NodeDataT *pre, *cur;
	pre = NULL;
	cur = tree->root;
	while(!found && cur){
		pre = cur;
		if(number < cur->key){
			cur = cur->left;
		} else{
			cur = cur->right;
		}
		found = number == cur->key;
	}
	
	if(found){
		tree->size--;
		tree->sum -= number;
		if(! pre){
			deleteNode(& tree->root);
		}else{
			if(number < pre->key){
				deleteNode(& pre->left);
			}else{
				deleteNode(& pre->right);
			}
		}
	}
}

void inorder(treeADT tree, NodeDataT *cp, int n){
    if(cp == NULL && n == 0){
        cp=tree->root;
        n = 1;
    }

    if(cp){
        inorder(tree, cp->left, n);
        printf("%d  ", cp->key);
        inorder(tree, cp->right, n);
    }
}

void preorder(treeADT tree, NodeDataT *cp, int n){
     if(cp == NULL && n == 0){
        cp=tree->root;
        n = 1;
     }

    if(cp){
        printf("%d  ", cp->key);
        preorder(tree, cp->left, n);
        preorder(tree, cp->right, n);
    }
}

void postorder(treeADT tree, NodeDataT *cp, int n){
    if(cp == NULL && n == 0){
        cp=tree->root;
        n = 1;
    }
    
    if(cp){
        postorder(tree, cp->left, n);
        postorder(tree, cp->right, n);
        printf("%d  ", cp->key);
    }
}

void levelorder(treeADT tree){
	NodeDataT *temp, *queue[100];
	int size = 0;
	int take = 0;
	if(tree->root){
		queue[size++] = tree->root;
		while(size > take){
			temp = queue[take++];
			printf("%d ", temp->key);
			if(temp->left != NULL){
				queue[size++] = temp->left;
			}
			if(temp->right != NULL){
				queue[size++] = temp->right;
			}
		}
	}
	printf("\n");
}

int max(treeADT tree){
	NodeDataT *cur;
	if(tree->root){
		cur = tree->root;
		while(cur->right){
			cur = cur->right;
		}
		return cur->key;
	}
	return 0;
}

int min(treeADT tree){
	NodeDataT *cur;
	if(tree->root){
		cur = tree->root;
		while(cur->left){
			cur = cur->left;
		}
		return cur->key;
	}
	return 0;
}

int count(treeADT tree){
	return tree->size;
}

int sum(treeADT tree){
	return tree->sum;
}

int height(treeADT tree, NodeDataT *cp, int n){
    if(cp == NULL && n == 0){
        cp=tree->root;
        n = 1;
    }
    if(!cp){
        return 0;
    }
    
    int a = height(tree, cp->left, n);
	int b = height(tree, cp->right, n);
    
    if(a > b)
        return 1+a;
    else
        return 1+b;
}

void ClearElements(treeADT tree, NodeDataT *cp, int n){
    if(cp == NULL && n == 0){
        cp = tree->root;
        n = 1;
    }
    
    if(cp){
        ClearElements(tree, cp->left, n);
        ClearElements(tree, cp->right, n);
        free(cp);
    }
}

void ClearTree(treeADT tree){
    ClearElements(tree, NULL, 0);
    free(tree);
} 