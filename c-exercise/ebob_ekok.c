#include <stdio.h>

int main() {
	int ebob(int a, int b);
	int ekok(int a, int b);

	int x, y, n1;

	printf("Enter two numbers for ebob-ekok :");
	scanf_s("%d%d", &x, &y);
	if (ebob(x, y) != 0)
		printf("Ebob of %d and %d : %d\n", x, y, ebob(x, y));
	else
		printf("There is no ebob.\n");
	
	if (ekok(x, y) != 0)
		printf("Ekok of %d and %d : %d", x, y, ekok(x, y));
	else
		printf("Ekok of %d and %d : %d", x, y, x*y);
	return 0;
}
int ebob(int a, int b) {
	int hold = 0, ebob = 0;
	if (a <= b)
		hold = a;
	else
		hold = b;
	
	for (int i = 2; i <= hold; i++) 
	{
		if ((a%i == 0) && (b%i == 0))
			ebob = i;
	}
	return ebob;
}
int ekok(int a,int b) {
	int ekok = 0;

	if (ebob(a,b) != 0)
		ekok = (a * b) / ebob(a, b);
	
	return ekok;
}