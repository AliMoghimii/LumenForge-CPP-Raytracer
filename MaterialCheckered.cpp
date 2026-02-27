#include "MaterialCheckered.hpp"
#include <math.h>

MaterialCheckered::MaterialCheckered(Color colorA, Color colorB, double ambient, double diffuse, double specular, double reflection)
{
    this->colorA = colorA;
    this->colorB = colorB;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->reflection = reflection;
}

Color MaterialCheckered::colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const
{
    if(fmod(floor((hitPosition.x + 5.0) * 3.0), 2) == fmod(static_cast<int>(hitPosition.z * 3.0),2))
    {
        return this->colorA;
    } 
    else 
    {
        return this->colorB;
    }
}