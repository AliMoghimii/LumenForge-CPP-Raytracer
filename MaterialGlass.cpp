#include "MaterialGlass.hpp"
#include <algorithm>
#include <cmath>

MaterialGlass::MaterialGlass(double ior)
{
    this->colorA = Color(1.0, 1.0, 1.0);
    this->ambient = 0.0;
    this->diffuse = 0.0;
    this->specular = 1.0;
    this->ior = ior;
    this->reflection = 0.0; 
    this->transparency = 0.9; // Crucial for the shadow logic
}

double MaterialGlass::calculateFresnel(const Vector3D& viewDir, const Vector3D& hitNormal) const
{
    double cosi = std::max(-1.0, std::min(1.0, viewDir.dot(hitNormal)));
    double etai = 1.0, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }

    double r0 = (etai - etat) / (etai + etat);
    r0 = r0 * r0;
    double cosTheta = std::abs(cosi);

    if (etai > etat) {
        double n = etai / etat;
        double sin2t = n * n * (1.0 - cosTheta * cosTheta);
        if (sin2t > 1.0) return 1.0;
        cosTheta = std::sqrt(1.0 - sin2t);
    }

    return r0 + (1.0 - r0) * std::pow(1.0 - cosTheta, 5);
}

Color MaterialGlass::colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const
{
    return this->colorA;
}