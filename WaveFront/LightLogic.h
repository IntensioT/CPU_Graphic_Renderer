#pragma once
#include "3DVectorStruct.h"
#include "PointLightStruct.h"
#include <vector>



CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings);
CoordinateStruct calculatePBRLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings, 
	float albedo, float metallic, float roughness, float ambientOcclusion);
CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings, float specularWeight);
CoordinateStruct GetReflectionDirection(const CoordinateStruct& lightDirection, const CoordinateStruct& hitNormal);

CoordinateStruct fresnelSchlick(float cosTheta, CoordinateStruct F0);
