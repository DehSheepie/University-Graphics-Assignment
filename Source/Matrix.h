#pragma once
#include "Vertex.h"
#include <initializer_list>

// Class for a 4 x 4 matrix object.
const int ROWS = 4;
const int COLS = 4;
class Matrix
{
public:
	// Default constructor
	Matrix();
	// Destructor
	~Matrix();
	// Constructor that initialises all elements.
	Matrix(std::initializer_list<float>);
	// Copy constructor
	Matrix(const Matrix&);
	// Retrieve value in matrix at specified row and column
	float GetM(const int, const int) const;
	// Set value in matrix at specified row and column
	void SetM(const int, const int, const float);
	// Assignment operator
	Matrix& operator= (const Matrix&);
	// Test for two matrices being equivalent;
	bool operator==(const Matrix&) const;
	// Multiply two matrices together
	const Matrix operator*(const Matrix&) const;
	// Multiply a matrix by a vertex, returning a vertex
	const Vertex operator*(const Vertex&) const;
private:
	void Copy(const Matrix&);
	float _m[ROWS][COLS];
};

