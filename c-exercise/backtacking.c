#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    if (digits == NULL || *digits == '\0') {
        *returnSize = 0;
        return NULL;
    }

    // Telefon tuþ takýmýnýn harf eþleþmeleri
    const char* phone_map[] = {
        "", "", "abc", "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"
    };

    // Maksimum kombinasyon sayýsý hesaplanýr
    int max_combinations = 1;
    int len = strlen(digits);
    for (int i = 0; i < len; i++) {
        max_combinations *= strlen(phone_map[digits[i] - '0']);
    }

    // Dinamik bellek ayýr
    char** result = (char**)malloc(max_combinations * sizeof(char*));
    for (int i = 0; i < max_combinations; i++) {
        result[i] = (char*)malloc((len + 1) * sizeof(char));  // +1, null karakter için
    }

    *returnSize = 0;

    // Backtracking fonksiyonu
    void backtrack(int index, char* current) {
        if (index == len) {
            strcpy(result[*returnSize], current);
            (*returnSize)++;
            return;
        }

        int digit = digits[index] - '0';
        const char* letters = phone_map[digit];

        for (int i = 0; letters[i] != '\0'; i++) {
            current[index] = letters[i];
            backtrack(index + 1, current);
        }
    }

    char current[len + 1];  // Geçici string
    current[len] = '\0';  // Null-terminator eklenir

    // Backtracking baþlat
    backtrack(0, current);

    return result;
}

// ** Test Kodu **
int main() {
    char digits[] = "23";
    int returnSize;
    char** combinations = letterCombinations(digits, &returnSize);

    printf("Sonuçlar (%d adet):\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", combinations[i]);
        free(combinations[i]);  // Belleði temizle
    }
    free(combinations);

    return 0;
}
