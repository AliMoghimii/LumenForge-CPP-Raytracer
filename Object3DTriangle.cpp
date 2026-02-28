#include "Object3DTriangle.hpp"

Object3DTriangle::Object3DTriangle(Vector3D v0, Vector3D v1, Vector3D v2, Material* material)
{
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->material = material;
    this->isSmooth = false;
    
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    this->normalVector = edge1.cross(edge2).normalize();
}

Object3DTriangle::Object3DTriangle(Vector3D v0, Vector3D v1, Vector3D v2, Vector3D n0, Vector3D n1, Vector3D n2, Material* material)
{
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->n0 = n0;
    this->n1 = n1;
    this->n2 = n2;
    this->material = material;
    this->isSmooth = true;
    
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    this->normalVector = edge1.cross(edge2).normalize();
}

double Object3DTriangle::object3DIntersects(const Ray& ray) const
{
    const double EPSILON = 0.0000001;
    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON) return -1.0; 

    double f = 1.0 / a;
    Vector3D s = ray.origin - v0;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0) return -1.0;

    Vector3D q = s.cross(edge1);
    double v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0) return -1.0;

    double t = f * edge2.dot(q);
    if (t > EPSILON) return t;

    return -1.0;
}

Vector3D Object3DTriangle::object3DNormal(Vector3D surfacePoint) 
{
    if (!this->isSmooth) {
        return this->normalVector;
    }

    Vector3D edge1 = v1 - v0;
    Vector3D edge2 = v2 - v0;
    Vector3D pVector = surfacePoint - v0;

    double d00 = edge1.dot(edge1);
    double d01 = edge1.dot(edge2);
    double d11 = edge2.dot(edge2);
    double d20 = pVector.dot(edge1);
    double d21 = pVector.dot(edge2);

    double denom = d00 * d11 - d01 * d01;
    
    double u = (d11 * d20 - d01 * d21) / denom;
    double v = (d00 * d21 - d01 * d20) / denom;
    
    double w = 1.0 - u - v;

    return (n0 * w + n1 * u + n2 * v).normalize();
}