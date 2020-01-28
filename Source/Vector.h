#pragma once
#include "Math.h"
class Vector
{
public:
	// Default constructor
	Vector();
	// Constructor
	Vector(float, float, float);
	// Accessors
	float GetX() const;
	void SetX(const float);
	float GetY() const;
	void SetY(const float);
	float GetZ() const;
	void SetZ(const float);
	// Gets the dot product of two vectors 
	static float DotProduct(Vector, Vector);
	// Gets the cross product of two vectors
	static Vector CrossProduct(Vector, Vector);
	const Vector operator-(const Vector&) const;
	// Normalises the vector
	const Vector GetUnitVector() const;
	float GetVectorLength() const;
	Vector operator+ (const Vector&);
	Vector& operator= (const Vector&);
	void DivideBy(float);
private:
	Vector& Copy(const Vector&);
	float _x;
	float _y;
	float _z;
};


