#include<stdio.h>
//harfin tekrar sayýsýný bulma
void calculate(char*);
char upperToLower(char);

int main() {
    char massage[100];
    puts("enter a sentence:");
    fgets(massage,sizeof(massage),stdin);

    calculate(massage);
    return 0;
}

void calculate(char* ptr) {
    int letters[26] = {0}, length= 0;
    char activeLetter;
    // cümlenin uzunluðu
    while (*(ptr + length) != '\0') {
        length++;
    }

    
    for (int i = 0; i < length; i++)
    {
        activeLetter = upperToLower(*(ptr + i));
        letters[activeLetter - 97]++;
    }
    printf("Letter\tRepeat\n");
    printf("------\t------\n");

    for (int i = 0; i < 26; i++)
    {
        if (letters[i] != 0)
        {
            printf("%c\t%d\n", i + 97, letters[i]);
        }
    }
}


char upperToLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    else {
        return c;
    }
}


/*void printReverse(char*);

int main() {

    char massage[100];

    puts("enter a massage");
    fgets(massage,sizeof(massage),stdin);

    printReverse(massage);

    return 0;
}

void printReverse(char* ptr) {
    int i = 0, length = 0;
    length = strlen(ptr);

    for (int i = length- 1; i >= 0; i--)
    {
        putchar(*(ptr+i));
    }
}*/


/*int stringLength(char* str) {
    int length = 0;
    while (*(str + length) != '\0') {
        length++;
    }
    return length;
}

// Her kelimeyi tersine çevirip yazdýrma fonksiyonu
void printReverse(char* ptr) {
    int length = stringLength(ptr);
    int wordStart = 0;

    for (int i = 0; i <= length; i++) {
        if (*(ptr + i) == ' ' || *(ptr + i) == '\n' || *(ptr + i) == '\0') {
            for (int j = i - 1; j >= wordStart; j--) {
                putchar(*(ptr + j));
            }
            wordStart = i + 1;

            // Kelime aralarýna boþluk eklenmesi
            if (*(ptr + i) == ' ') {
                putchar(' ');
            }
        }
    }
}

int main() {
    char message[100];

    puts("Enter a message:");
    fgets(message, sizeof(message), stdin);

    printReverse(message);

    return 0;
}*/