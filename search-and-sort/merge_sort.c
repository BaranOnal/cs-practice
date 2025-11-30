#include <stdio.h>
#define SIZE 8

void mergeSort(int left, int right,int arr[]);
void merge(int l, int r, int m, int arr[]);
void printArr(int arr[]);

int temp[SIZE];

int main() {
	int Arr[SIZE] = { 45,78,5,84,111,0,56,30 };

	mergeSort(0, SIZE - 1, Arr);

	printArr(Arr);

	return 0;
}

void mergeSort(int left, int right, int arr[]){
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(left, mid, arr);
		mergeSort(mid + 1, right, arr);
		merge(left, right, mid, arr);
	}
}

void merge(int l, int r, int m, int arr[]){
	int j = m + 1, i = l, k = 0;
	for (; i <= m && j <= r; ) {
		if (arr[i] < arr[j]) {
			temp[k] = arr[i];
			i++;
			k++;
		}
		else {
			temp[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= m)
	{
		temp[k] = arr[i];
		i++;
		k++;

	}
	while (j <= r)
	{
		temp[k] = arr[j];
		j++;
		k++;
	}
	for (int p = l, q = 0; p <= r; p++, q++) {
		arr[p] = temp[q];
	}
}

void printArr(int arr[]){
	for (int i = 0; i < SIZE; i++){
		printf("Arr[%d] : %d\n", i, arr[i]);
	}
}
