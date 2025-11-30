#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100 // Dizi boyutunu belirle

typedef struct clientData {
    int account;
    char lastName[15];
    char firstName[10];
    double balance;
}clientData;

int main() {
    int choice, index;

    FILE* fPtr = NULL;
    clientData data = { 0 };//kulanici girisini tutuyor
    clientData temp = { 0, "","",0.0 };//sectigimiz indexsin durumuna bakmak icin
    clientData temp_del = { 0, "","",0.0 };//silece�imiz indexe bunu yazicaz


    if ((fPtr = fopen("client.txt", "wb+")) == NULL) {
        return 1;
    }

    for (int i = 0; i < 100; i++)
    {
        fwrite(&data, sizeof(clientData), 1, fPtr);
    }


    while (1) {
        printf("1: Ekle\n2: Guncelle\n3: Sil\n4:Yazdir\n5: Cikis\nSecim: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter account number (1 to 100, 0 to end input): ");
            scanf("%d", &data.account);
            
            fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
            fread(&temp, sizeof(clientData), 1, fPtr);

            
            if (temp.account != 0) {//dolu
                puts("Dolu");
                break;
            }
            //bu satira geldiyse o index bos demek

            printf("Enter lastname, firstname, balance: ");
            fscanf(stdin, "%14s%9s%lf", data.lastName, data.firstName, &data.balance);

            fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
            fwrite(&data, sizeof(clientData), 1, fPtr);

            break;

        case 2:
            printf("Enter account number (1 to 100, 0 to end input): ");
            scanf("%d", &data.account);
            
            fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
            fread(&temp, sizeof(clientData), 1, fPtr);
            
            if (temp.account  != 0) {//dolu
                printf("Enter lastname, firstname, balance: ");
                fscanf(stdin, "%14s%9s%lf", data.lastName, data.firstName, &data.balance);

                fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
                fwrite(&data, sizeof(clientData), 1, fPtr);
            }
            else {
                puts("empty");
            }
            break;

        case 3:
            printf("Enter account number (1 to 100, 0 to end input): ");
            scanf("%d", &data.account);
            
            fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
            fread(&temp, sizeof(clientData), 1, fPtr);
            
            if (temp.account != 0) {//dolu
                fseek(fPtr, (data.account - 1) * sizeof(clientData), SEEK_SET);
                fwrite(&temp_del, sizeof(clientData), 1, fPtr);
                puts("deleted");
            }
            else {
                puts("there is already empty");
            }


            break;

        case 4:
            fseek(fPtr, 0, SEEK_SET);
            printf("%-10s %-15s %-10s %-10s\n", "Account", "Last Name", "First Name", "Balance");
            while (fread(&temp, sizeof(clientData), 1, fPtr)) {
                if (temp.account != 0) {
                    printf("%-10d %-15s %-10s %-10.2f\n", temp.account, temp.lastName, temp.firstName, temp.balance);
                }
            }
            break;


        case 5:
            exit(0);

        default:
            printf("Gecersiz secim.\n");
        }
    }

    return 0;
}
