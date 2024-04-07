#ifndef UNICODE
#define UNICODE
#endif 

#include "WindowMain.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ObjLoader* loader = new ObjLoader();

	modelCoordSystem = new CoordSystem({ 0.0f,0.0f,0.0f });

	vertexes = loader->GetVetrexVector();
	indexes = loader->GetIndexes();

	normalIndexes = loader->GetNormalIndexes();
	normals = loader->GetNormals();

	textureIndicies = loader->GetTextureCoordinateIndicies();
	textures = loader->GetTexturesVector();

	vertexesOutp.resize(vertexes.size() + normals.size());
	std::vector<HomogeneousCoordinateStruct> vertexesHomo;

	std::vector<int> steps = loader->GetMtlSteps();

	vertexesHomo.resize(vertexes.size());

	for (int i = 0; i < vertexes.size(); i++)
	{
		vertexesHomo[i] = { vertexes[i].x, vertexes[i].y, vertexes[i].z, 1 };
	}

	int curMtl = 0;
	int j = 0;
	for (int i = 0; i < indexes.size(); i += 3)
	{
		vertexesHomo[indexes[i] - 1].normal = normals[normalIndexes[i] - 1];
		vertexesHomo[indexes[i + 1] - 1].normal = normals[normalIndexes[i + 1] - 1];
		vertexesHomo[indexes[i + 2] - 1].normal = normals[normalIndexes[i + 2] - 1];

		vertexesHomo[indexes[i] - 1].texture = textures[textureIndicies[i] - 1];
		vertexesHomo[indexes[i + 1] - 1].texture = textures[textureIndicies[i + 1] - 1];
		vertexesHomo[indexes[i + 2] - 1].texture = textures[textureIndicies[i + 2] - 1];

		polygons.push_back({ vertexesHomo[indexes[i] - 1], vertexesHomo[indexes[i + 1] - 1], vertexesHomo[indexes[i + 2] - 1] });
		polygons[j++].textureId = curMtl;
		if (steps.size() - 1 <= curMtl) continue;
		else if (i >= steps[curMtl+1])
		{
			curMtl++;
		}
	}
	//polygons = GetAllPolygons(vertexesHomo, indexes, normalIndexes, normals);
	polygonsOutp.resize(polygons.size());

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//textureDatas.push_back(LoadTexture("../../assets/cube/texture.jpg"));

	/*textureDatas.push_back(LoadTexture("../../assets/Shovel Knight/shovel_diffuse.png"));
	textureDatas.push_back(LoadTexture("../../assets/Shovel Knight/shovel_mrao.png"));
	textureDatas[0].specularTexturData = textureDatas[1].textureData;
	textureDatas.push_back(LoadTexture("../../assets/Shovel Knight/shovel_normal_map.png"));
	textureDatas[0].normalTexturData = textureDatas[2].textureData;*/

	/*textureDatas.push_back(LoadTexture("../../assets/madokaMachida/textures/tex_hair.png"));
	textureDatas.push_back(LoadTexture("../../assets/madokaMachida/textures/tex_cloth.png"));
	textureDatas.push_back(LoadTexture("../../assets/madokaMachida/textures/tex_face.png"));*/
	
	/*textureDatas.push_back(LoadTexture("../../assets/schoolUniform/textures/bow_FRONT_1123501_Base_Color_1011.png"));
	textureDatas.push_back(LoadTexture("../../assets/schoolUniform/textures/shirt_FRONT_539393_Base_Color_1011.png"));
	textureDatas.push_back(LoadTexture("../../assets/schoolUniform/textures/shirt_wrist_collar_FRONT_672717_Base_Color_1011.png"));
	textureDatas.push_back(LoadTexture("../../assets/schoolUniform/textures/skirt_FRONT_1119_Base_Color_1001.png"));*/

	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_2_BaseColor.png"));
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_cloth_BaseColor.png"));
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_golden_BaseColor.png"));
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_1_BaseColor.png"));

	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_2_Normal.png"));
	textureDatas[0].normalTexturData = textureDatas[4].textureData;
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_cloth_Normal.png"));
	textureDatas[1].normalTexturData = textureDatas[5].textureData;
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_golden_Normal.png"));
	textureDatas[2].normalTexturData = textureDatas[6].textureData;
	textureDatas.push_back(LoadTexture("../../assets/AtomicHeart/textures/Titi_1_Normal.jpg"));
	textureDatas[3].normalTexturData = textureDatas[7].textureData;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	rasterizator = new Rasterizator();


	light1.globalPosition = { 10.f,15.f,500.f };
	light1.objectAlbedo = 0.18; //  base color input that defines the diffuse color or reflectivity of the surface
	light1.PhongDiffuseWeight = 0.8; // phong model diffuse weight
	light1.PhongSpecularWeight = 0.2; // phong model specular weight
	light1.PhongSpecularExponent = 10;   // phong specular exponent
	light1.LightColor = { 255,255,255 };
	light1.LightIntesity = 70;

	Lightnings.push_back(light1);

	PointLightStruct light2;
	light2.globalPosition = { 0.f,500.f,0.f };
	light2.objectAlbedo = 0.18; //  base color input that defines the diffuse color or reflectivity of the surface
	light2.PhongDiffuseWeight = 0.8; // phong model diffuse weight
	light2.PhongSpecularWeight = 0.2; // phong model specular weight
	light2.PhongSpecularExponent = 10;   // phong specular exponent
	light2.LightColor = { 255,255,255 };
	light2.LightIntesity = 70;

	Lightnings.push_back(light2);

	UpdateNormals();
	/////

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Simple 3d graphics",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, FrameWidth, FrameHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	UnloadTexture(textureDatas);
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		UpdateWindowSize(hwnd);
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
	{
		// Update the window title with the frame count
		std::string title = "3D Engine - FPS: " + std::to_string(fps);
		SetWindowTextA(hwnd, title.c_str());

		Render();
		ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	case WM_LBUTTONDOWN:
	{
		// Сохраняем текущие координаты курсора как предыдущие
		prevMouseX = LOWORD(lParam);
		prevMouseY = HIWORD(lParam);

		mouseDown = true;
		return 0;
	}

	case WM_LBUTTONUP:
	{
		// Сбрасываем флаг, что кнопка мыши нажата
		mouseDown = false;
		return 0;
	}

	case WM_MOUSEMOVE:
	{
		if (mouseDown)
		{
			int currMouseX = LOWORD(lParam);
			int currMouseY = HIWORD(lParam);

			int deltaX = currMouseX - prevMouseX;
			int deltaY = currMouseY - prevMouseY;

			phiAngleSphere -= deltaX * 0.1f;
			thetaAngleSphere -= deltaY * 0.1f;

			thetaAngleSphere = (thetaAngleSphere > 175.f) ? 175.f : ((thetaAngleSphere < 5.f) ? 5.f : thetaAngleSphere);

			prevMouseX = currMouseX;
			prevMouseY = currMouseY;

			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;
	}

	case WM_MOUSEWHEEL:
	{
		int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (wheelDelta > 0)
		{
			zCamera += coordSpeed;
			rSphere += coordSpeed;

		}
		else if (wheelDelta < 0)
		{
			if (zCamera > 1.f)
			{
				zCamera -= coordSpeed;
				rSphere -= coordSpeed;
			}
		}

		// Перерисовать окно
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			// Process the LEFT ARROW key. 
			yAngleObject -= angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key. 
			yAngleObject += angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case VK_UP:
			// Process the UP ARROW key. 
			xAngleObject += angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);

			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			xAngleObject -= angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'W':
			zCamera += coordSpeed;
			rSphere += coordSpeed;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'S':
			if (zCamera > 0.1f)
			{
				zCamera -= coordSpeed;
				rSphere -= coordSpeed;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			return 0;

		case 'Z':

			phiAngleSphere += angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'X':

			phiAngleSphere -= angleSpeed;
			InvalidateRect(hwnd, NULL, TRUE);

			return 0;

		case 'C':
			if (thetaAngleSphere < 175.f)
			{
				thetaAngleSphere += 5.f;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			return 0;

		case 'V':
			if (thetaAngleSphere > 5.f)
			{
				thetaAngleSphere -= 5.f;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			return 0;
		case '1':
			curGraphic = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '2':
			curGraphic = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '3':
			curGraphic = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '4':
			curGraphic = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '5':
			curGraphic = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '6':
			curGraphic = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '7':
			curGraphic = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '8':
			curGraphic = 8;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '9':
			curGraphic = 9;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case '0':
			curGraphic = 0;
			return 0;
		case VK_OEM_PLUS: // клавиша "=" из ряда с обычными клавишами
			if (zCamera < 51) return 0;
			zCamera -= 50;
			rSphere -= 50;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case VK_OEM_MINUS: // клавиша "-" из ряда с обычными клавишами
			if (zCamera > 1000) return 0;
			zCamera += 50;
			rSphere += 50;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case 'I':
			if (targetGlobalCoord.y > 300) return 0;
			targetGlobalCoord.y += 10.f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'K':
			if (targetGlobalCoord.y < -300) return 0;
			targetGlobalCoord.y -= 10.f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'O':
			if (targetGlobalCoord.x > 300) return 0;
			targetGlobalCoord.x += 10.f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'P':
			if (targetGlobalCoord.x < -300) return 0;
			targetGlobalCoord.x -= 10.f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}



	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}

void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	// Создаем битмап, совместимый с устройством
	HBITMAP hBitMap = CreateCompatibleBitmap(hdc, width, height);

	// Получаем доступ к битам битмапа
	BITMAPINFO bitmapInfo;
	ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
	bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
	bitmapInfo.bmiHeader.biWidth = width;
	//bitmapInfo.bmiHeader.biHeight = height; 
	bitmapInfo.bmiHeader.biHeight = (height == 0) ? 0 : -static_cast<LONG>(height); // Отрицательная высота означает, что битмап будет перевернут
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32; // 32 бита на пиксель - 8 бит на канал RGBA
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

	void* bits = nullptr;
	HDC srcHdc = CreateCompatibleDC(hdc);
	SelectObject(srcHdc, hBitMap);
	SetDIBits(srcHdc, hBitMap, 0, height, pixels, &bitmapInfo, DIB_RGB_COLORS);

	// Копируем битмап в целевое устройство
	BitBlt(hdc, 0, 0, width, height, srcHdc, 0, 0, SRCCOPY);
	/*[in] hdc
		Дескриптор контекста целевого устройства.
		[in] x
		Координата X в логических единицах левого верхнего угла целевого прямоугольника.
		[in] y
		Координата Y в логических единицах левого верхнего угла целевого прямоугольника.
		[in] cx
		Ширина (в логических единицах) исходного и целевого прямоугольников.
		[in] cy
		Высота (в логических единицах) исходного и целевого прямоугольников.
		[in] hdcSrc
		Дескриптор контекста исходного устройства.
		[in] x1
		Координата X в логических единицах верхнего левого угла исходного прямоугольника.
		[in] y1
		Координата Y в логических единицах верхнего левого угла исходного прямоугольника.
		[in] rop
		Код растровой операции. Эти коды определяют, как данные цвета исходного прямоугольника должны сочетаться с данными цвета для целевого прямоугольника для достижения окончательного цвета.
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////

		// Освобождаем ресурсы
	DeleteObject(hBitMap);
	DeleteDC(srcHdc);
	ReleaseDC(hWnd, hdc);

}

void SetPoint(void* buffer, int x, int y, RGBQUAD color)
{
	if (x >= 0 && x <= (FrameWidth - 1) && y >= 0 && y <= (FrameHeight - 1))
	{
		reinterpret_cast<RGBQUAD*>(buffer)[y * FrameWidth + x] = color;
	}
}

void Render()
{
	///////////////////////////////////////////////////////////
	frameCount++;

	// Measure the elapsed time since the last frame
	float deltaTime = getElapsedTime();
	accumulatedTime += deltaTime;

	// Update the FPS every updateInterval seconds
	if (accumulatedTime >= updateInterval)
	{
		fps = static_cast<int>(frameCount / accumulatedTime);
		frameCount = 0;
		accumulatedTime -= updateInterval;
	}


	//////////////////////////////////////////////////////////

	std::memset(frameBuffer, 0, sizeof(frameBuffer));

	
	for (int i = 0; i < 1080; ++i) {
		for (int j = 0; j < 1920; ++j) {
			depthBuffer[i][j] = MAX_DEPTH;
			//depthBuffer[i][j] = MIN_DEPTH;
		}
	}
	/////////////////////////////////////////SET MATRIXES////////////////////////////////////////////////////////////////
	modelCoordSystem->SetRotateYMatrix(GetRadians(yAngleObject));
	modelCoordSystem->SetRotateXMatrix(GetRadians(xAngleObject));
	modelCoordSystem->GlobalTransformationMatrix = modelCoordSystem->RotateYMatrix * modelCoordSystem->RotateXMatrix;

	cameraGlobalCoord = { SphericalToCartesian(rSphere, phiAngleSphere, thetaAngleSphere) };
	CoordinateStruct cameraUpVect = { 0,1,0 };
	modelCoordSystem->SetCameraTransformationMatrix(cameraGlobalCoord, targetGlobalCoord, cameraUpVect);

	modelCoordSystem->SetProjectionTransformationMatrix(45.0f, ((float)FrameWidth / (float)FrameHeight), zNear, zFar);

	modelCoordSystem->SetViewPortTransformationMatrix((float)FrameWidth, (float)FrameHeight, 0, 0, 0.0f, 1.0f);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UpdateVectors();



	/*for (int i = 0; i < polygonsOutp.size(); i++)
	{
		DrawTriangle(polygonsOutp[i]);
	}*/

	Concurrency::parallel_for(0, static_cast<int>(polygonsOutp.size()), [&](int i)
		{
			DrawTriangle(polygonsOutp[i]);
		});

}

void UpdateNormals()
{

	HomogeneousCoordinateStruct homoNormal, normalSum, vertexSum;
	for (int i = 0; i < polygons.size(); i++)
	{
		normalSum = { 0,0,0,0 };
		vertexSum = { 0,0,0,0 };
		for (int j = 0; j < (1 / vectorCount); j++)
		{

			homoNormal = { polygons[i].vectors[j].normal.x, polygons[i].vectors[j].normal.y, polygons[i].vectors[j].normal.z, 0 };

			//homoNormal *= modelCoordSystem->GlobalTransformationMatrix;

			polygonsOutp[i].vectors[j].normal = { homoNormal.x, homoNormal.y , homoNormal.z };
			polygonsOutp[i].vectors[j].normalW = homoNormal.w;
			normalSum = normalSum + homoNormal;

			// For center of polygon
			vertexSum = vertexSum + polygons[i].vectors[j];
		}
		vertexSum *= vectorCount;
		normalSum *= vectorCount;
		polygonsOutp[i].polygonNormal = Normalize(normalSum);
		polygonsOutp[i].polygonCenter = vertexSum;

		polygons[i].isOnScreen = true;
		polygonsOutp[i].isOnScreen = true;

		polygonsOutp[i].textureId = polygons[i].textureId;
	}
}

void UpdateVectors()
{
	//omp_set_num_threads(6);
	// Цикл будет выполняться в g_nNumberOfThreads потоков.
	// Параметры цикла будут автоматически распределены между потоками.
	#pragma omp parallel for
	for (int i = 0; i < polygons.size(); i++)
	{
		if (!ClipFacePolygons(i)) continue;
		if (!UpdatePolygons(i)) continue;
	}
}



bool IsObjectBehindClipPlanes(int polygonIterator, const std::vector<Plane>& clipPlanes)
{
	Triangle polygon;
	HomogeneousCoordinateStruct pointHomogeneous;

	polygon = polygonsOutp[polygonIterator];

	for (int i = 0; i < 3; i++)
	{
		pointHomogeneous = polygon.vectors[i];
		bool isVertexBehindClipPlanes = true;

		for (const Plane& clipPlane : clipPlanes) {
			if (!modelCoordSystem->IsVertexBehindClipPlane(pointHomogeneous, clipPlane)) {
				isVertexBehindClipPlanes = false;
				break;
			}
		}
		if (!isVertexBehindClipPlanes) {
			return false;
		}
	}
	return true;
}

Triangle CalculateLambertTermAndShade(int polygonIterator, int vectorIterator, CoordinateStruct curVector, Triangle inputPolygon)
{
	Triangle polygon = inputPolygon;

	CoordinateStruct curNormal = polygonsOutp[polygonIterator].vectors[vectorIterator].normal;

	CoordinateStruct lightDirection = Normalize(SubstractVectors(lightGlobalCoord, curVector));

	float lambertTerm = (DotProduct(curNormal, lightDirection) >= 0.0) ? DotProduct(curNormal, lightDirection) : 0.0f;
	polygon.vectors[vectorIterator].shade = lambertTerm;

	polygon.vectors[vectorIterator].diffuse = { DiffuseLightColor.x * lambertTerm, DiffuseLightColor.y * lambertTerm, DiffuseLightColor.z * lambertTerm };

	return polygon;
}

void DrawObject(int i)
{
	if (polygonsOutp[i].isOnScreen == false) return;
	//vectorCount = 1 / (sizeof(polygonsOutp[i].vectors) / sizeof(polygonsOutp[i].vectors[0]));
	HomogeneousCoordinateStruct homoNormal0, homoNormal1, homoNormal2;

	switch (curGraphic)
	{
	case 1:
		polygonOutputMutex.lock();
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0], polygonsOutp[i].vectors[0 + 1], color2);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 1], polygonsOutp[i].vectors[0 + 2], color2);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 2], polygonsOutp[i].vectors[0], color2);
		polygonOutputMutex.unlock();
		break;
	case 2:
		polygonOutputMutex.lock();
		for (int j = 0; j < (1 / vectorCount); j++)
		{
			if (polygonsOutp[i].vectors[j].x > 1920 || polygonsOutp[i].vectors[j].x < 0 || polygonsOutp[i].vectors[j].y > 1080 || polygonsOutp[i].vectors[j].y < 0) return;
		}

		rasterizator->UpdateXleftAndXRight(polygonsOutp[i]);

		rasterizator->DrawLines(polygonsOutp[i], frameBuffer, depthBuffer, color);
		polygonOutputMutex.unlock();
		break;
	case 3:
		polygonOutputMutex.lock();
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0], polygonsOutp[i].vectors[0 + 1], color2);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 1], polygonsOutp[i].vectors[0 + 2], color2);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 2], polygonsOutp[i].vectors[0], color2);

		homoNormal0 = { polygonsOutp[i].vectors[0].projectedNormal.x, polygonsOutp[i].vectors[0].projectedNormal.y, polygonsOutp[i].vectors[0].projectedNormal.z, 1 };
		homoNormal1 = { polygonsOutp[i].vectors[1].projectedNormal.x, polygonsOutp[i].vectors[1].projectedNormal.y, polygonsOutp[i].vectors[1].projectedNormal.z, 1 };
		homoNormal2 = { polygonsOutp[i].vectors[2].projectedNormal.x, polygonsOutp[i].vectors[2].projectedNormal.y, polygonsOutp[i].vectors[2].projectedNormal.z, 1 };
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0], homoNormal0, color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 1], homoNormal1, color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 2], homoNormal2, color);
		polygonOutputMutex.unlock();
		break;
	case 4:


		for (int j = 0; j < (1 / vectorCount); j++)
		{
			if (polygonsOutp[i].vectors[j].x > 1920 || polygonsOutp[i].vectors[j].x < 0 || polygonsOutp[i].vectors[j].y > 1080 || polygonsOutp[i].vectors[j].y < 0) return;
		}

		rasterizator->DrawPolygon(polygonsOutp[i], frameBuffer, depthBuffer, color);

		break;
	}
}

