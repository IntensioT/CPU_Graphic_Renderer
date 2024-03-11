#ifndef RASTERIZATOR_H
#define RASTERIZATOR_H


#include "Triangle.h"



class Rasterizator
{
public:
	Rasterizator(int width, int height);
	//std::vector<float> zInterpolated;
	float zInterpolated[1080][1920];

	int isLeft;


	std::vector<std::vector<float>> zBuffer;

	std::vector<float> Interpolate(float x0, float y0, float x1, float y1);
	std::vector<float> xLeft, xRight, zLeft, zRight;
	void UpdateXleftAndXRight(Triangle& polygon);

private:
	void SortYPoints(Triangle& polygon);
	Triangle correctOrdinary(Triangle polygon);
	void getXleftAndRight(Triangle polygon);
	void getZLeftAndZRight(Triangle polygon);
};

#endif