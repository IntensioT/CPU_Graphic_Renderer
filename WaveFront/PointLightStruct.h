#pragma once

#ifndef _POINT_LIGHT_STRUCT_H_
#define _POINT_LIGHT_STRUCT_H_


#include "MathLogic.h"

struct PointLightStruct
{
	CoordinateStruct globalPosition;

	float objectAlbedo; //  base color input that defines the diffuse color or reflectivity of the surface
	float PhongDiffuseWeight; // phong model diffuse weight
	float PhongSpecularWeight; // phong model specular weight
	float PhongSpecularExponent;   // phong specular exponent

	CoordinateStruct DiffuseLightColor;
	CoordinateStruct SpecularLightColor;
    CoordinateStruct LightColor;
	float LightIntesity;

	void illuminate(const CoordinateStruct& Point, CoordinateStruct& lightDirection, CoordinateStruct& lightIntensity/*, float& distance*/) const; // struct fields will stay const
};

//float CalculatePhongHitColor();

#endif // ! _POINT_LIGHT_STRUCT_H_
