#pragma once
#include "Vertex.h"
#include "Vector.h"
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();
	PointLight(float, Vertex);
	PointLight(float, Vertex, float, float, float);
	PointLight(float, float, float, Vertex);
	PointLight(float, float, float, Vertex, float, float, float);
	float GetAAttenuation();
	void SetAAttenuation(float);
	float GetBAttenuation();
	void SetBAttenuation(float);
	float GetCAttenuation();
	void SetCAttenuation(float);
	Vertex GetLightPosition() const;
	void setLightPosition(const Vertex);
	Vector GetLightVector(Vertex);
private:
	Vertex _lightPosition;
	// Is not multiplied by anything meaning. This will create a constant lighting on its own
	float _attenA;
	// Makes light dissipate more slowly as distance increases
	float _attenB;
	// Will make light dissipate more quickly closer to the source and then slow down
	float _attenC;
};

