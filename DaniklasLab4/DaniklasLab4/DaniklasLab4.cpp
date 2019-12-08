#include <iostream>
#include "Keyboard.h"
#include "scanner.h"


int main()
{
	setlocale(LC_ALL, "rus");
	bool Work=1;
	const int NumbPer = 4;
	peripheral* per[NumbPer];
	Keyboard key1;
	Keyboard key2;
	scanner scan1;
	scanner scan2;

	per[0] = &key1;
	per[1] = &key2;
	per[2] = &scan1;
	per[3] = &scan2;

	while (Work)
	{
		int choice;
		std::cout << "1)Характеристики\n2)Изменить характеристики\n3)Средняя цена\n4)Выход\n>>> ";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				system("cls");
				for (int i = 0; i < NumbPer; i++)
				{
					std::cout << i+1 << ") ";
					per[i]->show();
				}
				std::cout << std::endl;
				break;
			}
			case 2:
			{
				system("cls");
				int a;
				std::cout << "Характеристики какого элемента необходимо изменить?\n>>> ";
				std::cin >> a;
				a--;
				if (a <= NumbPer)
				{
					system("cls");
					Keyboard* key = dynamic_cast<Keyboard*>(per[a]);
					if (key)
					{
						int b;
						std::cout << "Какую характеристику необходимо изменить:\n 1)Цвет\n 2)Производитель \n 3)Цена \n 4)Кол-во клавиш \n>>> ";
						std::cin >> b;
						switch (b)
						{
							case 1:
							{
								char newColor[30];
								std::cout << "Введите новый цвет: ";
								std::cin >> newColor;
								key->SetColor(newColor);
								system("cls");
								break;
							}
							case 2:
							{
								char newManufacturer[30];
								std::cout << "Введите нового производителя: ";
								std::cin >> newManufacturer;
								key->SetManufacturer(newManufacturer);
								system("cls");
								break;
							}
							case 3:
							{
								float newPrice;
								std::cout << "Введите новую цену: ";
								std::cin >> newPrice;
								key->SetPrice(newPrice);
								system("cls");
								break;
							}
							case 4:
							{
								int newNumbKey;
								std::cout << "Введите новое кол-во клавиш: ";
								std::cin >> newNumbKey;
								key->SetNumbOfKey(newNumbKey);
								system("cls");
								break;
							}
							default:
							{
								system("cls");
								std::cout << "Ошибка ввода\n\n";
								break;
							}	
						}
					}
					else
					{
						int b;
						std::cout << "Какую характеристику необходимо изменить:\n 1)Цвет\n 2)Производитель \n 3)Цена \n 4)Разрешение \n>>> ";
						std::cin >> b;
						scanner* scan = dynamic_cast<scanner*>(per[a]);
						switch (b)
						{
							case 1:
							{
								char newColor[30];
								std::cout << "Введите новый цвет: ";
								std::cin >> newColor;
								scan->SetColor(newColor);
								system("cls");
								break;
							}
							case 2:
							{
								char newManufacturer[30];
								std::cout << "Введите нового производителя: ";
								std::cin >> newManufacturer;
								scan->SetManufacturer(newManufacturer);
								system("cls");
								break;
							}
							case 3:
							{
								float newPrice;
								std::cout << "Введите новую цену: ";
								std::cin >> newPrice;
								scan->SetPrice(newPrice);
								system("cls");
								break;
							}
							case 4:
							{
								int newResolution;
								std::cout << "Введите новое разрешение: ";
								std::cin >> newResolution;
								scan->SetResolution(newResolution);
								system("cls");
								break;
							}
							default:
							{
								system("cls");
								std::cout << "Ошибка ввода\n\n";
								break;
							}

						}
						
					}
				}
				else
				{
					system("cls");
					std::cout << "Ошибка такого элемента не существует" << std::endl;
				}
				break;
			}
			case 3:
			{
				system("cls");
				float TotalPrice = 0;
				for (int i = 0; i < NumbPer; i++)
				{
					TotalPrice+= per[i]->GetPrice();
				}
				TotalPrice /= float(NumbPer);
				std::cout << "Средняя цена: "<<TotalPrice << "\n\n";
				break;
			}
			case 4:
			{
				Work = 0;
				system("cls");
				break;
			}
			default:
			{
				system("cls");
				std::cout << "Ошибка ввода\n";
			}
		}
	}



	/////////////////
	delete[] per;
}