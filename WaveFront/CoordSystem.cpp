#include "CoordSystem.h"

HomogeneousCoordinateStruct CoordSystem::ToGlobalCoords(HomogeneousCoordinateStruct local)
{
	//return AddVectors((this->MultiplyMatByVector(GlobalTransformationMatrix,local)), Center);
	HomogeneousCoordinateStruct cent = { Center.x, Center.y, Center.z, 1.0f };
	return AddHomogeneousVectors((this->MultiplyMatByVector(GlobalTransformationMatrix, local)), cent);
}

CoordSystem::CoordSystem(CoordinateStruct Translation)
{
	GlobalTransformationMatrix = {	XAxis.x, YAxis.x, ZAxis.x, Translation.x,
									XAxis.y, YAxis.y, ZAxis.y, Translation.y,
									XAxis.z, YAxis.z, ZAxis.z, Translation.z,
										0,		0,		 0,		 1 };

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

	return { result[0],result[1],result[2], result[3]};
}

void CoordSystem::MoveSystem(CoordinateStruct vect)
{
	Center = AddVectors(Center, vect);
}

void CoordSystem::SetMovementMatrix(CoordinateStruct Translation)
{
	MovementMatrix = {	1, 0, 0, Translation.x,
						0, 1, 0, Translation.y,
						0, 0, 1, Translation.z,
						0, 0, 0,	1 };
}

void CoordSystem::SetScaleMatrix(CoordinateStruct Scale)
{
	ScaleMatrix = {		Scale.x,	0,				0,		0,
						0,			Scale.y,		0,		0,
						0,			0,			Scale.z,	0,
						0,			0,				0,		1 };
}

void CoordSystem::SetRotateXMatrix(float angle)
{
	RotateXMatrix = {	1,		0,			0,		0,
						0, cos(angle), -sin(angle), 0,
						0, sin(angle),	cos(angle),	0,
						0,		0,			0,		1 };
}

void CoordSystem::SetRotateYMatrix(float angle)
{
	RotateYMatrix = {	cos(angle),		0,			sin(angle),		0,
						0,				1,				0,			0,
						-sin(angle),	0,			cos(angle),		0,
						0,				0,				0,			1 };
}

void CoordSystem::SetRotateZMatrix(float angle)
{
	RotateZMatrix = {	cos(angle),		-sin(angle),0,0,
						sin(angle),		 cos(angle),0,0,
						0,					0,		1,0,
						0,					0,		0,1 };
}

