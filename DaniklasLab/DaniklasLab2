#include <iostream>
#include <vector>
#include <iomanip>
#include "locale.h"

using namespace std;

class TurFirma
{
private:
	string Name;
	string Way;
	int Number;
public:
	TurFirma() //Конструктор
	{
		Name = '0'; //начальные значения переменным
		Way = '0';
		Number = 0;
	}
	TurFirma(string A,string B,int C) //Конструктор с параметрами
	{
		Name = A; 
		Way = B;
		Number = C;
	}
	void setName(string a)
	{
		Name = a;
	}
	void setWay(string a)
	{
		Way=a;
	}
	void setNumber(int a)
	{
		Number = a;
	}
	int getNumber()
	{
		return Number;
	}
	void getInf()
	{
		cout.setf(ios::left);
		cout.width(15);
		cout << setw(15) << Name << setw(15) << Way << setw(15) << Number << endl;
	}
	~TurFirma()//Деструктор
	{
		
	}

};

int main()
{
	string enterS;
	int enterI, a = 0;
	setlocale(LC_ALL, "rus");
	cout.setf(ios::left);

	//TurFirma turFirma1;
	//TurFirma turFirma2;
	TurFirma turFirma3[4];
	for (int i = 0; i < 4; i++)
	{
		cout << "Введите название: ";
		cin >> enterS;
		turFirma3[i].setName(enterS);
		cout << "Введите путь: ";
		cin >> enterS;
		turFirma3[i].setWay(enterS);
		cout << "Введите кол-во оставшихся путевок: ";
		cin >> enterI;
		turFirma3[i].setNumber(enterI);
	}

	while (1)
	{
		cout << "1) Редактировать " << "\n" << "2) Вывод массива " << "\n" << "3) Общее кол-во оставшихся путёвок" << "\n";
	tryAgain: //Для goto

		cout << ">>> ";
		cin >> a;


		switch (a)
		{
		case 1:
		{
			cout << "Какую строку необходимо изменить?" << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << i + 1 << ")";
				cout.width(15);
				turFirma3[i].getInf();
			}
			cout << ">>> ";
			cin >> a;
			a--;
			int param;
			cout << "Какой из параметров необходимо изменить?" << endl;
			cout << "1)Название " << endl << "2)Маршрут" << endl << "3)Кол-во оставшихся путёвок" << endl << "4)Всю строку " << endl << ">>> ";
			cin >> param;
			switch (param)
			{
			case 1:
			{
				cout << "Введите новое название: " << endl;
				cin >> enterS;
				turFirma3[a].setName(enterS);
				break;
			}
			case 2:
			{
				cout << "Введите новый маршрут: " << endl;
				cin >> enterS;
				turFirma3[a].setWay(enterS);
				break;
			}
			case 3:
			{
				cout << "Введите кол-во оставшихся путёвок: " << endl;
				cin >> enterI;
				turFirma3[a].setNumber(enterI);
				break;
			}

			case 4:
			{
				cout << "Введите новое название: " << endl;
				cin >> enterS;
				turFirma3[a].setName(enterS);
				cout << "Введите новый маршрут: " << endl;
				cin >> enterS;
				turFirma3[a].setWay(enterS);
				cout << "Введите кол-во оставшихся путёвок: " << endl;
				cin >> enterI;
				turFirma3[a].setNumber(enterI);
				break;
			}
			break;
			}
		case 2:
		{
			cout.width(30);
			cout << "-----------------------------------------------------" << endl;
			cout << setw(15) << "Название " << setw(15) << "Маршрут " << setw(15) << "Кол-во оставшихся путёвок " << endl;
			for (int i = 0; i < 4; i++)
			{
				turFirma3[i].getInf();
			}
			cout << "-----------------------------------------------------" << endl << endl;
			break;
		}
		case 3:
		{
			int Number = 0;
			for (int i = 0; i < 4; i++)
			{
				Number += turFirma3[i].getNumber();
			}
			cout << "Осталось " << Number << " путёвок" << "\n";
			break;
		}
		default:
		{
			cout << "Ошибка ввода!" << endl;
			goto tryAgain;
			break;
		}
		}
		}

	}
}
