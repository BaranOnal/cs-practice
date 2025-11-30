#include <stdio.h>

int main() {

	char stri[] = "Hello C!";
	int size1, size2, size3;
	size1 = sizeof(stri);
	char* array[] = {"Naber mudur?"};
	char* arr[] = { 'N','a','b','e','r' };
	size2 = sizeof(array);
	size3 = sizeof(arr)/sizeof(arr[0]);

	printf("%lu\n", size1);
	printf("%s\n", stri);
	printf("%c\n", stri[6]);

	for (int i = 0; i < 1; i++)
	{
		printf("%s", *(array+i));
	}

	printf("\n%lu\n", size2);
	printf("%c\n", *(array + 0));
	printf("%c\n", arr[0]);

	for (int i = 0; i < size3; i++)
	{
		printf("%c", *(arr + i));
	}
	puts("");
	for (int i = 0; i <size3; i++)
	{
		printf("%c", arr[i]);
	}
	return 0;
}