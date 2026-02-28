#include "Material.hpp"

Material::Material()
{
    this->colorA = Color(1, 1, 1);
    this->ambient = 0.05;
    this->diffuse = 1.0;
    this->specular = 1.0;
    this->reflection = 0.0;
    this->transparency = 0.0;
    this->ior = 1.0;
}

Color Material::colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const
{
    return Color(1,1,1);
}