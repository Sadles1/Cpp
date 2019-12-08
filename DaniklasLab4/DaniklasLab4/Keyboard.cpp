#include "Keyboard.h"
#include <string>

int Keyboard::GetNumberOfKey()
{
	return NumbOfKey;
}

void Keyboard::SetNumbOfKey(int newNumber)
{
	NumbOfKey = newNumber;
}

void Keyboard::show()
{
	std::cout << "Тип: Клавиатура\n";
	std::cout << "Цвет: " << Color << std::endl;
	std::cout << "Производитель: " << Manufacturer << std::endl;
	std::cout << "Цена: " << Price << std::endl;
	std::cout << "Кол-во клавиш: " << NumbOfKey << "\n\n";
}	
