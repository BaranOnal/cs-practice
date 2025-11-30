/*#include <stdio.h>

int main() {
	int i, j, rows, a = 0;
	char myLetter;

	printf("Pleas enter a letter : ");
	scanf_s("%c", &myLetter);
	
	printf("Pleas enter the number of row (odd number) : ");
	scanf_s("%d", &rows);
	
	for ( i = 0; i < rows; i++)
	{
		if (i <= rows / 2)
			a++;
		else
			a--;
		for ( j = 0; j < a; j++)
			printf(" ");

		printf(" %c\n", myLetter);
	}
	return 0;
}*/

#include <stdio.h>

int main() {
	int i, j, rows, a = 0;
	char myLetter;

	printf("Pleas enter a letter : ");
	scanf_s("%c", &myLetter);

	printf("Pleas enter the number of row (odd number) : ");
	scanf_s("%d", &rows);

	for (i = 0; i < rows; i++)
	{
		if (i <= rows / 2)
			a++;
		else
			a--;
		for (j = 0; j < a; j++)
		{
			printf(" ");
		}
		printf("%c\n", myLetter);
	}
	return 0;
}