void DrawTriangle(Triangle& triangle)
{
	if (triangle.isOnScreen == false) return;
	int curVectorCount = (1 / vectorCount);
	RectangleStruct bbox;
	HomogeneousCoordinateStruct homoNormal0, homoNormal1, homoNormal2;

	switch (curGraphic)
	{
	case 1:
		polygonOutputMutex.lock();
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0], triangle.vectors[0 + 1], color2);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 1], triangle.vectors[0 + 2], color2);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 2], triangle.vectors[0], color2);
		polygonOutputMutex.unlock();
		break;
	case 2:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;


		polygonOutputMutex.lock();


		rasterizator->UpdateXleftAndXRight(triangle);

		rasterizator->DrawLines(triangle, frameBuffer, depthBuffer, color);
		polygonOutputMutex.unlock();
		break;
	case 3:
		polygonOutputMutex.lock();
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0], triangle.vectors[0 + 1], color2);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 1], triangle.vectors[0 + 2], color2);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 2], triangle.vectors[0], color2);

		homoNormal0 = { triangle.vectors[0].projectedNormal.x, triangle.vectors[0].projectedNormal.y, triangle.vectors[0].projectedNormal.z, 1 };
		homoNormal1 = { triangle.vectors[1].projectedNormal.x, triangle.vectors[1].projectedNormal.y, triangle.vectors[1].projectedNormal.z, 1 };
		homoNormal2 = { triangle.vectors[2].projectedNormal.x, triangle.vectors[2].projectedNormal.y, triangle.vectors[2].projectedNormal.z, 1 };
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0], homoNormal0, color);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 1], homoNormal1, color);
		BresenhamLineOptimised(frameBuffer, triangle.vectors[0 + 2], homoNormal2, color);
		polygonOutputMutex.unlock();
		break;
	case 4:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentric(triangle,Lightnings,cameraGlobalCoord, frameBuffer, depthBuffer, color);
		break;
	case 5:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentricTexture(triangle, Lightnings, cameraGlobalCoord, frameBuffer, depthBuffer, color, textureDatas[triangle.textureId]);
		break;
	case 6:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentricTextureWithLight(triangle, Lightnings, cameraGlobalCoord, frameBuffer, depthBuffer, color, textureDatas[triangle.textureId]);
		break;
	case 7:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentricTextureWithBillinearFiltration(triangle, Lightnings, cameraGlobalCoord, frameBuffer, depthBuffer, color, textureDatas[triangle.textureId]);
		break;
	case 8:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentricParam(triangle, Lightnings, cameraGlobalCoord, frameBuffer, depthBuffer, color, textureDatas[triangle.textureId]);
		break;
	case 9:
		bbox = FindTriangleBoundingRectangle2D(triangle);
		if (bbox.left > 1920 || bbox.right < 0 || bbox.top > 1080 || bbox.bottom < 0) return;

		rasterizator->DrawPolygonBarycentricLast(triangle, Lightnings, cameraGlobalCoord, frameBuffer, depthBuffer, color, textureDatas[triangle.textureId]);
		break;
	}
	
}

