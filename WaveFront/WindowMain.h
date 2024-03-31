#pragma once

#include <concurrent_vector.h>
#include <ppl.h>
#include <omp.h>


#include "ThreadPool.h"
#include "Rasterizator.h"

#include "GlobalParams.h"

#include "TextureLoader.h"


#define WIDTH 1920
#define HEIGHT 1080

LONG FrameHeight = 720, FrameWidth = 1280;

int prevMouseX, prevMouseY;
bool mouseDown = false;

const float updateInterval = 1.f; // Update FPS
float accumulatedTime = 0.0f;
int fps = 0;
int frameCount = 0;



RGBQUAD frameBuffer[1080][1920];
float depthBuffer[1080][1920];

//RGBQUAD color = { 255, 255, 255, 0 };
RGBQUAD color = { 200, 200, 200, 0 };
RGBQUAD color2 = { 0, 0, 255, 0 };

CoordinateStruct cameraGlobalCoord;
CoordinateStruct targetGlobalCoord = { 0,0.6f,0.f };
//CoordinateStruct targetGlobalCoord = { 0,50.f,0.f };
//CoordinateStruct targetGlobalCoord = { 0,100.f,0.f };

CoordinateStruct lightGlobalCoord = { 10.f,15.f,500.f };

PointLightStruct light1;

CoordinateStruct DiffuseLightColor = { 204,204,204 };
CoordinateStruct SpecularLightColor = { 51,51,51 };


std::vector<PointLightStruct> Lightnings;




std::vector<CoordinateStruct> vertexes;
std::vector<HomogeneousCoordinateStruct> vertexesOutp;
std::vector<Triangle> polygons;
//std::vector<Triangle> polygonsOutp;
concurrency::concurrent_vector<Triangle> polygonsOutp;
std::vector<int> indexes;
std::vector<int> normalIndexes;
std::vector<CoordinateStruct> normals;
std::vector<int> textureIndicies;
std::vector<CoordinateStruct> textures;
std::vector<TextureStruct> textureDatas;

CoordSystem* modelCoordSystem;
Rasterizator* rasterizator;

std::mutex polygonsMutex, polygonOutputMutex;

float vectorCount = 0.333333333333333f;


float yAngleObject = 0.0f;
float xAngleObject = 0.0f;
float xCamera = 0.0f;
float yCamera = 0.0f;
//float zCamera = 4.f;
float zCamera = 250.5f;
//float zCamera = 10.5f;
float rSphere = zCamera;
float phiAngleSphere = 0.0f;
float thetaAngleSphere = 90.0f;

float zNear = 10.0f;
float zFar = 100.0f;

int curGraphic = 1;

float coordSpeed = 3.f;
float angleSpeed = 5.f;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowFrame(unsigned int width, unsigned int height, void* pixels, HWND hWnd);
void SetPoint(void* buffer, int x, int y, RGBQUAD color = { 0,0,0,0 });
void plotLine(void* buffer, int x0, int y0, int x1, int y1, RGBQUAD color);
void Render();
bool ClipFacePolygons(int polygonIterator);
void UpdateNormals();
void UpdateVectors();
void UpdateWindowSize(HWND hWnd);
bool UpdatePolygons(int polygonIterator);
void BresenhamLineOptimised(void* buffer, HomogeneousCoordinateStruct vectorA, HomogeneousCoordinateStruct vectorB, RGBQUAD color);
void UpdatePolygonsAsync();
void DrawPolygonsAsync();

double getElapsedTime();


bool IsObjectBehindClipPlanes(int polygonIterator, const std::vector<Plane>& clipPlanes);
void DrawObject(int i);
void DrawTriangle(Triangle& triangle);


Triangle CalculateLambertTermAndShade(int polygonIterator, int vectorIterator, CoordinateStruct curVector, Triangle inputPolygon);
