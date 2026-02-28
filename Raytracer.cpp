#include "Color.hpp"
#include "Vector3D.hpp"
#include "Object3DSphere.hpp"
#include "Object3DPlane.hpp"
#include "Object3DQuad.hpp"  
#include "Object3DCube.hpp"   
#include "Object3DTriangle.hpp"   
#include "Object3D.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Light.hpp"
#include "MaterialSimple.hpp"
#include "MaterialGlass.hpp"
#include "MaterialCheckered.hpp"
#include "ModelLoader.hpp"

#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    system("cls");

    int width = 1280;
    int height = 720;
    Color color;

    auto timerStart = chrono::high_resolution_clock::now();

    Vector3D camera = Vector3D(0, 0.3, -1);
    
    vector<Object3D*> objects;
    
    objects.push_back(new Object3DPlane(Vector3D(0, -0.5, 0), Vector3D(0, 1, 0), new MaterialSimple(color.HexToRgb("#111111"), 0.2, 1.0, 1.0, 0.2)));

    objects.push_back(new Object3DSphere(Vector3D(-0.25, 0, 0.6), 0.5, new MaterialSimple(color.HexToRgb("#FF0000"))));
    
    objects.push_back(new Object3DSphere(Vector3D(-0.15, 0.1, 0.15), 0.1, new MaterialSimple(color.HexToRgb("#FFFFFF"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.12, 0.12, 0.05), 0.05, new MaterialSimple(color.HexToRgb("#000000"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.4, 0.1, 0.15), 0.1, new MaterialSimple(color.HexToRgb("#FFFFFF"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.37, 0.12, 0.05), 0.05, new MaterialSimple(color.HexToRgb("#000000"), 0.05, 1.0, 1.0, 0.01)));

    objects.push_back(new Object3DSphere(Vector3D(1.3, 0.15, 1), 0.75, new MaterialSimple(color.HexToRgb("#FFFF00"))));
    objects.push_back(new Object3DSphere(Vector3D(1, 1.85, 8), 0.75, new MaterialSimple(color.HexToRgb("#00FF00"))));

    objects.push_back(new Object3DSphere(Vector3D(-5, -3, 5), 5, new MaterialCheckered(color.HexToRgb("#0000FF"), color.HexToRgb("#FFFFFF"))));

    objects.push_back(new Object3DCube(Vector3D(0.25, -0.5, 0.25), Vector3D(0.5, -0.25, 0.5), new MaterialSimple(color.HexToRgb("#00FFFF")), Vector3D(0, 35, 0)));
    
    //objects.push_back(new Object3DSphere(Vector3D(0.0, 0, -0.1), 0.4, new MaterialGlass(1.5)));

    Vector3D top(0, 1, 0);
    Vector3D front(-1, -1, 1);
    Vector3D backRight(1, -1, 1);
    Vector3D backLeft(0, -1, -1);

    double scale = 0.1; 
    Vector3D rot(0, 125, 0); 
    Vector3D pos(0.35, 0, 0.35); 

    Vector3D pts[4] = {top, front, backRight, backLeft};
    for (int i = 0; i < 4; i++) {
        pts[i] = pts[i] * scale; 
        pts[i] = pts[i].rotateX(rot.x).rotateY(rot.y).rotateZ(rot.z); 
        pts[i] = pts[i] + pos; 
    }

    MaterialSimple* matFront  = new MaterialSimple(color.HexToRgb("#FFA500"), 0.05, 1.0, 1.0, 0.1); 
    MaterialSimple* matRight  = new MaterialSimple(color.HexToRgb("#800080"), 0.05, 1.0, 1.0, 0.1); 
    MaterialSimple* matLeft   = new MaterialSimple(color.HexToRgb("#00FFFF"), 0.05, 1.0, 1.0, 0.1); 
    MaterialSimple* matBottom = new MaterialSimple(color.HexToRgb("#00FF00"), 0.05, 1.0, 1.0, 0.1); 
    
    objects.push_back(new Object3DTriangle(pts[0], pts[1], pts[2], matFront));  
    objects.push_back(new Object3DTriangle(pts[0], pts[2], pts[3], matRight));  
    objects.push_back(new Object3DTriangle(pts[0], pts[3], pts[1], matLeft));   
    objects.push_back(new Object3DTriangle(pts[1], pts[3], pts[2], matBottom)); 

    MaterialSimple* modelMat = new MaterialSimple(color.HexToRgb("#8A2BE2"), 0.1, 1.0, 1.0, 0.2); 

    ModelLoader::load("model_cube.obj", objects, modelMat, Vector3D(-0.75, 0, 0), Vector3D(0, -35, 0), 0.1);
    //ModelLoader::load("model_shuttle.obj", objects, modelMat, Vector3D(-1.3, 0, 0.4), Vector3D(270, 45, 0), 0.07);
    //ModelLoader::load("model_teapot.obj", objects, modelMat, Vector3D(-1.2, 0, 0.5), Vector3D(0, 0, 0), 0.004);
    //ModelLoader::load("model_doughnut.obj", objects, modelMat, Vector3D(-1.2, 0, 0.5), Vector3D(0, 0, 0), 0.004);

    vector<Light*> lights;
    lights.push_back(new Light(Vector3D(-1, 15, -1), color.HexToRgb("#FFFFFF")));
    lights.push_back(new Light(Vector3D(2, 1, -10), color.HexToRgb("#FFACF4")));

    Scene scene = Scene(camera, objects, lights, width, height);
    Engine engine = Engine();

    Vector3D target(0, 0, 0);

    //Image image = engine.render(scene, target, false, false, false, false, true); //only shapes
    //Image image = engine.render(scene, target, true, false, false, false, true); //only shading
    //Image image = engine.render(scene, target, true, false, true, false, true); //raytracing without shadows
    Image image = engine.render(scene, target, true, true, true, false, true); //raytracing with shadows
    //Image image = engine.render(scene, target, true, true, true, true, true); //full

    image.exportImage("00 - Result.ppm");

    auto timerEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = timerEnd - timerStart;
    cout << "Time elapsed : " << round(elapsed.count() * 100.0) / 100.0 << " seconds\n";

    for (Object3D* obj : objects) { delete obj; }
    for (Light* light : lights) { delete light; }

    return 0;
}