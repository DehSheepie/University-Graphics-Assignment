#include "Model.h"

Model::Model() 
{

}

Model::~Model()
{

}

const std::vector<Polygon3D>& Model::GetPolyons()
{
	return _polygons;
}

const std::vector<Vertex>& Model::GetVerticies()
{
	return _verticies;
}

const std::vector<Vertex>& Model::GetTransformedVerticies()
{
	return _transformedVerticies;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _verticies.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_verticies.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model:: ApplyTransformToLocalVerticies(const Matrix& transform)
{
	_transformedVerticies.clear();
	for (Vertex i : _verticies)
	{
		_transformedVerticies.push_back(transform * i);
	}
}

void Model::ApplyTransformToTransformedVerticies(const Matrix& transform)
{
	// this isn't as efficient as i'd like it to be. come back to this
	std::vector<Vertex> v;
	for (Vertex i : _transformedVerticies)
	{
		v.push_back(transform * i);
	}
	_transformedVerticies.clear();
	_transformedVerticies = v;
}

void Model::DehomogeniseVerticies()
{
	for (int i = 0; i < static_cast<float>(GetVertexCount()); i++)
	{
		_transformedVerticies[i].Dehomogenise();
	}
}

void Model::CalculateBackfaces(Vertex cameraPos)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		// Gets all the verticies in the polygon
		Vertex polygonPoint0 = _transformedVerticies[_polygons[i].GetIndex(0)];
		Vertex polygonPoint1 = _transformedVerticies[_polygons[i].GetIndex(1)];
		Vertex polygonPoint2 = _transformedVerticies[_polygons[i].GetIndex(2)];

		// Creates vectors by subtracting point 1 and 2 from point 0

		Vector a = polygonPoint0.SubstractVertexToVector(polygonPoint1);
		Vector b = polygonPoint0.SubstractVertexToVector(polygonPoint2);
		Vector normalVector = Vector::CrossProduct(b, a);
		_polygons[i].SetNormalVector(normalVector);

		// Creates a vector from point 0 of the polygon to the camera
		Vector eyeVector = polygonPoint0.SubstractVertexToVector(cameraPos);
		// Checks to see whether the angle between the view point vector and the polygon normal vector is less than 90 degrees
		// If it is less than 90 degrees, the angle is larger and therefore the polygon should not be visible.
		if (Vector::DotProduct(normalVector, eyeVector) < 0)
		{
			_polygons[i].SetMarkedForCulling(true);
		}
		else 
		{
			_polygons[i].SetMarkedForCulling(false);
		}
	}
}

void Model::Sort()
{
	// All of the comments below imply this method is called before the viewing transformation and after the camera transformation
	for (int i = 0 ; i < static_cast<int>(GetPolygonCount()); i++)
	{
		// Gets all the indicies from the polygon class
		int index0 = _polygons[i].GetIndex(0);
		int index1 = _polygons[i].GetIndex(1);
		int index2 = _polygons[i].GetIndex(2);

		// Gets the verticies from _transformedVerticies using the above indicies 
		Vertex vertex0 = _transformedVerticies[index0];
		Vertex vertex1 = _transformedVerticies[index1];
		Vertex vertex2 = _transformedVerticies[index2];

		// Sets the _zDepth value for the polygon to the avaerage of the above Verticies' Z values 
		_polygons[i].SetZDepth(vertex0.GetZ() + vertex1.GetZ() + vertex2.GetZ() / 3);
	}
	// Sorts the polygons in order of average distance from camera
	std::sort(_polygons.begin(), _polygons.end(), [](Polygon3D a, Polygon3D b)
		{
			return a.GetZDepth() > b.GetZDepth(); 
		});
}

void Model::CalculateLightingAmbientVertex(AmbientLight aLight)
{
	for (Vertex& v : _transformedVerticies)
	{
		v.SetColour(COLORREF(RGB(Clamp(aLight.GetRedIntensity() * _kdRed), Clamp(aLight.GetGreenIntensity() * _kdGreen), Clamp(aLight.GetBlueIntensity() * _kdBlue))));
	}
}

