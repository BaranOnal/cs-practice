#include <stdio.h>
#define SIZE 8

void quickSort(int left, int right,int arr[]);
void printArr(int arr[]);

int main() {

	int Arr[SIZE] = { 45,111,98,55,0,9,32,44 };

	quickSort(0, SIZE - 1, Arr);
	printArr(Arr);

	return 0;
}

void quickSort(int left, int right,int arr[])
{
	int p = arr[(left + right) / 2];
	int i = left, j = right, temp;
	do
	{
		while (arr[i] < p && i <= right)
		{
			i++;
		}
		while (arr[j] > p && j >= left)
		{
			j--;
		}
		if (i <= j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
		if (j > left) {
			quickSort(left, j, arr); // Burada "left" ve "j" parametreleri düzeltilmeli
		}
		if (i < right) {
			quickSort(i, right, arr); // Burada "i" ve "right" parametreleri düzeltilmeli
		}

	
	} while (i <= j);
}

void printArr(int arr[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("Arr[%d] : %d\n", i, arr[i]);
	}
}