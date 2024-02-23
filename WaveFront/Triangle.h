#pragma once

#include "CoordSystem.h"

struct Triangle
{
	HomogeneousCoordinateStruct vectors[3];

};

Triangle GetTriangle(std::vector<HomogeneousCoordinateStruct> vec, std::vector<int> indicies);
std::vector<Triangle> GetAllPolygons(std::vector<HomogeneousCoordinateStruct> vectors, std::vector<int> indicies);