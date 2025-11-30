#include <stdio.h>
#include <stdlib.h>

typedef struct s {
    int item;
    struct s* next;
} STACK;

STACK* sp = NULL;

int push(int item) {
    STACK* p = (STACK*)malloc(sizeof(STACK));
    if (p == NULL) {
        printf("Memory error!\n");
        return -1;
    }
    p->item = item;
    p->next = sp;
    sp = p;
    return 0;
}

int pop() {
    if (sp == NULL) {
        printf("List is empty!\n");
        return -1;  // INT_MIN kullananlar var?
    }
    STACK* p = sp;
    int i = sp->item;
    sp = sp->next;
    free(p);
    return i;
}

void reset() {
    STACK* p;
    while (sp != NULL) {
        p = sp;
        sp = sp->next;
        free(p);
    }
}

STACK* top() {
    if (sp == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    return sp;
}

int size() {
    STACK* p = sp;
    int i = 0;
    while (p != NULL) {
        p = p->next;
        i++;
    }
    return i;
}

int isEmpty() {
    return sp == NULL;
}

int main() {
    char c;

    printf("Enter a string: ");
    while ((c = getchar()) != '\n') {
        push(c);
    }

    printf("Reversed string: ");
    while (!isEmpty()) {
        printf("%c", pop());
    }
    printf("\n");

    return 0;
}