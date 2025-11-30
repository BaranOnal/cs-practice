#include <stdio.h>

int main() {
    FILE* fPtr = NULL;
    int choice;
    int account = 0;
    char name[30] = "";
    double balance = 0.0;
    char continueAdding;

    do {
        printf("\nMake a choice (-1 to Exit)\n");
        printf("\t1. Add a single record(delete all)\n");
        printf("\t2. Add multiple records\n");
        printf("\t3. Read all data (formatted)\n");
        printf("\t4. Read file character by character (method 1)\n");
        printf("\t5. Read file character by character (method 2)\n");
        printf("\t6. Read file using fread\n");
        scanf("%d", &choice);

        if (choice == -1) break;

        if (choice < 1 || choice > 6) {
            printf("Invalid choice!!\n");
            continue;
        }

        switch (choice) {
            case 1: // Write to file
                if ((fPtr = fopen("cleants.txt", "w")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                printf("Enter account, name, and balance: ");
                /*
                fscanf(fPtr, "%d%29s%lf", &account, name, &balance);

                while (!feof(fPtr)) {
                    printf("%-10d%-13s%7.2f\n", account, name, balance);
                    fscanf(fPtr, "%d%29s%lf", &account, name, &balance);

                }*/
                if (scanf("%d%29s%lf", &account, name, &balance) == 3) {
                    fprintf(fPtr, "%d %s %.2f\n", account, name, balance);
                }

                fclose(fPtr);
                break;

            case 2: // Çoklu kayıt ekleme
                if ((fPtr = fopen("cleants.txt", "a")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                do {
                    /*
                    if (scanf("%d%29s%lf", &account, name, &balance) == 3) {
                        fprintf(fPtr, "%d %s %.2f\n", account, name, balance);
                    }*/
                    printf("\nEnter account number: ");
                    scanf("%d", &account);
                    printf("Enter name: ");
                    scanf("%29s", name);
                    printf("Enter balance: ");
                    scanf("%lf", &balance);

                    fprintf(fPtr, "%d %s %.2f\n", account, name, balance);

                    printf("\nAdd another record? (y/n): ");
                    scanf(" %c", &continueAdding);
                } while (continueAdding == 'y' || continueAdding == 'Y');

                fclose(fPtr);
                break;

            case 3: // Read formatted data
                if ((fPtr = fopen("cleants.txt", "r")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                printf("\n%-10s%-13s%s\n", "Account", "Name", "Balance");

			
				/*
				fscanf(fPtr, "%d%29s%lf", &account, name, &balance);
				while (!feof(fPtr)) {
					printf("%-10d%-13s%7.2f\n", account, name, balance);
					fscanf(fPtr, "%d%29s%lf", &account, name, &balance);
				}
				*/

                while (fscanf(fPtr, "%d%29s%lf", &account, name, &balance) == 3) {
                    printf("%-10d%-13s%7.2f\n", account, name, balance);
                }

                fclose(fPtr);
                break;

            case 4: // Read character by character (method 1)
                if ((fPtr = fopen("cleants.txt", "r")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                int ch;
                while ((ch = fgetc(fPtr)) != EOF) {
                    putchar(ch);
                }

                fclose(fPtr);
                break;

            case 5: // Read character by character (method 2)
                if ((fPtr = fopen("cleants.txt", "r")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                while (!feof(fPtr)) {
                    int ch = fgetc(fPtr);
                    if (ch != EOF) {
                        putchar(ch);
                    }
                }

                fclose(fPtr);
                break;

            case 6: // Read using fread
                if ((fPtr = fopen("cleants.txt", "r")) == NULL) {
                    puts("File could not be opened");
                    break;
                }

                char b;
                while (fread(&b, sizeof(char), 1, fPtr)) {
					//fwrite(&b, sizeof(char), 1, dest); dosyaya yazmak i�in
                    putchar(b);
                }

                fclose(fPtr);
                break;
        }
    } while (choice != -1);

    return 0;
}
