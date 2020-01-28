#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	_iRed = 0;
	_iGreen = 0;
	_iBlue = 0;
	_lightVector = Vector(0, 0, 0);
}

DirectionalLight::DirectionalLight(float i, Vector v)
{
	_iRed = i;
	_iGreen = i;
	_iBlue = i;
	_lightVector = v;
}

DirectionalLight::DirectionalLight(float r, float g, float b, Vector v)
{
	_iRed = r;
	_iGreen = g;
	_iBlue = b;
	_lightVector = v;
}

Vector DirectionalLight::GetLightVector()
{
	return _lightVector;
}

 void DirectionalLight::SetLightVector(const Vector ldir)
{
	_lightVector = ldir;
}

void DirectionalLight::Copy(const DirectionalLight& other)
{
	_iRed = other._iRed;
	_iGreen = other._iGreen;
	_iBlue = other._iBlue;
	_lightVector = other._lightVector;
}
