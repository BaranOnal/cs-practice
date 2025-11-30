#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

CRITICAL_SECTION mutex;
CONDITION_VARIABLE cond_full;
CONDITION_VARIABLE cond_empty;

DWORD WINAPI producer(LPVOID param) {
    int item;
    while (1) {
        item = rand() % 100;

        EnterCriticalSection(&mutex);

        while (count == BUFFER_SIZE) {
            SleepConditionVariableCS(&cond_empty, &mutex, INFINITE);
        }

        buffer[count++] = item;
        printf("Producer produced: %d\n", item);

        WakeConditionVariable(&cond_full);
        LeaveCriticalSection(&mutex);

        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    int item;
    while (1) {
        EnterCriticalSection(&mutex);

        while (count == 0) {
            SleepConditionVariableCS(&cond_full, &mutex, INFINITE);
        }

        item = buffer[--count];
        printf("Consumer consumed: %d\n", item);

        WakeConditionVariable(&cond_empty);
        LeaveCriticalSection(&mutex);

        Sleep(1500);
    }
    return 0;
}

int main() {
    HANDLE prodThread, consThread;

    InitializeCriticalSection(&mutex);
    InitializeConditionVariable(&cond_full);
    InitializeConditionVariable(&cond_empty);

    prodThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    // Sonsuza kadar bekliyoruz
    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    CloseHandle(prodThread);
    CloseHandle(consThread);
    DeleteCriticalSection(&mutex);
    return 0;
}
