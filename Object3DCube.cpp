#include "Object3DCube.hpp"

Object3DCube::Object3DCube(Vector3D minCorner, Vector3D maxCorner, Material* material, Vector3D rotation)
{
    this->bounds[0] = minCorner;
    this->bounds[1] = maxCorner;
    this->material = material;
    this->rotation = rotation;
    this->center = (minCorner + maxCorner) / 2.0;
}

double Object3DCube::object3DIntersects(const Ray& ray) const
{
    Vector3D localOrigin = ray.origin - this->center;
    Vector3D localDir = ray.direction;

    localOrigin = localOrigin.rotateZ(-rotation.z).rotateY(-rotation.y).rotateX(-rotation.x);
    localDir = localDir.rotateZ(-rotation.z).rotateY(-rotation.y).rotateX(-rotation.x);

    localOrigin = localOrigin + this->center;

    double invDx = 1.0 / (localDir.x != 0 ? localDir.x : 1e-8);
    double tmin = (bounds[0].x - localOrigin.x) * invDx;
    double tmax = (bounds[1].x - localOrigin.x) * invDx;
    if (tmin > tmax) std::swap(tmin, tmax);

    double invDy = 1.0 / (localDir.y != 0 ? localDir.y : 1e-8);
    double tymin = (bounds[0].y - localOrigin.y) * invDy;
    double tymax = (bounds[1].y - localOrigin.y) * invDy;
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return -1.0;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    double invDz = 1.0 / (localDir.z != 0 ? localDir.z : 1e-8);
    double tzmin = (bounds[0].z - localOrigin.z) * invDz;
    double tzmax = (bounds[1].z - localOrigin.z) * invDz;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return -1.0;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    if (tmin >= 0.0001) return tmin;
    if (tmax >= 0.0001) return tmax;
    
    return -1.0;
}

Vector3D Object3DCube::object3DNormal(Vector3D surfacePoint) 
{
    Vector3D localPoint = surfacePoint - this->center;
    localPoint = localPoint.rotateZ(-rotation.z).rotateY(-rotation.y).rotateX(-rotation.x);
    localPoint = localPoint + this->center;

    Vector3D localNormal;
    const double epsilon = 0.0001;
    if (abs(localPoint.x - bounds[0].x) < epsilon) localNormal = Vector3D(-1, 0, 0);
    else if (abs(localPoint.x - bounds[1].x) < epsilon) localNormal = Vector3D(1, 0, 0);
    else if (abs(localPoint.y - bounds[0].y) < epsilon) localNormal = Vector3D(0, -1, 0);
    else if (abs(localPoint.y - bounds[1].y) < epsilon) localNormal = Vector3D(0, 1, 0);
    else if (abs(localPoint.z - bounds[0].z) < epsilon) localNormal = Vector3D(0, 0, -1);
    else if (abs(localPoint.z - bounds[1].z) < epsilon) localNormal = Vector3D(0, 0, 1);
    else localNormal = Vector3D(0, 1, 0); 
    
    return localNormal.rotateX(rotation.x).rotateY(rotation.y).rotateZ(rotation.z).normalize();
}