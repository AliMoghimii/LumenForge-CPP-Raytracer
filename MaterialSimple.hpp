#ifndef MATERIALSIMPLE_H
#define MATERIALSIMPLE_H

#include "Material.hpp"

#include <iostream>
using namespace std;

class MaterialSimple : public Material
{
    public: 
    MaterialSimple(Color colorA = Color(1,1,1), double ambient = 0.05, double diffuse = 1.0, double specular = 1.0, double reflection = 0.5, double transparency = 0.0, double ior = 1.0);

    Color colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const override;
};

#endif