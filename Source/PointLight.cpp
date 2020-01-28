#include "PointLight.h"

PointLight::PointLight()
{
	_iRed = 0;
	_iGreen = 0;
	_iBlue = 0;
	_attenA = 0;
	_attenB = 0;
	_attenC = 0;
}

PointLight::PointLight(float c, Vertex v)
{
	_iRed = _iGreen = _iBlue = c;
	_lightPosition = v;
}

PointLight::PointLight(float c, Vertex v, float aa, float ab, float ac)
{
	_iRed = _iGreen = _iBlue = c;
	_attenA = aa;
	_attenB = ab;
	_attenC = ac;
	_lightPosition = v;
}

PointLight::PointLight(float r, float g, float b, Vertex v)
{
	_iRed = r;
	_iGreen = g;
	_iBlue = b;
	_lightPosition = v;
}

PointLight::PointLight(float r, float g, float b, Vertex v, float aa, float ab, float ac)
{
	_iRed = r;
	_iGreen = g;
	_iBlue = b;
	_attenA = aa;
	_attenB = ab;
	_attenC = ac;
	_lightPosition = v;
}

float PointLight::GetAAttenuation()
{
	return _attenA;
}

void PointLight::SetAAttenuation(float aa)
{
	_attenA = aa;
}

float PointLight::GetBAttenuation()
{
	return _attenB;
}

void PointLight::SetBAttenuation(float ab)
{
	_attenB = ab;
}

float PointLight::GetCAttenuation()
{
	return _attenC;
}

void PointLight::SetCAttenuation(float ac)
{
	_attenC = ac;
}

Vertex PointLight::GetLightPosition() const
{
	return _lightPosition;
}

void PointLight::setLightPosition(const Vertex v)
{
	_lightPosition = v;
}

Vector PointLight::GetLightVector(Vertex v)
{
	return _lightPosition.SubstractVertexToVector(v);
}
