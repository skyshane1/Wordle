#include <string.h>
#include <stdlib.h>

typedef struct {
	char *data[6];
	struct Node *right;
	struct Node *left;	
} Node;

Node *create_node(char *data);

typedef struct {
	Node *root;	
} BST;

BST *create_bst();

Node *bst_insertAt(char *data, Node *node);

void bst_insert(BST *bst, char *data);

Node *bst_searchAt(char *data, Node *node);

char *bst_search(BST *bst, char *data);
