#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "CoordSystem.h"
#include "TestGLM.h"



//#define FrameHeight 720
//#define FrameWidth 960
#define FrameHeight 600
#define FrameWidth 800

RGBQUAD frameBuffer[FrameHeight][FrameWidth];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void SetLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLineWithErr(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	std::vector<CoordinateStruct> v2;
	v2.push_back({ -0.1f, -0.1f, -0.1f });
	v2.push_back({ -0.1f, 0.1f, -0.1f });
	v2.push_back({ 0.1f, 0.1f, -0.1f });
	v2.push_back({ 0.1f, -0.1f, -0.1f });
	v2.push_back({ -0.1f, -0.1f, 0.1f });
	v2.push_back({ -0.1f, 0.1f, 0.1f });
	v2.push_back({ 0.1f, 0.1f, 0.1f });
	v2.push_back({ 0.1f, -0.1f, 0.1f });

	std::vector<int> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(6);
	indices.push_back(2);

	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(3);
	indices.push_back(7);

	ObjLoader* loader = new ObjLoader();
	CoordSystem* coord = new CoordSystem({ 10,20,20 });
	//CoordSystem* ViewCoord = new CoordSystem({ -3.0f,0.0f,0.0f });
	CoordSystem* cube = new CoordSystem({ 0.0f,0.0f,0.0f });

	//std::string res = loader->GetOutput();
	std::vector<CoordinateStruct> vertexes = loader->GetVetrexVector();
	std::vector<int> indexes = loader->GetIndexes();

	/*glm::vec4 inp;
	inp.x = vertexes[0].x;
	inp.y = vertexes[0].y;
	inp.z = vertexes[0].z;
	inp.w = 1;
	doMagic(inp);*/


	/////
	//cube->SetProjectionTransformationMatrix(45.0f, ((float)FrameWidth / (float)FrameHeight), 0.1f, 100.0f);
	cube->SetProjectionTransformationMatrix(3.14f / 2.0f, 800.0f / 600.0f, 10.0f, 100.0f);


	/*CoordinateStruct cameraGlobalCoord = {4,3,3};
	CoordinateStruct targetGlobalCoord = {0,0,0};
	CoordinateStruct cameraUpVect = {0,1,0};*/

	CoordinateStruct cameraGlobalCoord = { 0.05f,-0.2f,-0.5f };
	CoordinateStruct targetGlobalCoord = { 0,0,1 };
	CoordinateStruct cameraUpVect = { 0,1,0 };

	cube->SetCameraTransformationMatrix(cameraGlobalCoord, targetGlobalCoord, cameraUpVect);

	//cube->SetViewPortTransformationMatrix((float)FrameWidth, (float)FrameHeight, 0, 0);
	cube->SetViewPortTransformationMatrix(800.0f, 600.0f, 0, 0, 0.0f, 1.0f);

	//// Матрица проекции : 45° Угол обзора. 4:3 соотношение, дальность вида : 0.1 единиц <-> 100 единиц
	//glm::mat4 Projection = glm::perspective(40.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//// Матрица камеры
	//glm::mat4 View = glm::lookAt(
	//	glm::vec3(4, 10, 3), // Позиция в  (4,3,3)мировых координат
	//	glm::vec3(0, 0, 0), // И смотрит в центр экрана
	//	glm::vec3(0, 1, 0)  // Верх камеры смотрит вверх
	//);
	//// Матрица модели – единичная матрица. Модель находится в центре мировых координат
	//glm::mat4 Model = glm::mat4(1.0f);  // Выставляем свое значение для каждой модели!
	//// НАША МВП : Умножаем все наши три матрицы
	//glm::mat4 MVP = Projection * View * Model;

	//glm::mat4 ViewPort;
	//ViewPort[0][0] = 480;
	//ViewPort[0][1] = 0;
	//ViewPort[0][2] = 0;
	//ViewPort[0][3] = 480;

	//ViewPort[1][0] = 0;
	//ViewPort[1][1] = -360;
	//ViewPort[1][2] = 360;
	//ViewPort[1][3] = 0;

	//ViewPort[2][0] = 0;
	//ViewPort[2][1] = 0;
	//ViewPort[2][2] = 1;
	//ViewPort[2][3] = 0;

	//ViewPort[3][0] = 0;
	//ViewPort[3][1] = 0;
	//ViewPort[3][2] = 0;
	//ViewPort[3][3] = 1;

	//glm::mat4 viewPortRESULT = ViewPort * MVP;


	//_3DMATRIX sus = cube->CameraTransformationMatrix * cube->GlobalTransformationMatrix;
	//_3DMATRIX sus2 = cube->ProjectionTransformationMatrix * sus;
	//_3DMATRIX tmp = cube->MultiplyMatrixByMatrix(cube->CameraTransformationMatrix, cube->GlobalTransformationMatrix);
	//_3DMATRIX tmp2 = cube->MultiplyMatrixByMatrix(cube->ProjectionTransformationMatrix, tmp);
	//_3DMATRIX ModelViewProjectionMatrix = cube->MultiplyMatrixByMatrix(cube->ProjectionTransformationMatrix, cube->MultiplyMatrixByMatrix(cube->CameraTransformationMatrix, cube->GlobalTransformationMatrix));
	//_3DMATRIX ViewPortRESULTMatrix = cube->MultiplyMatrixByMatrix(cube->ViewPortTransformationMatrix, ModelViewProjectionMatrix);

	//for (int i = 0; i < vertexes.size(); i++)
	for (int i = 0; i < v2.size(); i++)
	{
		HomogeneousCoordinateStruct pointHomogeneous;
		/*pointHomogeneous.x = vertexes[i].x;
		pointHomogeneous.y = vertexes[i].y;
		pointHomogeneous.z = vertexes[i].z;*/

		pointHomogeneous.x = v2[i].x;
		pointHomogeneous.y = v2[i].y;
		pointHomogeneous.z = v2[i].z;
		pointHomogeneous.w = 1.0f;

		HomogeneousCoordinateStruct point = { vertexes[i].x, vertexes[i].y, vertexes[i].z, 1.0f };
		//point = cube->MultiplyMatByVector(ViewPortRESULTMatrix, point);
		//point = cube->MultiplyMatByVector(sus2, point);

		pointHomogeneous *= cube->GlobalTransformationMatrix;
		pointHomogeneous *= cube->CameraTransformationMatrix;
		pointHomogeneous *= cube->ProjectionTransformationMatrix;
		pointHomogeneous *= (1 / pointHomogeneous.w);
		pointHomogeneous *= cube->ViewPortTransformationMatrix;

		/*vertexes[i].x = point.x;
		vertexes[i].y = point.y;
		vertexes[i].z = point.z;
		*/
		v2[i].x = pointHomogeneous.x;
		v2[i].y = pointHomogeneous.y;
		v2[i].z = pointHomogeneous.z;

		/*vertexes[i].x = pointGLM.x;
		vertexes[i].y = pointGLM.y;
		vertexes[i].z = pointGLM.z;*/
	}
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
		L"Learn to Program Windows",    // Window text
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

	frameBuffer[10][200] = { 0, 255, 0, 0 };

	//SetLine(frameBuffer, 100, 100, 200, 200, { 255, 0, 0, 0 });
	/*plotLine(frameBuffer, 500, 100, 500, 300, { 255,0,0,0 });
	plotLine(frameBuffer, 150, 150, 350, 350, { 0,255,0,0 });
	plotLineWithErr(frameBuffer, 100, 200, 100, 400, { 0,255,0,0 });*/


	/*for (int i = 0; i < vertexes.size(); i++)
	{
		SetPoint(frameBuffer, vertexes[i].x, vertexes[i].y, { 0,255,0,0 });
	}*/


	/*for (int i = 0; i < indexes.size(); i += 3)
	{
		plotLine(frameBuffer, vertexes[indexes[i] - 1].x, vertexes[indexes[i] - 1].y, vertexes[indexes[i + 1] - 1].x, vertexes[indexes[i + 1] - 1].y, { 0,255,0,0 });
		plotLine(frameBuffer, vertexes[indexes[i + 1] - 1].x, vertexes[indexes[i + 1] - 1].y, vertexes[indexes[i + 2] - 1].x, vertexes[indexes[i + 2] - 1].y, { 0,255,0,0 });
		plotLine(frameBuffer, vertexes[indexes[i + 2] - 1].x, vertexes[indexes[i + 2] - 1].y, vertexes[indexes[i] - 1].x, vertexes[indexes[i] - 1].y, { 0,255,0,0 });
	}*/

	for (int i = 0; i < indices.size(); i += 3)
	{
		plotLine(frameBuffer, v2[indices[i]].x, v2[indices[i]].y, v2[indices[i + 1]].x, v2[indices[i + 1]].y, { 0,255,0,0 });
		plotLine(frameBuffer, v2[indices[i + 1]].x, v2[indices[i + 1]].y, v2[indices[i + 2]].x, v2[indices[i + 2]].y, { 0,255,0,0 });
		plotLine(frameBuffer, v2[indices[i + 2]].x, v2[indices[i + 2]].y, v2[indices[i]].x, v2[indices[i]].y, { 0,255,0,0 });
	}

	//std::vector<CoordinateStruct> vertexes1 = { {100,100,200},{100,200,200},{200,100,200}, {200,200,200},{200,110,200},{110,200,200} };
	/*for (int i = 0; i < 6; i += 3)
	{
		plotLine(frameBuffer, vertexes1[i].x, vertexes1[i].y, vertexes1[i + 1].x, vertexes1[i + 1].y, { 0,255,0,0 });
		plotLine(frameBuffer, vertexes1[i + 1].x, vertexes1[i + 1].y, vertexes1[i + 2].x, vertexes1[i + 2].y, { 0,255,0,0 });
		plotLine(frameBuffer, vertexes1[i + 2].x, vertexes1[i + 2].y, vertexes1[i].x, vertexes1[i].y, { 0,255,0,0 });
	}*/
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