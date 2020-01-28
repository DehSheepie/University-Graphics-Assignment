#pragma once
#include "Vector.h"
class Light
{
public:
	Light();
	Light(float, float, float);
	Light(float);
	float GetRedIntensity();
	void SetRedIntensity(const float);
	float GetGreenIntensity();
	void SetGreenIntensity(const float);
	float GetBlueIntensity();
	void SetBlueIntensity(const float);
protected:
	// colour values ranging 0-255
	float _iRed;
	float _iGreen;
	float _iBlue;
};

