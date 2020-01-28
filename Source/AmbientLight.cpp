#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_iRed = 0;
	_iGreen = 0;
	_iBlue = 0;
}

AmbientLight::AmbientLight(float i)
{
	_iRed = i;
	_iGreen = i;
	_iBlue = i;
}

AmbientLight::AmbientLight(float r, float g, float b)
{
	_iRed = r;
	_iGreen = g;
	_iBlue = b;
}