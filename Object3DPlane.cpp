#include "Object3DPlane.hpp"

Object3DPlane::Object3DPlane(Vector3D center, Vector3D normalVector, Material* material)
{
    this->center = center;
    this->normalVector = normalVector.normalize();
    this->material = material;
}

double Object3DPlane::object3DIntersects(const Ray& ray) const
{
    double denom = ray.direction.dot(this->normalVector);
    
    if (abs(denom) > 1e-6) 
    {
        double t = (this->center - ray.origin).dot(this->normalVector) / denom;
        if (t >= 0.0001) return t;
    }
    return -1.0;
}

Vector3D Object3DPlane::object3DNormal(Vector3D surfacePoint) 
{
    return this->normalVector;
}