#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Math.h"
#include <iostream>
#include "stdlib.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"

class Rasteriser : public Framework
{
public:
	bool Initialise() override;
	void Render(const Bitmap&) override;
	void Update(const Bitmap&) override;
	void GeneratePerspectiveMatrix(float, float);
	void GenerateViewMatrix(float, int, int);
	void DrawWireFrame(const Bitmap&);
	void DrawSolidFlat(const Bitmap&);
	void MyDrawSolidFlat(const Bitmap&);
	void FillPolygonFlat(const Bitmap&, Vertex, Vertex, Vertex, COLORREF);
	void MyDrawSolidFlatGouraud(const Bitmap&);
	void FillPolygonGouraud(const Bitmap&, Vertex, Vertex, Vertex);
	void DrawString(const Bitmap&, LPCTSTR);
private:
	void FillFlatBottomTriangleGouraud(const Bitmap&, Vertex, Vertex, Vertex);
	void FillFlatTopTriangleGouraud(const Bitmap&, Vertex, Vertex, Vertex);
	void FillFlatBottomTriangle(const Bitmap&, Vertex, Vertex, Vertex , COLORREF);
	void FillFlatTopTriangle(const Bitmap&, Vertex, Vertex, Vertex, COLORREF);
	int Clamp(float);
	Model _model;
	Vertex _squareVerticies[4];
	Matrix transform;
	float _x{ 0 };
	float _y{ 0 };
	float _z{ 0 };
	float _timeElapsed{ 0 };
	Camera _camera;
	Matrix _currentModelTrans;
	Matrix _perspectiveTrans;
	Matrix _screenTrans;
	std::vector<DirectionalLight>_directionalLights;
	std::vector<PointLight>_pointLights;
	AmbientLight _ambientLight;
	bool _modelLoaded{ false };
	int _state;
	int _substate;
	int _counter;
	// Determines the speed at which substate and states are progressed through
	int _increment {1};
};