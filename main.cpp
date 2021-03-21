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

	const int width = 1500;
	const int height = width;
	
	std::string textAddr = "textures/earth.jpg";
	std::string skyAddr = "skyboxes/cliff.jpg";
	std::vector<Vector> colors;

	Material material;
	material.color = Vector(.2f, .2f, .2f);
	material.psia = .3f;
	material.psis = .5f;
	material.psid = .4f;
	material.rhor = .2f;
	material.rhoe = .0f;
	material.f = 200.0f;
	
	Material material1;
	material1.color = SALMON;
	material1.psia = .3f;
	material1.psis = .5f;
	material1.psid = .3f;
	material1.rhor = .4f;
	material1.rhoe = .0f;
	material1.f = 10.0f;
	material1.glossy_radius = .1f;


	Skybox skybox(skyAddr);
	skybox.setPhi(M_PI / 2.0f);

	Camera camera(Vector(.0f, .1f, 1.7f), Vector());
	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setAmbientOcclusionSamples(60.0);
//	renderer.setIsOcclusion(true);
	renderer.setOcclusionExponent(0.8f);
	renderer.setSamples(10);
	//renderer.setSkybox(skybox);

	ChequeredPlane plane(-1.0f, Vector(.8, .3, .3), Vector(.3, .8, .3));
	plane.setMaterial(material1);

	Sphere sphere(Vector(.0f, .0f, .0f), 1.0f);
	sphere.setTexture(textAddr);
	Sphere sphere1(Vector(1.0f, 0.0f, -1.0f), 1.0f);

	sphere.setMaterial(material);
	sphere1.setMaterial(material1);
	
	Light light1(Vector(10.0f, 10.0f, 10.f), Vector(1.0f));
	Light light2(Vector(10.0f, 20.0f, 10.0f), Vector(1.0f));
	
	std::vector<Hittable*> hittables = {
					    &sphere,
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
