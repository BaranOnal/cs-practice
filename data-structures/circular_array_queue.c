#include <stdio.h>
#define N 10

int Q[N];
int front = 0, last = 0, count;


int enqueue(int item) {
	if (count >= N) {
		printf("List is full!\n");
		return -1;
	}
	else {
		Q[last] = item;
		last = (last + 1) % N;
		count++;
		return 0;
	}
}

int dequeue() {
	int item;
	if (count == 0) {
		printf("List is empty!\n");
		return -1;
	}
	else {
		item = Q[front];
		front = (front + 1) % N;
		count--;
		return item;
	}
}

void reset() {
	front = last = count = 0;
}

int main() {
	char c;
	while ((c = getchar()) != '\n') {
		enqueue(c);
	}

	dequeue();

	while ((c = getchar()) != '\n') {
		enqueue(c);
	}

	while (count > 0) {
		printf("%c", dequeue());
	}

	printf("\n");

	return 0;
}