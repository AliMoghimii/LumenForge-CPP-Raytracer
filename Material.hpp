#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.hpp"
#include "Vector3D.hpp"

#include <iostream>
using namespace std;

class Material
{
    public: 

        Color colorA;
        double ambient;
        double diffuse;
        double specular;
        double reflection;

    Material();

    virtual Color colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const;
};

#endif