#include "Color.hpp"
#include "Vector3D.hpp"
#include "Object3DSphere.hpp"
#include "Object3D.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Light.hpp"
#include "MaterialSimple.hpp"
#include "MaterialCheckered.hpp"

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

    Vector3D camera = Vector3D(0, -0.3, -1);
    
    vector<Object3D*> objects;
    
    objects.push_back(new Object3DSphere(Vector3D(0, 10000.5, 1), 10000.0, new MaterialSimple(color.HexToRgb("#111111"), 0.2, 1.0, 1.0, 0.2)));

    objects.push_back(new Object3DSphere(Vector3D(-0.25, 0, 0.6), 0.5, new MaterialSimple(color.HexToRgb("#FF0000"))));

    objects.push_back(new Object3DSphere(Vector3D(-0.15, -0.1, 0.15), 0.1, new MaterialSimple(color.HexToRgb("#FFFFFF"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.12, -0.12, 0.05), 0.05, new MaterialSimple(color.HexToRgb("#000000"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.4, -0.1, 0.15), 0.1, new MaterialSimple(color.HexToRgb("#FFFFFF"), 0.05, 1.0, 1.0, 0.01)));
    objects.push_back(new Object3DSphere(Vector3D(-0.37, -0.12, 0.05), 0.05, new MaterialSimple(color.HexToRgb("#000000"), 0.05, 1.0, 1.0, 0.01)));
    
    objects.push_back(new Object3DSphere(Vector3D(1.3, -0.15, 1), 0.75, new MaterialSimple(color.HexToRgb("#FFFF00"))));
    
    objects.push_back(new Object3DSphere(Vector3D(1, -1.85, 8), 0.75, new MaterialSimple(color.HexToRgb("#00FF00"))));

    objects.push_back(new Object3DSphere(Vector3D(-5, 3, 5), 5, new MaterialCheckered(color.HexToRgb("#0000FF"), color.HexToRgb("#FFFFFF"))));

    vector<Light*> lights;
    lights.push_back(new Light(Vector3D(-1, -15, -1), color.HexToRgb("#FFFFFF")));
    lights.push_back(new Light(Vector3D(2, -1, -10), color.HexToRgb("#FFACF4")));

    Scene scene = Scene(camera, objects, lights, width, height);

    Engine engine = Engine();

    Image image = engine.render(scene, true, false, true);

    image.exportImage("XX - Result.ppm");

    auto timerEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = timerEnd - timerStart;
    cout << "Time elapsed : " << round(elapsed.count() * 100.0) / 100.0 << " seconds\n";

    for (Object3D* obj : objects)
    {
        delete obj;
    }
    for (Light* light : lights) 
    {
        delete light; 
    }

    return 0;
}