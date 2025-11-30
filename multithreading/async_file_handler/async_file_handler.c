
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define QUEUE_SIZE 10
#define MAX_FILENAME_LENGTH 50
#define WORKER_COUNT 2
#define FILE_COUNT 5

typedef struct
{
	char files[QUEUE_SIZE][MAX_FILENAME_LENGTH];
	int front;
	int rear;
	int count;
	CRITICAL_SECTION mutex;
	CONDITION_VARIABLE not_full;
	CONDITION_VARIABLE not_empty;
}f_queue;

f_queue queue;

void init_queue(f_queue* queue) {
	queue->front = queue->rear = queue->count = 0;
	InitializeCriticalSection(&queue->mutex);
	InitializeConditionVariable(&queue->not_full);
	InitializeConditionVariable(&queue->not_empty);
}

void enqueue(f_queue* file, const char* file_name) {
	EnterCriticalSection(&file->mutex);
	while (file->count == QUEUE_SIZE)
		SleepConditionVariableCS(&file->not_full, &file->mutex, INFINITE);

	strncpy(file->files[file->rear], file_name, MAX_FILENAME_LENGTH);
	file->rear = (file->rear + 1) % QUEUE_SIZE;
	file->count++;
	WakeConditionVariable(&file->not_empty);
	LeaveCriticalSection(&file->mutex);
}
void dequeue(f_queue* file, char* out_file_name) {
	EnterCriticalSection(&file->mutex);
	while (file->count == 0)
		SleepConditionVariableCS(&file->not_empty, &file->mutex, INFINITE);

	strncpy(out_file_name, file->files[file->front], MAX_FILENAME_LENGTH);
	file->front = (file->front + 1) % QUEUE_SIZE;
	file->count--;

	WakeConditionVariable(&file->not_full);
	LeaveCriticalSection(&file->mutex);
}

DWORD WINAPI worker_thread(LPVOID param) {
	char filename[MAX_FILENAME_LENGTH];
	int thread_id = (int)(intptr_t)param;

	while (1) {
		
		EnterCriticalSection(&queue.mutex);
		if (queue.count == 0) {
			LeaveCriticalSection(&queue.mutex);
			break;
		}
		dequeue(&queue, filename);
		LeaveCriticalSection(&queue.mutex);

		FILE* f = fopen(filename, "r");
		if (!f) {
			printf(stderr, "[Thread %d] Error opening %s\n", thread_id, filename);
			continue;
		}
		int char_count = 0;

		while (fgetc(f) != EOF) {
			char_count++;
		}
		printf("[Thread %d] %s: %d characters\n", thread_id, filename, char_count);
		fclose(f);
	}
	return 0;
}


int main() {
	init_queue(&queue);
	
	const char* files[FILE_COUNT] = {
		"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"
	};
	
	for (int i = 0; i < FILE_COUNT; i++) {
		enqueue(&queue, files[i]);
	}
	HANDLE threads[WORKER_COUNT];

	for (int i = 0; i < WORKER_COUNT; i++) {
		threads[i] = CreateThread(NULL, 0, worker_thread, i, 0, NULL);
	}

	WaitForMultipleObjects(WORKER_COUNT, threads, TRUE, INFINITE);

	for (int i = 0; i < WORKER_COUNT; i++) {
		CloseHandle(threads[i]);
	}

	DeleteCriticalSection(&queue.mutex);

	printf("All files processed");
	return 0;
}