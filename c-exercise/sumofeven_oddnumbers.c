/*#include <stdio.h>

int main() {
	int osum = 0;
	int esum = 0;
	int num = 0;

	int flag = 1;

	do {

		flag = 1;

		printf("enter a number: ");

		scanf_s("%d", &num);

		if (num < 0)
		{
			printf("duzgun gir\n");
			flag = 0;
		}
	} while (flag == 0);

	for (int i = 1; i <= num; i++)
	{
		if (i % 2 == 0)
		{
			osum += i;
		}

		else {
			esum += i;
		}

	}
	printf("Sum of even is %d\n", esum);
	printf("Sum of odd is %d\n", osum);

	return 0;
}*/


#include <stdio.h>

int main()
{
	int osum = 0, esum = 0;

	for (int i = 1; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			esum = esum + i;
		}
		else
		{
			osum = osum + i;
		}

	}

	printf("Sum of Odd numbers= %d\n", osum);
	printf("Sum of Even numbers= %d", esum);

	return 0;
}