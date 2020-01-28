#include "Polygon3D.h"

Polygon3D::Polygon3D() : _indicies{ 0 }
{
	_markedForCulling = false;
	_colour = RGB(255, 255, 255);
}

Polygon3D::Polygon3D(int x, int y, int z) : _indicies{ 0 }
{
	_indicies[0] = x;
	_indicies[1] = y;
	_indicies[2] = z;
	_markedForCulling = false;
	_colour = RGB(255, 255, 255);
}

Polygon3D::~Polygon3D()
{

}

int Polygon3D::GetIndex(const int x) const
{
	return _indicies[x];
}

bool Polygon3D::GetMarkedForCulling() const
{
	return _markedForCulling;
}

void Polygon3D::SetMarkedForCulling(const bool b)
{
	_markedForCulling = b;
}

void Polygon3D::SetZDepth(const float depth)
{
	_zDepth = depth;
}

float Polygon3D::GetZDepth() const
{
	return _zDepth;
}

Vector Polygon3D::GetNormalVector() const
{
	return _normalVector;
}

void Polygon3D::SetNormalVector(const Vector nVector)
{
	_normalVector = nVector;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(const COLORREF newColour)
{
	_colour = newColour;
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

Polygon3D& Polygon3D::Copy (const Polygon3D& rhs)
{
	if (this != &rhs) 
	{
		_indicies[0] = rhs.GetIndex(0);
		_indicies[1] = rhs.GetIndex(1);
		_indicies[2] = rhs.GetIndex(2);
		_markedForCulling = rhs._markedForCulling;
		_colour = rhs.GetColour();
		_normalVector = rhs.GetNormalVector();
	}
	return *this;
}