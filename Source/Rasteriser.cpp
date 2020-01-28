#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise() 
{
	_modelLoaded = false;
	if (!MD2Loader::LoadModel("marvin2.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	else
	{
		_modelLoaded = true;
	}
	_ambientLight = AmbientLight(10);
	_camera.SetPosition(Vertex(0, 0, -40));
	DirectionalLight dLight1(100, Vector(0, 0, 10));
	_directionalLights.push_back(dLight1);
	PointLight pLight(55, Vertex(0, 0, 60), 0 , 0.3f, 0.0f);
	_pointLights.push_back(pLight);
	return true;
	_state = 0;
	_substate = 0;
	_counter = 0;
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	if (_modelLoaded)
	{
		bitmap.Clear(RGB(0, 0, 0));
		HDC hdc = bitmap.GetDC();
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(255, 0, 0));
		bitmap.Clear(RGB(0, 0, 0));
		switch (_state)
		{
		case 0:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in model
			DrawWireFrame(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"Wireframe + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"Wireframe + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"Wireframe + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"Wireframe + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"Wireframe + Translation");
				break;
			case 5:
				DrawString(bitmap, L"Wireframe + Camera Movement");
				break;
			}
			break;
		case 1:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in model

			DrawWireFrame(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"Wireframe backface culling + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"Wireframe backface culling + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"Wireframe backface culling + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"Wireframe backface culling + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"Wireframe backface culling + Translation");
				break;
			case 5:
				DrawString(bitmap, L"Wireframe backface culling + Camera Movement");
				break;
			}
			break;
		case 2:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in the model
			DrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"Solid Flat WinGDI + Ambient Light + Camera Movement");
				break;
			}
			break;
		case 3:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Calculates directional lighting
			_model.CalculateLightingDirectional(_directionalLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in the model
			DrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"Solid Flat WinGDI + Directional Light + Camera Movement");
				break;
			}
			break;
		case 4:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Calculates point lighting
			_model.CalculateLightingPoint(_pointLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in the model
			DrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"Solid Flat WinGDI + Point Light + Camera Movement");
				break;
			}
			break;
		case 5:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat + Ambient Light + Camera Movement");
				break;
			}
			break;
		case 6:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Calculates directional lighting
			_model.CalculateLightingDirectional(_directionalLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat + Directional Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat + Directional Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat + Directional Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat + Directional Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat + Directional Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat + Directional Light + Camera Movement");
				break;
			}
			break;
		case 7:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Calculates ambient lighting
			_model.CalculateLightingAmbient(_ambientLight);
			// Calculates point lighting
			_model.CalculateLightingPoint(_pointLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlat(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat + Point Light + X rotation");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat + Point Light + Y rotation");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat + Point Light + Z rotaton");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat + Point Light + Scaling");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat + Point Light + Translation");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat + Point Light + Camera Movement");
				break;
			}
			break;
		case 8:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Generates normal for vertices
			_model.CalculateVertexNormals();
			// Calculates ambient lighting for verticies
			_model.CalculateLightingAmbientVertex(_ambientLight);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlatGouraud(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + X rotation (errors)");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + Y rotation (errors)");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + Z rotaton (errors)");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + Scaling (errors)");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + Translation (errors)");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat Gouraud + Ambient Light + Camera Movement (errors)");
				break;
			}
			break;
		case 9:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Generates normal for verticies
			_model.CalculateVertexNormals();
			// Calculates ambient lighting for verticies
			_model.CalculateLightingAmbientVertex(_ambientLight);
			// Calculates directional lighting for verticies
			_model.CalculateLightingDirectionalVertex(_directionalLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlatGouraud(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + X rotation (errors)");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + Y rotation (errors)");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + Z rotaton (errors)");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + Scaling (errors)");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + Translation (errors)");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat Gouraud + Directional Light + Camera Movement (errors)");
				break;
			}
			break;
		case 10:
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Generates normal for vertices
			_model.CalculateVertexNormals();
			// Calculates ambient lighting for verticies
			_model.CalculateLightingAmbientVertex(_ambientLight);
			// Calculates point lighting for verticies
			_model.CalculateLightingPointVertex(_pointLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws polygons using my polygon function
			MyDrawSolidFlatGouraud(bitmap);
			switch (_substate)
			{
			case 0:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + X rotation (errors)");
				break;
			case 1:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + Y rotation (errors)");
				break;
			case 2:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + Z rotaton (errors)");
				break;
			case 3:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + Scaling (errors)");
				break;
			case 4:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + Translation (errors)");
				break;
			case 5:
				DrawString(bitmap, L"My Solid Flat Gouraud + Point Light + Camera Movement (errors)");
				break;
			}
			break;
		//default:
		case 11:
			// Here is my most recent work. I couldn't manage to get Gouraud working.
			// Transforms the model relative to space
			_model.ApplyTransformToLocalVerticies(transform);
			// Calculates which polygons should be drawn and which shouldn't
			_model.CalculateBackfaces(_camera.GetPosition());
			// Generates normal for verticies
			_model.CalculateVertexNormals();
			// Calculates ambient lighting
			//_model.CalculateLightingAmbient(_ambientLight);
			// Calculates ambient lighting for verticies
			_model.CalculateLightingAmbientVertex(_ambientLight);
			// Calculates directional lighting
			//_model.CalculateLightingDirectional(_directionalLights);
			// Calculates directional lighting for verticies
			_model.CalculateLightingDirectionalVertex(_directionalLights);
			// Calculates point lighting
			//_model.CalculateLightingPoint(_pointLights);
			// Calculates point lighting for verticies
			// _model.CalculateLightingPointVertex(_pointLights);
			// Transforms the model relative to the camera
			_model.ApplyTransformToTransformedVerticies(_camera.GetCameraMatrix());
			//Sorts the polygons in the model in order of distance from the camera
			_model.Sort();
			// Transforms the model relative to perspective 
			_model.ApplyTransformToTransformedVerticies(_perspectiveTrans);
			// _w may not be equal to 1 after the above matrix multiplications
			// dehomogenise will divide the x y and z values in the verticies in the list by _w which should correct the values and set _w to 1
			_model.DehomogeniseVerticies();
			// Transforms the verticies relative to the screen
			_model.ApplyTransformToTransformedVerticies(_screenTrans);
			// Draws the polygons in model
			// DrawWireFrame(bitmap);
			// Draws the polygons in the model
			// DrawSolidFlat(bitmap);
			// Draws polygons using my polygon function
			//MyDrawSolidFlat(bitmap);
			// Draws polygons using Gouraud
			MyDrawSolidFlatGouraud(bitmap);
			break;
		}
	}
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	_counter += _increment;
	if (_modelLoaded) 
	{
		_x+= 0.1f;
		_y+= 0.5f;

		// Converts the _x value to radians
		float xRadians = static_cast<float>(_x * 3.14159265359f / 180.0f);
		// Convert the _y value to radians
		float yRadians = static_cast<float>(_y * 3.14159265359f / 180.0f);

		Matrix rotationZ{
		static_cast<float>(cos(yRadians)), static_cast<float>(-sin(yRadians)), 0, 0,
		static_cast<float>(sin(yRadians)), static_cast<float>(cos(yRadians)), 0, 0,
		0, 0, 1 ,0,
		0, 0, 0, 1
		};

		Matrix rotationX{
				1, 0, 0, 0,
				0, cos(yRadians), -sin(yRadians), 0,
				0, sin(yRadians), cos(yRadians), 0,
				0, 0, 0 ,1
		};

		Matrix rotationY{
			static_cast<float>(cos(yRadians)), 0,  static_cast<float>(sin(yRadians)), 0,
			0,											   1,						0                        , 0,
			static_cast<float>(-sin(yRadians)), 0, static_cast<float>((cos(yRadians))), 0,
			0,												0,						0,							 1
		};

		// Reduces the number of frames shown depending on the state (number of features included)
		if (_counter > 150 - _state * 10)
		{
			if (_substate > 4) 
			{
				if (_state < 10)
				{
					// Resets the substate if it gets to the last state and moves onto the next state
					_state++;
					_substate = 0;
					_camera.SetPosition(Vertex(0, 0, -40));
					_camera.SetXRotation(0);
					_camera.SetYRotation(0);
					_camera.SetZRotation(0);
				}
				else
				{
					_substate = 0;
					_state = 0;
					_camera.SetPosition(Vertex(0, 0, -40));
					_camera.SetXRotation(0);
					_camera.SetYRotation(0);
					_camera.SetZRotation(0);
				}
			}
			else 
			{
				// Increases the substate provided it isn't the last substate
				_counter = 0;
				_substate++;
				_x = 0;
				_y = 0;
			}

		}
		// Translate the model
		float transValue = static_cast<float>(sin(_x)) * 20;

		Matrix translation{
			1,0,0,-transValue/3,
			0,1,0,transValue/2,
			0,0,1,transValue/3,
			0,0,0, 1
		};

		// Scale the model 
		float scaleValue = 1 + sin(_x) * 1;

		// Scale the model by +2 and 0
		Matrix scaling{
			scaleValue/2,0,0,0,
			0,scaleValue/2,0,0,
			0,0,scaleValue/2,0,
			0,0,0,1
		};

		switch (_substate)
		{
		case 0:
			transform = rotationX;
			break;
		case 1:
			transform = rotationY;
			break;
		case 2:
			transform = rotationZ;
			break;
		case 3:
			transform = scaling;
			break;
		case 4:
			transform = translation;
			break;
		case 5:
			// zoom camera inwards and then outwards
			float cameramove = (static_cast<float>(sin((_x/2))) * 100.0f) - 150.0f;
			_camera.SetPosition(Vertex(0, 0, cameramove));

			// camera move left and right
			float cameraSwivel = (static_cast<float>(sin(_x * 1.5f)) * 10);
			_camera.SetYRotation(cameraSwivel);
		}

		// aspect ratio
		float a = static_cast<float>(bitmap.GetWidth()) / static_cast<float>(bitmap.GetHeight());
		GeneratePerspectiveMatrix(1.0f, a);
		GenerateViewMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight());
}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveTrans = Matrix{
		d / aspectRatio,	0,			0,			0,
		0,                  d,			0,			0,
		0,                  0,			d,			0,
		0,                  0,			1,			0
	} ;
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_screenTrans = Matrix
	{
		static_cast<float>(width) / 2,								0,							0,			 static_cast<float>(width) / 2,
		0,							  static_cast<float>(-height) / 2,							0,			static_cast<float>(height) / 2,
		0,															0,							d / 2,								 d / 2,
		0,															0,							0,									   	1
	};
}

