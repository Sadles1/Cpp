#include "peripheral.h"

peripheral::peripheral()
{
	strcpy_s(Manufacturer, "Samsung");
	strcpy_s(Color, "Black");
	Price = 5000;
}

void peripheral::SetManufacturer(char* newManufacturer)
{
	strcpy_s(Manufacturer, newManufacturer);
}


void peripheral::SetColor(char* newColor)
{
	strcpy_s(Color, newColor);
}

float peripheral::GetPrice()
{
	return Price;
}

void peripheral::SetPrice(float newPrice)
{
	Price = newPrice;
}

void peripheral::show()
{
	std::cout << "Цвет: " << Color << std::endl;
	std::cout << "Производитель: " << Manufacturer << std::endl;
	std::cout << "Цена: " << Price << std::endl;
}
