#include "Mat3Struct.h"

CoordinateStruct Mat3Struct::operator*(const CoordinateStruct& vect)
{
	CoordinateStruct result = {0,0,0};
	for (int i = 0; i < 3; i++) {
		result.x += m[i][0] * vect.x;
		result.y += m[i][1] * vect.y;
		result.z += m[i][2] * vect.z;
	}
	return result;
}

// ¬ычисление обратной матрицы дл€ TBN
Mat3Struct Mat3Struct::Inverse(const Mat3Struct& TBN)
{
	float determinant = TBN.m[0][0] * (TBN.m[1][1] * TBN.m[2][2] - TBN.m[1][2] * TBN.m[2][1]) -
		TBN.m[0][1] * (TBN.m[1][0] * TBN.m[2][2] - TBN.m[1][2] * TBN.m[2][0]) +
		TBN.m[0][2] * (TBN.m[1][0] * TBN.m[2][1] - TBN.m[1][1] * TBN.m[2][0]);

	Mat3Struct inverse;
	inverse.m[0][0] = (TBN.m[1][1] * TBN.m[2][2] - TBN.m[1][2] * TBN.m[2][1]) / determinant;
	inverse.m[0][1] = (TBN.m[0][2] * TBN.m[2][1] - TBN.m[0][1] * TBN.m[2][2]) / determinant;
	inverse.m[0][2] = (TBN.m[0][1] * TBN.m[1][2] - TBN.m[0][2] * TBN.m[1][1]) / determinant;
	inverse.m[1][0] = (TBN.m[1][2] * TBN.m[2][0] - TBN.m[1][0] * TBN.m[2][2]) / determinant;
	inverse.m[1][1] = (TBN.m[0][0] * TBN.m[2][2] - TBN.m[0][2] * TBN.m[2][0]) / determinant;
	inverse.m[1][2] = (TBN.m[1][0] * TBN.m[0][2] - TBN.m[0][0] * TBN.m[1][2]) / determinant;
	inverse.m[2][0] = (TBN.m[1][0] * TBN.m[2][1] - TBN.m[1][1] * TBN.m[2][0]) / determinant;
	inverse.m[2][1] = (TBN.m[0][1] * TBN.m[2][0] - TBN.m[0][0] * TBN.m[2][1]) / determinant;
	inverse.m[2][2] = (TBN.m[0][0] * TBN.m[1][1] - TBN.m[0][1] * TBN.m[1][0]) / determinant;

	return inverse;
}

// ¬ычисление транспонированной матрицы дл€ TBN
Mat3Struct Mat3Struct::Transpose(const Mat3Struct& TBN)
{
	Mat3Struct transpose;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			transpose.m[i][j] = TBN.m[j][i];
		}
	}
	return transpose;
}