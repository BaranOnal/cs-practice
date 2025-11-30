/*#include <stdio.h>

int main() {
	int n;
	int max = 0;
	int lim = 999;

	printf("If you want to quit enter -0\n");

	for (int i = 0; i < lim; i++)
	{
		printf("Enter a number.\n");
		scanf_s("%d", &n);
		if (n > max)
		{
			max = n;
		}
		else if (n == -0)
		{
			break;
		}
	}

	printf("Max number is %d", max);

	return 0;
}*/



#include<stdio.h>

int main() {

	int lim = 9999, num, i = 0, max = 0;

	printf("If you want to quit enter -0.\n");

	while (lim>i)
	{
		printf("Enter a number:\n");
		scanf_s("%d", &num);
		if (max<num)
		{
			max = num;
		}
		else if(num==-0)
		{
			break;
		}
		i++;
	}
	printf("Max number is %d", max);

	return 0;
}