void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	// Creates a copy of _model.GetTransformedVerticies() as to make the code easier to read further down
	// This isn't the most effcient method but it makes the code more managable
	std::vector<Vertex>vert = _model.GetTransformedVerticies();
	// Iterates through the polygons in the model
	for (Polygon3D p : _model.GetPolyons())
	{	
		// Checks whether the polygon should be drawn
		if (p.GetMarkedForCulling() != true || _state == 0)
		{
			// Moves to the first point in the polygon before drawing a line to every point after that looping back to the first point
			MoveToEx(bitmap.GetDC(), static_cast<int>(vert[p.GetIndex(0)].GetX()), static_cast<int>(vert[p.GetIndex(0)].GetY()), NULL);
			LineTo(bitmap.GetDC(), static_cast<int>(vert[p.GetIndex(1)].GetX()), static_cast<int>(vert[p.GetIndex(1)].GetY()));
			LineTo(bitmap.GetDC(), static_cast<int>(vert[p.GetIndex(2)].GetX()), static_cast<int>(vert[p.GetIndex(2)].GetY()));
			LineTo(bitmap.GetDC(), static_cast<int>(vert[p.GetIndex(0)].GetX()), static_cast<int>(vert[p.GetIndex(0)].GetY()));
		}
	}
}

void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	std::vector<Vertex>vert = _model.GetTransformedVerticies();
	for (Polygon3D p : _model.GetPolyons())
	{
		// Only runs the below code if the polygon is not marked for backface culling and therefore should not be drawn
		if (p.GetMarkedForCulling() != true)
		{
			POINT points[3];
			points[0] = { static_cast<long>(vert[p.GetIndex(0)].GetX()), static_cast<long>(vert[p.GetIndex(0)].GetY()) };
			points[1] = { static_cast<long>(vert[p.GetIndex(1)].GetX()), static_cast<long>(vert[p.GetIndex(1)].GetY()) };
			points[2] = { static_cast<long>(vert[p.GetIndex(2)].GetX()), static_cast<long>(vert[p.GetIndex(2)].GetY()) };

		//	SelectObject(bitmap.GetDC(), GetStockObject(DC_PEN));
			HPEN hPen = CreatePen(PS_SOLID, 1, p.GetColour());
			HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);
			// int r = static_cast<int>(sin(sqrt(_y)) * 15) * static_cast<int>(sin(sqrt(_y)) * 17);
			// int a = static_cast<int>(sin(sqrt(_x)) * 15)* static_cast<int>(sin(sqrt(_x)) * 17);
			// int b = static_cast<int>(sin(sqrt(_y*_x)) * 15)* static_cast<int>(sin(sqrt(_y*_x)) * 17);
			HBRUSH hBrush = CreateSolidBrush(p.GetColour());
			HGDIOBJ oldBrush = SelectObject(bitmap.GetDC(), hBrush);
			Polygon(bitmap.GetDC(), points, 3);
			SelectObject(bitmap.GetDC(), oldPen);
			SelectObject(bitmap.GetDC(), oldBrush);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
	}
}

