#include <stdio.h>

void printArray(int a[][3]);

int main() {

	int array1[2][3] = { {1, 2, 3}, {4, 5, 6} };
	 puts("Values in array1 by row are:");
	 printArray(array1);
	
		 int array2[2][3] = { {1, 2, 3}, {4, 5} };
	 puts("Values in array2 by row are:");
	 printArray(array2);
	
		 int array3[2][3] = { {1, 2}, {4} };
	 puts("Values in array3 by row are:");
	 printArray(array3);

	return 0;
}
void printArray(int a[][3]) {
	 // loop through rows
		 for (int i = 0; i <= 1; ++i) {
		 // output column values
			 for (int j = 0; j <= 2; ++j) {
			 printf("%d ", a[i][j]);
			
		}
		
			 printf("\n"); // start new line of output
		
	}
}