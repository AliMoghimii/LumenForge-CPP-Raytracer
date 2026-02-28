#ifndef OBJECT3DQUAD_H
#define OBJECT3DQUAD_H

#include "Object3D.hpp"

class Object3DQuad : public Object3D
{
    public: 
        Vector3D corner;
        Vector3D edge1;
        Vector3D edge2;
        Vector3D normalVector;

    Object3DQuad(Vector3D corner, Vector3D edge1, Vector3D edge2, Material* material);

    double object3DIntersects(const Ray& ray) const override;
    Vector3D object3DNormal(Vector3D surfacePoint) override;
};

#endif