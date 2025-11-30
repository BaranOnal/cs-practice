#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bTree {
    int info;
    char message[100];
    struct bTree* left;
    struct bTree* right;
} BTREE;

BTREE* root = NULL;

// node oluþturma
BTREE* readNode() {
    BTREE* newNode = (BTREE*)malloc(sizeof(BTREE));
    if (newNode == NULL) return NULL;

    printf("Enter info: ");
    scanf("%d", &(newNode->info));

    printf("Enter message: ");
    scanf("%s", newNode->message);

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(BTREE* treeRoot, BTREE* newNode) {
    if (root == NULL) {
        root = newNode;
    }
    else {
        if (newNode->info < treeRoot->info) {
            if (treeRoot->left == NULL)
                treeRoot->left = newNode;
            else
                insert(treeRoot->left, newNode);
        }
        else {
            if (treeRoot->right == NULL)
                treeRoot->right = newNode;
            else
                insert(treeRoot->right, newNode);
        }
    }
}

BTREE* search(BTREE* treeRoot, int item) {
    while (treeRoot != NULL && treeRoot->info != item) {
        if (item < treeRoot->info)
            treeRoot = treeRoot->left;
        else
            treeRoot = treeRoot->right;
    }
    return treeRoot;
}
//Node sayýsý
int countNodes(BTREE* treeRoot, int sum) {
    if (treeRoot == NULL) return sum;
    sum++;
    sum = countNodes(treeRoot->left, sum);
    sum = countNodes(treeRoot->right, sum);
    return sum;
}
int countNodes2(BTREE* treeRoot) {
    int sum = 0;

    if (treeRoot != NULL) {
        sum++;
        countNodes2(treeRoot->left);
        countNodes2(treeRoot->right);
    }
    return sum;
}
int countNodes3(BTREE* treeRoot) {
    if (treeRoot == NULL)
        return 0;
    return 1 + countNodes3(treeRoot->left) + countNodes3(treeRoot->right);
}

BTREE* deleteNode(BTREE* treeRoot, int data) {
    BTREE* q = treeRoot, * qa = NULL, * qc, * s, * sa;

    // Düðümü bul
    while (q != NULL && q->info != data) {
        qa = q;
        if (data < q->info)
            q = q->left;
        else
            q = q->right;
    }

    if (q == NULL) {
        printf("Item to be deleted is not found\n");
        return treeRoot;
    }

    // Ýki çocuklu node için (q sol aðacýn en saðý olur)
    if (q->left != NULL && q->right != NULL) {
        s = q->left;
        sa = q;
        while (s->right != NULL) {
            sa = s;
            s = s->right;
        }
        q->info = s->info;
        strcpy(q->message, s->message);
        q = s;
        qa = sa;
    }

    // Tek çocuklu veya çocuksuz
    qc = (q->left != NULL) ? q->left : q->right;

    if (q == treeRoot) {
        treeRoot = qc;  // Yeni kök düðüm
    }
    else {
        if (q == qa->left)
            qa->left = qc;
        else
            qa->right = qc;
    }

    free(q);
    return treeRoot;
}

// Aðaç dolaþma fonksiyonu (Pre-order)
void traverse(BTREE* treeRoot) {
    if (treeRoot != NULL) {
        printf("%d %s\n", treeRoot->info, treeRoot->message);
        traverse(treeRoot->left);
        traverse(treeRoot->right);
    }
}

int main() {
    BTREE* n, * a;
    int choice, i, count;

    while (1) {
        printf("\n1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. List nodes (Pre-order Traversal)\n");
        printf("4. Search for a node\n");
        printf("5. Count number of nodes\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            n = readNode();
            insert(root, n);
            break;
        case 2:
            printf("Enter node to be deleted: ");
            scanf("%d", &i);
            root = deleteNode(root, i);
            break;
        case 3:
            if (root != NULL)
                traverse(root);
            else
                printf("Tree is empty\n");
            break;
        case 4:
            printf("Enter node to be searched for: ");
            scanf("%d", &i);
            a = search(root, i);
            if (a != NULL)
                printf("Found: %d %s\n", a->info, a->message);
            else
                printf("Item is not found\n");
            break;
        case 5:
            count = countNodes(root, 0);
            printf("Number of nodes in the tree = %d\n", count);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}