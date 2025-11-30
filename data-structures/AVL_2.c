#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int item;
	int height;
	struct node* left;
	struct node* right;
}node;

int height(node* n) {
	if (n == NULL)
		return 0;
	return n->height;
}

node* newNode(int key) {
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL)
		return NULL;
	newNode->item = key;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

int getBalance(node* node) {
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

node* rightRotate(node* x) {
	node* y = x->left;
	node* z = y->right;

	y->right = x;
	x->left = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

node* leftRotate(node* x) {
	node* y = x->right;
	node* z = y->left;

	y->left = x;
	x->right = z;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

void printTree(node* treeRoot) {
	if (treeRoot != NULL) {
		printTree(treeRoot->left);
		printf("%d  ", treeRoot->item);
		printTree(treeRoot->right);
	}
}

node* insert(node* treeRoot, int key) {
	if (treeRoot == NULL)
		return newNode(key);

	if (key < treeRoot->item)
		treeRoot->left = insert(treeRoot->left, key);
	else if (key > treeRoot->item)
		treeRoot->right = insert(treeRoot->right, key);
	else
		return treeRoot;

	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right));

	int balance = getBalance(treeRoot);

	if (balance > 1 && key < treeRoot->left->item)
		return rightRotate(treeRoot);

	if (balance < -1 && key > treeRoot->right->item)
		return leftRotate(treeRoot);

	if (balance > 1 && key > treeRoot->left->item) {
		treeRoot->left = leftRotate(treeRoot->left);
		return rightRotate(treeRoot);
	}

	if (balance < -1 && key < treeRoot->left->item) {
		treeRoot->right = rightRotate(treeRoot->right);
		return leftRotate(treeRoot);
	}
	return treeRoot;
}

int main() {
	node* root = NULL;
	
	root = insert(root, 15);
	root = insert(root, 30);
	root = insert(root, 50);
	root = insert(root, 25);
	root = insert(root, 10);
	root = insert(root, 10);
	root = insert(root, 5);


	printf("Preorder traversal : \n");
	printTree(root);
	return 0;
}
