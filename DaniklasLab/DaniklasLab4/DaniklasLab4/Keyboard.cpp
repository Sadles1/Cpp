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
	std::cout << "Кол-во клавиш: " << NumbOfKey << std::endl;
	std::cout << "Наличие: ";
	if (inStock)
	{
		std::cout << "Есть\n\n";
	}
	else
	{
		std::cout << "Нету\n\n";
	}
}	
