#include "Camera.h"

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRot = xRotation;
	_yRot = yRotation;
	_zRot = zRotation;
	_position = position;
}

Camera::Camera()
{
	_xRot = 0;
	_yRot = 0;
	_zRot = 0;
	_position = Vertex(0, 0, -50);
}

float Camera::GetXRotation() const 
{
	return _xRot;
}

void Camera::SetXRotation(const float x)
{
	_xRot = x;
}

float Camera::GetYRotation() const
{
	return _yRot;
}

void Camera::SetYRotation(const float y)
{
	_yRot = y;
}

void Camera::SetZRotation(const float z)
{
	_zRot = z;
}

Vertex Camera::GetPosition() const
{
	return _position;
}

void Camera::SetPosition(const Vertex p)
{
	_position = p;
}

Matrix Camera::GetCameraMatrix() const
{
	float convert = (3.14159265359f / 180.0f);
	float xRadians = _xRot * convert;
	float yRadians = _yRot * convert;
	float zRadians = _zRot * convert;

	Matrix xRotation
	{
		1, 0, 0, 0,
		0, static_cast<float>(cos(xRadians)), static_cast<float>(sin(xRadians)),0,
		0,static_cast<float>(-sin(xRadians)), static_cast<float>(cos(xRadians)),0,
		0,0,0,1
	};

	Matrix yRotation
	{
		static_cast<float>(cos(yRadians)), 0, static_cast<float>(-sin(yRadians)),0,
		0,1,0,0,
		static_cast<float>(sin(yRadians)),0,static_cast<float>(cos(yRadians)),0,
		0,0,0,1
	};

	Matrix zRotation
	{
		static_cast<float>(cos(zRadians)), static_cast<float>(sin(zRadians)),0,0,
		static_cast<float>(-sin(zRadians)), static_cast<float>(cos(zRadians)),0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix cameraPos{
		1,0,0, -_position.GetX(),
		0,1,0,-_position.GetY(),
		0,0,1,-_position.GetZ(),
		0,0,0,1 };

	Matrix cMatrix = xRotation * yRotation * zRotation * cameraPos;

		return cMatrix;
}

float Camera::GetZRotation() const
{
	return _zRot;
}