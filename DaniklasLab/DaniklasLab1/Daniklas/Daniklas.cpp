#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale.h>
using namespace std;


struct person
{
	string surname;
	string forename;
	string position;
	int price;
};

int main()
{
	setlocale(LC_ALL, "");
	cout.setf(ios::left);
	bool program = 1;
	int choice;
	int N=3;
	person *employee = new person[N];
	int i = 0, n = 0;
	ifstream F;
	ofstream FileExit;
	F.open("File.txt");
	FileExit.setf(ios::left);
	if (F)
	{ 
		/*
		string s;
		getline(F, s);
		FileExit << s << endl;
		*/

		while (!F.eof())
		{
			F >> employee[i].surname;
			F >> employee[i].forename;
			F >> employee[i].position;
			F >> employee[i].price;
			i++;
			n++;
		}

		F.close(); 

	}
	else
		cout << "Файл не найден!" << endl;

	while (program)
	{
		cout << "---------------------------" << endl;
		cout << "1) Список " << endl << "2) Отредактировать строку " << endl << "3) Наибольший оклад" << endl << "4) Сохранить" <<  endl << "5) Выйти" << endl << ">>> " ;
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				cout << endl;
				cout << "-----------------------------------------------------" << endl;
				cout.width(15);
				cout << "Фамилия" << setw(15) << "Имя" << setw(15) << "Должность"<< setw(10) << "Оклад" << endl;
				for (i = 0; i < n; i++)
				{
					cout.width(15);
					cout << employee[i].surname << setw(15) << employee[i].forename << setw(15) << employee[i].position << setw(10) << employee[i].price  << endl;
				}
				cout << "-----------------------------------------------------" << endl << endl;
				break;
			}
			case 2:
			{
				cout << "Какую строку необходимо изменить?" << endl;
				for (i = 0; i < n; i++)
				{
					cout << i+1 << ")";
					cout.width(15);
					cout << employee[i].surname << setw(15) << employee[i].forename << setw(15) << employee[i].position << setw(10) << employee[i].price << endl;
				}
				cout << ">>> ";
				cin >> i;
				i--;
				int param;
				cout << "Какой из параметров необходимо изменить?" << endl;
				cout << "1)Фамилия" << endl << "2)Имя" << endl << "3)Должность" << endl << "4)Оклад" << endl << "5)Всю строку " << endl << ">>> ";
				cin >> param;
				string newparam;
				switch (param)
				{
					case 1:
					{
						cout << "Введите новую фамилию" << endl << ">>> ";
						cin >> newparam;
						employee[i].surname = newparam;
						break;
					}
					case 2:
					{
						cout << "Введите новое имя" << endl << ">>> ";
						cin  >> newparam;
						employee[i].forename = newparam;
						break;
					}
					case 3:
					{
						cout << "Введите новую должность" << endl << ">>> ";
						cin >> newparam;
						employee[i].position= newparam;
						break;
					}
					case 4:
					{
						int newprice;
						cout << "Введите новый оклад" << endl << ">>> ";
						cin >> newprice;
						employee[i].price = newprice;
						break;
					}
					case 5:
					{
						cout << "Введите новую фамилию" << endl << ">>> ";
						cin >> newparam;
						employee[i].surname = newparam;
						cout << "Введите новое имя" << endl << ">>> ";
						cin >> newparam;
						employee[i].forename = newparam;
						cout << "Введите новую должность" << endl << ">>> ";
						cin >> newparam;
						employee[i].position = newparam; 
						int newprice;
						cout << "Введите новый оклад" << endl << ">>> ";
						cin >> newprice;
						employee[i].price = newprice;
						break;
					}
				}
				break;
			}
			case 3:
			{
				int e = 0;
				int MPrice = employee[0].price;

				for (i = 1; i < n; i++)
				{
					if (MPrice < employee[i].price)
					{
						MPrice = employee[i].price;
						e = i;
					}
				}
				cout << "Наибольший оклад у сотрудника " << employee[e].surname << " " << employee[e].forename << " равный " << employee[e].price << endl;
				break;
			}
			case 4:
			{
				string NameFile;
				cout << "Введите название файла в который необходимо сохранить таблицу: ";
				cin >> NameFile;
				FileExit.open(NameFile);
				FileExit <<  "-----------------------------------------------------" << endl;
				FileExit.width(15);
				FileExit << "Фамилия" << setw(15) << "Имя" << setw(15) << "Должность" << setw(10) << "Оклад" << endl;
				for (i = 0; i < n; i++)
				{
					FileExit.width(15);
					FileExit << employee[i].surname << setw(15) << employee[i].forename << setw(15) << employee[i].position << setw(10) << employee[i].price << left << endl;
				}
				FileExit <<  "-----------------------------------------------------" << endl;
				break;
			}
			case 5:
			{
				program = 0;
				break;
			}
		}
	}
}

