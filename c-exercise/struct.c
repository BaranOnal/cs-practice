#include<stdio.h>

/*struct myDate
{
	int day;
	int month;
	int year;
};

int main() {
	struct myDate x;
	struct myDate y;

	printf("doðum tarihin");
	scanf_s("%d%d%d", &x.day, &x.month, &x.year);
		
	printf("today's date");
	scanf_s("%d%d%d", &y.day, &y.month, &y.year);

	if (x.day>y.day)
	{
		y.day += 30;
		y.month -= 1;
	}
	if (x.month > y.month)
	{
		y.month += 12;
		y.year -= 1;
	}


	printf("\n You have lived ");
	printf("%d day,%d montg, %d year", y.day - x.day, y.month - x.month, y.year - x.year);

	printf("  till now\n\n");

	return 0;
}*/

typedef struct 
{
	int second;
	int minute;
	int hour;
}timee;

timee getTime();
timee add(timee x, timee y);
void printTime(timee);

int main() {

	 timee x, y;

	 x = getTime();
	 y = getTime();

	 printTime(x);
	 printf(" + ");
	 printTime(y);
	 printf(" = ");

	 printTime(add(x,y));

	return 0;
}

timee getTime() {

	timee t;

	printf("Hours:");
	scanf_s("%d",&t.hour);
	printf("Minuts:");
	scanf_s("%d",&t.minute);
	printf("Seconds:");
	scanf_s("%d",&t.second);
	return t;
}

timee add(timee x, timee y) {


	y.second += x.second;
	y.minute += x.minute;
	y.hour += x.hour;
	y.minute += y.second / 60;
	y.hour += y.minute / 60;
	y.second = y.second % 60;
	y.minute = y.minute % 60;

	return y;
}


void printTime(timee t){

printf("%d hour %d minute %d second", t.hour, t.minute, t.second);

}