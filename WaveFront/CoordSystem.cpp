#include "CoordSystem.h"

HomogeneousCoordinateStruct CoordSystem::ToGlobalCoords(HomogeneousCoordinateStruct local)
{
	//return AddVectors((this->MultiplyMatByVector(GlobalTransformationMatrix,local)), Center);
	HomogeneousCoordinateStruct cent = { Center.x, Center.y, Center.z, 1.0f };
	return AddHomogeneousVectors((this->MultiplyMatByVector(GlobalTransformationMatrix, local)), cent);
}

CoordSystem::CoordSystem(CoordinateStruct Translation)
{
	GlobalTransformationMatrix = { XAxis.x, YAxis.x, ZAxis.x, Translation.x,
									XAxis.y, YAxis.y, ZAxis.y, Translation.y,
									XAxis.z, YAxis.z, ZAxis.z, Translation.z,
										0,		0,		 0,		 1 };

}

CoordinateStruct CoordSystem::SubstractVectors(CoordinateStruct& vector1, CoordinateStruct& vector2)
{
	CoordinateStruct result;
	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return result;
}

CoordinateStruct CoordSystem::MultiplyVectors(CoordinateStruct& vector1, CoordinateStruct& vector2)
{
	CoordinateStruct result;
	result.x = vector1.x * vector2.x;
	result.y = vector1.y * vector2.y;
	result.z = vector1.z * vector2.z;
	return result;
}

HomogeneousCoordinateStruct CoordSystem::MultiplyMatByVector(_3DMATRIX matrix, HomogeneousCoordinateStruct vector)
{
	float homogeneousVector[4] = { vector.x, vector.y, vector.z, 1.0f };
	float result[4];

	for (int i = 0; i < 4; i++) {
		result[i] = 0.0f;
		for (int j = 0; j < 4; j++) {
			result[i] += matrix.m[i][j] * homogeneousVector[j];
		}
	}

	return { result[0],result[1],result[2], result[3] };
}

_3DMATRIX CoordSystem::MultiplyMatrixByMatrix(const _3DMATRIX& matrix1, const _3DMATRIX& matrix2)
{
	_3DMATRIX result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] +
				matrix1.m[i][1] * matrix2.m[1][j] +
				matrix1.m[i][2] * matrix2.m[2][j] +
				matrix1.m[i][3] * matrix2.m[3][j];
		}
	}

	return result;
}

float CoordSystem::VectorLength(const CoordinateStruct& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

CoordinateStruct CoordSystem::NormalizeVector(const CoordinateStruct& vector)
{
	float vectorLength = VectorLength(vector);
	if (vectorLength > 0.0f) {
		float invLength = 1.0f / vectorLength; //  позволяет избежать повторного деления на одно и то же значение в каждой компоненте вектора.
		return { vector.x * invLength, vector.y * invLength, vector.z * invLength };
	}
	else {
		return vector;
	}
}

float CoordSystem::DotProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2) 
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

CoordinateStruct CoordSystem::CrossProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2) 
{
	CoordinateStruct result;
	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return result;
}

HomogeneousCoordinateStruct CoordSystem::TransformVector(HomogeneousCoordinateStruct& originalVector, CoordinateStruct& scale, float angle, CoordinateStruct& axis, CoordinateStruct& translation)
{
	SetScaleMatrix(scale);
	SetRotationMatrixOptimized(angle, axis);
	SetMovementMatrix(translation);
	_3DMATRIX ModelMatrix = MultiplyMatrixByMatrix(MovementMatrix, MultiplyMatrixByMatrix(RotationMatrix, ScaleMatrix));
	//HomogeneousCoordinateStruct res = MultiplyMatByVector(MovementMatrix , MultiplyMatByVector(RotationMatrix , MultiplyMatByVector(ScaleMatrix, originalVector)));
	HomogeneousCoordinateStruct res = MultiplyMatByVector(ModelMatrix, originalVector);
	return res;
}

