#pragma once

#include "CoordSystem.h"

struct Triangle
{
	CoordinateStruct vectors[3];

};

Triangle GetTriangle(std::vector<CoordinateStruct> vec, std::vector<int> indicies);
std::vector<Triangle> GetAllPolygons(std::vector<CoordinateStruct> vectors, std::vector<int> indicies);