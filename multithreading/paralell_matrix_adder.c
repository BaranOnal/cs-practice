#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define R 1000  // 1000x1000 matris
#define C 1000
#define M 10    // 10 matris
#define MAX_THREADS 16

int matrices[R][C][M];
int result[R][C];

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

// Matrisleri rastgele üret
void generate_matrices() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (int k = 0; k < M; k++) {
                matrices[i][j][k] = rand() % 10;
            }
        }
    }
}

// Single-thread versiyon
void single_thread_add() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int sum = 0;
            for (int k = 0; k < M; k++) {
                sum += matrices[i][j][k];
            }
            result[i][j] = sum;
        }
    }
}

// Multi-thread versiyon
DWORD WINAPI worker_thread(LPVOID param) {
    ThreadData* data = (ThreadData*)param;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < C; j++) {
            int sum = 0;
            for (int k = 0; k < M; k++) {
                sum += matrices[i][j][k];
            }
            result[i][j] = sum;
        }
    }
    return 0;
}

void multi_thread_add(int thread_count) {
    HANDLE threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    int rows_per_thread = R / thread_count;
    int remainder = R % thread_count;
    int current_row = 0;

    for (int i = 0; i < thread_count; i++) {
        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + rows_per_thread + (i < remainder ? 1 : 0);
        current_row = thread_data[i].end_row;

        threads[i] = CreateThread(NULL, 0, worker_thread, &thread_data[i], 0, NULL);
    }

    WaitForMultipleObjects(thread_count, threads, TRUE, INFINITE);

    for (int i = 0; i < thread_count; i++) {
        CloseHandle(threads[i]);
    }
}

int main() {
    generate_matrices();
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    // Single-thread test
    QueryPerformanceCounter(&start);
    single_thread_add();
    QueryPerformanceCounter(&end);
    double single_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    // Multi-thread test (1-16 thread)
    printf("Thread Count\tTime (s)\tSpeedup\n");
    printf("------------------------------------\n");
    printf("1 (Single)\t%.4f\t\t1.00x\n", single_time);

    for (int threads = 2; threads <= MAX_THREADS; threads++) {
        memset(result, 0, sizeof(result));

        QueryPerformanceCounter(&start);
        multi_thread_add(threads);
        QueryPerformanceCounter(&end);

        double multi_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        printf("%d\t\t%.4f\t\t%.2fx\n", threads, multi_time, single_time / multi_time);
    }

    return 0;
}