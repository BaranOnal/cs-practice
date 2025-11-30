#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROW 5
#define COL 5

int rowMove[4] = { -1,1,0,0 };
int colMove[4] = { 0,0,-1,1 };

typedef struct {
    int x, y;
    int dist;
} Node;

typedef struct {
    Node* nodes;
    int front, rear, size;
} Queue;

Queue* createQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) exit(1);
    q->nodes = (Node*)malloc(size * sizeof(Node));
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

void enqueue(Queue* q, int x, int y, int dist) {
    q->nodes[q->rear++] = (Node){ x, y, dist };
}

Node dequeue(Queue* q) {
    return q->nodes[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

int isValid(int maze[ROW][COL], int visited[ROW][COL], int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL && maze[x][y] == 1 && !visited[x][y]);
}

int shortestPath(int maze[ROW][COL], int sx, int sy, int dx, int dy) {
    if (maze[sx][sy] == 0 || maze[dx][dy] == 0) return -1;

    int visited[ROW][COL] = { 0 };
    visited[sx][sy] = 1;

    Queue* q = createQueue(ROW * COL);
    enqueue(q, sx, sy, 0);

    while (!isEmpty(q)) {
        Node current = dequeue(q);

        // Hedefe ulaþtýk mý?
        if (current.x == dx && current.y == dy)
            return current.dist;

        // 4 Yöne hareket et
        for (int i = 0; i < 4; i++) {
            int newX = current.x + rowMove[i];
            int newY = current.y + colMove[i];

            if (isValid(maze, visited, newX, newY)) {
                visited[newX][newY] = 1;
                enqueue(q, newX, newY, current.dist + 1);
            }
        }
    }
    return -1;
}


int main() {
    int maze[ROW][COL] = {
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 1}
    };

    int startX = 0, startY = 0;
    int destX = 4, destY = 4;

    int result = shortestPath(maze, startX, startY, destX, destY);

    if (result != -1)
        printf("En kýsa yol uzunluðu: %d\n", result);
    else
        printf("Hedefe ulaþmak mümkün deðil!\n");

    return 0;
}