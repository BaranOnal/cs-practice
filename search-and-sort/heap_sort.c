#include<stdio.h>
#define SIZE 8


void heapSort(int arr[]);
void heapify(int arr[],int size, int i);
void printArr(int arr[]);

int main() {
	int Arr[8] = { 5,6,0,7,1,9,3,2 };

	heapSort(Arr);
	printArr(Arr);

	return 0;
}

void heapSort(int arr[])
{
	for (int i = SIZE/2 - 1; 0 <= i; i--)
	{
		heapify(arr, SIZE, i);
	}
	
	for (int i = SIZE - 1; i > 0 ; i--)
	{
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		heapify(arr, i, 0);
	}
}

void heapify(int arr[],int size, int i)
{
	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != i)
	{	
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		heapify(arr, size, largest);
	}
}

void printArr(int arr[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("Arr[%d] : %d \n", i, arr[i]);
	}
}