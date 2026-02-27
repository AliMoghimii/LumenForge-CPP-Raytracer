#include "Object3DSphere.hpp"

Object3DSphere::Object3DSphere()
{

}

Object3DSphere::Object3DSphere(Vector3D center, double radius, Material* material)
{
    this->center = center;
    this->radius = radius;
    this->material = material;
}

double Object3DSphere::object3DIntersects(const Ray& ray) const
{
    Ray rayToCenter = Ray(center, ray.origin - center, false);
    double a = 1.0;
    double b = 2.0 * ray.direction.dot(rayToCenter.direction);
    double c = rayToCenter.direction.dot(rayToCenter.direction) - (radius * radius);

    double discriminant = b * b - 4.0 * a * c;

    if(discriminant >= 0) 
    {
        double dist = (-b - sqrt(discriminant)) / (2.0 * a);
        if(dist > 0) 
            return dist;
        
        dist = (-b + sqrt(discriminant)) / (2.0 * a);
        if(dist > 0) 
            return dist;
    }
    return -1.0;
}

Vector3D Object3DSphere::object3DNormal(Vector3D surfacePoint) 
{
    return (surfacePoint - this->center).normalize();
}