#include "Triangle.h"

Triangle GetTriangle(std::vector<CoordinateStruct> vec, std::vector<int> indicies)
{
	Triangle result;

	for (int i = 0; i < 3; i++)
	{
		result.vectors[i] = vec[indicies[i] - 1];
	}

	return result;
}

std::vector<Triangle> GetAllPolygons(std::vector<CoordinateStruct> vectors, std::vector<int> indicies)
{
	std::vector<Triangle> triangles;

	for (int i = 0; i < indicies.size(); i+=3)
	{
		triangles.push_back(GetTriangle(vectors, { indicies[i], indicies[i + 1], indicies[i + 2] }));
	}

	return triangles;
}
