#pragma once

#ifndef _MATHLOGIC_H_
#define _MATHLOGIC_H_

#include "3DVectorStruct.h"
#include "HomogeneousVectorStruct.h"
#include <cmath>

#define M_PI       3.14159265358979323846   // pi
const float MAX_DEPTH = 3.4E+38f;
const float MIN_DEPTH = -3.4E+38f;


template <typename T>
constexpr T getMin(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template <typename T>
constexpr T getMax(const T& a, const T& b)
{
    return (a > b) ? a : b;
}

template <typename T>
constexpr T getMin(const T& a, const T& b, const T& c)
{
    return getMin(getMin(a, b), c);
}

template <typename T>
constexpr T getMax(const T& a, const T& b, const T& c)
{
    return getMax(getMax(a, b), c);
}

template <typename T>
T clamp(T value, T minValue, T maxValue) {
    return getMax(minValue, getMin(value, maxValue));
}


float GetVectorLength(const HomogeneousCoordinateStruct& vector);


HomogeneousCoordinateStruct addZeroToGetHomogeneous(const CoordinateStruct& vector);

HomogeneousCoordinateStruct Normalize(const HomogeneousCoordinateStruct& vector);
CoordinateStruct Normalize(const CoordinateStruct& vector);

float DotProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2);
float DotProduct(const HomogeneousCoordinateStruct& vector1, const HomogeneousCoordinateStruct& vector2);

CoordinateStruct SubstractVectors(CoordinateStruct& vector1, CoordinateStruct& vector2);

CoordinateStruct ReverseVector(const CoordinateStruct& vector);

#endif // _MATHLOGIC_H_

