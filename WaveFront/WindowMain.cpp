#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "CoordSystem.h"
#include "Triangle.h"
//#include "TestGLM.h"



LONG FrameHeight = 720, FrameWidth = 1280;

RGBQUAD frameBuffer[720][1280];

RGBQUAD color = { 255, 255, 255, 0 };


std::vector<CoordinateStruct> vertexes;
std::vector<HomogeneousCoordinateStruct> vertexesOutp;
std::vector<Triangle> polygons;
std::vector<Triangle> polygonsOutp;
std::vector<int> indexes;
HomogeneousCoordinateStruct pointHomogeneous;
CoordSystem* modelCoordSystem;

float yAngleObject = 0.0f;
float xAngleObject = 0.0f;
float xCamera = 0.0f;
float yCamera = 0.0f;
float zCamera = 1.5f;
float rSphere = zCamera;
float phiAngleSphere = 0.0f;
float thetaAngleSphere = 90.0f;

float zNear = 10.0f;
float zFar = 100.0f;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLineWithErr(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void Render();
void UpdateVectors();
void UpdateWindowSize(HWND hWnd);
void UpdatePolygons(int polygonIterator);
void BresenhamLineOptimised(void* buffer, HomogeneousCoordinateStruct vectorA, HomogeneousCoordinateStruct vectorB, RGBQUAD color);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ObjLoader* loader = new ObjLoader();

	modelCoordSystem = new CoordSystem({ 0.0f,0.0f,0.0f });

	//std::string res = loader->GetOutput();
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

	Render();

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

		//Render();
		//ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);
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
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key. 
			yAngleObject += 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case VK_UP:
			// Process the UP ARROW key. 
			xAngleObject += 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);;

			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			xAngleObject -= 5.0f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case 'W':
			zCamera += 0.05f;
			 rSphere += 0.05f;
			 InvalidateRect(hwnd, NULL, TRUE);;
			 return 0;

		case 'S':
			zCamera -= 0.05f;
			rSphere -= 0.05f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case 'Z':
			phiAngleSphere += 5.f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case 'X':
			phiAngleSphere -= 5.f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case 'C':
			thetaAngleSphere += 5.f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;

		case 'V':
			thetaAngleSphere -= 5.f;
			InvalidateRect(hwnd, NULL, TRUE);;
			return 0;
		}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}

void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd)
{
	HBITMAP hBitMap = CreateBitmap(width, height, 1, 8 * 4, pixels);  //CreateCompatibleBitmap  с цветным будет быстрее 
	/*
	  [in] nPlanes
	  Количество цветовых плоскостей, используемых устройством.
	  [in] nBitCount (4 байта)
	  Количество битов, необходимых для идентификации цвета одного пикселя.
	 */

	HDC hdc = GetDC(hWnd);

	// Временный DC для переноса bit-map'а
	HDC srcHdc = CreateCompatibleDC(hdc);

	SelectObject(srcHdc, hBitMap);

	BitBlt(hdc, 0, 0, static_cast<int>(width), static_cast<int>(height), srcHdc, 0, 0, SRCCOPY);
	/*[in] hdc
		Дескриптор контекста целевого устройства.
		[in] x
		Координата X в логических единицах верхнего левого угла прямоугольника назначения.
		[in] y
		Координата Y в логических единицах верхнего левого угла прямоугольника назначения.
		[in] cx
		Ширина(в логических единицах) исходного и целевого прямоугольников.
		[in] cy
		Высота(в логических единицах) исходного и целевого прямоугольников.
		[in] hdcSrc
		Дескриптор контекста исходного устройства.
		[in] x1
		Координата X в логических единицах верхнего левого угла исходного прямоугольника.
		[in] y1
		Координата Y в логических единицах верхнего левого угла исходного прямоугольника.
		[in] rop
		Код растровой операции.Эти коды определяют, как данные цвета исходного прямоугольника должны сочетаться с данными цвета для прямоугольника назначения для достижения окончательного цвета.*/


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
	std::memset(frameBuffer, 0, sizeof(frameBuffer));

	UpdateVectors();


	bool isInvisible = false;
	for (int i = 0; i < polygonsOutp.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (polygonsOutp[i].vectors[j].x == 0 && polygonsOutp[i].vectors[j].y == 0 && polygonsOutp[i].vectors[j].z == 0 && polygonsOutp[i].vectors[j].w == 1)
			{
				isInvisible = true;
				break;
			}
		}
		if (isInvisible)
		{
			isInvisible = false;
			continue;
		}

		int j = 0;
		/*plotLine(frameBuffer, polygonsOutp[i].vectors[j].x, polygonsOutp[i].vectors[j].y, polygonsOutp[i].vectors[j + 1].x, polygonsOutp[i].vectors[j + 1].y, color);
		plotLine(frameBuffer, polygonsOutp[i].vectors[j + 1].x, polygonsOutp[i].vectors[j + 1].y, polygonsOutp[i].vectors[j + 2].x, polygonsOutp[i].vectors[j + 2].y, color);
		plotLine(frameBuffer, polygonsOutp[i].vectors[j + 2].x, polygonsOutp[i].vectors[j + 2].y, polygonsOutp[i].vectors[j].x, polygonsOutp[i].vectors[j].y, color);*/

		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j], polygonsOutp[i].vectors[j + 1], color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j + 1], polygonsOutp[i].vectors[j + 2], color);
		BresenhamLineOptimised(frameBuffer, polygonsOutp[i].vectors[j + 2], polygonsOutp[i].vectors[j], color);

	}
}

