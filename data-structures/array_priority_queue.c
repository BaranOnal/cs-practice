#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int elements[MAX][2];
int last = 0;

void initQueue() {
    last = 0;
}

int isEmpty() {
    return last == 0;
}

void enqueue(int data, int priority) {
    if (last == MAX) {
        printf("Priority Queue is full!\n");
        return;
    }

    elements[last][0] = data;
    elements[last][1] = priority;
    last++;

    for (int i = last - 1; i > 0; i--) {
        if (elements[i][1] < elements[i - 1][1]) {
            int tempData = elements[i][0];
            int tempPriority = elements[i][1];
            elements[i][0] = elements[i - 1][0];
            elements[i][1] = elements[i - 1][1];
            elements[i - 1][0] = tempData;
            elements[i - 1][1] = tempPriority;
        }
        else 
            break;
    }
}

int dequeue() {
    if (isEmpty()) {
        printf("Priority Queue is empty!\n");
        return -1;
    }

    int data = elements[0][0];

    for (int i = 0; i < last - 1; i++) {
        elements[i][0] = elements[i + 1][0];
        elements[i][1] = elements[i + 1][1];
    }

    last--;
    return data;
}


void display() {
    if (isEmpty()) {
        printf("Priority Queue is empty!\n");
        return;
    }

    printf("Priority Queue:\n");
    for (int i = 0; i < last; i++) {
        printf("Data: %d, Priority: %d\n", elements[i][0], elements[i][1]);
    }
}

int main() {
    initQueue();

    enqueue(10, 2);
    enqueue(30, 3);
    enqueue(20, 1);
    enqueue(3, 3);
    enqueue(0, 0);

    display();

    printf("Dequeued: %d\n\n\n\n", dequeue());

    display();

    return 0;
}
