#include "Vertex.h"

Vertex::Vertex()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_w = 1;
	_colour = COLORREF(RGB(0, 0, 0));
	_count = 0;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
	_colour = COLORREF(RGB(0, 0, 0));
	_count = 0;
}

Vertex::Vertex(const Vertex& other)
{
	Copy(other);
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetZ() const
{
	return _z;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const  Vector Vertex::SubstractVertexToVector(const Vertex& other) const
{
	float x = this->GetX() - other.GetX();
	float y = this->GetY() - other.GetY();
	float z = this->GetZ() - other.GetZ();
	return Vector(x, y, z);
}

Vertex& Vertex::Copy(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		this->SetX(rhs.GetX());
		this->SetY(rhs.GetY());
		this->SetZ(rhs.GetZ());
		this->SetW(rhs.GetW());
		this->SetCount(rhs.GetCount());
		this->SetColour(rhs.GetColour());
		this->SetNormal(rhs.GetNormal());
	}
	return *this;
}

void Vertex::Dehomogenise()
{
	_x /= _w;
	_y /= _w;
	_z /= _w;
	_w /= _w;
}

void Vertex::SetNormal(const Vector v)
{
	_normal = v;
}

Vector Vertex::GetNormal() const
{
	return _normal;
}

void Vertex::SetColour(const COLORREF c)
{
	_colour = c;
}

COLORREF Vertex::GetColour() const
{
	return _colour;
}

void Vertex::SetCount(const int i)
{
	_count = i;
}

int Vertex::GetCount() const
{
	return _count;
}

void Vertex::IncreaseCount()
{
	_count++;
}

void Vertex::DivideNormalByCount()
{
	_normal.DivideBy(static_cast<float>(_count));
}
