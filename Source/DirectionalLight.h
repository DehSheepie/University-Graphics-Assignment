#pragma once
#include "Vector.h"
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(float, Vector);
	DirectionalLight(float, float, float, Vector);
	Vector GetLightVector();
	void SetLightVector(const Vector);
private:
	void Copy(const DirectionalLight&); //probably get rid of this
	Vector _lightVector;
};

