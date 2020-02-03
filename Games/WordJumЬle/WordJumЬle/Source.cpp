// Игра Word JumЫe
//Классическая игра - головоломка.в которой пользователь разгадывает слова.с подсказками 
//или без них.
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main()
{
	int points=0;
	enum fields { WORD, HINT, NUM_FIELDS };
	const int NUM_WORDS = 5;
	const string WORDS[NUM_WORDS][NUM_FIELDS] =
	{
		{"wall", "Do you feel you're banging your head against something?"},
		{"glasses", "These might help you see the answer. "},
		{"labored", "Going slowly. is it?"},
		{"persistent", "Keep at it."},
		{"jumble", "It's what the game is all about."}
	};
	srand(time(NULL));
	cout << "\tWelcome to Word Jumblee!\n\n";
	cout << "Unscramble the letters to make a word. \n";
	cout << "Enter 'hint' for a hint. \n";
	cout << "Enter 'quit' to quit the game. \n\n";
	while (true)
	{
		bool useHint = 0;
		int choice = (rand() % NUM_WORDS);
		string theWord = WORDS[choice][WORD]; //слово. которое нужно угадать
		string theHint = WORDS[choice][HINT]; //подсказка для слова
		string jumble = theWord; // перемешанный вариант слова
		int length = jumble.size();
		for (int i = 0; i < length; ++i)
		{
			int indexl = (rand() % length);
			int index2 = (rand() % length);
			char temp = jumble[indexl];
			jumble[indexl] = jumble[index2];
			jumble[index2] = temp;
		}
		cout << "The jumble is: " << jumble;
		string guess;
		cout << "\n\nYour guess: ";
		cin >> guess;
		while ((guess != theWord) && (guess != "quit"))
		{
			if (guess == "hint")
			{
				cout << theHint;
				useHint = 1;
			}
			else
			{
				cout << "Sorry. that's not it. ";
				points--;
			}
			cout << "\n\nYour guess: ";
			cin >> guess;
		}
		if (guess == theWord)
		{
			cout << "\nThat's it! You guessed it!\n";
			if (useHint)
			{
				points += theWord.length() / 2;
			}
			else
			{
				points += theWord.length();
			}
			cout << "Your score: " << points << "\n\nNext word\n\n";
		}
		if (guess == "quit")
		{
			break;
		}
	}
	cout << "\nThanks for playing. You score = " << points << endl;
	return 0;
}