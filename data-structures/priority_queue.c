#include <stdio.h>
#include <stdlib.h>

typedef struct q {
    int data;
    int priority;
    struct q* next;
} QUEUE;

QUEUE* front = NULL;

int enqueue(int item, int value) {
    QUEUE* p = (QUEUE*)malloc(sizeof(QUEUE));
    if (!p) {
        printf("Memory error\n");
        return -1;
    }

    p->data = item;
    p->priority = value;
    p->next = NULL;

    if (front == NULL || value < front->priority) {
        p->next = front;
        front = p;
    }
    else {
        QUEUE* current = front;
        while (current->next != NULL && current->next->priority <= value) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
    }

    return 1;
}

int dequeue() {
    if (!front) {
        printf("Queue is empty!\n");
        return -1;
    }

    QUEUE* p = front;
    int data = p->data;
    front = front->next;
    free(p);

    return data;
}

int main() {
    enqueue(5, 4);
    enqueue(7, 0);
    enqueue(15, 0);
    enqueue(1, 1);

    while (front) {
        printf("%d -> ", dequeue());
    }
    printf("NULL\n");

    return 0;
}