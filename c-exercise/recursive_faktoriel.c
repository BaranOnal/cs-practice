#include <stdio.h>
 void fact(int num);

int main() {
	int input = 0;
	printf("Enter a number.\n");
	scanf_s("%d", &input);

	fact(input);

	return 0;
}

void fact(int num) {
	
	int result = 1;

	for (int i = 1; i <= num; i++)
	{
		result *= i;
	}

	printf("%d", result);
}


int fakt(int num);

int main() {
	int input = 0;
	printf("Enter a number.\n");
	scanf_s("%d", &input);

	printf("%d", fakt(input));

	return 0;
}
int fakt(int num) {

	int result = 1;

	for (int i = 1; i <= num; i++)
	{
		result *= i;
	}

	return result;
}


int fakt(int num);
int main() {
	int input;
	printf("Enter a number.\n");
	scanf_s("%d", &input);

	printf("%d", fakt(input));

	return 0;
}

int fakt(int num) {
	if (num == 0 || num == 1)
	{
		return 1;
	}
	return (num * fakt(num - 1));
}