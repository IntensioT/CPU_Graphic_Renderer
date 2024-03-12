#ifndef RASTERIZATOR_H
#define RASTERIZATOR_H


#include "Triangle.h"



class Rasterizator
{
public:
	//std::vector<float> zInterpolated;
	float zInterpolated[1080][1920];

	int isLeft;


	std::vector<float> Interpolate(float x0, float y0, float x1, float y1);
	std::vector<float> xLeft, xRight, zLeft, zRight, hLeft, hRight;
	void UpdateXleftAndXRight(Triangle& polygon);

private:
	void SortYPoints(Triangle& polygon);
	Triangle correctOrdinary(Triangle polygon);
	void getXleftAndRight(Triangle polygon);
	void getZLeftAndZRight(Triangle polygon);
	void getHLeftAndHRight(Triangle polygon);
};

#endif