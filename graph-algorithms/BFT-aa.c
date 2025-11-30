#include <stdio.h>
#include <stdbool.h>

int G[9][9] = {
    {0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0}
};// a  b  c  d  e  f  g  h  i

int visited[9] = { 0 };

int queue[9], front = -1, rear = -1;

void enqueue(int value) {
    if (rear == 8) return; // Kuyruk dolu
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1 || front > rear) return -1; // Kuyruk boþ
    return queue[front++];
}

bool isEmptyQueue() {
    return front == -1 || front > rear;
}
void BFT() {
    int node, n, i;
    for (node = 0; node < 9; node++) {
        if (visited[node] == 0) {
            enqueue(node);
            while (!isEmptyQueue()) {
                n = dequeue();
                if (visited[n] != 0)
                    continue;
                printf("%c\n", 'a' + n);
                for (i = 0; i < 9; i++) {
                    if ((G[n][i] != 0) && (visited[i] == 0))
                        enqueue(i);
                    visited[n] = 1;

                }
            }
        }
    }
}   

int main() {
    printf("Breadth-First Traversal Output:\n");
    BFT();
    return 0;
}
