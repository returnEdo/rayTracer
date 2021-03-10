#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Ray.h"
#include "Renderer.h"
#include "Sphere.h"
#include "ChequeredPlane.h"
#include "Collision.h"
#include "Vector.h"
#include "Camera.h"
#include "PPMtools.h"


int main(){

	const int width = 900;
	const int height = width;
	
	std::string address = "renderings/trial.ppm";
	std::string textAddr = "earth.jpg";
	std::vector<Vector> colors;

	float r = 1.0f;

	Camera camera(Vector(3.0f, 5.0f, .0f), Vector(.0f, .0f, .0f));
	Renderer renderer(width, height);
	renderer.setIsBar(false);
	renderer.setRays(camera);

	Sphere sphere1(Vector(), r);
	sphere1.getMaterial().color = Vector(.8f, .2f, .2f);
	sphere1.getMaterial().psia = .3f;
	sphere1.getMaterial().psis = .8f;
	sphere1.getMaterial().psid = .6f;
	sphere1.getMaterial().rhor = .17f;
	sphere1.getMaterial().rhoe = .00f;
	sphere1.getMaterial().f = 8.0f;
	sphere1.getMaterial().eta = 1.23f;

	sphere1.setTexture(textAddr);

	Sphere sphere2(Vector(2.0f, .0f, 2.0f), r);
	sphere2.getMaterial().color = Vector(.8f, .2f, .2f);
	sphere2.getMaterial().psia = .3f;
	sphere2.getMaterial().psis = .8f;
	sphere2.getMaterial().psid = .6f;
	sphere2.getMaterial().rhor = .17f;
	sphere2.getMaterial().rhoe = .00f;
	sphere2.getMaterial().f = 8.0f;
	sphere2.getMaterial().eta = 1.23f;



	Light light1(Vector(50.0f, 50.0f, 50.0f));
	Light light2(Vector(-2.0f * r, 40.0f, -2.0f * r));

	std::vector<Hittable*> hittables = {&sphere1,
					    &sphere2
					    };
	std::vector<Light> lights = {light1, light2};

	
//	Vector f = sphere2.getCenter();
	float a = .15f;
	unsigned int N = 30;

//	renderer.depthOfField(camera, f, a, N, hittables, lights, colors);
	renderer.findColors(hittables, lights, colors);
	
	savePPM(address, colors, width, height);
	

	
	return 0;
}
