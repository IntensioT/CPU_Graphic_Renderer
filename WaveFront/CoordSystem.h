#pragma once

#ifndef _COORDINATE_SYSTEM_H_
#define _COORDINATE_SYSTEM_H_

#include "ObjLoader.h"

#include <emmintrin.h>
#include <immintrin.h>


#define M_PI       3.14159265358979323846   // pi



typedef struct _3DMATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };

    _3DMATRIX operator*(const _3DMATRIX& a);
    CoordinateStruct operator*(const CoordinateStruct& vect);
}; 



struct Plane {
    HomogeneousCoordinateStruct normal;
    float distance;
};


inline CoordinateStruct AddVectors(const CoordinateStruct& vector1, const CoordinateStruct& vector2) {
    CoordinateStruct result;
    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    return result;
}

inline HomogeneousCoordinateStruct AddHomogeneousVectors(const HomogeneousCoordinateStruct& vector1, const HomogeneousCoordinateStruct& vector2) {
    HomogeneousCoordinateStruct result;
    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    result.w = vector1.w + vector2.w;
    return result;
}

inline HomogeneousCoordinateStruct operator* (HomogeneousCoordinateStruct& p, const _3DMATRIX& m) 
{
    HomogeneousCoordinateStruct t = p;

    t.x = p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0] + p.w * m.m[3][0];
    t.y = p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1] + p.w * m.m[3][1];
    t.z = p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2] + p.w * m.m[3][2];
    t.w = p.x * m.m[0][3] + p.y * m.m[1][3] + p.z * m.m[2][3] + p.w * m.m[3][3];
    return t;
}


inline HomogeneousCoordinateStruct operator*=(HomogeneousCoordinateStruct& p, const _3DMATRIX& m) {
    p = p * m;
    return p;
}


inline float GetRadians(float angle)
{
    return (angle) * (M_PI / 180.0f);
}

inline CoordinateStruct SphericalToCartesian(float radius, float phiAngle, float thetaAngle)
{
    CoordinateStruct res;

    float theta = GetRadians(thetaAngle);
    float phi = GetRadians(phiAngle);

    res.z = radius * sin(theta) * cos(phi);
    res.x = radius * sin(theta) * sin(phi);
    res.y = radius * cos(theta);
    return res;
}



class CoordSystem
{
    CoordinateStruct XAxis, YAxis, ZAxis;


public:
    _3DMATRIX GlobalTransformationMatrix;
    _3DMATRIX CameraTransformationMatrix;
    _3DMATRIX ProjectionTransformationMatrix;
    _3DMATRIX ViewPortTransformationMatrix;

    _3DMATRIX TranslationMatrix;

    _3DMATRIX ScaleMatrix;

    _3DMATRIX RotateXMatrix;
    _3DMATRIX RotateYMatrix;
    _3DMATRIX RotateZMatrix;

    _3DMATRIX RotationMatrix;



    CoordSystem(CoordinateStruct Translation);

    //CoordinateStruct SubstractVectors(CoordinateStruct& vector1, CoordinateStruct& vector2);
    CoordinateStruct MultiplyVectors(CoordinateStruct& vector1, CoordinateStruct& vector2);
    HomogeneousCoordinateStruct MultiplyMatByVector(_3DMATRIX matrix, HomogeneousCoordinateStruct vector);
    _3DMATRIX MultiplyMatrixByMatrix(const _3DMATRIX& mat1, const _3DMATRIX& mat2);
    //float DotProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2);
    //float DotProduct(const HomogeneousCoordinateStruct& vector1, const HomogeneousCoordinateStruct& vector2);
    CoordinateStruct CrossProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2);
    HomogeneousCoordinateStruct CrossProduct(const HomogeneousCoordinateStruct& vector1, const HomogeneousCoordinateStruct& vector2);




    float VectorLength(const CoordinateStruct& vector);
    float VectorLength(const HomogeneousCoordinateStruct& vector);
    //CoordinateStruct NormalizeVector(const CoordinateStruct& vector);
    //HomogeneousCoordinateStruct NormalizeVector(const HomogeneousCoordinateStruct& vector);

    HomogeneousCoordinateStruct TransformVector(HomogeneousCoordinateStruct& originalVector, CoordinateStruct& scale, float angle, CoordinateStruct& axis, CoordinateStruct& translation);


    void SetCameraTransformationMatrix(CoordinateStruct& cameraGlobalCoord, CoordinateStruct& targetGlobalCoord, CoordinateStruct& cameraUpVect);
    void SetProjectionTransformationMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
    void SetViewPortTransformationMatrix(float width, float height, float x, float y, float zMin, float zMax);

    bool IsVertexBehindClipPlane(const HomogeneousCoordinateStruct vertex, const Plane& clipPlane);
    //bool IsObjectBehindClipPlanes(const std::vector<CoordinateStruct>& vertices, const std::vector<Plane>& clipPlanes, const _3DMATRIX& modelMatrix, const _3DMATRIX& viewMatrix, const _3DMATRIX& projectionMatrix);

    HomogeneousCoordinateStruct CalculateNormalProjections(HomogeneousCoordinateStruct homoVector);


    void SetTranslationMatrix(CoordinateStruct Translation);
    void SetScaleMatrix(CoordinateStruct Scale);
    void SetRotateXMatrix(float angle);
    void SetRotateYMatrix(float angle);
    void SetRotateZMatrix(float angle);
    void SetRotateMatrix(float angle, CoordinateStruct Axis);
    void SetRotationMatrixOptimized(float angle, const CoordinateStruct& axis);



private:
	_3DMATRIX TransformationMatrix;
	_3DMATRIX LocalTransformationMatrix;

    CoordinateStruct Right;
    CoordinateStruct Up;
    CoordinateStruct Look;

    CoordinateStruct Position;
};

#endif
