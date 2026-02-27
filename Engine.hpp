#ifndef ENGINE_H
#define ENGINE_H

#include "Image.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Object3D.hpp" 
#include "Material.hpp"

#include <math.h>
#include <float.h>
#include <iostream>
#include <utility>

using namespace std;

class Engine 
{
    public: 

    bool shaded = true;
    bool additiveReflection = true; 
    int maxDepth = 5;
    double minDisplacement = 0.0001;
    int samplesPerPixel = 16; 

    Image render(const Scene& scene, bool shaded = true, bool antiAliasing = true, bool additiveReflection = true);

    Color raytrace(const Ray& ray, const Scene& scene, int depth = 0);

    pair<Object3D*, double> rayCollision(const Ray& ray, const Scene& scene); 

    Color colorBlending(Object3D* objectHit, const Vector3D& hitPosition, const Vector3D& hitNormal, const Scene& scene);

    Color lambertianShading(const Material* objectHitMaterial, const Color& objectHitColor, const Vector3D& hitNormal, const Ray& rayToLight);

    Color blingPhongShading(const Material* objectHitMaterial, const Light& light, const Vector3D& hitNormal, const Ray& rayToLight, const Ray& rayToCamera, double specularExponent = 50.0);
};

#endif