void Model::CalculateLightingAmbient(AmbientLight aLight)
{
	for (Polygon3D& p : _polygons)
	{
		p.SetColour(COLORREF(RGB(Clamp(aLight.GetRedIntensity() * _kdRed), Clamp(aLight.GetGreenIntensity() * _kdGreen), Clamp(aLight.GetBlueIntensity() * _kdBlue))));
	}
}

void Model::CalculateLightingPointVertex(std::vector<PointLight> pLights)
{
	float totRed;
	float totGreen;
	float totBlue;

	float tempRed;
	float tempGreen;
	float tempBlue;

	for (Vertex& v : _transformedVerticies)
	{
		totRed = GetRValue(v.GetColour());
		totGreen = GetGValue(v.GetColour());
		totBlue = GetBValue(v.GetColour());
		for (PointLight pLight : pLights)
		{
			tempRed = pLight.GetRedIntensity();
			tempGreen = pLight.GetGreenIntensity();
			tempBlue = pLight.GetBlueIntensity();
			// Multiplies the colours by the diffuse reflectance coefficients for the model
			tempRed *= _kdRed;
			tempGreen *= _kdGreen;
			tempBlue *= _kdBlue;

			Vector LightVector = pLight.GetLightVector(v).GetUnitVector();
			Vector VertexVector = v.GetNormal(); // Normal should already be normalised
			float distanceToLight = pLight.GetLightPosition().SubstractVertexToVector(v).GetVectorLength();
			float dotProd = Vector::DotProduct(LightVector, VertexVector);
			tempRed *= dotProd;
			tempGreen *= dotProd;
			tempBlue *= dotProd;
			float attenuation = 100 * (1 / (pLight.GetAAttenuation() + pLight.GetBAttenuation() * distanceToLight + pLight.GetCAttenuation() * static_cast<float>(pow(distanceToLight, 2))));
			tempRed *= attenuation;
			tempGreen *= attenuation;
			tempBlue *= attenuation;
			totRed += tempRed;
			totGreen += tempGreen;
			totBlue += tempBlue;
		}
		COLORREF VertexColour = RGB(Clamp(totRed), Clamp(totGreen), Clamp(totBlue));
		v.SetColour(VertexColour);
	}
}

int Model::Clamp(float value)
{
	if (value > 255)
	{
		value = 255;
		return static_cast<int>(value);
	}
	else if (value < 0)
	{
		value = 0;
		return static_cast<int>(value);
	}
	return static_cast<int>(value);
}

void Model::CalculateLightingPoint(std::vector<PointLight> pLights)
{
	float totRed;
	float totGreen;
	float totBlue;

	float tempRed;
	float tempGreen;
	float tempBlue;

	for (Polygon3D& p : _polygons)
	{
		totRed = GetRValue(p.GetColour());
		totGreen = GetGValue(p.GetColour());
		totBlue = GetBValue(p.GetColour());
		for (PointLight pLight : pLights)
		{
			tempRed = pLight.GetRedIntensity();
			tempGreen = pLight.GetGreenIntensity();
			tempBlue = pLight.GetBlueIntensity();
			// Multiplies the colours by the diffuse reflectance coefficients for the model
			tempRed *= _kdRed;
			tempGreen *= _kdGreen;
			tempBlue *= _kdBlue;

			Vector normalisedLightVector = pLight.GetLightVector(_transformedVerticies[p.GetIndex(0)]).GetUnitVector();
			Vector normalisedPolygonVector = p.GetNormalVector().GetUnitVector();
			float distanceToLight = pLight.GetLightPosition().SubstractVertexToVector(_transformedVerticies[p.GetIndex(0)]).GetVectorLength();
			float dotProd = Vector::DotProduct(normalisedLightVector, normalisedPolygonVector);
			tempRed *= dotProd;
			tempGreen *= dotProd;
			tempBlue *= dotProd;
			float attenuation = 100 * (1 / (pLight.GetAAttenuation() + pLight.GetBAttenuation() * distanceToLight + pLight.GetCAttenuation() * static_cast<float>(pow(distanceToLight, 2))));
			tempRed *= attenuation;
			tempGreen *= attenuation;
			tempBlue *= attenuation;
			totRed += tempRed;
			totGreen += tempGreen;
			totBlue += tempBlue;
		}
		COLORREF polyColour = RGB(Clamp(totRed), Clamp(totGreen), Clamp(totBlue));
		p.SetColour(polyColour);
	}
}

