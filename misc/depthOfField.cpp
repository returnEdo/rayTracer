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
#include "JPGTools.h"
#include "DepthOfField.h"
#include "PastelPalette.h"


int main(){

	const int width = 500;
	const int height = width;
	
	std::string address = "renderings/depthOfField.jpg";
	std::string textAddr = "earth.jpg";
	std::string skyAddr = "skyboxes/hills.jpg";
	std::vector<Vector> colors;


	Skybox skybox(skyAddr);
	skybox.setPhi(M_PI / 2.0f);

	Camera camera(Vector(.0f, -1.0f, 8.0f), Vector());
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setSkybox(skybox);

	Sphere sphere1(Vector(-4.0f, .0f, 4.0f), 2.0f);
	sphere1.getMaterial().color = MAGIC_MINT;
	sphere1.getMaterial().psia = .3f;
	sphere1.getMaterial().psis = .9f;
	sphere1.getMaterial().psid = .6f;
	sphere1.getMaterial().rhor = .30f;
	sphere1.getMaterial().rhoe = .00f;
	sphere1.getMaterial().f = 100.0f;

	Sphere sphere2(Vector(4.0f, .0f, -4.0f), 2.0f);
	sphere2.getMaterial().color = MELON;
	sphere2.getMaterial().psia = .3f;
	sphere2.getMaterial().psis = .9f;
	sphere2.getMaterial().psid = .6f;
	sphere2.getMaterial().rhor = .3f;
	sphere2.getMaterial().rhoe = .0f;
	sphere2.getMaterial().f = 400.0f;

//	sphere2.setTexture(textAddr);

	Sphere sphere3(Vector(.0f, -1.0f, .0f), 1.0f);
	sphere3.getMaterial().color = INDIGO;
	sphere3.getMaterial().psia = .3f;
	sphere3.getMaterial().psis = .9f;
	sphere3.getMaterial().psid = .6f;
	sphere3.getMaterial().rhor = .30;
	sphere3.getMaterial().rhoe = .0f;
	sphere3.getMaterial().f = 100.0f;

	ChequeredPlane plane(-2.0f, Vector(1.0f, .95f, .85f), Vector(.2f, .3f, .3f));
	plane.getMaterial().psia = .3f;
	plane.getMaterial().psis = .5f;
	plane.getMaterial().psid = .4f;
	plane.getMaterial().rhor = .5f;
	plane.getMaterial().rhoe = .00f;
	plane.getMaterial().f = 100.0f;
	

	Light light1(Vector(50.0f, 50.0f, 50.0f), Vector(1.0f));
	Light light2(Vector(.0f, 100.0f, .0f), Vector(1.0f));

	std::vector<Hittable*> hittables = {&sphere1,
					    &sphere2,
					    &sphere3,
					    &plane
					    };
	std::vector<Light*> lights = {&light1, &light2};

	
	float a = .08f;
	int N = 20;

	DepthOfField dof(Vector(), a);
//	dof.render(hittables, lights, renderer, camera, colors, N);	

	renderer.findColors(hittables, lights, camera, colors);

	saveJpg(address, renderer.getWidth(), renderer.getHeight(), colors);
	

	
	return 0;
}
