#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define QUEUE_SIZE 10
#define MAX_FILENAME_LENGTH 50
#define WORKER_COUNT 2
#define FILE_COUNT 5

typedef struct {
    char files[QUEUE_SIZE][MAX_FILENAME_LENGTH];
    int front;
    int rear;
    int count;
    CRITICAL_SECTION mutex;
    CONDITION_VARIABLE not_full;
    CONDITION_VARIABLE not_empty;
} f_queue;

f_queue queue;

void init_queue(f_queue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    InitializeCriticalSection(&queue->mutex);
    InitializeConditionVariable(&queue->not_full);
    InitializeConditionVariable(&queue->not_empty);
}

void enqueue(f_queue* q, const char* file_name) {
    EnterCriticalSection(&q->mutex);
    while (q->count == QUEUE_SIZE) {
        SleepConditionVariableCS(&q->not_full, &q->mutex, INFINITE);
    }

    strncpy(q->files[q->rear], file_name, MAX_FILENAME_LENGTH);
    q->files[q->rear][MAX_FILENAME_LENGTH - 1] = '\0'; // Null-termination garantisi
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->count++;

    WakeConditionVariable(&q->not_empty);
    LeaveCriticalSection(&q->mutex);
}

void dequeue(f_queue* q, char* out_file_name) {
    EnterCriticalSection(&q->mutex);
    while (q->count == 0) {
        SleepConditionVariableCS(&q->not_empty, &q->mutex, INFINITE);
    }

    strncpy(out_file_name, q->files[q->front], MAX_FILENAME_LENGTH);
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;

    WakeConditionVariable(&q->not_full);
    LeaveCriticalSection(&q->mutex);
}

DWORD WINAPI worker_thread(LPVOID param) {
    char filename[MAX_FILENAME_LENGTH];
    int thread_id = (int)param;

    while (1) {
        EnterCriticalSection(&queue.mutex);
        if (queue.count == 0) {
            LeaveCriticalSection(&queue.mutex);
            break;
        }
        LeaveCriticalSection(&queue.mutex);

        dequeue(&queue, filename);

        FILE* f = fopen(filename, "r");
        if (!f) {
            printf("[Thread %d] Error opening %s\n", thread_id, filename);
            continue;
        }

        int char_count = 0;
        while (fgetc(f) != EOF) char_count++;
        printf("[Thread %d] %s: %d characters\n", thread_id, filename, char_count);
        fclose(f);
    }
    return 0;
}

int main() {
    init_queue(&queue);

    const char* files[FILE_COUNT] = {
        "file1.txt", "file2.txt", "file3.txt",
        "file4.txt", "file5.txt"
    };

    // Kuyruða dosyalarý ekle
    for (int i = 0; i < FILE_COUNT; i++) {
        enqueue(&queue, files[i]);
    }

    // Thread'leri oluþtur
    HANDLE threads[WORKER_COUNT];
    for (int i = 0; i < WORKER_COUNT; i++) {
        threads[i] = CreateThread(NULL, 0, worker_thread, (LPVOID)i, 0, NULL);
        if (threads[i] == NULL) {
            fprintf(stderr, "Failed to create thread %d\n", i);
            return 1;
        }
    }

    // Thread'lerin bitmesini bekle
    WaitForMultipleObjects(WORKER_COUNT, threads, TRUE, INFINITE);

    // Temizlik
    for (int i = 0; i < WORKER_COUNT; i++) CloseHandle(threads[i]);
    DeleteCriticalSection(&queue.mutex);

    printf("\nAll files processed successfully!\n");
    return 0;
}