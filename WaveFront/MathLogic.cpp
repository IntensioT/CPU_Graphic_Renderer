#include "MathLogic.h"

float GetVectorLength(const HomogeneousCoordinateStruct& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

HomogeneousCoordinateStruct addZeroToGetHomogeneous(const CoordinateStruct& vector)
{
	return { vector.x, vector.y, vector.z, 0 };
}

HomogeneousCoordinateStruct Normalize(const HomogeneousCoordinateStruct& vector)
{
	float vectorLength = GetVectorLength(vector);
	if (vectorLength > 0.0f) {
		float invLength = 1.0f / vectorLength; //  позволяет избежать повторного деления на одно и то же значение в каждой компоненте вектора.
		return { vector.x * invLength, vector.y * invLength, vector.z * invLength };
	}
	else {
		return vector;
	}
}

CoordinateStruct Normalize(const CoordinateStruct& vector)
{
	float vectorLength = GetVectorLength(addZeroToGetHomogeneous(vector));
	if (vectorLength > 0.0f) {
		float invLength = 1.0f / vectorLength; //  позволяет избежать повторного деления на одно и то же значение в каждой компоненте вектора.
		return { vector.x * invLength, vector.y * invLength, vector.z * invLength };
	}
	else {
		return vector;
	}
}

float DotProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

float DotProduct(const HomogeneousCoordinateStruct& vector1, const HomogeneousCoordinateStruct& vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

CoordinateStruct SubstractVectors(CoordinateStruct& vector1, CoordinateStruct& vector2)
{
	CoordinateStruct result;
	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return result;
}

CoordinateStruct ReverseVector(const CoordinateStruct& vector)
{
	return {-vector.x, -vector.y, -vector.z};
}
