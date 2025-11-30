#include <stdio.h>
int main() {
	int num, i = 2, count = 0;

	printf("Enter a number for prime number control: ");
	
	scanf_s("%d", &num);

	while (i <= num /2)
	{
		if (num%i == 0)
		{
			count = 1;
			break;
		}
		i++;
	}
	if (count == 0)
		printf("%d is a prime number.", num);

	else
		printf("%d is not a prime number.", num);
	
	return 0;
}