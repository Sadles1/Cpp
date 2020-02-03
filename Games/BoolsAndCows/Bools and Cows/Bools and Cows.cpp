#include <time.h>
#include "Header1.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
int Win, Lose, WinRate;
using namespace std;
void main()
{

	srand(time(NULL));//Нужно для генерации рандомных чисел
	setlocale(LC_ALL, "Rus");//Для ввода русских символов
	int n;
ProfileChange:
	cout << "Choose Profile: \n";
	fstream Profile;
	Profile.open("Profile.txt");
	string S;
	int i = 1;
	while (!Profile.eof())
	{
		int Res;
		Profile >> S;
		for(int j=0;j<3;j++)
		{
			Profile >> Res;
		}

		cout << i++ << ")" << S << endl;
	}
	int CNNumber = i;
	cout << i << ")Create New \n";
	Profile.close();
	Profile.open("Profile.txt");
	cout << ">>> ";
	cin >> n;
	if (n != CNNumber)
	{
		for (int j = 1; j < n;j++)
		{
			int Res;
			Profile >> S;
			for (int k = 0; k < 3; k++)
			{
				Profile >> Res;
			}
		}
		Profile >> S;
		Profile >> Win;
		Profile >> Lose;
		Profile >> WinRate;
		cout << "You choose profile: " << S << endl << endl;
	}
Menu:

	cout << "Profile: " << S <<"\n1)Start \n2)Instruction \n3)Credits \n4)Change Profile\n5)Statistics \n>>> ";
	cin >> n;
	switch (n)
	{
	case 1:
	{
		Singleplayer();
	Play:
		cout << endl;
		cout << "1)Play another game \n2)Exit to main menu \n>>> ";

		cin >> n;
		switch (n)
		{
		case 1:
		{
			cout << endl;
			Singleplayer();
			goto Play;
		}
		case 2:
		{
			goto Menu;
		}
		default:
		{
			if (cin.fail())//Этот и следующий if нужен для проверки ввода
			{
				cout << "You write a wrong point, please try again: " << endl;
				cin.clear();
				cin.ignore(numeric_limits <streamsize>::max(), '\n');
				goto Play;
			}
			else
			{
				if (cin.fail())
				{
					cout << "You write a wrong point, please try again: " << endl;

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), ' \n ');

					goto Play;
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), ' \n ');
				cout << "You write a wrong point, please try again: " << endl;
				goto Play;
			}
		}
		}
	}
	case 2:
	{
		//Следующая строчка просто описывает правила
		cout << "Компьютер и игрок задумывают четырехзначные числа, так чтобы все цифры числа были различные. \nЦель каждого – угадать это число.За каждый ход отгадывающий называет свое четырех - значное число. \nЕсли цифра из названного числа есть в отгадываемом числе, но стоит не на своем месте, то эта ситуация называется \"корова\" \nЕсли цифра стоит на своем месте, то эта ситуация называется \"бык\" \nНапример, компьютер сгенерировал 6109, а пользователь назвал 0123. \nКомпьютер должен вывести : 1б1к(1 бык и 1 корова).";

	MenuInstruction:
		cout << "1)Back \n>>> ";
		cin >> n;
		if (cin.fail())//Этот и следующий if нужен для проверки ввода
		{
			cout << "You write a wrong point, please try again \n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto MenuInstruction;
		}
		else
		{
			if (n == 1)
			{
				goto Menu;
			}
			else
			{
				if (cin.fail())
				{
					cout << "You write a wrong point, please try again \n";


					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					goto Play;
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You write a wrong point, please try again \n";
				goto MenuInstruction;
			}
		}
	}
	case 3:
	{

	MenuCreate:
		cout << "Create by @Sadles \nTested by @p4shark \n1)Back \n>>> ";
		cin >> n;
		if (cin.fail())//Этот и следующий if нужен для проверки ввода
		{
			cout << "You write a wrong point, please try again \n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto MenuInstruction;
		}
		else
		{
			if (n == 1)
			{
				goto Menu;
			}
			else
			{
				if (cin.fail())
				{
					cout << "You write a wrong point, please try again \n";


					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					goto Play;
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You write a wrong point, please try again \n";
				goto MenuInstruction;
			}
		}
	}
	case 4:
	{
		goto ProfileChange;
	}
	case 5:
	{
		cout << "Win: " << Win << "\nLose: " << Lose << "\nWinRate: " << WinRate << " %\n\n";
		goto Menu;
	}
	default:
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You write wrong point, please try again";
		if (cin.fail())
		{
			cout << " You write a wrong point, please try again \n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto Menu;
		}
		goto Menu;
	}
	}
}