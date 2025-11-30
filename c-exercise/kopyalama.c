#include<stdio.h>
#include<stdlib.h>


int main() {

	FILE* src;
	FILE* dest;
	char b;
	int ch;
	src = fopen("kopyalama.c", "r");
	dest = fopen("temp.txt", "w");

	if (src == NULL || dest == NULL) {
		printf("Dosya açýlamadý!\n");
		return 1;
	}
	/*
	while (fread(&b, sizeof(char), 1, src)) {
		fwrite(&b, sizeof(char), 1, dest);
	}	*/

	while ((ch = fgetc(src)) != EOF) {
		fputc(ch, src);
		//fwrite(&ch, sizeof(char), 1, dest);
	}
	fclose(src);
	fclose(dest);


	return 0;
}