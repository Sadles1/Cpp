#include <iostream>
#include <vector>
#include "Keyboard.h"
#include "scanner.h"
#include <memory>
#include <ctime>


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	bool Work = 1;
	int NumbKey = rand() % 3 + 1;
	int NumbScan = rand() % 3 + 1;

	int NumbPer = NumbKey + NumbScan;
	//peripheral per[NumbPer];
	std::vector <std::unique_ptr<peripheral>> per{};

	for (int i = 0; i < NumbKey; i++)
	{
		per.emplace_back(std::make_unique<Keyboard>());
	}
	for (int i = NumbKey; i < NumbPer; i++)
	{
		per.emplace_back(std::make_unique<scanner>());
	}

	while (Work)
	{
		int choice;
		std::cout << "Клавиатур: "<< NumbKey <<"\nСканнеров: "<< NumbScan <<"\n\n1)Характеристики\n2)Изменить характеристики\n3)Средняя цена\n4)Показать товары в наличии\n5)Выход\n>>> ";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				system("cls");
				for (int i = 0; i < NumbPer; i++)
				{
					const auto& item = per[i];
					std::cout << i+1 << ") ";
					item->show();
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
				const auto& item = per[a];
				auto key = dynamic_cast<Keyboard*>(item.get());
				if (key)
				{
					int b;
					std::cout << "Какую характеристику необходимо изменить:\n 1)Цвет\n 2)Производитель \n 3)Цена \n 4)Кол-во клавиш \n 5)Наличие\n>>> ";
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
						case 5:
						{
							key->ChangeInStock();
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
					std::cout << "Какую характеристику необходимо изменить:\n 1)Цвет\n 2)Производитель \n 3)Цена \n 4)Разрешение \n5)Наличие\n>>> ";
					std::cin >> b;
					auto scan = dynamic_cast<scanner*>(item.get());
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
						case 5:
						{
							key->ChangeInStock();
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
				break;
			}
			case 3:
			{
				system("cls");
				float TotalPrice = 0;

				for (int i = 0; i < NumbPer; i++)
				{
					const auto& item = per[i];
					TotalPrice += item->GetPrice();
				}
				TotalPrice /= float(NumbPer);
				std::cout << "Средняя цена: " << TotalPrice << "\n\n";
				break;
			}
			case 4:
			{
				system("cls");
				int a = 0;
				for (int i = 0; i < NumbPer; i++)
				{
					const auto& item = per[i];
					if (item->GetInStock())
					{
						a++;
						std::cout << a << ") ";
						item->show();
					}
				}
				std::cout << std::endl;
				break;
			}
			case 5:
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
}