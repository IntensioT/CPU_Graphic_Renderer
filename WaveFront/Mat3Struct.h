#pragma once
#include "CoordSystem.h"

typedef struct Mat3Struct
{
    union {
        struct {
            float        _11, _12, _13;
            float        _21, _22, _23;
            float        _31, _32, _33;
        };
        float m[3][3];
    };

    CoordinateStruct operator*(const CoordinateStruct& vect);
    Mat3Struct Inverse(const Mat3Struct& TBN);
    Mat3Struct Transpose(const Mat3Struct& TBN);
};