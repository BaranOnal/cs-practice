#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int key;
	struct tree* left;
	struct tree* right;
	int height;
}tree;


int height(tree* node) {
	if (node == NULL)
		return 0;
	return node->height;
}

tree* newNode(int key) {

	tree* node = (tree*)malloc(sizeof(tree));
	if (node == NULL)
		return NULL;

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
}

tree* rightRotate(tree* x) {
	tree* y = x->left;
	tree* z = y->right;


	y->right = x;
	x->left = z;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

tree* leftRotate(tree* x) {
	tree* y = x->right;
	tree* z = y->left;

	y->left = x;
	x->right = z;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(tree* node) {
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}


tree* insert(tree* treeRoot, int data) {
	if (treeRoot == NULL)
		return newNode(data);

	if (data < treeRoot->key)
		treeRoot->left = insert(treeRoot->left, data);
	else if (data > treeRoot->key)
		treeRoot->right = insert(treeRoot->right, data);
	else
		return treeRoot;

	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right)) + 1;

	int balance = getBalance(treeRoot);


	if (balance > 1 && data < treeRoot->left->key)
		return rightRotate(treeRoot);
	if (balance < -1 && data > treeRoot->right->key)
		return leftRotate(treeRoot);

	if (balance > 1 && data > treeRoot->left->key) {
		treeRoot->left = leftRotate(treeRoot->left);
		return rightRotate(treeRoot);
	}
	if (balance < -1 && data < treeRoot->right->key) {
		treeRoot->right = rightRotate(treeRoot->right);
		return leftRotate(treeRoot);
	}

	return treeRoot;
}

void preOrder(tree* treeRoot)
{
	if (treeRoot != NULL)
	{
		printf("%d ", treeRoot->key);
		preOrder(treeRoot->left);
		preOrder(treeRoot->right);
	}
}

int main()
{
	tree* root = NULL;

	/* Constructing tree given in the above figure */
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	/* The constructed AVL Tree would be
			  30
			 /  \
		   20   40
		  /  \     \
		 10  25    50
	*/

	printf("Preorder traversal : \n");
	preOrder(root);

	return 0;
}