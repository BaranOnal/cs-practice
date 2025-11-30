#include <stdio.h>

int main() {
	int num, snum = 0, cnum = 0, rem;

	printf("Enter a number.\n");
	scanf_s("%d", &num);

	while (num > 0)
	{
		rem = num % 10;
		snum += rem;
		cnum++;
		num = num / 10;
	}
	
	printf("The number of digit is %d\n", cnum);
	printf("The sum of digits is %d", snum);

	return 0;
}