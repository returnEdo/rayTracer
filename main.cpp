#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Ray.h"
#include "Skybox.h"
#include "Renderer.h"
#include "Sphere.h"
#include "ChequeredPlane.h"
#include "Collision.h"
#include "Vector.h"
#include "Camera.h"
#include "PPMtools.h"


int main(){

	const int width = 1500;
	const int height = width;
	
	std::string address = "renderings/trial.ppm";
	std::string textAddr = "earth.jpg";
	std::string skyAddr = "skyboxes/milky.jpg";
	std::vector<Vector> colors;

	float r = 1.0f;

	Skybox skybox(skyAddr);
	skybox.setPhi(3.14f);

	Camera camera(Vector(.0f * r, .2f, 6.0f * r), Vector(.0f, .0f, .0f));
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setSkybox(skybox);
	renderer.setRays(camera);

	Sphere sphere1(Vector(r * 2.0f, 0.0f, -r * 6.0f), r);
	sphere1.getMaterial().color = Vector(.8f, .2f, .2f);
	sphere1.getMaterial().psia = .3f;
	sphere1.getMaterial().psis = .8f;
	sphere1.getMaterial().psid = .6f;
	sphere1.getMaterial().rhor = .17f;
	sphere1.getMaterial().rhoe = .00f;
	sphere1.getMaterial().f = 8.0f;
	sphere1.getMaterial().eta = 1.23f;
//
//	Sphere sphere2(Vector(), r);
//	sphere2.getMaterial().color = Vector(.2f, .8f, .2f);
//	sphere2.getMaterial().psia = .3f;
//	sphere2.getMaterial().psis = .9f;
//	sphere2.getMaterial().psid = .6f;
//	sphere2.getMaterial().rhor = .3f;
//	sphere2.getMaterial().rhoe = .0f;
//	sphere2.getMaterial().f = 400.0f;

	Sphere sphere2(Vector(), r);
	sphere2.getMaterial().color = Vector(.3f, .3f, .3f);
	sphere2.getMaterial().psia = .3f;
	sphere2.getMaterial().psis = .6f;
	sphere2.getMaterial().psid = .6f;
	sphere2.getMaterial().rhor = .0f;
	sphere2.getMaterial().rhoe = .8f;
	sphere2.getMaterial().f = 400.0f;
	sphere2.getMaterial().eta = 1.2f;

	sphere2.setTexture(textAddr);

//	sphere2.setTexture(textAddr);

	Sphere sphere3(Vector(r * 2.0f, .0f, -r * 2.0f), r);
	sphere3.getMaterial().color = Vector(.2f, .2f, .8f);
	sphere3.getMaterial().psia = .3f;
	sphere3.getMaterial().psis = .4f;
	sphere3.getMaterial().psid = .6f;
	sphere3.getMaterial().rhor = .02f;
	sphere3.getMaterial().rhoe = .0f;
	sphere3.getMaterial().f = 100.0f;

	sphere3.setTexture(textAddr);


	Sphere sphere4(Vector(.0f, 4.0f * r, .0f), r * 2.0f);
	sphere4.getMaterial().color = Vector(.8f, .8f, .8f);
	sphere4.getMaterial().psia = .3f;
	sphere4.getMaterial().psis = .5f;
	sphere4.getMaterial().psid = .4f;
	sphere4.getMaterial().rhor = .95f;
	sphere4.getMaterial().rhoe = .00f;
	sphere4.getMaterial().f = 500.0f;
	
	ChequeredPlane plane(-2.0f * r, Vector(1.0f, .95f, .85f), Vector(.2f, .3f, .3f));
	plane.getMaterial().psia = .3f;
	plane.getMaterial().psis = .5f;
	plane.getMaterial().psid = .4f;
	plane.getMaterial().rhor = .5f;
	plane.getMaterial().rhoe = .00f;
	plane.getMaterial().f = 100.0f;
	

	Light light1(Vector(50.0f, 50.0f, 50.0f));
	Light light2(Vector(-2.0f * r, 40.0f, -2.0f * r));

	std::vector<Hittable*> hittables = {&sphere2,
					    &sphere1
					    };
	std::vector<Light> lights = {light1, light2};

	
	Vector f = sphere2.getCenter();
	float a = .15f;
	unsigned int N = 30;

//	renderer.depthOfField(camera, f, a, N, hittables, lights, colors);
	
	renderer.findColors(hittables, lights, colors);
	
	savePPM(address, colors, width, height);
	

	
	return 0;
}
