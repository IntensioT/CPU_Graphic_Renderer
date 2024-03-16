#pragma once

struct CoordinateStruct
{
	float x, y, z;

	CoordinateStruct operator-(const CoordinateStruct& other) const {
		return CoordinateStruct{ x - other.x, y - other.y, z - other.z };
	}
};