#include <stdio.h>

#define ROWS 5
#define COLS 5


//DFS
void floodFill(int image[ROWS][COLS], int x, int y, int newColor, int originalColor) {
    // Sýnýr kontrolü
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) return;

    // Eðer hücre farklý bir renkteyse veya zaten boyanmýþsa dur
    if (image[x][y] != originalColor || image[x][y] == newColor) return;

    // Yeni rengi uygula
    image[x][y] = newColor;

    // 4 yönlü ilerleme (yukarý, aþaðý, sað, sol)
    floodFill(image, x + 1, y, newColor, originalColor);
    floodFill(image, x - 1, y, newColor, originalColor);
    floodFill(image, x, y + 1, newColor, originalColor);
    floodFill(image, x, y - 1, newColor, originalColor);
}

void printImage(int image[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int image[ROWS][COLS] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    printf("Orijinal Resim:\n");
    printImage(image);

    int x = 0, y = 0; // Baþlangýç noktasý
    int newColor = 2; // Yeni renk
    floodFill(image, x, y, newColor, image[x][y]);

    printf("\nFlood Fill Sonrasý:\n");
    printImage(image);

    return 0;
}


//----------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

typedef struct {
    int x, y;
} Point;

void floodFillBFS(int image[ROWS][COLS], int x, int y, int newColor) {
    int originalColor = image[x][y];
    if (originalColor == newColor) return;

    // Basit bir kuyruk yapýsý
    Point queue[ROWS * COLS];
    int front = 0, rear = 0;

    queue[rear++] = (Point){ x, y };

    while (front < rear) {
        Point p = queue[front++];
        int px = p.x, py = p.y;

        // Sýnýr kontrolü ve renk kontrolü
        if (px < 0 || px >= ROWS || py < 0 || py >= COLS || image[px][py] != originalColor)
            continue;

        // Yeni rengi ata
        image[px][py] = newColor;

        // Komþularý kuyruða ekle
        queue[rear++] = (Point){ px + 1, py };
        queue[rear++] = (Point){ px - 1, py };
        queue[rear++] = (Point){ px, py + 1 };
        queue[rear++] = (Point){ px, py - 1 };
    }
}

void printImage(int image[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int image[ROWS][COLS] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    printf("Orijinal Resim:\n");
    printImage(image);

    int x = 0, y = 0;
    int newColor = 2;
    floodFillBFS(image, x, y, newColor);

    printf("\nFlood Fill Sonrasý:\n");
    printImage(image);

    return 0;
}
