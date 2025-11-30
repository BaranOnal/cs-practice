#include<stdio.h>
#define SIZE 5
 double getSquare(double* ptr);

int main() {

	double result, number;

	printf("Enter a number:");
	scanf_s("%lf", &number);

	result = getSquare(&number);

	printf("Result = %.2f \n\n", result);

	return 0;
}

double getSquare(double* ptr) {

	return *ptr * *ptr;
} 
 int main() {

    char name[3] = { 'a','b','c' };

    printf("%p\n", name);
    printf("%p\n", name + 1);
    printf("%p\n", name + 2);

    printf("%c\n", *name);
    printf("%c\n", *name + 1);
    printf("%c\n", *name + 2);

    int num[3] = { 1,2,3 };

    printf("%p\n", num);
    printf("%p\n", num + 1);
    printf("%p\n", num + 2);

    printf("%d\n", *num);
    printf("%d\n", *num + 1);
    printf("%d\n", *num + 2);

    return 0;
} 
 void myArray(int*, int);
int main() {
    int numbers[6] = { 2,4,65,12,85,6 };
    int i, size;
    size = sizeof(numbers) / sizeof(numbers[0]);
    printf("Previous state:\n");
    printf("--------------:\n");
    for (i = 0; i < size; i++)
    {
        printf("numbers[%d] : %d\n", i, numbers[i]);
    }
    myArray(numbers,size);
    printf("\nNext state:\n");
    printf("--------------:\n");
    for (i = 0; i < size; i++)
    {
        printf("numbers[%d] : %d\n", i, numbers[i]);
    }
    return 0;
}

void myArray(int* numbers,int size)
{
    int j = 0;
    for (j = 0; j < size; j++) {
        *(numbers + j) *= 3;

    }
} 
 
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
 
 
void bubbleSort(int* array, int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // Pointerlar aracýlýðýyla dizideki elemanlara eriþim
            if (*(array + j) > *(array + j + 1)) {
                // Deðerleri yer deðiþtirme
                temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
}

int main() {
    int i;
    int array[SIZE];

    printf("Enter %d elements:\n", SIZE);
    for (i = 0; i < SIZE; i++) {
        scanf_s("%d", &array[i]);
    }

    // Dizinin orijinal hali
    printf("Original array: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Bubble sort çaðrýsý
    bubbleSort(array, SIZE);

    // Sýralanmýþ dizi
    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
} 


void bubble(int*, int);

int main() {
    int array[SIZE];
    int size = sizeof(array) / sizeof(array[0]);


    printf("Enter 5 elements\n");
    for (int i = 0; i < SIZE; i++) {

        scanf_s("%d", &array[i]);
    }

    printf("Original array: \n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%4d\n", array[i]);
    }

     bubble(array, size);

     printf("Sorted: \n");

     for (int i = 0; i < SIZE; i++)
     {
         printf("%4d\n", array[i]);
     }

    return 0;
}


void bubble(int* array, int size) {

    for (int  k = 0; k < size - 1; k++)
    {
        for (int i = 0; i < size -i- 1 ; i++)
        {
            if (*(array+i) > *(array+i + 1))
            {
                int temp = *(array+i);
                *(array+i) = *(array+i + 1);
                *(array+i + 1) = temp;
            }
        }
    }
}