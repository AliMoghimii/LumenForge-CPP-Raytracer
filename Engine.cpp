#include "Engine.hpp"
#include "MaterialGlass.hpp" // Necessary for the dynamic_cast
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

Image Engine::render(const Scene& scene, const Vector3D& lookAt, bool shaded, bool shadows, bool reflections, bool antiAliasing, bool additiveReflection, int numThreads)
{
    this->shaded = shaded;
    this->shadows = shadows; 
    this->reflections = reflections;
    this->additiveReflection = additiveReflection;

    int width = scene.width;
    int height = scene.height;
    double aspectRatio = static_cast<double>(width) / height;
    
    double x0 = -1.0;
    double x1 = 1.0;
    double xdelta = (x1 - x0) / (width - 1);
    double y0 = 1.0 / aspectRatio; 
    double y1 = -1.0 / aspectRatio; 
    double ydelta = (y1 - y0) / (height - 1);

    Vector3D cameraPos = scene.camera;
    Image canvas = Image(width, height);

    // Look-At Basis Vectors
    Vector3D forward = (lookAt - cameraPos).normalize();
    Vector3D worldUp(0, 1, 0);
    Vector3D right = worldUp.cross(forward).normalize();
    Vector3D up = forward.cross(right).normalize();

    int currentSamples = antiAliasing ? this->samplesPerPixel : 1;
    int actualThreads = numThreads;

    if (actualThreads <= 0) 
    {
        actualThreads = std::thread::hardware_concurrency();
        if (actualThreads == 0) actualThreads = 8;
    }

    std::vector<std::thread> threads;
    std::atomic<int> rowsCompleted(0);

    auto renderChunk = [&](int startY, int endY) {
        std::mt19937 rng(std::random_device{}()); 
        std::uniform_real_distribution<double> dist(-0.5, 0.5);

        for (int j = startY; j < endY; ++j) 
        {
            float yBase = y0 + j * ydelta;

            for (int i = 0; i < width; ++i) 
            {
                float xBase = x0 + i * xdelta;
                Color accumulatedColor = Color(0, 0, 0);

                for (int s = 0; s < currentSamples; ++s) 
                {
                    double jitterX = 0.0;
                    double jitterY = 0.0;
                    
                    if (antiAliasing) 
                    {
                        jitterX = dist(rng) * xdelta;
                        jitterY = dist(rng) * ydelta;
                    }
                    
                    Vector3D localRayDir(xBase + jitterX, yBase + jitterY, 1.0);
                    Vector3D worldRayDir = (right * localRayDir.x) + (up * localRayDir.y) + (forward * localRayDir.z);
                    Ray ray = Ray(cameraPos, worldRayDir.normalize());
                    
                    accumulatedColor = accumulatedColor + raytrace(ray, scene);
                }

                Color finalColor = accumulatedColor / currentSamples;
                canvas.setPixel(i, j, finalColor);
            }
            rowsCompleted++; 
        }
    };

    int chunkSize = height / actualThreads;
    for (int t = 0; t < actualThreads; ++t) 
    {
        int startY = t * chunkSize;
        int endY = (t == actualThreads - 1) ? height : startY + chunkSize;
        threads.push_back(std::thread(renderChunk, startY, endY));
    }

    while (rowsCompleted < height) 
    {
        double progress = (double)(rowsCompleted) / height * 100;
        cout << "Rendering: In Progress (" << (int) progress << "% | Threads: " << actualThreads << ")\r";
        cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto& t : threads) { t.join(); }

    cout << "\nRendering: Completed Successfully (100%)" << endl; 
    return canvas;
}

