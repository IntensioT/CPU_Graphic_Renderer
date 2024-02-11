#pragma once
#include "ObjLoader.h"

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
}; 

struct HomogeneousCoordinateStruct
{
    float x, y, z, w;
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

class CoordSystem
{
    CoordinateStruct Center;
    CoordinateStruct XAxis, YAxis, ZAxis;


public:
    _3DMATRIX GlobalTransformationMatrix;
    _3DMATRIX CameraTransformationMatrix;
    _3DMATRIX ProjectionTransformationMatrix;
    _3DMATRIX ViewPortTransformationMatrix;

    _3DMATRIX MovementMatrix;

    _3DMATRIX ScaleMatrix;

    _3DMATRIX RotateXMatrix;
    _3DMATRIX RotateYMatrix;
    _3DMATRIX RotateZMatrix;

    _3DMATRIX RotationMatrix;


    HomogeneousCoordinateStruct ToGlobalCoords(HomogeneousCoordinateStruct local);
    CoordinateStruct ToLocalCoords(CoordinateStruct global);
    CoordSystem(CoordinateStruct Translation);

    CoordinateStruct SubstractVectors(CoordinateStruct& vector1, CoordinateStruct& vector2);
    CoordinateStruct MultiplyVectors(CoordinateStruct& vector1, CoordinateStruct& vector2);
    HomogeneousCoordinateStruct MultiplyMatByVector(_3DMATRIX matrix, HomogeneousCoordinateStruct vector);
    _3DMATRIX MultiplyMatrixByMatrix(const _3DMATRIX& mat1, const _3DMATRIX& mat2);
    float DotProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2);
    CoordinateStruct CrossProduct(const CoordinateStruct& vector1, const CoordinateStruct& vector2);



    float VectorLength(const CoordinateStruct& vector);
    CoordinateStruct NormalizeVector(const CoordinateStruct& vector);

    HomogeneousCoordinateStruct TransformVector(HomogeneousCoordinateStruct& originalVector, CoordinateStruct& scale, float angle, CoordinateStruct& axis, CoordinateStruct& translation);


    void SetCameraTransformationMatrix(CoordinateStruct& cameraGlobalCoord, CoordinateStruct& targetGlobalCoord, CoordinateStruct& cameraUpVect);
    void SetProjectiosTransformationMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
    void SetViewPortTransformationMatrix(float width, float height, float x, float y);

    void MoveSystem(CoordinateStruct vect);

    void SetMovementMatrix(CoordinateStruct Translation);
    void SetScaleMatrix(CoordinateStruct Scale);
    void SetRotateXMatrix(float angle);
    void SetRotateYMatrix(float angle);
    void SetRotateZMatrix(float angle);
    void SetRotateMatrix(float angle, CoordinateStruct Axis);
    void SetRotationMatrixOptimized(float angle, const CoordinateStruct& axis);



private:
	_3DMATRIX TransformationMatrix;
	_3DMATRIX LocalTransformationMatrix;
};