void Rasteriser::MyDrawSolidFlatGouraud(const Bitmap& bitmap)
{
	std::vector<Vertex>vert = _model.GetTransformedVerticies();
	for (Polygon3D p : _model.GetPolyons())
	{
		if (p.GetMarkedForCulling() != true)
		{
			Vertex v0 = vert[p.GetIndex(0)];
			Vertex v1 = vert[p.GetIndex(1)];
			Vertex v2 = vert[p.GetIndex(2)];
			FillPolygonGouraud(bitmap, v0, v1, v2);
		}
	}
}

void Rasteriser::MyDrawSolidFlat(const Bitmap& bitmap)
{
	std::vector<Vertex>vert = _model.GetTransformedVerticies();
	for (Polygon3D p : _model.GetPolyons())
	{
		if (p.GetMarkedForCulling() != true) 
		{
			Vertex v0 = vert[p.GetIndex(0)];
			Vertex v1 = vert[p.GetIndex(1)];
			Vertex v2 = vert[p.GetIndex(2)];
			FillPolygonFlat(bitmap, v0, v1, v2, p.GetColour());
		}
	}
}

void Rasteriser::FillPolygonGouraud(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2)
{
	Vertex tempV;
	// Orders the verticies in descending order of Y
	if (v1.GetY() > v0.GetY())
	{
		tempV = v0;
		v0 = v1;
		v1 = tempV;
	}
	if (v2.GetY() > v1.GetY())
	{
		tempV = v1;
		v1 = v2;
		v2 = tempV;
	}
	if (v1.GetY() > v0.GetY())
	{
		tempV = v0;
		v0 = v1;
		v1 = tempV;
	}

	// Checks whether the polygon is a natural flat-bottom triangle
	if (v1.GetY() == v2.GetY())
	{
		// Sorts verticies by X
		if (v2.GetX() > v1.GetX())
		{
			FillFlatBottomTriangleGouraud(bitmap, v0, v1, v2);
		}
		else
		{
			FillFlatBottomTriangleGouraud(bitmap, v0, v2, v1);
		}
	}
	// Checks whether the polygon is a natural flat-top triangle
	else if (v0.GetY() == v1.GetY())
	{
		if (v1.GetX() > v0.GetX())
		{
			FillFlatTopTriangleGouraud(bitmap, v0, v1, v2);
		}
		else
		{
			FillFlatTopTriangleGouraud(bitmap, v1, v0, v2);
		}
	}
	// General case polygon - Splits the triangle into a flat-top and a flat- bottom triangle
	else
	{
		// The y value of the triangle should be v1.GetY() (easy)
		float alpha = (v1.GetY() - v0.GetY()) / (v2.GetY() - v0.GetY()); // Gets the ratio of distance in Y in v0-v1 compared with v0-v2
		Vertex vTemp = Vertex(v0.GetX() + (alpha * (v2.GetX() - v0.GetX())), v1.GetY(), 0.0f); // Gets the X distance between v2 and v0 and multiplies it by alpha. Sets the Y value to v1.GetY()
		// z is set to 0 because it isn't important at this stage

		float vTempColours[3];
		vTempColours[0] = GetRValue(v1.GetColour()) + alpha * (GetRValue(v2.GetColour()) - GetRValue(v0.GetColour()));
		vTempColours[1] = GetGValue(v1.GetColour()) + alpha * (GetGValue(v2.GetColour()) - GetGValue(v0.GetColour()));
		vTempColours[2] = GetBValue(v1.GetColour()) + alpha * (GetBValue(v2.GetColour()) - GetBValue(v0.GetColour()));
		
		// Sets the colour of the temp vertex
		vTemp.SetColour(COLORREF(RGB(Clamp(vTempColours[0]), Clamp(vTempColours[1]), Clamp(vTempColours[2]))));

		// Checks whether left leaning or right leaning triangle
		if (v1.GetX() > vTemp.GetX())
		{
			FillFlatBottomTriangleGouraud(bitmap, v0, vTemp, v1);
			FillFlatTopTriangleGouraud(bitmap, vTemp, v1, v2);
		}
		else
		{
			FillFlatBottomTriangleGouraud(bitmap, v0, v1, vTemp);
			FillFlatTopTriangleGouraud(bitmap, v1, vTemp, v2);
		}
	}
}

