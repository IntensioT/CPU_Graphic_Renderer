#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "CoordSystem.h"

struct Triangle
{
	HomogeneousCoordinateStruct vectors[3];
	HomogeneousCoordinateStruct vectorsInGlobal[3];
	HomogeneousCoordinateStruct polygonNormal;
	HomogeneousCoordinateStruct polygonCenter;

	bool isOnScreen;

	int textureId;
};

void AddTriangle(std::vector<Triangle>& triangles,const std::vector<HomogeneousCoordinateStruct>& homogeneousCoordinates,
				const std::vector<int>& vertexIndices, const std::vector<int>& normalIndices,const std::vector<CoordinateStruct>& normalVectors,int index);

std::vector<Triangle> GetAllTriangles(const std::vector<HomogeneousCoordinateStruct>& homogeneousCoordinates,const std::vector<int>& vertexIndices,
									const std::vector<int>& normalIndices,const std::vector<CoordinateStruct>& normalVectors);

Triangle GetTriangle(std::vector<HomogeneousCoordinateStruct> vec, std::vector<int> indicies, std::vector<int> normalIndicies, std::vector<CoordinateStruct> normals);
//std::vector<Triangle> GetAllPolygons(std::vector<HomogeneousCoordinateStruct> vectors, std::vector<int> indicies);
std::vector<Triangle> GetAllPolygons(std::vector<HomogeneousCoordinateStruct> vectors, std::vector<int> indicies, std::vector<int> normalIndicies, std::vector<CoordinateStruct> normals);
void SwapVectorsInPolygon(Triangle polygon, int indVec1, int indVec2);

#endif