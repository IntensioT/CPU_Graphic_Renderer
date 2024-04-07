#ifndef RASTERIZATOR_H
#define RASTERIZATOR_H


#include "Triangle.h"
#include "Rectangle2D.h"
#include "MathLogic.h"

#include "LightLogic.h"
#include "TextureStruct.h"

#include <windows.h>


inline void SetPoint(void* buffer, int x, int y, RGBQUAD color);

RectangleStruct FindTriangleBoundingRectangle2D(Triangle polygon);


class Rasterizator
{
public:

	float zInterpolated[1080][1920];

	int isLeft;


	std::vector<float> Interpolate(float x0, float y0, float x1, float y1);
	std::vector<float> xLeft, xRight, zLeft, zRight, hLeft, hRight, diffuseLeft, diffuseRight;
	void UpdateXleftAndXRight(Triangle& polygon);
	void DrawLines(Triangle polygon, void* frameBuffer, void* depthBuffer, RGBQUAD color);
	void DrawPolygon(Triangle polygon, void* frameBuffer, void* depthBuffer, RGBQUAD color);
	void DrawPolygonBarycentric(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color);
	void DrawPolygonBarycentricTexture(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture);
	void DrawPolygonBarycentricTextureWithLight(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture);
	void DrawPolygonBarycentricTextureWithBillinearFiltration(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture);
	void DrawPolygonBarycentricParam(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture);
	void DrawPolygonBarycentricLast(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture);



private:
	RGBQUAD PhongLight();

	bool IsTopLeft(const Triangle& polygon);
	bool IsInTriangle(float x, float y, Triangle polygon);
	bool IsInPolygon(float x, float y, const Triangle& polygon);

	void SortYPoints(Triangle& polygon);
	Triangle correctOrdinary(Triangle polygon);
	void getXleftAndRight(Triangle polygon);
	void getZLeftAndZRight(Triangle polygon);
	void getHLeftAndHRight(Triangle polygon);
};

#endif