void Rasteriser::FillPolygonFlat(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2, COLORREF c)
{
	Vertex tempV;
	// Orders the verticies in descending order of Y
	if (v1.GetY() > v0.GetY())
	{
		tempV = v0;
		v0 = v1;
		v1 = tempV;
	}
	if (v2.GetY() > v1.GetY())
	{
		tempV = v1;
		v1 = v2;
		v2 = tempV;
	}
	if (v1.GetY() > v0.GetY())
	{
		tempV = v0;
		v0 = v1;
		v1 = tempV;
	}

	// Checks whether the polygon is a natural flat-bottom triangle
	if (v1.GetY() == v2.GetY())
	{
		// Sorts verticies by X
		if (v2.GetX() > v1.GetX())
		{
			FillFlatBottomTriangle(bitmap, v0, v1, v2, c);
		}
		else
		{
			FillFlatBottomTriangle(bitmap, v0, v2, v1, c);
		}
	}
	// Checks whether the polygon is a natural flat-top triangle
	else if (v0.GetY() == v1.GetY())
	{
		if (v1.GetX() > v0.GetX())
		{
			FillFlatTopTriangle(bitmap, v0, v1, v2, c);
		}
		else
		{
			FillFlatTopTriangle(bitmap, v1, v0, v2, c);
		}
	}
	// General case polygon - Splits the triangle into a flat-top and a flat- bottom triangle
	else 
	{
		// The y value of the triangle should be v1.GetY() (easy)
		float alpha = (v1.GetY() - v0.GetY()) / (v2.GetY() - v0.GetY()); // Gets the ratio of distance in Y in v0-v1 compared with v0-v2
		Vertex vTemp = Vertex(v0.GetX() + (alpha * (v2.GetX() - v0.GetX())), v1.GetY(), 0.0f); // Gets the X distance between v2 and v0 and multiplies it by alpha. Sets the Y value to v1.GetY()
		// z is set to 0 because it isn't important at this stage

		// Checks whether left leaning or right leaning triangle
		if (v1.GetX() > vTemp.GetX())
		{
			FillFlatBottomTriangle(bitmap, v0, vTemp, v1, c);
			FillFlatTopTriangle(bitmap, vTemp, v1, v2, c);
		}
		else 
		{
			FillFlatBottomTriangle(bitmap, v0, v1, vTemp, c);
			FillFlatTopTriangle(bitmap, v1, vTemp, v2, c);
		}
	}
}

