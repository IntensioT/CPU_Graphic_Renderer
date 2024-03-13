#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "CoordSystem.h"

struct Triangle
{
	HomogeneousCoordinateStruct vectors[3];
};

Triangle GetTriangle(std::vector<HomogeneousCoordinateStruct> vec, std::vector<int> indicies, std::vector<int> normalIndicies, std::vector<CoordinateStruct> normals);
//std::vector<Triangle> GetAllPolygons(std::vector<HomogeneousCoordinateStruct> vectors, std::vector<int> indicies);
std::vector<Triangle> GetAllPolygons(std::vector<HomogeneousCoordinateStruct> vectors, std::vector<int> indicies, std::vector<int> normalIndicies, std::vector<CoordinateStruct> normals);
void SwapVectorsInPolygon(Triangle polygon, int indVec1, int indVec2);

#endif