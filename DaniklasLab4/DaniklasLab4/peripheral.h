#pragma once
#include <iostream>
#include <string>

class peripheral
{

public:

	peripheral();

	void SetColor(char* newColor);

	float GetPrice();
	void SetPrice(float newPrice);

	bool GetInStock();

	void ChangeInStock();
	virtual void show();

	void SetManufacturer(char* newManufacturer);

protected:

	char Color[30];
	char Manufacturer[30];//Производитель
	float Price;
	bool inStock;

};