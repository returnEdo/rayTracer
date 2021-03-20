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
#include "DepthOfField.h"
#include "PastelPalette.h"
#include "LightSystem.h"


int main(int argc, char** argv){
	
	std::string address = "rayTracer";
	if (argc > 0){
		
		address = std::string(*(argv+1));
	}
	address = "renderings/" + address + ".jpg";

	const int width = 3000;
	const int height = 1500;
	
	std::string textAddr = "earth.jpg";
	std::string skyAddr = "skyboxes/cliff.jpg";
	std::vector<Vector> colors;

	float side = 5.0f;
	float distance = 10.0f;

	Material glass;
	glass.color = Vector(.2f, .2f, .2f);
	glass.psia = .3f;
	glass.psis = .7f;
	glass.psid = .5f;
	glass.rhor = .97f;
	glass.rhoe = .0f;
	glass.f = 100.0f;
	glass.glossy_radius = .0001f;

	Material material;
	material.color = SALMON;
	material.psia = .3f;
	material.psis = .5f;
	material.psid = .5f;
	material.rhor = .0f;
	material.rhoe = .0f;
	material.f = 100.0f;

	Skybox skybox(skyAddr);
	skybox.setPhi(M_PI / 2.0f);

	Camera camera(Vector(side *3.0f / 4.0f, side / 2.0f, distance - DELTA), Vector(side / 2.0f, side / 2.0f, .0f));
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setSkybox(skybox);
	renderer.setAmbientOcclusionSamples(60.0);
//	renderer.setIsOcclusion(true);
	renderer.setOcclusionExponent(0.8f);
	renderer.setSamples(5);

	Vector k(-2.0f,- 3.0f, .0f);
	k.normalize();

	Sphere sphere(Vector(.0f, .0f, distance / 3.0f), 1.5f);
	Cuboid cuboidf(Vector(side, side, 1.0f), Vector(.0f, .0f, distance), Vector(.0f, 1.0f, .0f), .0f);
	Cuboid cuboidb(Vector(side, side, 1.0f), Vector(), Vector(.0f, 1.0f, .0f), .0f);
	Cuboid cube(Vector(2.0f, 2.0f, 2.0f), Vector(side, .0f, distance / 3.0f), k, M_PI / 2.0f);

	sphere.setMaterial(glass);
	sphere.getMaterial().glossy_radius = .08f;
	cuboidf.setMaterial(glass);
	cuboidb.setMaterial(glass);
	cube.setMaterial(glass);


	Light light1(Vector(-10.0f, 10.0f, distance / 2.0f), Vector(1.0f));
	
	std::vector<Hittable*> hittables = {
					    &sphere,
					    &cuboidf,
					    &cuboidb
					    };
	std::vector<Light*> lights = {&light1};

	
	float a = .08f;
	int N = 20;

	DepthOfField dof(Vector(), a);
//	dof.render(hittables, lights, renderer, camera, colors, N);	

	renderer.findColors(hittables, lights, camera, colors);

	saveJpg(address, renderer.getWidth(), renderer.getHeight(), colors);
	

	
	return 0;
}
