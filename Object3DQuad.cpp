#include "Object3DQuad.hpp"

Object3DQuad::Object3DQuad(Vector3D corner, Vector3D edge1, Vector3D edge2, Material* material)
{
    this->corner = corner;
    this->edge1 = edge1;
    this->edge2 = edge2;
    this->material = material;
    
    this->normalVector = edge1.cross(edge2).normalize();
}

double Object3DQuad::object3DIntersects(const Ray& ray) const
{
    double denom = ray.direction.dot(this->normalVector);
    
    if (abs(denom) > 1e-6) 
    {
        double t = (this->corner - ray.origin).dot(this->normalVector) / denom;
        if (t >= 0.0001) 
        {
            Vector3D hitPoint = ray.origin + ray.direction * t;
            Vector3D p = hitPoint - this->corner;
            
            double u = p.dot(this->edge1) / this->edge1.dot(this->edge1);
            double v = p.dot(this->edge2) / this->edge2.dot(this->edge2);
            
            if (u >= 0.0 && u <= 1.0 && v >= 0.0 && v <= 1.0) 
            {
                return t;
            }
        }
    }
    return -1.0;
}

Vector3D Object3DQuad::object3DNormal(Vector3D surfacePoint) 
{
    return this->normalVector;
}