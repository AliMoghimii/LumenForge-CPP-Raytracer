#ifndef MATERIALGLASS_H
#define MATERIALGLASS_H

#include "Material.hpp"

class MaterialGlass : public Material
{
    public: 
        // Only IOR is needed now; reflection/transparency are calculated per-ray
        MaterialGlass(double ior = 1.5);

        // Math for the Fresnel/Schlick effect
        double calculateFresnel(const Vector3D& viewDir, const Vector3D& hitNormal) const;

        Color colorBlendingProperties(const Vector3D& hitPosition, const Vector3D& hitNormal) const override;
};

#endif