bool ClipFacePolygons(int polygonIterator)
{
	HomogeneousCoordinateStruct polygonCenter, polygonNormal;

	polygonCenter = polygonsOutp[polygonIterator].polygonCenter;
	polygonNormal = polygonsOutp[polygonIterator].polygonNormal;

	polygonCenter *= modelCoordSystem->GlobalTransformationMatrix;
	polygonNormal *= modelCoordSystem->GlobalTransformationMatrix;


	CoordinateStruct curPolygonCenter = polygonCenter.toCoordinateStruct();
	CoordinateStruct curCameraPos = { 0,0,0 };
	CoordinateStruct cameraDirectionOnPoint = Normalize(SubstractVectors(cameraGlobalCoord, curPolygonCenter));

	float dotProduct = DotProduct(polygonNormal.toCoordinateStruct(), cameraDirectionOnPoint);
	if (dotProduct < 0)
	{
		polygonsOutp[polygonIterator].isOnScreen = false;
		return false;
	}
	polygonsOutp[polygonIterator].isOnScreen = true;
	return true;
}



bool UpdatePolygons(int polygonIterator)
{

	Triangle polygon = polygonsOutp[polygonIterator];
	HomogeneousCoordinateStruct pointHomogeneous, normalHomogeneous;

	for (int i = 0; i < (1 / vectorCount); i++)
	{
		pointHomogeneous = polygons[polygonIterator].vectors[i];

		normalHomogeneous = { polygonsOutp[polygonIterator].vectors[i].normal.x, polygonsOutp[polygonIterator].vectors[i].normal.y, polygonsOutp[polygonIterator].vectors[i].normal.z, 1 };

		pointHomogeneous *= modelCoordSystem->GlobalTransformationMatrix;
		//CoordinateStruct curVector = { pointHomogeneous.x,pointHomogeneous.y,pointHomogeneous.z };
		polygon.vectorsInGlobal[i] = pointHomogeneous;

		modelCoordSystem->SetTranslationMatrix(pointHomogeneous.toCoordinateStruct());

		pointHomogeneous *= modelCoordSystem->CameraTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->ProjectionTransformationMatrix;

		if (/*pointHomogeneous.w < 0.4 && */pointHomogeneous.w > -0.4)
		{
			polygonsOutp[polygonIterator].isOnScreen = false;
			return false;
		}

		float temp = -(1 / pointHomogeneous.w);
		pointHomogeneous *= (1 / pointHomogeneous.w);
		polygon.vectorsInGlobal[i].w = temp;


		// Normalized Decart Coordinates here 
		if (pointHomogeneous.x < -1.0f || pointHomogeneous.x > 1.0f ||
			pointHomogeneous.y < -1.0f || pointHomogeneous.y > 1.0f )
		{
			polygonsOutp[polygonIterator].isOnScreen = false;
			return false;
		}
		
		pointHomogeneous *= modelCoordSystem->ViewPortTransformationMatrix;

		///////////////////////////////////////////////////////////////////////////////
		polygon.vectors[i] = pointHomogeneous;

		//////////////////////////////Normals Showcase//////////////////////////////////
		if (curGraphic == 3)
		{
			normalHomogeneous = modelCoordSystem->CalculateNormalProjections({ polygonsOutp[polygonIterator].vectors[i].normal.x,
																				polygonsOutp[polygonIterator].vectors[i].normal.y,
																				polygonsOutp[polygonIterator].vectors[i].normal.z, 1 });
		}
		polygon.vectors[i].projectedNormal = { normalHomogeneous.x, normalHomogeneous.y, normalHomogeneous.z };
		///////////////////////////////// LAMBERT///////////////////////////////////////////////////////

		CoordinateStruct curVector = { polygon.vectorsInGlobal[i].x,polygon.vectorsInGlobal[i].y,polygon.vectorsInGlobal[i].z };
		if (curGraphic == 2) polygon = CalculateLambertTermAndShade(polygonIterator, i, curVector, polygon);
	}
	polygonOutputMutex.lock();
	polygonsOutp[polygonIterator] = polygon;
	polygonOutputMutex.unlock();
	return true;
}

