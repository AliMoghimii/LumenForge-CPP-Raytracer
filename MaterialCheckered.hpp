#ifndef MATERIALCHECKERED_H
#define MATERIALCHECKERED_H

#include "Material.hpp"

#include <iostream>
using namespace std;

class MaterialCheckered : public Material
{
    public: 

    Color colorB;

    MaterialCheckered(Color colorA = Color(1,1,1), Color colorB = Color(0,0,0), double ambient = 0.05, double diffuse = 1.0, double specular = 1.0, double reflection = 0.5);

    Color colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const override;
};

#endif