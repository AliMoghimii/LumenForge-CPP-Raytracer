#ifndef OBJECT3DCUBE_H
#define OBJECT3DCUBE_H

#include "Object3D.hpp"
#include <algorithm>

class Object3DCube : public Object3D
{
    public: 
        Vector3D bounds[2]; 
        Vector3D rotation;

    Object3DCube(Vector3D minCorner, Vector3D maxCorner, Material* material, Vector3D rotation = Vector3D(0,0,0));

    double object3DIntersects(const Ray& ray) const override;
    Vector3D object3DNormal(Vector3D surfacePoint) override;
};

#endif