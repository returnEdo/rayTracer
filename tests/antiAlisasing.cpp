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

	const int width = 1000;
	const int height = width;
	
	std::string textAddr = "earth.jpg";
	std::string skyAddr = "skyboxes/hills.jpg";
	std::vector<Vector> colors;

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

	Camera camera(Vector(.0f, .0f, 1.7f), Vector());
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setAmbientOcclusionSamples(60.0);
//	renderer.setIsOcclusion(true);
	renderer.setOcclusionExponent(0.8f);
	renderer.setSamples(20);

	Sphere sphere(Vector(.0f, .0f, .0f), 1.0f);
	Cylinder cylinder(2.5f, .7f, Vector(2.0f, .0f, -1.0f), Vector(.0f, 1.0f, .0f), .0f);
	Cuboid cuboid(Vector(3.0f, 3.0f, 1.0f), Vector(-3.0f, .0f, -1.0f), Vector(.0f, 1.0f, .0f), M_PI / 5.0f);
	ChequeredPlane plane(.0f, Vector(.7, .7, .7), Vector(.7, .7, .7));

	sphere.setMaterial(material);
	cuboid.setMaterial(material);
	cylinder.setMaterial(material);
	plane.setMaterial(material);

	Light light1(Vector(10.0f, 10.0f, 10.f), Vector(1.0f));
	
	std::vector<Hittable*> hittables = {
					    &sphere
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
