#include "Vector.h"

Vector::Vector() 
{
	_x = 0;
	_y = 0;
	_z = 0;
	
}

Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

float Vector::GetX() const
{
	return _x;
}

void Vector::SetX(const float x)
{
	_x = x;
}

float Vector::GetY() const
{
	return _y;
}

void Vector::SetY(const float y)
{
	_y = y;
}

float Vector::GetZ() const
{
	return _z;
}

void Vector::SetZ(const float z)
{
	_z = z;
}

float Vector::DotProduct(Vector a, Vector b)
{
	// Takes the x, y and z values from both vectors and multiplies them together respectively before adding the results together
	float x = a.GetX() * b.GetX();
	float y = a.GetY() * b.GetY();
	float z = a.GetZ() * b.GetZ();
	return x + y + z;
}

Vector Vector::CrossProduct(Vector a, Vector b)
{
	// Given vectors  (a1,a2,a3) and (b1,b2,b3)
	// the cross product is (a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1)
	// Which is the same as (aY*bZ - aZ*bY, aZ*bX - aX*bZ, aX*bY - aY*bX)
	float x = a.GetY() * b.GetZ() - a.GetZ() * b.GetY();
	float y = a.GetZ() * b.GetX() - a.GetX() * b.GetZ();
	float z = a.GetX() * b.GetY() - a.GetY() * b.GetX();
	return Vector(x,y,z);
}

const Vector Vector::operator-(const Vector& rhs) const
{
	float x = this->GetX() - rhs.GetX();
	float y = this->GetY() - rhs.GetY();
	float z = this->GetZ() - rhs.GetZ();
	return Vector(x, y, z);
}

Vector& Vector::Copy(const Vector& rhs)
{
	if (this != &rhs)
	{
		this->SetX(rhs.GetX());
		this->SetY(rhs.GetY());
		this->SetZ(rhs.GetZ());
	}
	return *this;
}

const Vector Vector::GetUnitVector() const
{
	// Gets the length of the vector
	float x = GetVectorLength();
	return Vector(GetX() / x, GetY() / x, GetZ() / x);
}

float Vector::GetVectorLength() const
{
	return static_cast<float>(sqrt(pow(GetX(), 2) + pow(GetY(), 2) + pow(GetZ(), 2)));
}

Vector Vector::operator+(const Vector& rhs)
{
	return Vector(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

Vector& Vector::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}

	return *this;
}

void Vector::DivideBy(float f)
{
	_x /= f;
	_y /= f;
	_z /= f;
}

