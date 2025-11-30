#include <stdio.h>

void bul(int a, int b);
int main() {

	int x, y;
	printf("iki pozitif sayi giriniz:\n");
	scanf_s("%d %d", &x, &y);
	bul(x, y);

	return 0;
}

void bul(int a, int b) {

	int carp = 1;
	for (int i = 0; i < b; i++){
		carp *= a;
	}
	printf("%d", carp);
}