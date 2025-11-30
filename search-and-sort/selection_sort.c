#include<stdio.h>
#define SIZE 8

void selectionSort(int arr[]);
void printSort(int arr[]);

int main() {
	int Arr[SIZE] = { 45,78,6,111,65,19,0,9 };

	selectionSort(Arr);
	printSort(Arr);
	return 0;
}

void selectionSort(int arr[])
{	
	for (int i = 0; i < SIZE - 1; i++)
	{
		int min = arr[SIZE - 1];
		int index = SIZE - 1;
		for (int k = i; k < SIZE; k++)
		{
			if (arr[k] < min)
			{
				min = arr[k];
				index = k;
			}
		}
		if (index != i)
		{
			arr[index] = arr[i];
			arr[i] = min;
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