void UpdateVectors()
{
	modelCoordSystem->SetRotateYMatrix(GetRadians(yAngleObject));
	modelCoordSystem->SetRotateXMatrix(GetRadians(xAngleObject));
	modelCoordSystem->GlobalTransformationMatrix = modelCoordSystem->RotateYMatrix * modelCoordSystem->RotateXMatrix;

	modelCoordSystem->SetProjectionTransformationMatrix(45.0f, ((float)FrameWidth / (float)FrameHeight), zNear, zFar);

	CoordinateStruct cameraGlobalCoord = { SphericalToCartesian(rSphere, phiAngleSphere, thetaAngleSphere) };

	//CoordinateStruct targetGlobalCoord = { 0,0.f,0.f };
	CoordinateStruct targetGlobalCoord = { 0,0.6f,0.f };
	CoordinateStruct cameraUpVect = { 0,1,0 };
	modelCoordSystem->SetCameraTransformationMatrix(cameraGlobalCoord, targetGlobalCoord, cameraUpVect);

	modelCoordSystem->SetViewPortTransformationMatrix((float)FrameWidth, (float)FrameHeight, 0, 0, 0.0f, 1.0f);


	for (int i = 0; i < polygons.size(); i++)
	{
		UpdatePolygons(i);
	}

}

void UpdatePolygons(int polygonIterator)
{
	Triangle polygon;
	for (int i = 0; i < 3; i++)
	{
		pointHomogeneous = polygons[polygonIterator].vectors[i];
		//pointHomogeneous = { vertexes[i].x, vertexes[i].y, vertexes[i].z, 1.0f };

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
	polygonsOutp[polygonIterator] = polygon;
}

void UpdateWindowSize(HWND hWnd)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	FrameHeight = clientRect.bottom - clientRect.top;
	FrameWidth = clientRect.right - clientRect.left;
}

//void BresenhamLineOptimised(void * buffer , CoordinateStruct vectorA, CoordinateStruct vectorB, RGBQUAD color)
void BresenhamLineOptimised(void * buffer , HomogeneousCoordinateStruct vectorA, HomogeneousCoordinateStruct vectorB, RGBQUAD color)
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
	int mat22 = 0;

	if (w < h)
	{
		(mat11, mat12) = (mat12, mat11);
		(mat21, mat22) = (mat22, mat21);
	}
	int y = 0;
	int error = 0;
	int errorDec = 2 * l;
	int errorInc = 2 * min(w, h);

	for (int x = 0; x <= l; x++)
	{
		int xt = x1 + mat11 * x + mat12 * y;
		int yt = y1 + mat21 * x + mat22 * y;
		SetPoint(buffer, xt, yt, color);

		if ((error += errorInc) > l)
		{
			error -= errorDec;
			y++;
		}
	}
}

void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	int deltaX = x1 - x0;
	int deltaY = y1 - y0;
	int absDeltaX = std::abs(deltaX);
	int absDeltaY = std::abs(deltaY);

	int accretion = 0;

	if (absDeltaX >= absDeltaY) // angle >45 ? 
	{
		int y = y0;
		int direction = deltaY != 0 ? (deltaY > 0 ? 1 : -1) : 0; //up or down
		for (int x = x0; deltaX > 0 ? x <= x1 : x >= x1; deltaX > 0 ? x++ : x--) //left or right
		{
			SetPoint(buffer, x, y, color);

			accretion += absDeltaY;

			if (accretion >= absDeltaX)
			{
				accretion -= absDeltaX;
				y += direction;
			}
		}
	}
	else
	{
		int x = x0;
		int direction = deltaX != 0 ? (deltaX > 0 ? 1 : -1) : 0;
		for (int y = y0; deltaY > 0 ? y <= y1 : y >= y1; deltaY > 0 ? y++ : y--)
		{
			SetPoint(buffer, x, y, color);

			accretion += absDeltaX;

			if (accretion >= absDeltaY)
			{
				accretion -= absDeltaY;
				x += direction;
			}
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

void plotLineWithErr(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	int dx = std::abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -std::abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;

	while (true) {
		SetPoint(buffer, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;

		int errorx2 = 2 * error;

		if (errorx2 >= dy) {
			if (x0 == x1)
				break;

			error += dy;
			x0 += sx;
		}

		if (errorx2 <= dx) {
			if (y0 == y1)
				break;

			error += dx;
			y0 += sy;
		}
	}
}