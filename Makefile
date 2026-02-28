output: Raytracer.o Image.o Color.o Vector3D.o Engine.o Ray.o ModelLoader.o Object3DSphere.o Object3DPlane.o Object3DTriangle.o Object3DQuad.o Object3DCube.o Object3D.o Scene.o Light.o MaterialSimple.o MaterialCheckered.o Material.o
	g++ Raytracer.o Image.o Color.o Vector3D.o Engine.o Ray.o ModelLoader.o Object3DSphere.o Object3DPlane.o Object3DTriangle.o Object3DQuad.o Object3DCube.o Object3D.o Scene.o Light.o MaterialSimple.o MaterialCheckered.o Material.o -o output

Raytracer.o: Raytracer.cpp
	g++ -c Raytracer.cpp

Image.o: Image.cpp
	g++ -c Image.cpp

Color.o: Color.cpp
	g++ -c Color.cpp

Vector3D.o: Vector3D.cpp
	g++ -c Vector3D.cpp

Engine.o: Engine.cpp
	g++ -c Engine.cpp

Ray.o: Ray.cpp
	g++ -c Ray.cpp

ModelLoader.o: ModelLoader.cpp
	g++ -c ModelLoader.cpp

Object3DTriangle.o: Object3DTriangle.cpp
	g++ -c Object3DTriangle.cpp

Object3DSphere.o: Object3DSphere.cpp
	g++ -c Object3DSphere.cpp   

Object3DPlane.o: Object3DPlane.cpp
	g++ -c Object3DPlane.cpp   

Object3DQuad.o: Object3DQuad.cpp
	g++ -c Object3DQuad.cpp   

Object3DCube.o: Object3DCube.cpp
	g++ -c Object3DCube.cpp   
    
Object3D.o: Object3D.cpp
	g++ -c Object3D.cpp
    
Scene.o: Scene.cpp
	g++ -c Scene.cpp    

Light.o: Light.cpp
	g++ -c Light.cpp

MaterialSimple.o: MaterialSimple.cpp
	g++ -c MaterialSimple.cpp

MaterialCheckered.o: MaterialCheckered.cpp
	g++ -c MaterialCheckered.cpp

Material.o: Material.cpp
	g++ -c Material.cpp



run: output
	./output

clean:
	rm *.o output