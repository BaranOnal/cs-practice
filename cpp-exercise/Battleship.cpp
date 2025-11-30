#include <iostream>

using namespace std;

int main() {

	bool ships[4][4] = {
		{0,1,0,0},
		{0,0,1,0},
		{0,0,1,0},
		{1,1,0,0}

	};

	int hits = 0, numberofHits = 0, row, column;
	

	while (hits < 5)
	{
		cout << "Enter the cordinates \n";
		cout << "Enter a row number(0-3):";
		cin >> row;
		cout << "Enter a columm number(0-3):";
		cin >> column;

		if (ships[row][column])
		{
			ships[row][column] = 0;
			hits++;

			cout << "You hit it." << 5 - hits << " ships left\n\n";
		}
		else
		{
			cout << "You missed\n\n";
		}
		numberofHits++;
	}
	cout << "You win\n";
	cout << "You shoot " << numberofHits << " times.";
	


	return 0;
}