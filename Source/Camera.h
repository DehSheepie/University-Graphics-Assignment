#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include "math.h"

class Camera
{
public: 
	Camera();
	Camera(float, float, float, const Vertex&);
	float GetXRotation() const;
	void SetXRotation(const float);
	float GetYRotation() const;
	void SetYRotation(const float);
	float GetZRotation() const;
	void SetZRotation(const float);
	Vertex GetPosition() const;
	void SetPosition(const Vertex);
	Matrix GetCameraMatrix() const;

private:
	float _xRot;
	float _yRot;
	float _zRot;
	Vertex _position;
};

