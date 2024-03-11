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

	vertexesOutp.resize(vertexes.size());
	std::vector<HomogeneousCoordinateStruct> vertexesHomo;
	vertexesHomo.resize(vertexes.size());

	for (int i = 0; i < vertexes.size(); i++)
	{
		vertexesHomo[i] = { vertexes[i].x, vertexes[i].y, vertexes[i].z, 1 };
	}

	polygons.resize(indexes.size() / 3);
	polygons = GetAllPolygons(vertexesHomo, indexes);
	polygonsOutp.resize(polygons.size());

	/////

	rasterizator = new Rasterizator(FrameWidth, FrameHeight);



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
		Render();
		ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			// Process the LEFT ARROW key. 
			yAngleObject -= 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key. 
			yAngleObject += 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case VK_UP:
			// Process the UP ARROW key. 
			xAngleObject += 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);

			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			xAngleObject -= 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'W':
			zCamera += 0.05f;
			rSphere += 0.05f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'S':
			zCamera -= 0.05f;
			rSphere -= 0.05f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'Z':

			phiAngleSphere += 5.f;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case 'X':

			phiAngleSphere -= 5.f;
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
		}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}

void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd)
{
	HDC hdc = GetDC(hWnd);


	HBITMAP hBitMap = CreateBitmap(width, height, 1, 8 * 4, pixels);
	//HBITMAP hBitMap = CreateCompatibleBitmap(hdc, width, height);
	/*
	  [in] nPlanes
	  ���������� �������� ����������, ������������ �����������.
	  [in] nBitCount (4 �����)
	  ���������� �����, ����������� ��� ������������� ����� ������ �������.
	 */


	 // ��������� DC ��� �������� bit-map'�
	HDC srcHdc = CreateCompatibleDC(hdc);

	SelectObject(srcHdc, hBitMap);

	BitBlt(hdc, 0, 0, static_cast<int>(width), static_cast<int>(height), srcHdc, 0, 0, SRCCOPY);
	/*[in] hdc
		���������� ��������� �������� ����������.
		[in] x
		���������� X � ���������� �������� �������� ������ ���� �������������� ����������.
		[in] y
		���������� Y � ���������� �������� �������� ������ ���� �������������� ����������.
		[in] cx
		������(� ���������� ��������) ��������� � �������� ���������������.
		[in] cy
		������(� ���������� ��������) ��������� � �������� ���������������.
		[in] hdcSrc
		���������� ��������� ��������� ����������.
		[in] x1
		���������� X � ���������� �������� �������� ������ ���� ��������� ��������������.
		[in] y1
		���������� Y � ���������� �������� �������� ������ ���� ��������� ��������������.
		[in] rop
		��� ��������� ��������.��� ���� ����������, ��� ������ ����� ��������� �������������� ������ ���������� � ������� ����� ��� �������������� ���������� ��� ���������� �������������� �����.*/


	DeleteObject(hBitMap);
	DeleteDC(srcHdc);
	ReleaseDC(hWnd, hdc);

}

void SetPoint(void* buffer, int x, int y, RGBQUAD color)
//void SetPoint(const std::vector<std::vector<RGBQUAD>>& frameBuffer, int x, int y, RGBQUAD color)
{
	if (x >= 0 && x <= (FrameWidth - 1) && y >= 0 && y <= (FrameHeight - 1))
	{
		reinterpret_cast<RGBQUAD*>(buffer)[y * FrameWidth + x] = color;
		//frameBuffer[y][x] = color;
	}
}

void SetPointWithZ(int x, int y, RGBQUAD color, float z)
{
	if (x >= 0 && x < FrameWidth && y >= 0 && y < FrameHeight && z < rasterizator->zBuffer[y][x]) {
		frameBuffer[y][x] = color;
		rasterizator->zBuffer[y][x] = z;
	}
}

