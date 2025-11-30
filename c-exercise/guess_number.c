#include <stdio.h>
#include <stdlib.h>	
int main() {
	int g;
	int num = rand() % 100;

	printf("Guess the number:\n");
	do{
		scanf_s("%d", &g);
		if (g < num)
		{
			printf("Guess upper.\n");
		}
		else if(g > num)
		
			printf("Guess lower.\n");
		
		else
		{
			printf("You're goddamn right!");

		}
	} while (num != g);

	return 0;
}