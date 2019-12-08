#pragma once
#include "peripheral.h"


class scanner : public peripheral
{
public:

	void SetResolution(float newResolution);
	float GetResolution();
	void show();

private:

	float Resolution = 600;

};

