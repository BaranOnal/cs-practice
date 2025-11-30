#include <stdio.h>

/*int main() {
	int num;
	printf("Enter a number.\n");
	scanf_s("%d", &num);

	for (int i = 1; i <= num; i++)
	{
		if (num % i == 0)
			printf("%4d", i);
	}




	return 0;
}*/

int dvd(int j);
int main() {
	int num;
	printf("Enter a number.\n");
	scanf_s("%d", &num);

	printf("%4d", dvd(num));

	return 0;
}
int dvd(int j) {

	for (int i = 1; i < j; i++)
	{
		if (j % i == 0)
			printf("%4d", i);
	}
	return j;
}