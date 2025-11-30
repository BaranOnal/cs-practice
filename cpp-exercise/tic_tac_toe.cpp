#include <iostream>
#include<ctime>

using namespace std;


void drawBoard(char* spaces);
void playerMove(char* spaces, char player);
void computerMove(char* spaces, char computer);
bool checkWinner(char* spaces, char computer, char player);
bool checkTie(char* spaces);

int main() {
	char spaces[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
	char player = 'X';
	char computer = 'O';
	bool running = true;

	drawBoard(spaces);

	while (running)
	{
		playerMove(spaces, player);
		drawBoard(spaces);
		if (checkWinner(spaces, computer, player))
		{
			running = false;
			break;
		}
		else if (checkTie(spaces))
		{
			running = false;
			break;
		}
		
		computerMove(spaces, computer);
		drawBoard(spaces);
		if (checkWinner(spaces, computer, player))
		{
			running = false;
			break;
		}
		else if (checkTie(spaces))
		{
			running = false;
			break;
		}
	}
	return 0;
}

void drawBoard(char* spaces)
{
	cout << '\n';
	cout << "     |     |     " << endl;
	cout << "  "<<spaces[0]<<"  |  " << spaces[1] << "  |  " << spaces[2] << "  " << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << endl;
	cout << "     |     |     " << endl;
	cout << '\n';

}

void playerMove(char* spaces, char player)
{
	int number;

	do
	{
		cout << "Enter the number of the area we will mark.(1-9)\n";
		cin >> number;
		number--;
		if (spaces[number] == ' ')
		{
			spaces[number] = player;
			break;
		}
		/*if (spaces[number] == player)
		{
			playerMove(spaces, player);
			
		}*/
	} while (true);
	
}

void computerMove(char* spaces, char computer)
{
	int number;
	srand(time(NULL));

	while (true)
	{
		number = rand() % 9;
		if (spaces[number] == ' ')
		{
			spaces[number] = computer;
			break;
		}
	}
}

bool checkWinner(char* spaces, char computer, char player)
{
	// Satýr kontrolleri
	if ((spaces[0] != ' ') && (spaces[0] == spaces[1]) && (spaces[1] == spaces[2]))
	{
		spaces[0] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else if ((spaces[3] != ' ') && (spaces[3] == spaces[4]) && (spaces[4] == spaces[5]))
	{
		spaces[3] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else if ((spaces[6] != ' ') && (spaces[6] == spaces[7]) && (spaces[7] == spaces[8]))
	{
		spaces[6] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	// Sütun kontrolleri
	else if ((spaces[0] != ' ') && (spaces[0] == spaces[3]) && (spaces[3] == spaces[6]))
	{
		spaces[0] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else if ((spaces[1] != ' ') && (spaces[1] == spaces[4]) && (spaces[4] == spaces[7]))
	{
		spaces[1] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else if ((spaces[2] != ' ') && (spaces[2] == spaces[5]) && (spaces[5] == spaces[8]))
	{
		spaces[2] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	// Çapraz kontroller
	else if ((spaces[0] != ' ') && (spaces[0] == spaces[4]) && (spaces[4] == spaces[8]))
	{
		spaces[0] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else if ((spaces[2] != ' ') && (spaces[2] == spaces[4]) && (spaces[4] == spaces[6]))
	{
		spaces[2] == player ? cout << "YOU WIN!\n" : cout << "YOU LOSE!\n";
	}
	else
	{
		return false; // Henüz kazanan yok
	}
	return true; // Bir kazanan bulundu
}

bool checkTie(char* spaces)
{
	
	for (int i = 0; i < 9; i++)
	{
		if (spaces[i] == ' ')
		{
			return false;
		}
	}
	cout << "IT'S A TIE!\n";
	return true;
}