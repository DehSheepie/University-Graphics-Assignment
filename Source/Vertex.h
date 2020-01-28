#pragma once
#include "Vector.h"
#include "windows.h"
class Vertex
{
public:
	Vertex();
	Vertex(float, float, float);
	Vertex(const Vertex&);

	// Accessors
	float GetX() const;
	void SetX(const float);
	float GetY() const;
	void SetY(const float);
	void SetZ(const float);
	float GetZ() const;
	float GetW() const;
	void SetW(const float);
	void Dehomogenise();
	void SetNormal(const Vector);
	Vector GetNormal() const;
	void SetColour(const COLORREF);
	COLORREF GetColour() const;
	void SetCount(const int);
	int GetCount() const;
	void IncreaseCount();
	void DivideNormalByCount();

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	const Vector SubstractVertexToVector (const Vertex& ) const;

private:
	Vertex& Copy(const Vertex&);
	float _x;
	float _y;
	float _z;
	float _w;
	Vector _normal;
	COLORREF _colour;
	// Number of times a Vertex is used in a polygon
	int _count;
};