Color Engine::raytrace(const Ray& ray, const Scene& scene, int depth)
{
    Color color = Color(0, 0, 0);

    double distanceHit;
    Object3D* objectHit;

    tie(objectHit, distanceHit) = rayCollision(ray, scene);
    
    if(objectHit == nullptr) 
        return color;

    Vector3D hitPosition = ray.origin + ray.direction * distanceHit;
    Vector3D hitNormal = objectHit->object3DNormal(hitPosition);

    Color localColor = colorBlending(objectHit, hitPosition, hitNormal, scene);

    Color reflectedColor(0, 0, 0);
    Color refractedColor(0, 0, 0);

    double reflection = objectHit->material->reflection;
    double transparency = objectHit->material->transparency;
    double ior = objectHit->material->ior;

    // --- DYNAMIC FRESNEL (SCHLICK) CHECK ---
    MaterialGlass* glass = dynamic_cast<MaterialGlass*>(objectHit->material);
    if (glass) {
        reflection = glass->calculateFresnel(ray.direction, hitNormal);
        transparency = 1.0 - reflection;
    }

    // --- REFLECTION ---
    if(this->reflections && depth < this->maxDepth && reflection > 0.0)
    {
        Vector3D newRayOrigin = hitPosition + hitNormal * this->minDisplacement;
        Vector3D newRayDirection = ray.direction - 2 * ray.direction.dot(hitNormal) * hitNormal;
        Ray reflectedRay = Ray(newRayOrigin, newRayDirection, false);
        
        reflectedColor = raytrace(reflectedRay, scene, depth + 1);
    }

    // --- REFRACTION (Snell's Law) ---
    if(this->reflections && depth < this->maxDepth && transparency > 0.0)
    {
        double cosi = ray.direction.dot(hitNormal);
        double etai = 1.0;
        double etat = ior;
        Vector3D n = hitNormal;

        if (cosi > 0) {
            swap(etai, etat);
            n = hitNormal * -1;
        } else {
            cosi = -cosi;
        }

        double eta = etai / etat;
        double k = 1.0 - eta * eta * (1.0 - cosi * cosi);

        if (k >= 0) {
            Vector3D refractDir = (ray.direction * eta) + (n * (eta * cosi - sqrt(k)));
            refractDir = refractDir.normalize();

            // Offset origin along the refracted path to avoid self-intersection
            Vector3D refractOrigin = hitPosition + refractDir * this->minDisplacement;
            Ray refractRay = Ray(refractOrigin, refractDir, false);
            refractedColor = raytrace(refractRay, scene, depth + 1);
        }
    }

    // --- FINAL BLENDING ---
    if (this->additiveReflection) 
    {
        double opacity = 1.0 - transparency;
        if (opacity < 0.0) opacity = 0.0;
        color = (localColor * opacity) + (reflectedColor * reflection) + (refractedColor * transparency);
    } 
    else 
    {
        double opacity = 1.0 - reflection - transparency;
        if (opacity < 0.0) opacity = 0.0;
        color = (localColor * opacity) + (reflectedColor * reflection) + (refractedColor * transparency);
    }

    return color;
}

pair<Object3D*, double> Engine::rayCollision(const Ray& ray, const Scene& scene)
{
    double distanceMin = DBL_MAX;
    Object3D* objectHit = nullptr;

    for (Object3D* object : scene.objects) 
    {
        double distance = object->object3DIntersects(ray);
        if((distance != -1) && (objectHit == nullptr || distance < distanceMin)) 
        {
            distanceMin = distance;
            objectHit = object;
        }
    }

    return make_pair(objectHit, distanceMin);
}

Color Engine::colorBlending(Object3D* objectHit, const Vector3D& hitPosition, const Vector3D& hitNormal, const Scene& scene) 
{
    if(!this->shaded) return objectHit->material->colorA;

    Material* objectHitMaterial = objectHit->material;
    Color objectHitColor = objectHitMaterial->colorBlendingProperties(hitPosition, hitNormal); 
    Ray rayToCamera = Ray(hitPosition, scene.camera - hitPosition, true); 
    Color newColor = objectHitColor * objectHitMaterial->ambient;

    Vector3D shadowRayOrigin = hitPosition + hitNormal * this->minDisplacement;
    
    for (Light* light : scene.lights)
    {
        Ray rayToLight = Ray(shadowRayOrigin, light->position - hitPosition);
        double lightDist = (light->position - hitPosition).magnitude();
        
        // --- NEW: TRANSPARENT SHADOW LOGIC ---
        double shadowIntensity = 1.0; 

        if (this->shadows) 
        {
            // We check all objects to see if they block this specific light
            for (Object3D* obj : scene.objects) {
                double dist = obj->object3DIntersects(rayToLight);
                if (dist > 0 && dist < lightDist) {
                    // If we hit a transparent object, we reduce light instead of blocking it
                    if (obj->material->transparency > 0) {
                        shadowIntensity *= obj->material->transparency; 
                    } else {
                        shadowIntensity = 0; // Solid object, total shadow
                        break;
                    }
                }
            }
        }

        if(shadowIntensity > 0) 
        {
            Color diffuse = lambertianShading(objectHitMaterial, objectHitColor, hitNormal, rayToLight);
            Color specular = blingPhongShading(objectHitMaterial, *light, hitNormal, rayToLight, rayToCamera, 50.0);
            newColor = newColor + (diffuse + specular) * shadowIntensity;
        }
    }
    return newColor;
}

Color Engine::lambertianShading(const Material* objectHitMaterial, const Color& objectHitColor, const Vector3D& hitNormal, const Ray& rayToLight) 
{
    return objectHitColor * objectHitMaterial->diffuse * max(hitNormal.dot(rayToLight.direction), 0.0);
}

Color Engine::blingPhongShading(const Material* objectHitMaterial, const Light& light, const Vector3D& hitNormal, const Ray& rayToLight, const Ray& rayToCamera, double specularExponent) 
{
    Vector3D halfVector = (rayToLight.direction + rayToCamera.direction).normalize();
    return light.color * objectHitMaterial->specular * pow(max(hitNormal.dot(halfVector), 0.0), specularExponent);
}