int Clamp(float value)
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

void DrawLineGouraud(const Bitmap& bitmap, float x1, float x2, float y, float colourA[3], float colourB[3])
{
	for (int i = static_cast<int>(x1); i <= x2; i++)
	{
		float t = (i - x1) / (x2 - x1);

		float r = (1 - t) * colourA[0] + t * colourB[0];
		float g = (1 - t) * colourA[1] + t * colourB[1];
		float b = (1 - t) * colourA[2] + t * colourB[2];

		COLORREF currentColour = COLORREF(RGB(Clamp(r), Clamp(g), Clamp(b)));

		SetPixel(bitmap.GetDC(), i, static_cast<int>(y), static_cast<int>(currentColour));
	}
}

void DrawLine(const Bitmap& b ,float x1, float x2, float y, COLORREF c)
{
	for (int i = static_cast<int>(x1); i <= x2; i++)
	{
		SetPixel(b.GetDC(), i, static_cast<int>(y), static_cast<int>(c));
	}
}

void Rasteriser::FillFlatBottomTriangleGouraud(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2)
{
	// Calculates the slopes of the trinangles in screen space
	float invSlopeA = (v1.GetX() - v0.GetX()) / (v1.GetY() - v0.GetY()); // Is actually calculating the inverse slope (hence invSlope
	float invSlopeB = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY()); // Usually slope is calculated rise over run, but this is run over rise
	// This is done to avoid getting infinate value for the slope (there can be vertical lines but not horizontal ones for left and right triangle edges) 

	// Current x positions and colours
	float curxA = v0.GetX();
	float curxB = v0.GetX() + 0.5f;
	float curColourA[3] = { static_cast<float>(GetRValue(v0.GetColour())), static_cast<float>(GetGValue(v0.GetColour())), static_cast<float>(GetBValue(v0.GetColour())) };
	float curColourB[3] = { static_cast<float>(GetRValue(v0.GetColour())), static_cast<float>(GetGValue(v0.GetColour())), static_cast<float>(GetBValue(v0.GetColour())) };

	// y distance between point v0 and v1 in the y axis (difference in y)
	float yDiffA = v1.GetY() - v0.GetY();
	float colourSlopeA[3];
	// colour slope between point v0 and point v1

	colourSlopeA[0] = (static_cast<float>(GetRValue(v1.GetColour())) - static_cast<float>(GetRValue(v0.GetColour()))) / yDiffA;
	colourSlopeA[1] = (static_cast<float>(GetGValue(v1.GetColour())) - static_cast<float>(GetGValue(v0.GetColour()))) / yDiffA;
	colourSlopeA[2] = (static_cast<float>(GetBValue(v1.GetColour())) - static_cast<float>(GetBValue(v0.GetColour()))) / yDiffA;

	// y distance between point v0 and v2 in the y axis (difference in y)
	float yDiffB = v2.GetY() - v0.GetY();
	float colourSlopeB[3];
	// colour slope between point v0 and v2
	colourSlopeB[0] = (static_cast<float>(GetRValue(v2.GetColour())) - static_cast<float>(GetRValue(v0.GetColour()))) / yDiffB;
	colourSlopeB[1] = (static_cast<float>(GetGValue(v2.GetColour())) - static_cast<float>(GetGValue(v0.GetColour()))) / yDiffB;
	colourSlopeB[2] = (static_cast<float>(GetBValue(v2.GetColour())) - static_cast<float>(GetBValue(v0.GetColour()))) / yDiffB;

	for (float scanLineY = v0.GetY(); scanLineY >= v1.GetY(); scanLineY--) // Checks that scan line isn't lower than the bottom edge of the triangle and iterates through if it isn't
	{
		DrawLineGouraud(bitmap, curxA, curxB, scanLineY, curColourA, curColourB);
		curxA -= invSlopeA;
		curxB -= invSlopeB;
		
		curColourA[0] -= colourSlopeA[0];
		curColourA[1] -= colourSlopeA[1];
		curColourA[2] -= colourSlopeA[2];

		curColourB[0] -= colourSlopeB[0];
		curColourB[1] -= colourSlopeB[1];
		curColourB[2] -= colourSlopeB[2];
	}
}

