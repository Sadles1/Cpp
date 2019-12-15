#include <iostream>
#include <windows.h>
#include <string>

class Сonditioner
{
public:

	void OnOffHumidifier()
	{
		if (onHumidifier)
		{
			onHumidifier = 0;
		}
		else
		{
			onHumidifier = 1;
		}
	}

	void ChangeTemperature(float newTemperature)
	{
		Sleep(500*abs(Temperature - newTemperature));
		Temperature = newTemperature;
	}
	
	bool GetonHumidifier()
	{
		return onHumidifier;
	}

	float GetTemperature()
	{
		return Temperature;
	}

	void SetAirSpeed(int newAirSpeed)
	{
		AirSpeed=newAirSpeed;
	}

	int GetAirSpeed()
	{
		return AirSpeed;
	}



private:

	int AirSpeed = 1;
	float Temperature = 20.0;
	bool onHumidifier = 0;//Увлажнение воздуха(есть в некоторых кондиционерах)

};

int main()
{
	setlocale(LC_ALL, "rus");
	Сonditioner Cond1;
	int choice;
	while (1)
	{
		std::cout << "Кондиционер\n\n";
		std::cout << "Температура: " << Cond1.GetTemperature() << "\n" <<"Скорость потока воздуха: " << Cond1.GetAirSpeed() << "\nУвлажнение: ";
		if (Cond1.GetonHumidifier())
			std::cout << "Включено\n\n";
		else
			std::cout << "Выключено\n\n";
		std::cout << "1)Изменить температуру\n2)Включить увлажнение воздуха\n3)Изменить Скорость потока воздуха\n\n>>> ";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				float newTemperature;
				std::cout << "Введите новую температуру: ";
				std::cin >> newTemperature;
				Cond1.ChangeTemperature(newTemperature);
				system("cls");
				break;
			}
			case 2:
			{
				Cond1.OnOffHumidifier();
				system("cls");
				break;
			}
			case 3:
			{
				int newAirSpeed;
				std::cout << "Введите скорость(1-5): ";
				std::cin >> newAirSpeed;
				if (newAirSpeed < 6 && newAirSpeed > 0)
				{
					Cond1.SetAirSpeed(newAirSpeed);
					system("cls");
				}
				else
				{
					system("cls");
					std::cout << "Ошибка ввода\n\n";
				}
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
