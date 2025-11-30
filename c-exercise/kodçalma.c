#include<stdio.h>
#include<stdlib.h>


int main() {

	FILE* src;
	FILE* dest;
	char b;

	src = fopen("kodçalma.c", "r");
	dest = fopen("temp.txt", "w");
	while (fread(&b, sizeof(char), 1, src)) {
		
			fwrite(&b, sizeof(char), 1, dest);
		
	}	
	fclose(src);
	fclose(dest);


	return 0;
}