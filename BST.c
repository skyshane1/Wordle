#include <string.h>
#include <stdlib.h>

typedef struct {
	char *data[6];
	struct Node *left;
	struct Node *right;
} Node;

Node *create_node(char *data){
	Node *n = malloc(sizeof(Node));
	strcpy(n->data, data);
	n->left = NULL;
	n->right = NULL;
	return n;
}

typedef struct {
	Node *root;
} BST;

BST *create_bst() {
	BST *bst = malloc(sizeof(BST));
	bst->root = NULL;
	return bst;
}

Node *bst_insertAt(char *data, Node *node){
	if(node == NULL){
		Node *new_node = create_node(data);
		return new_node;
	}
	if(strcmp(node->data,data) < 0 ){
		node->right = bst_insertAt(data, node->right);
	} else {
		node->left = bst_insertAt(data, node->left);
	}
	return node;
}

void bst_insert(BST *bst, char *data){
	bst->root = bst_insertAt(data, bst->root);
}

Node *bst_searchAt(char *data, Node *node){
	if(node == NULL){
		return NULL;
	} else if (strcmp(node->data, data) == 0){
		return node;
	} else if (strcmp(node->data, data) < 0){
		return bst_searchAt(data, node->right);
	} else {
		return bst_searchAt(data, node->left);
	}
}

char *bst_search(BST *bst, char *data){
	Node *node = bst_searchAt(data, bst->root);
	if(node == NULL) {
		return NULL;
	} else {
		return node->data;
	}
}	