void CoordSystem::SetCameraTransformationMatrix(CoordinateStruct& cameraGlobalCoord, CoordinateStruct& targetGlobalCoord, CoordinateStruct& cameraUpVect)
{
	ZAxis = NormalizeVector(SubstractVectors(cameraGlobalCoord, targetGlobalCoord));
	XAxis = NormalizeVector(CrossProduct(cameraUpVect, ZAxis));
	//YAxis = cameraUpVect; // ????
	YAxis = CrossProduct(ZAxis, XAxis);

	CameraTransformationMatrix =  { XAxis.x, XAxis.y, XAxis.z, -(DotProduct(XAxis,cameraGlobalCoord)),
									YAxis.x, YAxis.y, YAxis.z, -(DotProduct(YAxis,cameraGlobalCoord)),
									ZAxis.x, ZAxis.y, ZAxis.z, -(DotProduct(ZAxis,cameraGlobalCoord)),
										0,		0,		 0,		 1 };

}



void CoordSystem::MoveSystem(CoordinateStruct vect)
{
	Center = AddVectors(Center, vect);
}

void CoordSystem::SetMovementMatrix(CoordinateStruct Translation)
{
	MovementMatrix = { 1, 0, 0, Translation.x,
						0, 1, 0, Translation.y,
						0, 0, 1, Translation.z,
						0, 0, 0,	1 };
}

void CoordSystem::SetScaleMatrix(CoordinateStruct Scale)
{
	ScaleMatrix = { Scale.x,	0,				0,		0,
						0,			Scale.y,		0,		0,
						0,			0,			Scale.z,	0,
						0,			0,				0,		1 };
}

void CoordSystem::SetRotateXMatrix(float angle)
{
	RotateXMatrix = { 1,		0,			0,		0,
						0, cos(angle), -sin(angle), 0,
						0, sin(angle),	cos(angle),	0,
						0,		0,			0,		1 };
}

void CoordSystem::SetRotateYMatrix(float angle)
{
	RotateYMatrix = { cos(angle),		0,			sin(angle),		0,
						0,				1,				0,			0,
						-sin(angle),	0,			cos(angle),		0,
						0,				0,				0,			1 };
}

void CoordSystem::SetRotateZMatrix(float angle)
{
	RotateZMatrix = { cos(angle),		-sin(angle),0,0,
						sin(angle),		 cos(angle),0,0,
						0,					0,		1,0,
						0,					0,		0,1 };
}

void CoordSystem::SetRotateMatrix(float angle, CoordinateStruct axis)
{
	SetRotateXMatrix(angle);
	SetRotateYMatrix(angle);
	SetRotateZMatrix(angle);

	RotationMatrix = MultiplyMatrixByMatrix(MultiplyMatrixByMatrix(RotateXMatrix, RotateYMatrix), RotateZMatrix);
		// Нормализуем ось вращения
		float axisLength = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	CoordinateStruct normalizedAxis = { axis.x / axisLength, axis.y / axisLength, axis.z / axisLength };


}

void CoordSystem::SetRotationMatrixOptimized(float angle, const CoordinateStruct& axis) 
{
	float rcos = cos(angle);
	float rsin = sin(angle);

	float u = axis.x;
	float v = axis.y;
	float w = axis.z;

	RotationMatrix = { rcos + u * u * (1 - rcos), w * rsin + v * u * (1 - rcos), -v * rsin + w * u * (1 - rcos), 0.0f,
					   -w * rsin + u * v * (1 - rcos), rcos + v * v * (1 - rcos), u * rsin + w * v * (1 - rcos), 0.0f,
					   v * rsin + u * w * (1 - rcos), -u * rsin + v * w * (1 - rcos), rcos + w * w * (1 - rcos), 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f };

	/*rcos = cos(phi);
	rsin = sin(phi);
	matrix[0][0] = rcos + u * u * (1 - rcos);
	matrix[1][0] = w * rsin + v * u * (1 - rcos);
	matrix[2][0] = -v * rsin + w * u * (1 - rcos);
	matrix[0][1] = -w * rsin + u * v * (1 - rcos);
	matrix[1][1] = rcos + v * v * (1 - rcos);
	matrix[2][1] = u * rsin + w * v * (1 - rcos);
	matrix[0][2] = v * rsin + u * w * (1 - rcos);
	matrix[1][2] = -u * rsin + v * w * (1 - rcos);
	matrix[2][2] = rcos + w * w * (1 - rcos);*/
}

