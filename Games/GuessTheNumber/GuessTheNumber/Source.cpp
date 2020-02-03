#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	const int MAX_NUMBER=100;
	int a, Number, tries = 0, guess;
	while (true)
	{
		cout << "Who will guess the number?\n1)Player\n2)Computer\n >>> ";
		cin >> a;
		switch (a)
		{
			case 1:
			{
				Number = rand() % MAX_NUMBER + 1;
				tries = 0;
				do
				{
					cout << "Enter a guess: ";
					cin >> guess;
					++tries;
					if (guess > Number)
					{
						cout << "Too high!\n\n";
					}
					else if (guess < Number)
					{
						cout << "Too low!\n\n";
					}
					else
					{
						cout << "\nThat's it! You got it in " << tries << " guesses!\n\n";
					}
				} while (guess != Number);
				break;
			}
			case 2:
			{
				cout << "Write the number: ";
				cin >> Number;
				cout << endl;
				int new_Max_Number = MAX_NUMBER;
				int new_Min_Number = 1;
				tries = 0;
				do
				{
					guess = (new_Max_Number + new_Min_Number) / 2;
					++tries;
					cout << "Computer predict: " << guess;
					if (guess > Number)
					{
						new_Max_Number = guess;
						cout << "\nToo high!\n\n";
					}
					else if (guess < Number)
					{
						new_Min_Number = guess;
						cout << "\nToo low!\n\n";
					}
					else
					{
						cout << "\nThat's it! Computer got it in " << tries << " guesses!\n\n";
					}
				} while (guess != Number);
				break;
			}
			default:
			{	
				cout << "Error of writing\n";
				break;
			}
			break;
		}
	}
	return 0;
}