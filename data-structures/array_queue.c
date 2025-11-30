#include <stdio.h>
#define N 15

int Q[N];
int last = 0;

int enqueue(int item) {
	if (last == N) {
		printf("List is full!\n");
		return -1;
	}
	else {
		Q[last] = item;
		last++;
		return 0;
	}
}

int dequeue() {
	int item;
	if (last == 0) {
		printf("List is empty!\n");
		return -1;
	}
	else {
		item = Q[0];
		for (int i = 1; i < last; i++)
			Q[i - 1] = Q[i];  //        front = (front + 1) % N;    döngüsel arttýrma ,shift yapma greksinimi kalmaz

		last--;
		return item;
	}
}

void reset() {
	last = 0;
}

int main() {
	char c;
	while ((c = getchar()) != '\n') {
		enqueue(c);
	}

	while (last > 0) {
		printf("%c", dequeue());
	}

	printf("\n");

	return 0;
}