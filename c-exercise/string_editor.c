#include<stdio.h>

int findW(char*);
void lowerToUpper(char*);
void upperToLower(char*);

int main() {
	int choice=1;
	char massage[100];
	
	puts("Enter a massage:\n");
	fgets(massage, sizeof(massage), stdin);

	printf("Make a choice(0 to Exit)\n");
	
	printf("\t1.Kelime sayisi ogrenmek.\n");
	printf("\t2.Lower to upper\n");
	printf("\t3.Upper to lower\n");
	
	scanf_s("%d", &choice);
	

	switch (choice)
	{
	case 1:
		printf("There are %d word in senteces.", findW(massage));
		break;
	case 2:
		lowerToUpper(massage);
		break;
	case 3:
		upperToLower(massage);
		break;
	default:
		break;
	}
	return 0;
}


int findW(char* ptr) {
	int space = 0;
	while (*ptr != '\0'){
		if (*ptr == ' ') {
			space++;
		}
		ptr++;
	}
	return space + 1;
}

void lowerToUpper(char* ptr) {
	for (; *ptr != '\0'; ptr++) {
		if (*ptr >= 'a' && *ptr <= 'z') {
			putchar(*ptr - 32);
		}
		else {
			putchar(*ptr);
		}
	}
}

void upperToLower(char* ptr) {
	for (; *ptr != '\0'; ptr++) {
		if (*ptr >= 'A' && *ptr <= 'Z') {
			putchar(*ptr + 32);
		}
		else {
			putchar(*ptr);
		}
	}
}


/*
void lowerToUpper(char* ptr) {

	for ( ;*ptr != '\0'; ptr++)
	{
		if (*ptr >= 'a' && *ptr <= 'z')
		{
			putchar(*ptr - 32);
		}
		else
		{
			putchar(*(ptr));

		}
	}

}
void upperToLower(char* ptr) {

	for (; *ptr != '\0'; ptr++)
	{
		if (*ptr >= 'A' && *ptr <= 'Z')
		{
			putchar(*ptr + 32);
		}
		else
		{
			putchar(*(ptr));

		}
	}
}*/
	
/*
	void lowerToUpper(char* ptr) {
		while (*ptr != '\0') {
			if (*ptr >= 'a' && *ptr <= 'z') {
				*ptr = *ptr - 32; // K���k harfi b�y�k harfe d�n��t�r
			}
			putchar(*(ptr));

			ptr++;
		}
	}

	void upperToLower(char* ptr) {
		while (*ptr != '\0') {
			if (*ptr >= 'A' && *ptr <= 'Z') {
				*ptr = *ptr + 32; // B�y�k harfi k���k harfe d�n��t�r
			}
			putchar(*(ptr));
			ptr++;
		}
	}*/
	