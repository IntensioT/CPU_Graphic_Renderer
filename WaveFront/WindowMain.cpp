#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "ObjLoader.h"

#define FrameHeight 720
#define FrameWidth 1425

RGBQUAD frameBuffer[FrameHeight][FrameWidth];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ObjLoader* loader = new ObjLoader();

	//std::string res = loader->GetOutput();
	std::vector<CoordinateStruct> vertexes = loader->GetVetrexVector();
	std::vector<int> indexes = loader->GetIndexes();


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
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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

	frameBuffer[10][200] = { 0, 255, 0, 0 };

	SetLine(frameBuffer, 100, 100, 200, 200, { 255, 0, 0, 0 });
	//SetPoint(frameBuffer, 200, 9, {0,0,255, 0});

	// Run the message loop.

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

	case WM_PAINT:
	{
		ShowFrame(FrameWidth, FrameHeight, frameBuffer, hwnd);
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
	if (x >= 0 && x <= static_cast<int>(FrameWidth - 1) && y >= 0 && y <= static_cast<int>(FrameHeight - 1))
	{
		reinterpret_cast<RGBQUAD*>(buffer)[y * FrameWidth + x] = color;
	}
}

void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color)
{
	int deltaX = std::abs(x1 - x0);
	int deltaY = std::abs(y1 - y0);

	double error = 0;
	double deltaerr = (deltaY + 1) / static_cast<double>(deltaX + 1);

	int y = y0;

	int directionY = y1 - y0;
	if (directionY > 0)
	{
		directionY = 1;
	}
	else if (directionY < 0)
	{
		directionY = -1;
	}


	for (int x = x0; x <= x1; x++)
	{
		SetPoint(buffer, x, y, color);
		error = error + deltaerr;
		if (error >= (deltaX + 1))
		{
			y += directionY;
			error -= (deltaX + 1);
		}
	}
}
