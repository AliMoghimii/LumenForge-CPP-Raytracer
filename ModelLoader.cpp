#include "ModelLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void ModelLoader::load(const string& filename, vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale) 
{
    string extension = "";
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != string::npos) {
        extension = filename.substr(dotPos + 1);
    }

    if (extension == "obj" || extension == "OBJ") {
        loadOBJ(filename, sceneObjects, material, position, rotation, scale);
    } 
    else if (extension == "stl" || extension == "STL") {
        loadSTL(filename, sceneObjects, material, position, rotation, scale);
    }
    else if (extension == "fbx" || extension == "FBX") {
        loadFBX(filename, sceneObjects, material, position, rotation, scale);
    }
    else {
        cout << "Error: Unsupported file format '." << extension << "'" << endl;
    }
}

void ModelLoader::loadOBJ(const string& filename, vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale) 
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error: Could not open " << filename << ". Check your file path!" << endl;
        return;
    }

    vector<Vector3D> vertices;
    vector<Vector3D> normals;
    string line;
    int facesCount = 0;

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string prefix;
        ss >> prefix;

        if (prefix == "v") 
        {
            double x, y, z;
            ss >> x >> y >> z;
            Vector3D v(x, y, z);
            
            v = v * scale; 
            v = v.rotateX(rotation.x).rotateY(rotation.y).rotateZ(rotation.z); 
            v = v + position; 
            
            vertices.push_back(v);
        } 
        else if (prefix == "vn")
        {
            double nx, ny, nz;
            ss >> nx >> ny >> nz;
            Vector3D n(nx, ny, nz);
            
            n = n.rotateX(rotation.x).rotateY(rotation.y).rotateZ(rotation.z);
            
            normals.push_back(n.normalize());
        }
        else if (prefix == "f") 
        {
            string token;
            vector<int> vIndices;
            vector<int> vnIndices;

            while (ss >> token) 
            {
                int v_idx = -1, vt_idx = -1, vn_idx = -1;
                stringstream token_ss(token);
                string item;
                int index = 0;
                
                while (getline(token_ss, item, '/')) 
                {
                    if (!item.empty()) 
                    {
                        if (index == 0) v_idx = stoi(item) - 1;
                        else if (index == 1) vt_idx = stoi(item) - 1;
                        else if (index == 2) vn_idx = stoi(item) - 1;
                    }
                    index++;
                }
                
                vIndices.push_back(v_idx);
                if (vn_idx != -1) vnIndices.push_back(vn_idx);
            }

            if (vIndices.size() >= 3)
            {
                for (size_t i = 1; i < vIndices.size() - 1; ++i)
                {
                    Vector3D p1 = vertices[vIndices[0]];
                    Vector3D p2 = vertices[vIndices[i]];
                    Vector3D p3 = vertices[vIndices[i+1]];

                    if (vnIndices.size() == vIndices.size()) 
                    {
                        Vector3D n1 = normals[vnIndices[0]];
                        Vector3D n2 = normals[vnIndices[i]];
                        Vector3D n3 = normals[vnIndices[i+1]];
                        
                        sceneObjects.push_back(new Object3DTriangle(p1, p2, p3, n1, n2, n3, material)); 
                        
                        sceneObjects.push_back(new Object3DTriangle(p1, p2, p3, material));
                    } 
                    else 
                    {
                        sceneObjects.push_back(new Object3DTriangle(p1, p2, p3, material));
                    }
                    
                    facesCount++;
                }
            }
        }
    }
    
    cout << "Successfully loaded " << filename << " (" << vertices.size() << " vertices, " << normals.size() << " normals, " << facesCount << " faces)" << endl;
}

void ModelLoader::loadSTL(const string& filename, vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale) 
{
    cout << "STL parser not yet implemented!" << endl;
}

void ModelLoader::loadFBX(const string& filename, vector<Object3D*>& sceneObjects, Material* material, const Vector3D& position, const Vector3D& rotation, double scale) 
{
    cout << "FBX parser not yet implemented!" << endl;
}