#include "Light.h"

Light::Light()
{
	_iRed = 0;
	_iGreen = 0;
	_iBlue = 0;
}

Light::Light(float r, float g, float b)
{
	_iRed = r;
	_iGreen = g;
	_iBlue = b;
}

Light::Light(float x)
{
	_iRed = _iBlue = _iGreen = x;
}

float Light::GetRedIntensity()
{
	return _iRed;
}

void Light::SetRedIntensity(const float r)
{
	_iRed = r;
}

float Light::GetGreenIntensity()
{
	return _iGreen;
}

void Light::SetGreenIntensity(const float g)
{
	_iGreen = g;
}

float Light::GetBlueIntensity()
{
	return _iBlue;
}

void Light::SetBlueIntensity(const float b)
{
	_iBlue = b;
}
