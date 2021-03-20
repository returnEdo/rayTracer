#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Ray.h"
#include "Skybox.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Cylinder.h"
#include "ChequeredPlane.h"
#include "Collision.h"
#include "Vector.h"
#include "Camera.h"
#include "PPMtools.h"
#include "JPGTools.h"
#include "PastelPalette.h"


int main(){

	const int width = 100;
	const int height = width;
	
	std::string address = "renderings/trial.jpg";
	std::string textAddr = "earth.jpg";
	std::string skyAddr = "skyboxes/room.jpg";
	std::vector<Vector> colors;

	float r = 1.0f;

	Skybox skybox(skyAddr);
	skybox.setPhi(3.14f);

	Camera camera(Vector(.0f, 4.0f, 4.0f), Vector(.0f, .0f, .0f));
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	//renderer.setSkybox(skybox);
	renderer.setRays(camera);

	Sphere sphere1(Vector(1.0f, .0f, -3.0f), 3.0f);
	sphere1.getMaterial().color = MELON;
	sphere1.getMaterial().psia = .3f;
	sphere1.getMaterial().psis = .6f;
	sphere1.getMaterial().psid = .6f;
	sphere1.getMaterial().rhor = .17f;
	sphere1.getMaterial().rhoe = .00f;
	sphere1.getMaterial().f = 108.0f;
	sphere1.getMaterial().eta = 1.23f;

	Cuboid cuboid(Vector(1.0f, 1.0f, 1.0f), Vector(), Vector(1.0f, .0f, .0f), .75);
	cuboid.getMaterial().color = MAGIC_MINT;
	cuboid.getMaterial().psia = .3f;
	cuboid.getMaterial().psis = .6f;
	cuboid.getMaterial().psid = .6f;
	cuboid.getMaterial().rhor = .25f;
	cuboid.getMaterial().rhoe = .00f;
	cuboid.getMaterial().f = 108.0f;
	cuboid.getMaterial().eta = 1.23f;

	Cylinder cylinder(4.0f, 1.3f, Vector(.0f, -2.0f, .0f), Vector(.0f, .0f, 1.0f), .0f);
	cylinder.getMaterial().color = Vector(.8f, .2f, .2f);
	cylinder.getMaterial().psia = .3f;
	cylinder.getMaterial().psis = .7f;
	cylinder.getMaterial().psid = .6f;
	cylinder.getMaterial().rhor = .25f;
	cylinder.getMaterial().rhoe = .70f;
	cylinder.getMaterial().f = 108.0f;
	cylinder.getMaterial().eta = 1.13f;

	ChequeredPlane plane(-2.0f, INDIGO, SALMON);


	Light light1(Vector(10.0f, .0f, .0f));

	std::vector<Hittable*> hittables = {
					    &sphere1
					    };
	std::vector<Light> lights = {light1};
	
	renderer.setSamples(500);
	renderer.findColors(hittables, lights, camera, colors);
	
	saveJpg(address, renderer.getWidth(), renderer.getHeight(), colors);
	
	return 0;
}
