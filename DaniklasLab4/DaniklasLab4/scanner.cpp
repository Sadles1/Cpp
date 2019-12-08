#include "scanner.h"

void scanner::SetResolution(float newResolution)
{
	Resolution = newResolution;
}

float scanner::GetResolution()
{
	return Resolution;
}

void scanner::show()
{
	std::cout << "Тип: Сканнер\n";
	std::cout << "Цвет: " << Color << std::endl;
	std::cout << "Производитель: " << Manufacturer << std::endl;
	std::cout << "Цена: " << Price << std::endl;
	std::cout << "Разрешение: " << Resolution << "\n\n";
}
