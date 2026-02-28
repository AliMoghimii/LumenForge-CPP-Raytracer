#ifndef OBJECT3DPLANE_H
#define OBJECT3DPLANE_H

#include "Object3D.hpp"

class Object3DPlane : public Object3D
{
    public: 
        Vector3D normalVector;

    Object3DPlane(Vector3D center, Vector3D normalVector, Material* material);

    double object3DIntersects(const Ray& ray) const override;
    Vector3D object3DNormal(Vector3D surfacePoint) override;
};

#endif