void Render()
{
	std::memset(frameBuffer, 0, sizeof(frameBuffer));

	const float MAX_DEPTH = 3.4E+38f;
	const float MIN_DEPTH = -3.4E+38f;
	for (int i = 0; i < 1080; ++i) {
		for (int j = 0; j < 1920; ++j) {
			depthBuffer[i][j] = MAX_DEPTH;
			//depthBuffer[i][j] = MIN_DEPTH;
		}
	}


	UpdateVectors();


	//bool isInvisible = false;
	//for (int i = 0; i < polygonsOutp.size(); i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		if (polygonsOutp[i].vectors[j].x == 0 && polygonsOutp[i].vectors[j].y == 0 && polygonsOutp[i].vectors[j].z == 0 && polygonsOutp[i].vectors[j].w == 1)
	//		{
	//			isInvisible = true;
	//			break;
	//		}
	//	}
	//	if (isInvisible)
	//	{
	//		isInvisible = false;
	//		continue;
	//	}
	//	int j = 0;

	//	/*BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j], polygonsOutp[i].vectors[j + 1], color);
	//	BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j + 1], polygonsOutp[i].vectors[j + 2], color);
	//	BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j + 2], polygonsOutp[i].vectors[j], color);*/


	//	rasterizator->UpdateXleftAndXRight(polygonsOutp[i]);

	//	// Отрисовка горизонтальных отрезков
	//	for (int y = polygonsOutp[i].vectors[0].y; y <= polygonsOutp[i].vectors[2].y; y++) {

	//		int xL = rasterizator->xLeft[y - polygonsOutp[i].vectors[0].y];
	//		int xR = rasterizator->xRight[y - polygonsOutp[i].vectors[0].y];
	//		for (int x = xL; x <= xR; x++) {
	//			float zL = rasterizator->zLeft[y - polygonsOutp[i].vectors[0].y];
	//			float zR = rasterizator->zRight[y - polygonsOutp[i].vectors[0].y];

	//			float z;
	//			if (xR - xL != 0)
	//			{
	//				z = zL + (x - xL) * (zR - zL) / (xR - xL);
	//			}
	//			else
	//			{
	//				z = zL;
	//			}

	//			if (z < depthBuffer[x][y])
	//			{
	//				SetPoint(frameBuffer, x, y, color);
	//				depthBuffer[x][y] = z;
	//			}
	//		}
	//	}
	//	color.rgbRed += 100;
	//	color.rgbGreen += 50;
	//	color.rgbBlue += 20;
	//}

}

void UpdateVectors()
{
	std::vector<Plane> clipPlanes = {
		{ {1, 0, 0}, 1 },
		{ {-1, 0, 0}, -1 },
		{ {0, 1, 0}, 1 },
		{ {0, -1, 0}, -1 },
		{ {0, 0, 1}, 1 },
		{ {0, 0, -1}, -1 }
	};



	modelCoordSystem->SetRotateYMatrix(GetRadians(yAngleObject));
	modelCoordSystem->SetRotateXMatrix(GetRadians(xAngleObject));
	modelCoordSystem->GlobalTransformationMatrix = modelCoordSystem->RotateYMatrix * modelCoordSystem->RotateXMatrix;

	modelCoordSystem->SetProjectionTransformationMatrix(45.0f, ((float)FrameWidth / (float)FrameHeight), zNear, zFar);

	CoordinateStruct cameraGlobalCoord = { SphericalToCartesian(rSphere, phiAngleSphere, thetaAngleSphere) };

	CoordinateStruct targetGlobalCoord = { 0,0.6f,0.f };
	CoordinateStruct cameraUpVect = { 0,1,0 };
	modelCoordSystem->SetCameraTransformationMatrix(cameraGlobalCoord, targetGlobalCoord, cameraUpVect);

	modelCoordSystem->SetViewPortTransformationMatrix((float)FrameWidth, (float)FrameHeight, 0, 0, 0.0f, 1.0f);


	for (int i = 0; i < polygons.size(); i++)
	{
		UpdatePolygons(i);
		if (!IsObjectBehindClipPlanes(i, clipPlanes))
		{
			DrawObject(i);
		}
	}

	//UpdatePolygonsAsync();
}