void Model::CalculateVertexNormals()
{
	for (Vertex& v : _transformedVerticies)
	{
		v.SetNormal(Vector(0, 0, 0));
		v.SetCount(0);
	}
	for (Polygon3D& p : _polygons)
	{
		int index0 = p.GetIndex(0);
		int index1 = p.GetIndex(1);
		int index2 = p.GetIndex(2);
		
		// Takes the transformed verticies using the above indicies and adds the polygon's normal vector them as well as increasing the count
		_transformedVerticies[index0].SetNormal(_transformedVerticies[index0].GetNormal() + p.GetNormalVector());
		_transformedVerticies[index0].IncreaseCount();
		_transformedVerticies[index1].SetNormal(_transformedVerticies[index1].GetNormal() + p.GetNormalVector());
		_transformedVerticies[index1].IncreaseCount();
		_transformedVerticies[index2].SetNormal(_transformedVerticies[index2].GetNormal() + p.GetNormalVector());
		_transformedVerticies[index2].IncreaseCount();
	}
	for (Vertex& v : _transformedVerticies)
	{
		// Divides the normal vector by the number of polygons that contributed by adding their normals to it.
		v.DivideNormalByCount();
		// Sets the normal to the unit vector of the normal (normalises)
		v.SetNormal(v.GetNormal().GetUnitVector());
	}
}

void Model::CalculateLightingDirectionalVertex(std::vector<DirectionalLight> dLights)
{
	float totRed;
	float totGreen;
	float totBlue;

	float tempRed;
	float tempGreen;
	float tempBlue;

	for (Vertex& v : _transformedVerticies)
	{
		totRed = GetRValue(v.GetColour());
		totGreen = GetGValue(v.GetColour());
		totBlue = GetBValue(v.GetColour());
		
		for (DirectionalLight& dLight : dLights)
		{
			tempRed = dLight.GetRedIntensity();
			tempGreen = dLight.GetGreenIntensity();
			tempBlue = dLight.GetBlueIntensity();
			// Multiplies the colours by the diffuse reflectance coefficients for the model
			tempRed *= _kdRed;
			tempGreen *= _kdGreen;
			tempBlue *= _kdBlue;

			Vector LightVector = dLight.GetLightVector();
			Vector VertexVector = v.GetNormal();
			float dotProd = Vector::DotProduct(LightVector, VertexVector);
			tempRed *= dotProd;
			tempGreen *= dotProd;
			tempBlue *= dotProd;
			totRed += tempRed;
			totGreen += tempGreen;
			totBlue += tempBlue;
		}
		COLORREF vertexColour = RGB(Clamp(totRed), Clamp(totGreen), Clamp(totBlue));
		v.SetColour(vertexColour);
	}
}

void Model::CalculateLightingDirectional(std::vector<DirectionalLight> dLights)
{
	float totRed;
	float totGreen;
	float totBlue;

	float tempRed;
	float tempGreen;
	float tempBlue;

	// read on this and put an explaintion (&) for each reference (alias)
	for (Polygon3D& p : _polygons)
	{
		totRed = GetRValue(p.GetColour());
		totGreen = GetGValue(p.GetColour());
		totBlue = GetBValue(p.GetColour());
		for (DirectionalLight& dLight : dLights)
		{
			tempRed = dLight.GetRedIntensity();
			tempGreen = dLight.GetGreenIntensity();
			tempBlue = dLight.GetBlueIntensity();
			// Multiplies the colours by the diffuse reflectance coefficients for the model
			tempRed *= _kdRed;
			tempGreen *= _kdGreen;
			tempBlue *= _kdBlue;

			Vector normalisedLightVector = dLight.GetLightVector().GetUnitVector();
			Vector normalisedPolygonVector = p.GetNormalVector().GetUnitVector();
			float dotProd = Vector::DotProduct(normalisedLightVector, normalisedPolygonVector);
			tempRed *= dotProd;
			tempGreen *= dotProd;
			tempBlue *= dotProd;
			totRed += tempRed;
			totGreen += tempGreen;
			totBlue += tempBlue;
		}
		COLORREF polyColour = RGB(Clamp(totRed),Clamp(totGreen), Clamp(totBlue));
		p.SetColour(polyColour);
	}

}




