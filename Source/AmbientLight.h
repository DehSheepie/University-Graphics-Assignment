#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight();
	AmbientLight(float);
	AmbientLight(float, float, float);
};

