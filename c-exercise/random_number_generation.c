
#include <stdio.h>
 #include <stdlib.h>

 int main(void) {

		 for (int i = 1; i <= 10; ++i) { // loop 10 times
		 printf("%d ", 1 + (rand() % 6)); // display random die value
			
	}
	
		 puts("");
}
 /*Random-Number Generation—Rolling a SixSided Die*/

#include <stdio.h>
#include <stdlib.h>


int main() {

	for (int i = 0; i <= 10; i++)
	{
		printf("%d ", 1 + (rand() % 10));
	}

	puts("");

	return 0;
}


#include <stdio.h>
#include <stdlib.h>

//Random-Number Generation—Rolling a SixSided Die 60,000,000 Times BÝR ZARIN ATILMASI VE DEÐERLERÝN YAKLAÞIK OLARAK 10,000,000 KEZ GELMESÝ
int main(void) {
	 int frequency1 = 0; // rolled 1 counter
	 int frequency2 = 0; // rolled 2 counter
	 int frequency3 = 0; // rolled 3 counter
	 int frequency4 = 0; // rolled 4 counter
	 int frequency5 = 0; // rolled 5 counter
	 int frequency6 = 0; // rolled 6 counter
	
		 // loop 60000000 times and summarize results
		 for (int roll = 1; roll <= 60000000; ++roll) {
		 int face = 1 + rand() % 6; // random number from 1 to 6

		 // determine face value and increment appropriate counter
			  switch (face) {
			  case 1: // rolled 1
				  ++frequency1;
				  break;
			  case 2: // rolled 2
				  ++frequency2;
				  break;
			  case 3: // rolled 3
				  ++frequency3;
				  break;
			  case 4: // rolled 4
				  ++frequency4;

				   break;
			   case 5: // rolled 5
				   ++frequency5;
				   break;
			   case 6: // rolled 6
				   ++frequency6;
				   break; // optional
				  
			  }
			  
		 }
			  // display results in tabular format
			  printf("%s%13s\n", "Face", "Frequency");
		  printf(" 1%13d\n", frequency1);
		  printf(" 2%13d\n", frequency2);
		  printf(" 3%13d\n", frequency3);
		  printf(" 4%13d\n", frequency4);
		  printf(" 5%13d\n", frequency5);
		  printf(" 6%13d\n", frequency6);
		 
} 

#include <stdio.h>
#include <stdlib.h>


 int main(void) {
	 printf("%s", "Enter seed: ");
	 int seed = 0; // number used to seed the randomnumber generator
	 scanf_s("%d", &seed);
	
		 srand(seed); // seed the random-number generator
		  for (int i = 1; i <= 10; ++i) {
			  printf("%d ", 1 + (rand() % 6)); // display random die value
				 
		 }
		  
			  puts("");
		 
 }


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(NULL));

	printf("%d", time(NULL));
}
