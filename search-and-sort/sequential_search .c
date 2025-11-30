#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    float gpa;
} STUDENT;

int secondaryKeySearch(STUDENT D[],
    int N,
    int Result[],
    char* key) {
    int i = 0, k;
    for (k = 0; k < N; k++) {
        if (strcmp(D[k].surname, key) == 0) {
            // Bulundu, Result dizisine ekle
            Result[i] = k;
            i++;
        }
    }
    return i; // Bulunan elemanlarýn sayýsýný döndür
}

int main() {
    STUDENT students[MAX_STUDENTS] = {
        {1, "Ali", "Yilmaz", 3.2},
        {2, "Veli", "Kaya", 2.8},
        {3, "Ayse", "Yilmaz", 3.6},
        {4, "Fatma", "Demir", 3.1}
    };

    int resultIndexes[MAX_STUDENTS];
    char searchKey[MAX_NAME_LENGTH];
    int count, i;

    printf("Aramak istediðiniz soyadý: ");
    scanf("%s", searchKey);

    count = secondaryKeySearch(students, 4, resultIndexes, searchKey);

    if (count > 0) {
        printf("'%s' soyadýna sahip öðrenciler:\n", searchKey);
        for (i = 0; i < count; i++) {
            int index = resultIndexes[i];
            printf("ID: %d, Ad: %s, Soyad: %s, GPA: %.2f\n",
                students[index].id, students[index].name,
                students[index].surname, students[index].gpa);
        }
    }
    else {
        printf("'%s' soyadýna sahip öðrenci bulunamadý.\n", searchKey);
    }

    return 0;
}
