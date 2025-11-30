#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int row, col, time;
}QueueNode;

typedef struct Queue{
    QueueNode data[MAX * MAX];
    int front, rear;
}Queue;

void initQueue(Queue* q) { q->front = q->rear = 0; }

int isEmpty(Queue* q) { return q->front == q->rear; }

void enqueue(Queue* q, int row, int col, int time) {
    q->data[q->rear++] = QueueNode{ row, col, time };
}

QueueNode dequeue(Queue* q) { return q->data[q->front++]; }

int minTimeToRot(int grind[MAX][MAX], int rows, int cols) {
    Queue q;
    initQueue(&q);

    int freshCount = 0, time = 0;
    int directions[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grind[r][c] == 2)
                enqueue(&q, r, c, 0);
            else if (grind[r][c] == 1)
                freshCount++;
        }
    }
    if (freshCount == 0) return 0;

    while (!isEmpty(&q)) {
        QueueNode node = dequeue(&q);
        int r = node.row, c = node.col;
        time = node.time;

        for (int i = 0; i < 4; i++) {
            int nr = r + directions[i][0], nc = c + directions[i][1];

            if (nr >= 0 && nr <= rows && nc >= 0 && nc <= cols && grind[nr][nc] == 1) {
                grind[nr][nc] = 2;
                freshCount--;
                enqueue(&q, nr, nc, time+1);
            }
        }
    }
    return (freshCount == 0) ? time : -1;
}




int main() {
    int grid[MAX][MAX] = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int rows = 3, cols = 3;
    int result = minTimeToRot(grid, rows, cols);
    printf("Minimum time to rot all oranges: %d\n", result);

    return 0;
}