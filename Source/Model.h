#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include <vector>
#include <algorithm>
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "Light.h"

class Model
{
public: 
	Model();
	~Model();

// Acessors
	const std::vector<Polygon3D>& GetPolyons();
	const std::vector<Vertex>& GetVerticies();
	const std::vector<Vertex>& GetTransformedVerticies();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float, float, float);
	void AddPolygon(int, int, int);
	void ApplyTransformToLocalVerticies(const Matrix&);
	void ApplyTransformToTransformedVerticies(const Matrix&);
	// Iterates through all the verticies, calling their 
	void DehomogeniseVerticies();
	// Calculates whether the polygon should be renedered and sets _markedForCulling accordingly
	void CalculateBackfaces(Vertex);
	// Sorts the polygons in relation to distance from the camera
	void Sort();
	// Calculates Directional Lighting for each point
	void CalculateLightingDirectional(std::vector<DirectionalLight>);
	// Calculates Ambient Lighting
	void CalculateLightingAmbient(AmbientLight);
	// Calculates Point Lighting
	void CalculateLightingPoint(std::vector<PointLight>);
	// Calculates normal vectors of verticies
	void CalculateVertexNormals();
	// Calculates the directional lighting for each vertex
	void CalculateLightingDirectionalVertex(std::vector<DirectionalLight>);
	// Calculates the ambient lighting for each vertex
	void CalculateLightingAmbientVertex(AmbientLight);
	// Calculates the point lighting for each vertex
	void CalculateLightingPointVertex(std::vector<PointLight>);

private:
	int Clamp(float);
	// Reflection Coefficients
	float _kdRed { 1.0f };
	float _kdGreen { 0.2f };
	float _kdBlue { 0.2f };

	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _verticies;
	std::vector<Vertex> _transformedVerticies;
};