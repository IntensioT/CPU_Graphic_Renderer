#ifndef RASTERIZATOR_H
#define RASTERIZATOR_H


#include "Triangle.h"



class Rasterizator
{
public:

	//CoordinateStruct DiffuseMaterialColor = { 0.8f,0.8f,0.8f };
	//CoordinateStruct DiffuseLightColor = { 255,255,255 };

	float zInterpolated[1080][1920];

	int isLeft;


	std::vector<float> Interpolate(float x0, float y0, float x1, float y1);
std::vector<float> xLeft, xRight, zLeft, zRight, hLeft, hRight, diffuseLeft, diffuseRight;
	void UpdateXleftAndXRight(Triangle& polygon);
	//CoordinateStruct LambertShading(CoordSystem* modelCoord, Triangle curPolygon,CoordinateStruct lightPos, CoordinateStruct CameraGlobalCoordinates);

private:


	void SortYPoints(Triangle& polygon);
	Triangle correctOrdinary(Triangle polygon);
	void getXleftAndRight(Triangle polygon);
	void getZLeftAndZRight(Triangle polygon);
	void getHLeftAndHRight(Triangle polygon);
	void getDiffuseLeftAndDiffuseRight(Triangle polygon);
};

#endif