// Deprecated
//Triangle UpdatePolygonsTriangle(int polygonIterator)
//{
//	Triangle polygon;
//	HomogeneousCoordinateStruct pointHomogeneous;
//	for (int i = 0; i < 3; i++)
//	{
//		pointHomogeneous = polygons[polygonIterator].vectors[i];
//
//		pointHomogeneous *= modelCoordSystem->GlobalTransformationMatrix;
//		CoordinateStruct curVector = { pointHomogeneous.x,pointHomogeneous.y,pointHomogeneous.z };
//		modelCoordSystem->SetTranslationMatrix(pointHomogeneous.toCoordinateStruct());
//		pointHomogeneous *= modelCoordSystem->CameraTransformationMatrix;
//		pointHomogeneous *= modelCoordSystem->ProjectionTransformationMatrix;
//
//		if (pointHomogeneous.w < 0.4 && pointHomogeneous.w > -0.4)
//		{
//			pointHomogeneous = { 0,0,0,1 };
//			//return false;
//		}
//
//		pointHomogeneous *= (1 / pointHomogeneous.w);
//		pointHomogeneous *= modelCoordSystem->ViewPortTransformationMatrix;
//
//		pointHomogeneous.shade = 1;
//		polygon.vectors[i] = pointHomogeneous;
//		polygon.vectors[i].normal = polygons[polygonIterator].vectors[i].normal;
//
//		///////////////////////////////// LAMBERT///////////////////////////////////////////////////////
//		//CoordinateStruct normal = modelCoordSystem->NormalizeVector(polygon.vectors[i].normal);
//		CoordinateStruct normal = Normalize(polygon.vectors[i].normal);
//		// получаем вектор направления света
//		CoordinateStruct curPos = { polygon.vectors[i].x,polygon.vectors[i].y,polygon.vectors[i].z };
//		CoordinateStruct lightDirection = Normalize(SubstractVectors(lightGlobalCoord, curVector));
//
//		// получаем скалярное произведение векторов нормали и направления света
//		float lambertTerm = (DotProduct(normal, lightDirection) >= 0.0) ? DotProduct(normal, lightDirection) : 0.0f;
//		polygon.vectors[i].shade = lambertTerm;
//
//		polygon.vectors[i].diffuse = { DiffuseLightColor.x * lambertTerm, DiffuseLightColor.y * lambertTerm, DiffuseLightColor.z * lambertTerm };
//	}
//	return polygon;
//}

