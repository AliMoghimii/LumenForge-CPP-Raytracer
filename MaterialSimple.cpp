#include "MaterialSimple.hpp"

MaterialSimple::MaterialSimple(Color colorA, double ambient, double diffuse, double specular, double reflection, double transparency, double ior)
{
    this->colorA = colorA;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->reflection = reflection;
    this->transparency = transparency;
    this->ior = ior;
}

Color MaterialSimple::colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const
{
    return this->colorA;
}