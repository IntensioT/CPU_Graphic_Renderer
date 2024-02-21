#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "CoordSystem.h"
//#include "TestGLM.h"


#define FrameHeight 720
#define FrameWidth 1280



//RECT clientRect;
//LONG FrameHeight, FrameWidth;

RGBQUAD frameBuffer[FrameHeight][FrameWidth];
//RGBQUAD frameBuffer[720][1280];

RGBQUAD color = { 255, 255, 255, 0 };


std::vector<CoordinateStruct> vertexes;
std::vector<HomogeneousCoordinateStruct> vertexesOutp;
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
float thetaAngleSphere = 0.0f;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLineWithErr(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void Render();
void UpdateVectors();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ObjLoader* loader = new ObjLoader();
	//CoordSystem* coord = new CoordSystem({ 10,20,20 });
	//CoordSystem* ViewCoord = new CoordSystem({ -3.0f,0.0f,0.0f });
	modelCoordSystem = new CoordSystem({ 0.0f,0.0f,0.0f });

	//std::string res = loader->GetOutput();
	vertexes = loader->GetVetrexVector();
	indexes = loader->GetIndexes();

	vertexesOutp.resize(vertexes.size());


	/////
	
	//UpdateVectors();
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

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		Render();
		ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);
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
			/*Render();
			ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);*/
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key. 
			yAngleObject += 5.0f;
			/*Render();
			ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);*/
			return 0;

		case VK_UP:
			// Process the UP ARROW key. 
			xAngleObject += 5.0f;
			/*Render();
			ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);*/
			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			xAngleObject -= 5.0f;
			return 0;

		case 'W':
			zCamera += 0.05f;
			return 0;

		case 'S':
			zCamera -= 0.05f;
			return 0;

		case 'Z':
			phiAngleSphere += 5.f;
			return 0;

		case 'X':
			phiAngleSphere -= 5.f;
			return 0;

		case 'C':
			thetaAngleSphere += 5.f;
			return 0;

		case 'V':
			thetaAngleSphere -= 5.f;
			return 0;
		}
		
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}

void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd)
{
	HBITMAP hBitMap = CreateBitmap(width, height, 1, 8 * 4, pixels);  //CreateCompatibleBitmap  � ������� ����� ������� 
	/*
	  [in] nPlanes
	  ���������� �������� ����������, ������������ �����������.
	  [in] nBitCount (4 �����)
	  ���������� �����, ����������� ��� ������������� ����� ������ �������.
	 */

	HDC hdc = GetDC(hWnd);

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
{
	if (x >= 0 && x <= static_cast<int>(FrameWidth - 1) && y >= 0 && y <= static_cast<int>(FrameHeight - 1))
	{
		reinterpret_cast<RGBQUAD*>(buffer)[y * FrameWidth + x] = color;
	}
}

void Render()
{
	std::memset(frameBuffer, 0, sizeof(frameBuffer));

	UpdateVectors();

	for (int i = 0; i < indexes.size(); i += 3)
	{
		/*plotLine(frameBuffer, vertexesOutp[indexes[i] - 1].x, vertexes[indexes[i] - 1].y, vertexes[indexes[i + 1] - 1].x, vertexes[indexes[i + 1] - 1].y, { 255,255,255,0 });
		plotLine(frameBuffer, vertexes[indexes[i + 1] - 1].x, vertexes[indexes[i + 1] - 1].y, vertexes[indexes[i + 2] - 1].x, vertexes[indexes[i + 2] - 1].y, { 255,255,255,0 });
		plotLine(frameBuffer, vertexes[indexes[i + 2] - 1].x, vertexes[indexes[i + 2] - 1].y, vertexes[indexes[i] - 1].x, vertexes[indexes[i] - 1].y, { 255,255,255,0 });*/

		plotLine(frameBuffer, vertexesOutp[indexes[i] - 1].x, vertexesOutp[indexes[i] - 1].y,
			vertexesOutp[indexes[i + 1] - 1].x, vertexesOutp[indexes[i + 1] - 1].y, color);

		plotLine(frameBuffer, vertexesOutp[indexes[i + 1] - 1].x, vertexesOutp[indexes[i + 1] - 1].y,
			vertexesOutp[indexes[i + 2] - 1].x, vertexesOutp[indexes[i + 2] - 1].y, color);

		plotLine(frameBuffer, vertexesOutp[indexes[i + 2] - 1].x, vertexesOutp[indexes[i + 2] - 1].y,
			vertexesOutp[indexes[i] - 1].x, vertexesOutp[indexes[i] - 1].y, color);
	}
}

void UpdateVectors()
{
	modelCoordSystem->SetRotateYMatrix(GetRadians(yAngleObject));
	modelCoordSystem->SetRotateXMatrix(GetRadians(xAngleObject));
	modelCoordSystem->GlobalTransformationMatrix = modelCoordSystem->RotateYMatrix * modelCoordSystem->RotateXMatrix;

	modelCoordSystem->SetProjectionTransformationMatrix(45.0f, ((float)FrameWidth / (float)FrameHeight), 10.0f, 100.0f);

	CoordinateStruct cameraGlobalCoord = { SphericalToCartesian(rSphere, phiAngleSphere, thetaAngleSphere)};
	//CoordinateStruct cameraGlobalCoord = { xCamera,yCamera,zCamera };
	//CoordinateStruct cameraGlobalCoord = { 0.0f,0.f,-5.0f };
	CoordinateStruct targetGlobalCoord = { 0,0.3f,0.5f };
	CoordinateStruct cameraUpVect = { 0,1,0 };
	modelCoordSystem->SetCameraTransformationMatrix(cameraGlobalCoord, targetGlobalCoord, cameraUpVect);

	modelCoordSystem->SetViewPortTransformationMatrix((float)FrameWidth, (float)FrameHeight, 0, 0, 0.0f, 1.0f);

	for (int i = 0; i < vertexes.size(); i++)
	{
		pointHomogeneous = { vertexes[i].x, vertexes[i].y, vertexes[i].z, 1.0f };

		pointHomogeneous *= modelCoordSystem->GlobalTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->CameraTransformationMatrix;
		pointHomogeneous *= modelCoordSystem->ProjectionTransformationMatrix;
		pointHomogeneous *= (1 / pointHomogeneous.w);
		pointHomogeneous *= modelCoordSystem->ViewPortTransformationMatrix;


		vertexesOutp[i] = pointHomogeneous;
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