bool IsObjectBehindClipPlanes(int polygonIterator, const std::vector<Plane>& clipPlanes)
{
	Triangle polygon;
	HomogeneousCoordinateStruct pointHomogeneous;

	polygon = polygonsOutp[polygonIterator];

	HomogeneousCoordinateStruct edge1 = polygon.vectors[1] - polygon.vectors[0];
	HomogeneousCoordinateStruct edge2 = polygon.vectors[2] - polygon.vectors[0];

	HomogeneousCoordinateStruct normal = modelCoordSystem->CrossProduct(edge1, edge2);
	CoordinateStruct normal3d = modelCoordSystem->NormalizeVector({normal.x,normal.y,normal.z});

	CoordinateStruct targetGlobalCoord = { 0,0.6f,0.f };
	CoordinateStruct vector0 = { polygon.vectors[0].x, polygon.vectors[0].y, polygon.vectors[0].z };
	CoordinateStruct viewVector = targetGlobalCoord - vector0;

	viewVector = modelCoordSystem->NormalizeVector(viewVector);

	float dotProduct = modelCoordSystem->DotProduct(normal3d, viewVector);

	//// Если скалярное произведение отрицательное, то отбрасываем треугольник
	//if (dotProduct < 0) {
	//	return true; // переходим к следующему треугольнику
	//}

	for (int i = 0; i < 3; i++)
	{
		pointHomogeneous = polygon.vectors[i];
		bool isVertexBehindClipPlanes = true;


		if (pointHomogeneous.x == 0 && pointHomogeneous.y == 0 && pointHomogeneous.z == 0 && pointHomogeneous.w == 1)
		{
			return true;
		}

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

void DrawObject(int i)
{
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0], polygonsOutp[i].vectors[0 + 1], color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 1], polygonsOutp[i].vectors[0 + 2], color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[0 + 2], polygonsOutp[i].vectors[0], color);

	//rasterizator->UpdateXleftAndXRight(polygonsOutp[i]);

	//// Проверяем, что размеры массивов zLeft и zRight соответствуют количеству горизонтальных отрезков
	//int numHorizontalSegments = polygonsOutp[i].vectors[2].y - polygonsOutp[i].vectors[0].y + 1;
	//if (rasterizator->zLeft.size() < numHorizontalSegments || rasterizator->zRight.size() < numHorizontalSegments) {
	//	return;
	//}


	//if (polygonsOutp[i].vectors[2].y > 1080) return;

	//// Отрисовка горизонтальных отрезков
	//for (int y = polygonsOutp[i].vectors[0].y; y <= polygonsOutp[i].vectors[2].y; y++) {

	//	int xL = rasterizator->xLeft[y - polygonsOutp[i].vectors[0].y];
	//	int xR = rasterizator->xRight[y - polygonsOutp[i].vectors[0].y];
	//	if (xR > 1920) return;

	//	for (int x = xL; x <= xR; x++) {
	//		if (y - polygonsOutp[i].vectors[0].y >= 0 && y - polygonsOutp[i].vectors[0].y < rasterizator->zLeft.size())
	//		{
	//			float zL = rasterizator->zLeft[y - polygonsOutp[i].vectors[0].y];
	//			float zR = rasterizator->zRight[y - polygonsOutp[i].vectors[0].y];

	//			float z;
	//			if (xR - xL != 0)
	//			{
	//				z = zL + (x - xL) * (zR - zL) / (xR - xL);
	//			}
	//			else
	//			{
	//				z = zL;
	//			}

	//			if (z < depthBuffer[x][y])
	//			{
	//				SetPoint(frameBuffer, x, y, color);
	//				depthBuffer[x][y] = z;
	//			}
	//		}

	//	}
	//}
	//color.rgbRed += 100;
	//color.rgbGreen += 50;
	//color.rgbBlue += 20;
}

void UpdatePolygons(int polygonIterator)
{
	Triangle polygon;
	HomogeneousCoordinateStruct pointHomogeneous;
	for (int i = 0; i < 3; i++)
	{
		pointHomogeneous = polygons[polygonIterator].vectors[i];

		pointHomogeneous *= modelCoordSystem->GlobalTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->CameraTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->ProjectionTransformationMatrix;


		/*if (pointHomogeneous.w < 0.4 && pointHomogeneous.w > -0.4)
		{
			pointHomogeneous = { 0,0,0,1 };
		}
		else
		{*/
			pointHomogeneous *= (1 / pointHomogeneous.w);
			pointHomogeneous *= modelCoordSystem->ViewPortTransformationMatrix;
		//}

		polygon.vectors[i] = pointHomogeneous;
	}
	polygonsOutp[polygonIterator] = polygon;
}

Triangle UpdatePolygonsTriangle(int polygonIterator)
{

	Triangle polygon;
	HomogeneousCoordinateStruct pointHomogeneous;
	for (int i = 0; i < 3; i++)
	{
		pointHomogeneous = polygons[polygonIterator].vectors[i];

		pointHomogeneous *= modelCoordSystem->GlobalTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->CameraTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->ProjectionTransformationMatrix;


		if (pointHomogeneous.w < 0.4 && pointHomogeneous.w > -0.4)
		{
			pointHomogeneous = { 0,0,0,1 };
		}
		else
		{
			pointHomogeneous *= (1 / pointHomogeneous.w);
			pointHomogeneous *= modelCoordSystem->ViewPortTransformationMatrix;
		}

		polygon.vectors[i] = pointHomogeneous;
	}
	return polygon;
}

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


void UpdatePolygonsAsync()
{
	ThreadPool pool(8);
	std::vector<std::future<Triangle>> futures;

	for (int i = 0; i < polygons.size(); i++)
	{
		futures.emplace_back(pool.enqueue([i] { return UpdatePolygonsTriangle(i); }));
	}

	for (int i = 0; i < polygons.size(); i++)
	{
		polygonsOutp[i] = futures[i].get();
	}
}