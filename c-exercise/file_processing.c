#include <stdio.h>
/*
int main(void) {

	FILE* outfile, * infile;
	int b = 5, f;
	float a = 14.64, c = 5.01, e, g;

	outfile = fopen("testdata.txt", "w");
	fprintf(outfile,"%f %d %f", a, b, c);
	fclose(outfile);

	infile= outfile = fopen("testdata.txt", "r");
	fscanf(infile, "%f %d %f", &e, &f, &g);
	printf("%f %d %f\n\n", a, b, c);
	printf("%f %d %f", e, f, g);



	return 0;
}
*/
/*
int main() {
	FILE* outfile,* infile;
	int a = 5, b;
	float c = 1.12, d;


	outfile = fopen("aaaa.txt", "w");
	fprintf(outfile, "%d %f", a, c);
	fclose(outfile);

	infile = fopen("aaaa.txt", "r");
	fscanf(infile, "%d %f", &b, &d);
	printf("%d %.2f\n\n", b, d);
	printf("%d %.2f", a, c);

	return 0;
}*/
/*
int main() {

	char ch;
	FILE* fp;

	fp = fopen("outtext.txt", "r");

	while (!feof(fp))
	{
		ch = getc(fp);
		
		printf("\n % c", ch);

	}
	return 0;
}*/



int main() {
	FILE* f;
	char buffer[11];
	if (f = fopen("fread.txt", "r"))
	{
		fread(buffer, 1, 10, f);
		buffer[10] = 0;
		fclose(f);
		printf("first 10 characters pf the file:\n%s\n", buffer);
	}
	return 0;
}

	


// fwrite
/*
int main() {
	FILE* fs;

	char a[10] = { '1','2','3','4','5','6','7','8','9','a' };

	fs = fopen("projetext", "w");

	fwrite(a, 1, 10, fs);

	fclose(fs);

	return 0;
}*/

  //fseek
/*
int main() {
	FILE* f;

	f = fopen("fseek.txt", "w");

	fputs("Naber mudur", f);

	fseek(f, 5, SEEK_SET);

	fputs("AAAAAAAAAA", f);
	fclose(f);
	return 0;
}
*/

//ftell
/*
int main() {

	FILE* stream;


	stream = fopen("ftell.txt", "w");
	fprintf(stream, "Naber Müdür");

	printf("dosyanýn konumu:%dl", ftell(stream));

	fclose(stream);


	return 0;
}*/
