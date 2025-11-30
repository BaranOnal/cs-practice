#include <iostream>

using namespace std;

int main() {

    int rows, n1 = 1, n2 = 1, number;

    cout << "Enter the number of rows :";
    cin >> rows;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 1; j < rows - i; j++)
        {
            cout << "   ";
        }

        for (int k = 0; k <= i; k++)
        {
            if (k == 0)
                number = 1;
            else
                number = number * (i - k + 1) / k;
            cout << number << "     ";
        }
        cout << "\n";
    }

    return 0;
}