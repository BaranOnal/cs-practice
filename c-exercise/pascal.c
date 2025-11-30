/*#include <stdio.h>

int main() {

	int space, rows, i, j, number = 1;

	printf("Enter the number of rows:	");
	scanf_s("%d", &rows);

	for (i = 0; i < rows; i++)
	{
		for (space = 1; space <= rows - i; space++)
		{
			printf("  ");
		}
		for ( j = 0; j <= i; j++)
		{
			if (i==0||j==0)
			{
				number = 1;
			}
			else
			{
				number = number * (i - j + 1) / j;
			}
			printf("%4d", number);
		}
		printf("\n");
	}

	return 0;
}*/

#include<stdio.h>	

int main(void) {

	int space, row, i, j ,number = 1;

printf("Enter the number of rows:  ");
scanf_s("%d", &row);

for ( i = 0; i < row; i++)
{

	for ( space = 1; space <= row - i; space++)
	{
		printf("  ");
	}
	for ( j = 0; j <=i; j++)
	{
		if (i == 0 || j == 0)
		{
			number = 1;
		}
		else
		{
			number = number * (i - j + 1) / j;
		}
		printf("%4d", number);
	}
	printf("\n");
}
	return 0;
}