#include<stdio.h>

int main(void) 
{
	double myValue = 0, myArray[10] = { 0 };
	int choice, index, ii = 0, hold[100] = { 0 };

	do
	{
		printf("Choice a choice (-1 to Exit)\n");
		printf("\t1. Write to array\n");
		printf("\t2. Read from array\n");
		printf("\t3. Read to all array\n");
		printf("\t4. Show modified arrays\n");
		scanf_s("%d", &choice);

		if (choice == -1) break;

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			printf("Wrong button!!\n");
			continue;
		}

		switch (choice)
		{
		case 1:
			printf("Enter array index:");
			scanf_s("%d", &index);
			if (index < 0 || index>9)
			{
				printf("Ýndex should be in the range of 0-9\n");
				continue;
			}
			printf("Enter the value: ");
			scanf_s("%lf", &myValue);
			myArray[index] = myValue;
			printf("The write operation is succesful!");

			if (myValue != 0)
			{
				hold[ii] = index;
				break;
			}


		case 2:
			printf("Enter array index:");
			scanf_s("%d", &index);
			if (index < 0 || index>9)
			{
				printf("Ýndex should be in the range of 0-9\n");
				continue;
			}
			printf("myArray[%d]:%.2f\n\n", index, myArray[index]);
			break;

		case 3:

			for (int i = 0; i <= 9; i++)
			{
				printf("myArray[%d]:%.2f\n\n", i, myArray[i]);
			}
			break;

		case 4:

			printf("Replaced arrays: \n");
			for (int i = 0; i < ii; i++)
			{
				printf("%d\n", hold[i]);
				continue;
			}
			break;
		}

		if ( myValue != 0)
		{
			ii++;
			myValue = 0;

		}
	}
	while (choice != -1);

	return 0;
	}


/*if (choice == 3)
{
	for (int i = 0; i <= 9; i++)
	{
		printf("myArray[%d]:%.2f\n\n", i, myArray[i]);
	}
}
if (choice == 4)
{
	printf("Replaced arrays: \n");
	for (int i = 0; i < j; i++)
	{
		printf("%d", hold[i]);
		continue;
	}
}
if (index < 0 || index>9)
{
	printf("Ýndex should be in the 0-9\n");
	continue;
}
if (choice == 1)
{
	printf("Enter the value: ");
	scanf_s("%lf", &myValue);
	myArray[index] = myValue;
	printf("The write operation is succesful!");
	if (myValue != 0)
	{
		hold[ii] = myValue;
	}
}
if (choice == 2) {
	printf("myArray[%d]:%.2f\n\n", index, myArray[index]);
}*/