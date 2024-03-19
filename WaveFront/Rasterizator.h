#ifndef RASTERIZATOR_H
#define RASTERIZATOR_H


#include "Triangle.h"
#include "Rectangle2D.h"
#include "MathLogic.h"

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
	void DrawLines(Triangle polygon, RGBQUAD(&frameBuffer)[1080][1920], float(&depthBuffer)[1080][1920], RGBQUAD color);
	void DrawPolygon(Triangle polygon, RGBQUAD(&frameBuffer)[1080][1920], float(&depthBuffer)[1080][1920], RGBQUAD color);
	


private:
	bool IsInTriangle(float x, float y, Triangle polygon);

	void SortYPoints(Triangle& polygon);
	Triangle correctOrdinary(Triangle polygon);
	void getXleftAndRight(Triangle polygon);
	void getZLeftAndZRight(Triangle polygon);
	void getHLeftAndHRight(Triangle polygon);
};

#endif