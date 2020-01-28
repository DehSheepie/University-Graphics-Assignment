#pragma once
#include "Vector.h"
#include <windows.h>

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int, int, int);
	~Polygon3D();
	int GetIndex(const int) const;
	bool GetMarkedForCulling() const;
	void SetMarkedForCulling(const bool);
	void SetZDepth(const float);
	float GetZDepth() const;
	Vector GetNormalVector() const;
	void SetNormalVector(const Vector);
	COLORREF GetColour() const;
	void SetColour(const COLORREF);
	
	Polygon3D& operator= (const Polygon3D&);
private:	
	Polygon3D& Copy(const Polygon3D&);
	COLORREF _colour;
	int _indicies[3];
	Vector _normalVector;
	bool _markedForCulling;	// Mwahahaha!
	float _zDepth;
};