void Rasteriser::FillFlatBottomTriangle(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2, COLORREF c)
{
	// FillFlatBottomTriangle(bitmap, v0(v0), vTemp(v1), v1(v2), c);
	// Calculates the slopes of the trinangles in screen space
	float invSlopeA = (v1.GetX() - v0.GetX()) / (v1.GetY() - v0.GetY()); // Is actually calculating the inverse slope (hence invSlope
	float invSlopeB = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY()); // Usually slope is calculated rise over run, but this is run over rise
	// This is done to avoid getting infinate value for the slope (there can be vertical lines but not horizontal ones for left and right triangle edges) 

	float curxA = v0.GetX();
	float curxB = v0.GetX() + 0.5f;

	for (float scanLineY = v0.GetY(); scanLineY >= v1.GetY(); scanLineY--) // Checks that scan line isn't lower than the bottom edge of the triangle and iterates through if it isn't
	{
		DrawLine(bitmap, curxA, curxB, scanLineY, c);
		curxA -= invSlopeA;
		curxB -= invSlopeB;
	}
}

void Rasteriser::FillFlatTopTriangle(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2, COLORREF c)
{
	// FillFlatTopTriangle(bitmap, vTemp(v0), v1(v1), v2(v2), c);
	// Calculates the slopes of the trinangles in screen space
	float invSlopeA = (v0.GetX() - v2.GetX()) / (v0.GetY() - v2.GetY()); // Gets the two edges either side of point v2 (the lowest point of the triangle
	float invSlopeB = (v1.GetX() - v2.GetX()) / (v1.GetY() - v2.GetY()); 
	
	float curxA = v2.GetX();
	float curxB = v2.GetX() + 0.5f;

	for (float scanLineY = v2.GetY(); scanLineY <= v0.GetY(); scanLineY++) // Checks that the scan line isn't higher than the top edge of the triangle and iterates through if it isn't
	{
		DrawLine(bitmap, curxA, curxB, scanLineY, c);
		curxA += invSlopeA;
		curxB += invSlopeB;
	}
}

