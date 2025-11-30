/*#include <stdio.h>

int main() {
	int num1 = 1, num2 =1, sum = 1, num;
	
	printf("Enter a number.");
	
	scanf_s("%d", &num);

	for (int i = 1; i < num - 1 ; i++) {
		if (num == 1 || num == 2) {
			break;
		}
		num1 = num2;
		num2 = sum;
		sum = num1 + num2;

		printf("%d\n", sum);
	}
	return 0;
}*/


/*#include <stdio.h>

int main() {

	int n1 = 1;
	int n2 = 1;
	int lim, temp;
	printf("Enter a number.\n");
	scanf_s("%d", &lim);


	if (lim == 1)
	{
		printf("%d\n", n1);
	}
	else if (lim >= 2)
	{
		printf("%d\n%d\n", n1, n2);
	}
	for (int i = 2; i < lim; i++)
	{

		temp = n1 + n2;
		n1 = n2;
		n2 = temp;
		printf("%d\n", temp);
	}

	return 0;
}*/



/*#include <stdio.h>

int main() {

	int n1 = 1;
	int n2 = 1;
	int lim, temp, i = 2;
	printf("Enter a number.\n");
	scanf_s("%d", &lim);


	if (lim == 1)
	{
		printf("%d\n", n1);
	}
	else if (lim >= 2)
	{
		printf("%d\n%d\n", n1, n2);
	}
	while (i < lim)
	{
		temp = n1 + n2;
		n1 = n2;
		n2 = temp;
		printf("%d\n", temp);
		i++;
	}
	return 0;
}*/




#include <stdio.h>

 unsigned long long int fibonacci(int n); // function prototype

 int main(void) {
	 // calculate and display fibonacci(number) for 0-10
		 for (int number = 0; number <= 10; number++) {
		 printf("Fibonacci(%d) = %llu\n", number,
			fibonacci(number));
		
	}
	
		 printf("Fibonacci(20) = %llu\n", fibonacci(20));
	 printf("Fibonacci(30) = %llu\n", fibonacci(30));
	 printf("Fibonacci(40) = %llu\n", fibonacci(40));
	
}

// Recursive definition of function fibonacci
 unsigned long long int fibonacci(int n) {
	 if (n == 0 || n == 1) { // base case 
		 return n;
		
	}
	 else { // recursive step 
		 return fibonacci(n - 1) + fibonacci(n - 2);
		
	}
	
}