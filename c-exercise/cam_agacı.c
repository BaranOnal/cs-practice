#include <stdio.h>

int main() {
	int space, star = 1, size, line = 1;

	printf("Enter size of the house: ");
	scanf_s("%d", &size);


	for (int i = 0; i < size; i++)
	{
		for (space = (size / 2) - 1; space >= line / 2; space--)
		{
			printf(" ");
		}
		for (star = 1; star <= line; star++)
		{
			printf("*");
		}
		printf("\n");
		line += 1;
	}

	return 0;
}


/*int main() {

	int base, size, star = 1, line = 1;

		printf("Enter size of the house: ");
		scanf_s("%d", &size);

		for (int i = 0; i < line; i++)
		{
			for (space = sice /2 - 1; space<=line; space++)
			{

			}
			for (size_t i = 0; i < length; i++)
			{

			}
		}







	return 0;
}	*/