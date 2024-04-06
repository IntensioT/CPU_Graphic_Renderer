#pragma once
#include "3DVectorStruct.h"
#include "PointLightStruct.h"
#include <vector>



CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings);
CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings, float specularWeight);
CoordinateStruct GetReflectionDirection(const CoordinateStruct& lightDirection, const CoordinateStruct& hitNormal);
