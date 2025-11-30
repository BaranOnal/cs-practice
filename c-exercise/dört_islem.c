#include <stdio.h>

int main() {

	int n1, n2, process;

	printf("Enter the first number.\n");
	scanf_s("%d", &n1);

	printf("Enter the second number.\n");
	scanf_s("%d", &n2);

	printf("1.Toplama\n 2.Cikarma\n  3.Bölme\n   4.Carpma\nChoos to process.");
	scanf_s("%d", &process);

	if (process == 1)
	{
		printf("Result is %d", n1 + n2);
	}
	else if (process == 2)
	{
		printf("Result is %d", n1 - n2);

	}
	else if (process == 3)
	{
		printf("Result is %f", (float)n1 / (float)n2);

	}
	else if (process == 4)
	{
		printf("Result is %d", n1 * n2);

	}

	return 0;
}