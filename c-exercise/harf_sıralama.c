#include<stdio.h>
void characterScroll(char*, int);

int main() {
	char characters[] = { 'Y','a','z','i','l','i','m'};
	int size = sizeof(characters) / sizeof(characters[0]);

	characterScroll(characters, size);

	return 0;
}
void characterScroll(char* characters, int size) {
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = i; j < size; j++)
		{
		
			printf("%c", *(characters + j));

		}
		for (int k = 0; k < i; k++)
		{
		
			printf("%c", *(characters + k));
		
		}
		printf("\n");
	}

}