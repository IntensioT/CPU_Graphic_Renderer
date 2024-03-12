#pragma once

#include <windows.h>
#include "CoordSystem.h"
#include "Triangle.h"
#include "ThreadPool.h"
#include "Rasterizator.h"



LONG FrameHeight = 720, FrameWidth = 1280;

RGBQUAD frameBuffer[1080][1920];
float depthBuffer[1080][1920];


RGBQUAD color = { 255, 255, 255, 0 };
RGBQUAD color2 = { 0, 0, 255, 0 };

CoordinateStruct cameraGlobalCoord;
CoordinateStruct targetGlobalCoord = { 0,0.6f,0.f };



std::vector<CoordinateStruct> vertexes;
std::vector<HomogeneousCoordinateStruct> vertexesOutp;
std::vector<Triangle> polygons;
std::vector<Triangle> polygonsOutp;
std::vector<int> indexes;
std::vector<int> normalIndexes;
std::vector<CoordinateStruct> normals;
//HomogeneousCoordinateStruct pointHomogeneous;
CoordSystem* modelCoordSystem;
Rasterizator* rasterizator;


float yAngleObject = 0.0f;
float xAngleObject = 0.0f;
float xCamera = 0.0f;
float yCamera = 0.0f;
float zCamera = 3.5f;
float rSphere = zCamera;
float phiAngleSphere = 0.0f;
float thetaAngleSphere = 90.0f;

float zNear = 10.0f;
float zFar = 100.0f;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void plotLineWithErr(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void Render();
void UpdateVectors();
void UpdateWindowSize(HWND hWnd);
//void UpdatePolygons(int polygonIterator);
bool UpdatePolygons(int polygonIterator);
void BresenhamLineOptimised(void* buffer, HomogeneousCoordinateStruct vectorA, HomogeneousCoordinateStruct vectorB, RGBQUAD color);
void UpdatePolygonsAsync();

bool IsObjectBehindClipPlanes(int polygonIterator, const std::vector<Plane>& clipPlanes);
void DrawObject(int i);
