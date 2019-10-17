#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "Header1.h"
using namespace std;
int Cows = 0, Bulls = 0, NewCows = 0, NewBulls = 0;

vector<int> AllVariants;//Вектор всех возможных вариантов для компьютера
int Cows_and_Bulls(int* Element1, int* Element2)//Подсчёт количества быков и коров
{
	Cows = 0;
	Bulls = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (Element1[i] == Element2[k])
			{
				if (i == k)

					Bulls++;
				else
					Cows++;

			}
		}
	}
	return 0;
}
int NewCows_and_NewBulls(int* Element1, int* Element2)
{
	NewCows = 0;
	NewBulls = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (Element1[i] == Element2[k])
			{
				if (i == k)
					NewBulls++;
				else
					NewCows++;

			}
		}
	}
	return 0;
}
int* Number_to_digit(int Number, int* Element)//Разделения числа на его составляющие
{
	Element[0] = Number % 10;
	int NewNumber = Number / 10;
	for (int i = 1; i < 4; i++)
	{
		Element[i] = NewNumber % 10;
		NewNumber /= 10;
	}
	reverse(&Element[-1], &Element[5]);

	return Element;
}
vector <int> Delete_All_Variants(int* ComputerStepElement, int* PlayerElement)//Удаление неподходящих вариантов(Метод Решета)
{
	int X[4];
	int size = AllVariants.size();
	vector <int> NewAllVariants;
	NewAllVariants.clear();
	for (int i = 0; i < size; i++)
	{
		Number_to_digit(AllVariants[i], X);
		NewCows_and_NewBulls(X, ComputerStepElement);
		if (NewCows == Cows && NewBulls == Bulls)
		{
			NewAllVariants.push_back(AllVariants[i]);
		}
	}
	AllVariants.clear();
	AllVariants = NewAllVariants;
	return AllVariants;
}
int Singleplayer()//Основная функция
{
	int size, step = 1;
	ifstream File;
	vector <int> AllVariantsForPlayer;
	File.open("File.txt");
	while (!File.eof())
	{
		int A;
		File >> A;
		AllVariants.push_back(A);
		AllVariantsForPlayer.push_back(A);
	}
	size = AllVariants.size();
	int PlayerNumber, PlayerStep = 0, PlayerElement[4],
		PlayerStepElement[4];//Переменные для игрока
	int ComputerNumber, ComputerStep = 0, ComputerDigits = 0, ComputerElement[4],
		ComputerStepElement[4], ComputerOldStepElement[4];//Переменные для компьютера
	cout << "Write your number: ";
TryAgain:
	cin >> PlayerNumber;
	if (cin.fail())//Этот if нужен для проверки ввода
	{

		cout << "You write a wrong text, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		goto TryAgain;
	}
	if (binary_search(AllVariantsForPlayer.begin(), AllVariantsForPlayer.end(), PlayerNumber)) {}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You write a wrong number, please try again: ";
		goto TryAgain;
	}
	Number_to_digit(PlayerNumber, PlayerElement);
	ComputerNumber = AllVariants[rand() % size];
	Number_to_digit(ComputerNumber, ComputerElement);
	/* Строчки нужные для упрощения разработки чтобы выводилось число загаданное
	компьютером
	cout << "For Develop, Computer Number: ";
	for (int i = 0; i &lt; 4; i++)
		cout << ComputerElement[i];
	cout << endl;
	*/
	cout << endl << endl;
	while (PlayerStep != ComputerNumber && ComputerStep != PlayerNumber)
	{
		cout << "Player Step " << step <<  ": ";
	TryAgain1:
		cin >> PlayerStep;
		Number_to_digit(PlayerStep, PlayerStepElement);
		if (cin.fail())
		{
			cout << "You write a wrong text, please try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			goto TryAgain1;
		}
		if (binary_search(AllVariantsForPlayer.begin(), AllVariantsForPlayer.end(),

			PlayerStep)) {
		}
		else
		{
			if (cin.fail())
			{
				cout <<"You write a wrong text, please try again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				goto TryAgain1;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You write a wrong number, please try again: ";
			goto TryAgain1;
		}
		Cows_and_Bulls(PlayerStepElement, ComputerElement);
		cout << "Bulls: " << Bulls << ", Cows: " << Cows << endl;
		size = AllVariants.size();
		int j = rand() % size;
		ComputerStep = AllVariants[j];
		cout << "Computer Step " << step << ": ";
		Number_to_digit(ComputerStep, ComputerStepElement);
		for (int i = 0; i < 4; i++)
			cout << ComputerStepElement[i];
		cout << endl;
		Cows_and_Bulls(ComputerStepElement, PlayerElement);
		cout << "Bulls: " << Bulls << ", Cows: " << Cows << endl;
		AllVariants.erase(AllVariants.begin() + j);
		Delete_All_Variants(ComputerStepElement, PlayerElement);
		if (PlayerStep == ComputerNumber || ComputerStep == PlayerNumber)
		{
			if (PlayerStep == ComputerNumber && ComputerStep != PlayerNumber)
			{
				cout <<"\n\nYou Win!!!!\n\n";
				Win++;
				break;
			}
			if (ComputerStep == PlayerNumber && PlayerStep != ComputerNumber)
			{
				cout << "\n\nYou Lose(\n\n";
				cout << "Computer Number: ";
				for (int i = 0; i < 4; i++)
					cout << ComputerElement[i];
				cout << endl << endl;
				Lose++;
				break;
			}
			if (ComputerStep == PlayerNumber && PlayerStep == ComputerNumber)
			{
				cout << "\n\n  Draw \n\n";
				break;
			}
		}
		step++;
		cout << endl << endl;
	}
	return 0;
}