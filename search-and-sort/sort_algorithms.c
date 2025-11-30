#include <stdio.h>
#define SIZE 8


//Insertion Sort
void inertionSort(int arr[]);

//Selection Sort
void selectionSort(int arr[]);

//Bubble Sort
void bubbleSort(int arr[]);

//Merge Sort
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

//Quick Sort
void quickSort(int arr[], int left, int right);

//Heap Sort
void heapSort(int arr[]);
void heapy(int arr[], int i);
int heap_size = SIZE;

void printArr(int arr[]);

int main() {

	int Arr[SIZE] = { 45,78,5,84,111,0,56,30 };

	//inertionSort(Arr);
	
	//selectionSort(Arr);
	
	//bubbleSort(Arr);

	//mergeSort(Arr, 0, SIZE - 1);
	
	//quickSort(Arr, 0, SIZE - 1);

	//heapSort(Arr);

	printArr(Arr);

	return 0;
}


void inertionSort(int arr[])
{
	int key;

	for (int i = 1; i < SIZE; i++)
	{
		key = arr[i];
		for (int j = i - 1; j >= 0 && key < arr[j] ; j--)
		{
			arr[j + 1] = arr[j];
			arr[j] = key;
		}
	}
}


void selectionSort(int arr[])
{
	int index, min;
	for (int i = 0; i < SIZE; i++)
	{
		index = i;
		min = arr[i];
		for (int j = i + 1; j < SIZE; j++)
		{
			if (arr[j] < min)
			{
				index = j;
				min = arr[j];
			}
		}
		if (i != index)
		{
			arr[index] = arr[i];
			arr[i] = min;
		}
	}
}


void bubbleSort(int arr[])
{
	int temp;
	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

}


void mergeSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);


	}
}

void merge(int arr[], int left, int mid, int right)
{
	int i = left, j = mid + 1, temp[SIZE], k = 0;
	for (; i <= mid && j <= right; )
	{
		if (arr[i] > arr[j])
		{
			temp[k] = arr[j];
			j++;
			k++;
		}
		else
		{
			temp[k] = arr[i];
			i++;
			k++;
		}
	}


	for (i = left, k = 0; i <= right; i++, k++)
		arr[i] = temp[k];
}


void quickSort(int arr[], int left, int right)
{
	int l = left, r = right, hold, pivot = arr[(left + right) / 2];

	do
	{
		while ((arr[l] < pivot) && (l < right))
			l++;

		while ((arr[r] > pivot) && (left < r))
			r--;


		if (l <= r)
		{
			hold = arr[l];
			arr[l] = arr[r];
			arr[r] = hold;
			l++, r--;
		}

	} while (l <= r);

	if (left < r)
		quickSort(arr, left, r);

	if (right > l)
		quickSort(arr, l, right);
}

void heapSort(int arr[])
{
	int tp;

	for (int i = SIZE / 2 - 1; i >= 0; i--)
	{
		heapy(arr, i);
	}


	for (int j = SIZE - 1; j > 0 ; j--)
	{
		tp = arr[j];
		arr[j] = arr[0];
		arr[0] = tp;
		heap_size--;
		heapy(arr, 0);
	}
}

void heapy(int arr[], int i)
{
	int left_c = 2 * i + 1;
	int right_c = 2 * i + 2;
	int max = i;
	int hld;

	//maxý buluyor
	if ((left_c < heap_size) && (arr[left_c] > arr[max]))
		max = left_c;

	if ((right_c < heap_size) && (arr[right_c] > arr[max]))
		max = right_c;

	if (i != max)
	{
		hld = arr[max];
		arr[max] = arr[i];
		arr[i] = hld;
		heapy(arr, max);
	}
	
}

void printArr(int arr[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("Arr[%d] : %d\n", i, arr[i]);
	}
}
