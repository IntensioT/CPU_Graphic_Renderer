#include "3DVectorStruct.h"

CoordinateStruct CoordinateStruct::operator*(const CoordinateStruct& other) const
{
	return CoordinateStruct{ x * other.x, y * other.y, z * other.z };
}

CoordinateStruct CoordinateStruct::operator*(const float other) const
{
	return CoordinateStruct{ x * other, y * other, z * other };
}

CoordinateStruct CoordinateStruct::operator/(const float other) const
{
	return CoordinateStruct{ x / other, y / other, z / other };
}

CoordinateStruct CoordinateStruct::operator+(const CoordinateStruct& other) const
{
	return { x + other.x, y + other.y, z + other.z };
}

CoordinateStruct CoordinateStruct::operator+(const float& other) const
{
	return { x + other, y + other, z + other };
}

CoordinateStruct CoordinateStruct::operator+=(const CoordinateStruct& other )
{
	return { x + other.x, y + other.y, z + other.z };
}

CoordinateStruct CoordinateStruct::operator-(const CoordinateStruct& other) const
{
	return CoordinateStruct{ x - other.x, y - other.y, z - other.z };
}

CoordinateStruct CoordinateStruct::operator-(const float other) const
{
	return CoordinateStruct{ x - other, y - other, z - other };
}
