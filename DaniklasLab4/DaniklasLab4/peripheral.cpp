#include "peripheral.h"

peripheral::peripheral()
{
	strcpy_s(Manufacturer, "Samsung");
	strcpy_s(Color, "Black");
	Price = rand() % 20000 + 3000;
	inStock = rand() & 1;
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

bool peripheral::GetInStock()
{
	return inStock;
}

void peripheral::ChangeInStock()
{
	if (inStock)
	{
		inStock = 0;
	}
	else
	{
		inStock = 1;
	}
}

void peripheral::show()
{
	std::cout << "Цвет: " << Color << std::endl;
	std::cout << "Производитель: " << Manufacturer << std::endl;
	std::cout << "Цена: " << Price << std::endl;
}
