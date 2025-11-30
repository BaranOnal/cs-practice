#include <stdio.h>
#define SIZE 8


void insertionSort(int arr[]);
void printSort(int arr[]);
int main() {

	int Arr[SIZE] = { 54,78,4,15,55,789,116,0 };

	insertionSort(Arr);
	printSort(Arr);

	return 0;
}

void insertionSort(int arr[])
{
	int key;
	for (int i = 1; i < SIZE; i++)
	{
		key = arr[i];
		for (int k = i - 1; k >= 0 && key < arr[k]; k--)
		{
			arr[k + 1] = arr[k];
			arr[k] = key;
		}

	}
}

void printSort(int arr[])
{
	for (int i = 0; i < SIZE; i++)
	{
		printf("Arr[%d] : %d\n", i, arr[i]);
	}
}
