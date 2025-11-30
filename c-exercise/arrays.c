/*#include<stdio.h>

int main() {

	int n[] = { 1, 2, 3, 4, 5 };

	printf("%s%8s\n", "Element", "Value");

	for (int i = 0; i < 5; ++i) {
		printf("%7d%8d\n", i, n[i]);
	}

	return 0;
}*/

/*#include <stdio.h>	
#define SIZE 5
int main(void) {

	int n[SIZE] = { 1, 2, 3, 4, 5 };
	int total = 0;

	for (int i = 0; i < SIZE; i++)
	{
		total += n[i];
	}

	printf("The total of n's values %d\n", total);



	return 0;
}*/

/*#include <stdio.h>

void staticArrayInit(void);
void automaticArrayInit(void);
int main(void) {
	 puts("First call to each function:");
	 staticArrayInit();
	 automaticArrayInit();
	
		 puts("\n\nSecond call to each function:");
	 staticArrayInit();
	 automaticArrayInit();
	 puts("");
	
}

// function to demonstrate a static local array
void staticArrayInit(void) {
	 // initializes elements to 0 before the function is called
		 static int array1[3];
	 puts("\nValues on entering staticArrayInit:");
	
		 // output contents of array1
		 for (int i = 0; i <= 2; ++i) {
		 printf("array1[%d] = %d ", i, array1[i]);
		
	}
	 puts("\nValues on exiting staticArrayInit:");
	 // modify and output contents of array1
		 for (int i = 0; i <= 2; ++i) {
		 printf("array1[%d] = %d ", i, array1[i] += 5);
	
	}
	
}

 // function to demonstrate an automatic local array
 void automaticArrayInit(void) {
	 // initializes elements each time function is called
		 int array2[3] = { 1, 2, 3 };
	
		 puts("\n\nValues on entering automaticArrayInit:");
	
		 // output contents of array2
		 for (int i = 0; i <= 2; ++i) {
		 printf("array2[%d] = %d ", i, array2[i]);
		
	}
	
		 puts("\nValues on exiting automaticArrayInit:");
	
		 // modify and output contents of array2
		 for (int i = 0; i <= 2; ++i) {
		 printf("array2[%d] = %d ", i, array2[i] += 5);
		
	}
	
}*/


 /*// Array name is the same as the address of the array’s first element.
 #include <stdio.h>

 // function main begins program execution
 int main(void) {
	 char array[5] = ""; // define an array of size 5
	
		 printf(" array = %p\n&array[0] = %p\n &array = %p\n",
			 array, &array[0], &array);

		 for (int ii = 0, i = 0; i < 5; i++, ii = ii+2){

			 array[i] = 2 + 2 * ii;
			 printf("array%d = %d\n", i, array[i]);
		 }
		 return 0;
 }*/


/*#include <stdio.h>

void staticArrayInit(void);
void automaticArrayInit(void);
int main(void) {
	puts("First call to each function:");
	staticArrayInit();
	automaticArrayInit();

	puts("\n\nSecond call to each function:");
	staticArrayInit();
	automaticArrayInit();
	puts("");

}

// function to demonstrate a static local array
void staticArrayInit(void) {
	// initializes elements to 0 before the function is called
	static int array1[3];
	puts("\nValues on entering staticArrayInit:");

	// output contents of array1
	for (int i = 0; i <= 2; ++i) {
		printf("array1[%d] = %d ", i, array1[i]);

	}
	puts("\nValues on exiting staticArrayInit:");
	// modify and output contents of array1
	for (int i = 0; i <= 2; ++i) {
		printf("array1[%d] = %d ", i, array1[i] += 5);

	}

}

// function to demonstrate an automatic local array
void automaticArrayInit(void) {
	// initializes elements each time function is called
	int array2[3] = { 1, 2, 3 };

	puts("\n\nValues on entering automaticArrayInit:");

	// output contents of array2
	for (int i = 0; i <= 2; ++i) {
		printf("array2[%d] = %d ", i, array2[i]);

	}

	puts("\nValues on exiting automaticArrayInit:");

	// modify and output contents of array2
	for (int i = 0; i <= 2; ++i) {
		printf("array2[%d] = %d ", i, array2[i] += 5);

	}

}*/



#include <stdio.h>
#define SIZE 5

void modifyArray(int b[], int size);
void modifyElement(int e);
int main(void) {
	int a[SIZE] = { 0, 1, 2, 3, 4 };

	puts("Effects of passing entire array by reference:\n\nThe values of the original array are:");

	for (int i = 0; i < SIZE; ++i) {
		printf("%3d", a[i]);
	}
	puts("");
	modifyArray(a, SIZE);

	puts("The values of the modified array are:");
	for (int i = 0; i < SIZE; ++i) {
		printf("%3d", a[i]);
	}
	printf("\n\n\nEffects of passing array element "
		"by value:\n\nThe value of a[3] is %d\n", a[3]);
	modifyElement(a[3]);
	printf("The value of a[3] is %d\n", a[3]);

}
void modifyArray(int b[], int size) {
	for (int j = 0; j < size; ++j) {
		b[j] *= 2;

	}

}
void modifyElement(int e) {
	e *= 2;
	printf("Value in modifyElement is %d\n", e);

}
