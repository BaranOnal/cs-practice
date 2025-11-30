#include <stdio.h>


int main(void) {
	FILE * fPtr = NULL; // fPtr = clients.txt file pointer 
	// fopen opens the file. Exit the program if unable to create the file 
	if ((fPtr = fopen("clients.txt", "w")) == NULL) {
		puts("File could not be opened");

	}
	else {
		puts("Enter the account, name, and balance.");
		puts("Enter EOF to end input.");
		//printf("%s", "? ");
		int account = 0; // account number
		char name[30] = ""; // account name
		double balance = 0.0; // account balance

		// write account, name and balance into file with fprintf
		
		
		while (scanf("%d%29s%lf", &account, name, &balance) == 3) {
			printf("%s", "? ");

			fprintf(fPtr, "%d %s %.2f\n", account, name, balance);
			
		}
		
		scanf("%d%29s%lf", &account, name, &balance);

		while (!feof(stdin))
		{
			fprintf(fPtr, "%d %s %.2f\n", account, name, balance);
			printf("%s", "? ");
			scanf("%d%29s%lf", &account, name, &balance);

		}
		fclose(fPtr); // fclose closes file 

	}	
}


int main() {

	FILE* f;
	if ((f = fopen("clients.txt", "r")) == NULL) {
		puts("File could not be opened");

	}
	else
	{
		int account = 0;
		char name[30] = "";
		double balance = 0.0;

		printf("%-10s%-13s%s\n", "Account", "Name", "Balance");


		fscanf(f, "%d%29s%lf", &account, name, &balance);


		while (!feof(f))
		{
			printf("%-10d%-13s%7.2f\n", account, name, balance);
			fscanf(f, "%d%29s%lf", &account, name, &balance);

		}

		fclose(f);
	}
	
}





// clientData structure definition 
struct clientData {
	int account;
	char lastName[15];
	char firstName[10];
	double balance;
};

int main(void) {
	FILE * fPtr = NULL; // accounts.dat file pointer
	// fopen opens the file; exits if file cannot be opened
	if ((fPtr = fopen("accounts.dat", "wb")) == NULL) {
		puts("File could not be opened.");
		
	}
	else {
		// create clientData with default information 
		struct clientData blankClient = { 0, "", "", 0.0 };
		
		// output 100 blank records to file 
		for (int i = 1; i <= 100; ++i) {
			fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
		}
		fclose(fPtr); // fclose closes the file

	}
	
}



int main(void) {
	FILE* fPtr = NULL; // Dosya i�aret�isi

	if ((fPtr = fopen("accounts.dat", "rb+")) == NULL) {
		puts("File could not be opened.");
	}
	else {

		struct clientData client = { 0, "", "", 0.0 };

		// Kullanicidan hesap numarasi al
		printf("Enter account number (1 to 100, 0 to end input): ");
		scanf("%d", &client.account);

		while (client.account != 0) {
			printf("Enter lastname, firstname, balance: ");
			fscanf(stdin, "%14s%9s%lf", client.lastName, client.firstName, &client.balance);

			// Dosyada dogru konuma git
			fseek(fPtr, (client.account - 1) * sizeof(struct clientData), SEEK_SET);

			// Veriyi yaz
			fwrite(&client, sizeof(struct clientData), 1, fPtr);

			// Yeni giris iste
			printf("\nEnter account number (1 to 100, 0 to end input): ");
			scanf("%d", &client.account);
		}

	fclose(fPtr);
	}
}




int main(void) {
	FILE* fPtr = NULL; // Dosya i�aret�isi

	if ((fPtr = fopen("accounts.dat", "rb+")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

		
		while (!feof(fPtr)) {
			struct clientData client = { 0, "", "", 0.0 };
			fread(&client, sizeof(struct clientData), 1, fPtr);

			// display record
			if (client.account != 0) {
				printf("%-6d%-16s%-11s%10.2f\n", client.account, client.lastName, client.firstName, client.balance);
			}
		}
		fclose(fPtr);
	}
}