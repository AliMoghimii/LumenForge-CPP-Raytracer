#pragma once

#include "Vector3D.hpp"
#include "Object3D.hpp"
#include "Object3DTriangle.hpp"
#include "Material.hpp" 

#include <vector>
#include <string>

class ModelLoader {
public:

    static void load(const std::string& filename, std::vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation = Vector3D(0,0,0), double scale = 1.0);

private:
    static void loadOBJ(const std::string& filename, std::vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale);
    static void loadSTL(const std::string& filename, std::vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale);
    static void loadFBX(const std::string& filename, std::vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale);
};