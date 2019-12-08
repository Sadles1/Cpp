#pragma once
#include "peripheral.h"

class Keyboard : public peripheral
{
public:

	int GetNumberOfKey();
	void SetNumbOfKey(int newNumber);
	void show();

private:

	int NumbOfKey=54;


};