void UpdateWindowSize(HWND hWnd)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	FrameHeight = clientRect.bottom;
	FrameWidth = clientRect.right;
}

void BresenhamLineOptimised(void* buffer, HomogeneousCoordinateStruct vectorA, HomogeneousCoordinateStruct vectorB, RGBQUAD color)
{
	int x1 = (int)(vectorA.x);
	int y1 = (int)(vectorA.y);
	int x2 = (int)(vectorB.x);
	int y2 = (int)(vectorB.y);

	int dx = x2 - x1;
	int dy = y2 - y1;
	int w = std::abs(dx);
	int h = std::abs(dy);
	int l = max(w, h);

	int sign = (dx >= 0) ? 1 : -1;
	int mat11 = sign;
	int mat12 = 0;
	int mat21 = 0;
	sign = (dy >= 0) ? 1 : -1;
	int mat22 = sign;

	if (w < h)
	{
		int temp = mat11;
		mat11 = mat12;
		mat12 = temp;

		temp = mat21;
		mat21 = mat22;
		mat22 = temp;
	}
	int y = 0;
	int error = 0;
	int errorDec = 2 * l;
	int errorInc = 2 * min(w, h);

	for (int x = 0; x <= l; x++)
	{
		int xt = x1 + (mat11 * x) + (mat12 * y);
		int yt = y1 + (mat21 * x) + (mat22 * y);
		SetPoint(buffer, xt, yt, color);

		if ((error += errorInc) > l)
		{
			error -= errorDec;
			y++;
		}
	}
}


