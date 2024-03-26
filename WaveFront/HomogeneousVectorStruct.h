#pragma once
#ifndef _HOMOGENEOUS_COORDINATE_STRUCT_H_
#define _HOMOGENEOUS_COORDINATE_STRUCT_H_


struct HomogeneousCoordinateStruct
{
    float x, y, z, w;
    float shade;
    CoordinateStruct diffuse;
    CoordinateStruct normal;
    float normalW;
    CoordinateStruct projectedNormal;

    HomogeneousCoordinateStruct& operator*=(const float f) {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    HomogeneousCoordinateStruct operator-(const HomogeneousCoordinateStruct& other) const {
        return HomogeneousCoordinateStruct{ x - other.x, y - other.y, z - other.z };
    }
    HomogeneousCoordinateStruct operator+(const HomogeneousCoordinateStruct& other) const {
        return HomogeneousCoordinateStruct{ x + other.x, y + other.y, z + other.z };
    }
    CoordinateStruct toCoordinateStruct()
    {
        return { x,y,z };
    }
};

#endif