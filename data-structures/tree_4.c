#include <stdio.h>
#include <stdlib.h>

typedef struct bTree {
    int item;
    struct bTree* left;
    struct bTree* right;
} bTree;

bTree* root = NULL;

bTree* newNode(int key) {
    bTree* node = (bTree*)malloc(sizeof(bTree));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->left = NULL;
    node->right = NULL;
    node->item = key;

    return node;
}

bTree* insert(bTree* treeRoot, int data) {
    if (treeRoot == NULL)
        return newNode(data);

    if (data < treeRoot->item)
        treeRoot->left = insert(treeRoot->left, data);
    else if (data > treeRoot->item)
        treeRoot->right = insert(treeRoot->right, data);
    
        return treeRoot;
}

bTree* search(bTree* treeRoot, int data) {
    while (treeRoot != NULL && data != treeRoot->item) {
        if (data < treeRoot->item)
            treeRoot = treeRoot->left;
        else
            treeRoot = treeRoot->right;
    }
    return treeRoot;
}

int countNodes(bTree* treeRoot) {
    if (treeRoot == NULL)
        return 0;
    return 1 + countNodes(treeRoot->left) + countNodes(treeRoot->right);
}

bTree* deleteNode(bTree* treeRoot, int data) {
    bTree* q = treeRoot, * qa = NULL, * qc, * s, * sa;

    while (q != NULL && data != q->item) {
        qa = q;
        if (data < q->item)
            q = q->left;
        else
            q = q->right;
    }

    if (q == NULL) {
        printf("Item to be deleted is not found\n");
        return treeRoot;
    }

    if (q->left != NULL && q->right != NULL) {
        s = q->left;
        sa = q;

        while (s->right != NULL) {
            sa = s;
            s = s->right;
        }
        q->item = s->item;
        q = s;
        qa = sa;
    }

    qc = (q->left == NULL) ? q->right : q->left;

    if (q == treeRoot)
        treeRoot = qc;
    else {
        if (q == qa->left)
            qa->left = qc;
        else
            qa->right = qc;
    }

    free(q);
    return treeRoot;
}

void traverse(bTree* treeRoot) {
    if (treeRoot != NULL) {
        printf("%d\n", treeRoot->item);
        traverse(treeRoot->left);
        traverse(treeRoot->right);
    }
}

void freeTree(bTree* treeRoot) {
    if (treeRoot != NULL) {
        freeTree(treeRoot->left);
        freeTree(treeRoot->right);
        free(treeRoot);
    }
}

int main() {
    int choice, value;
    bTree* result;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Count Nodes\n");
        printf("5. Traverse (Pre-order)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;

        case 2:
            printf("Enter the value to search: ");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("Value %d found in the tree.\n", result->item);
            else
                printf("Value %d not found in the tree.\n", value);
            break;

        case 3:
            printf("Enter the value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;

        case 4:
            printf("Total nodes in the tree: %d\n", countNodes(root));
            break;

        case 5:
            printf("Tree elements (Pre-order traversal):\n");
            traverse(root);
            break;

        case 6:
            printf("Exiting...\n");
            freeTree(root);
            return 0;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