void plotLineLow(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int D = (2 * dy) - dx;
	int y = y0;

	for (int x = x0; x <= x1; x++) {
		SetPoint(buffer, x, y, color);

		if (D > 0) {
			y += yi;
			D += (2 * (dy - dx));
		}
		else {
			D += (2 * dy);
		}
	}
}

void plotLineHigh(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int D = (2 * dx) - dy;
	int x = x0;

	for (int y = y0; y <= y1; y++) {
		SetPoint(buffer, x, y, color);

		if (D > 0) {
			x += xi;
			D += (2 * (dx - dy));
		}
		else {
			D += (2 * dx);
		}
	}
}

void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
		if (x0 > x1) {
			plotLineLow(buffer, x1, y1, x0, y0, color);
		}
		else {
			plotLineLow(buffer, x0, y0, x1, y1, color);
		}
	}
	else {
		if (y0 > y1) {
			plotLineHigh(buffer, x1, y1, x0, y0, color);
		}
		else {
			plotLineHigh(buffer, x0, y0, x1, y1, color);
		}
	}
}


//void UpdatePolygonsAsync()
//{
//	ThreadPool pool(8);
//	std::vector<std::future<Triangle>> futures;
//
//	for (int i = 0; i < polygons.size(); i++)
//	{
//		futures.emplace_back(pool.enqueue([i] { return UpdatePolygonsTriangle(i); }));
//	}
//
//	for (int i = 0; i < polygons.size(); i++)
//	{
//		polygonsOutp[i] = futures[i].get();
//	}
//}

//void UpdatePolygonsAsync()
//{
//	ThreadPool pool(8);
//	std::vector<std::future<void>> futures;
//
//	for (int i = 0; i < polygons.size(); i++)
//	{
//		futures.emplace_back(pool.enqueue([i] { return UpdateVectors(i); }));
//	}
//
//	for (int i = 0; i < polygons.size(); i++)
//	{
//		futures[i].get();
//	}
//}

void DrawPolygonsAsync()
{
	ThreadPool pool(8);
	std::vector<std::future<void>> futures;

	for (int i = 0; i < polygonsOutp.size(); i++)
	{
		futures.emplace_back(pool.enqueue([i] { return DrawObject(i); }));
	}

	for (int i = 0; i < polygons.size(); i++)
	{
		futures[i].get();
	}
}

double getElapsedTime()
{
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);
	lastTime = currentTime;
	return elapsedTime.count();
}