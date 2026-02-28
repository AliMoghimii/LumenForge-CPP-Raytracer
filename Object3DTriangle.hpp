#ifndef OBJECT3DTRIANGLE_H
#define OBJECT3DTRIANGLE_H

#include "Object3D.hpp"

class Object3DTriangle : public Object3D
{
    public: 
        Vector3D v0, v1, v2;
        Vector3D n0, n1, n2;
        Vector3D normalVector;
        bool isSmooth;

    Object3DTriangle(Vector3D v0, Vector3D v1, Vector3D v2, Material* material);

    Object3DTriangle(Vector3D v0, Vector3D v1, Vector3D v2, Vector3D n0, Vector3D n1, Vector3D n2, Material* material);

    double object3DIntersects(const Ray& ray) const override;
    Vector3D object3DNormal(Vector3D surfacePoint) override;
};

#endif