#include <stdio.h>
#include <Windows.h>

#define QUEUE_SIZE 10
#define WORKER_COUNT 4
#define JOB_COUNT 10

typedef struct {
	void (*function)(void*);
	void* arg;
}Job;

typedef struct {
	int front, rear, count;

	Job jobs[QUEUE_SIZE];

	CRITICAL_SECTION lock;
	CONDITION_VARIABLE not_full;
	CONDITION_VARIABLE not_empty;
}JobQueue;

JobQueue queue;

void init_queue(JobQueue* queue) {
	queue->count = queue->front = queue->rear = 0;
	InitializeCriticalSection(&queue->lock);
	InitializeConditionVariable(&queue->not_empty);
	InitializeConditionVariable(&queue->not_full);
}


void submit_job(JobQueue* q, void (*function)(void*), void* arg) {
	EnterCriticalSection(&q->lock);
	while (q->count == QUEUE_SIZE)
		SleepConditionVariableCS(&q->not_full, &q->lock, INFINITE);

	q->jobs[q->rear].function = function;
	q->jobs[q->rear].arg = arg;
	q->rear = (q->rear + 1) % QUEUE_SIZE;
	q->count++;

	WakeConditionVariable(&q->not_empty);
	LeaveCriticalSection(&q->lock);
}

DWORD WINAPI worker_thread(LPVOID param) {
	JobQueue* q = (JobQueue*)param;
	while (1) {
		EnterCriticalSection(&q->lock);
		while (q->count == 0)
			SleepConditionVariableCS(&q->not_empty, &q->lock, INFINITE);

		Job job = q->jobs[q->front];
		q->front = (q->front + 1) % QUEUE_SIZE;
		q->count--;

		WakeConditionVariable(&q->not_full);
		LeaveCriticalSection(&q->lock);

		if (job.function == NULL)
			break;

		job.function(job.arg);
	}
}

DWORD WINAPI input_thread(LPVOID param) {
	JobQueue* q = (JobQueue*)param;
	char cmd;

	while (1) {
		cmd = getchar();

		if (cmd == 'q') {
			for (int i = 0; i < WORKER_COUNT; i++)
				submit_job(q, NULL, NULL);

			break;
		}
	}
	return 0;
}

void example_job(void* arg) {
	int* num = (int*)arg;
	printf("%d is being processed.\n", *num);
	free(num);
	Sleep(500);  // Simülasyon
}


int main() {
	init_queue(&queue);

	HANDLE threads[4], input;
	for (int i = 0; i < WORKER_COUNT; i++) {
		threads[i] = CreateThread(NULL, 0, worker_thread, &queue, 0, NULL);
	}
	input = CreateThread(NULL, 0, input_thread, &queue, 0, NULL);

	for (int i = 0; i < JOB_COUNT; i++) {
		int* num = malloc(sizeof(int));
		if (num == NULL)
			exit(1);
		*num = i;
		submit_job(&queue, example_job, num);
	}

	WaitForSingleObject(input, INFINITE);
	WaitForMultipleObjects(WORKER_COUNT, threads, TRUE, INFINITE);

	return 0;
}