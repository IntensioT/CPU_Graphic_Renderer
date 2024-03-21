#pragma once

struct CoordinateStruct
{
	float x, y, z;

	CoordinateStruct operator*(const CoordinateStruct& other) const {
		return CoordinateStruct{ x * other.x, y * other.y, z * other.z };
	}
	CoordinateStruct operator*(const float other) const {
		return CoordinateStruct{ x * other, y * other, z * other };
	}
	CoordinateStruct operator-(const CoordinateStruct& other) const {
		return CoordinateStruct{ x - other.x, y - other.y, z - other.z };
	}
	CoordinateStruct operator-(const float other) const {
		return CoordinateStruct{ x - other, y - other, z - other };
	}
};