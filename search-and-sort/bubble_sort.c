#include<stdio.h>
#define SIZE 5
/* int main() {
	int a[SIZE] = { 0 };
	for (int ii = 0; ii < SIZE; ii++)
	{
		printf("Enter a number.\n");
		scanf_s("%d", &a[ii]);
	}

	puts("Orijinal data");


	for (int i = 0; i < SIZE; ++i) {
		 printf("%4d", a[i]);	
	}

	//bubble sort

	for (int pass = 1; pass < SIZE;pass++)
	{
		for (int i = 0; i < SIZE - 1; i++) {

			if (a[i] > a[i+1])
			{
				int hold = a[i];
				a[i] = a[i + 1];
				a[i + 1] = hold;
			}
		}
	}

	puts("\nLatest data");

	for (int i = 0; i < SIZE; ++i) {
		printf("%4d", a[i]);
	}


	
	}
		for (int i = 0; i < SIZE; ++i) {
		 printf("%4d", a[i]);
}*/

/*int main() {
	int a[SIZE] = { 0 };

	for (int i = 0; i < SIZE; i++)
	{
		printf("Enter a number.\n");
		scanf_s("%d", &a[i]);
	}
	puts("Orijinal data:\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%4d", a[i]);
	}
 //bubble sort
	for (int i = 1; i < SIZE; i++)
	{
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				int hold = a[i];
				a[i] = a[i + 1];
				a[i + 1] = hold;
			}
		}
	}
	puts("\nLatest data:\n");

	for (int i = 0; i < SIZE; i++)
	{
		printf("%4d", a[i]);
	}
	return 0;
}*/

void bubblesort(int* array, int size);
void swap(int* z, int* y);

int main(void) {
	int array2[SIZE];

	printf("Sayi giriniz\n");

	for (int i = 0; i < SIZE; i++) {

		scanf_s("%d", &array2[i]);
	}

	bubblesort(array2, SIZE);

	printf("Sirali dizi:\n");

	for (int i = 0; i < SIZE; i++) {

		printf("%d\n", array2[i]);
	}
	printf("\n");


	return 0;
}

void bubblesort(int* array, int size) {

	for (int i = 0; i < size - 1; i++) {

		for (int k = 0; k < size - i - 1; k++) {

			if (array[k] > array[k + 1]) {

				swap(&array[k], &array[k + 1]);

			}
		}
	}
}

void swap(int* z, int* y) {

	int temp = *z;

	*z = *y;

	*y = temp;
}