int Rasteriser::Clamp(float value)
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

void Rasteriser::FillFlatTopTriangleGouraud(const Bitmap& bitmap, Vertex v0, Vertex v1, Vertex v2)
{
	// FillFlatTopTriangle(bitmap, vTemp(v0), v1(v1), v2(v2), c);
// Calculates the slopes of the trinangles in screen space
	float invSlopeA = (v0.GetX() - v2.GetX()) / (v0.GetY() - v2.GetY()); // Gets the two edges either side of point v2 (the lowest point of the triangle)
	float invSlopeB = (v1.GetX() - v2.GetX()) / (v1.GetY() - v2.GetY());

	// Current colours and x values
	float curxA = v2.GetX();
	float curxB = v2.GetX() + 0.5f;
	float curColourA[3] = { static_cast<float>(GetRValue(v2.GetColour())), static_cast<float>(GetGValue(v2.GetColour())), static_cast<float>(GetBValue(v2.GetColour())) };
	float curColourB[3] = { static_cast<float>(GetRValue(v2.GetColour())), static_cast<float>(GetGValue(v2.GetColour())), static_cast<float>(GetBValue(v2.GetColour())) };

	// y distance between point v2 and v0
	float yDiffA = v2.GetY() - v0.GetY();
	float colourSlopeA[3];
	colourSlopeA[0] = (static_cast<float>(GetRValue(v2.GetColour())) - static_cast<float>(GetRValue(v0.GetColour()))) / yDiffA;
	colourSlopeA[1] = (static_cast<float>(GetGValue(v2.GetColour())) - static_cast<float>(GetGValue(v0.GetColour()))) / yDiffA;
	colourSlopeA[2] = (static_cast<float>(GetBValue(v2.GetColour())) - static_cast<float>(GetBValue(v0.GetColour()))) / yDiffA;

	// y distance between point v2 and v1
	float yDiffB = v2.GetY() - v1.GetY();
	float colourSlopeB[3];
	colourSlopeB[0] = (static_cast<float>((GetRValue(v2.GetColour())) - static_cast<float>(GetRValue(v1.GetColour()))) / yDiffB);
	colourSlopeB[1] = (static_cast<float>((GetGValue(v2.GetColour())) - static_cast<float>(GetGValue(v1.GetColour()))) / yDiffB);
	colourSlopeB[2] = (static_cast<float>((GetBValue(v2.GetColour())) - static_cast<float>(GetBValue(v1.GetColour()))) / yDiffB);

	for (float scanLineY = v2.GetY(); scanLineY <= v0.GetY(); scanLineY++) // Checks that the scan line isn't higher than the top edge of the triangle and iterates through if it isn't
	{
		DrawLineGouraud(bitmap, curxA, curxB, scanLineY, curColourA, curColourB);
		curxA += invSlopeA;
		curxB += invSlopeB;

		curColourA[0] += colourSlopeA[0];
		curColourA[1] += colourSlopeA[1];
		curColourA[2] += colourSlopeA[2];

		curColourB[0] += colourSlopeB[0];
		curColourB[1] += colourSlopeB[1];
		curColourB[2] += colourSlopeB[2];
	}
}

void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
// Output a string to the bitmap at co-ordinates 10, 10
// 
// Parameters: bitmap - A reference to the bitmap object
//             text   - A pointer to a string of wide characters
//
// For example, you might call this using:
//
//   DrawString(bitmap, L"Text to display");
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}
