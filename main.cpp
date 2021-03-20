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

	const int width = 800;
	const int height = width;
	
	std::string textAddr = "textures/earth.jpg";
	std::string skyAddr = "skyboxes/campus.jpg";
	std::vector<Vector> colors;

	Material material;
	material.color = SALMON;
	material.psia = .3f;
	material.psis = .5f;
	material.psid = .5f;
	material.rhor = .3f;
	material.rhoe = .0f;
	material.f = 100.0f;

	Material mat;
	mat.color = INDIGO * .6f;
	mat.psia = .4f;
	mat.psis = .6f;
	mat.psid = .5f;
	mat.rhor = .1f;
	mat.rhoe = .7f;
	mat.f = 100.0f;
	mat.eta = 1.22f;

	Skybox skybox(skyAddr);
	skybox.setPhi(M_PI / 2.0f * 3.0f);

	float distance = 5.0f;
	float rho = 1.7f;

	Camera camera(Vector(.0f, .0f, distance + 2.0f), Vector());
	camera.setFOV(M_PI / 3.0f);

	Renderer renderer(width, height);
	renderer.setIsBar(true);
	renderer.setAmbientOcclusionSamples(60.0);
//	renderer.setIsOcclusion(true);
	renderer.setOcclusionExponent(0.8f);
	renderer.setSamples(3);
	

	Sphere sphere1(Vector(), 1.0f);
	Sphere sphere2(Vector(.0f, rho, distance), 1.0f);
	Sphere sphere3(Vector(rho * cos(M_PI / 6.0f), -rho * sin(M_PI / 6.0f), distance), 1.0f);
	Sphere sphere4(Vector(-rho * cos(M_PI / 6.0f), -rho * sin(M_PI / 6.0f), distance), 1.0f);

	Sphere sphere7(Vector(.0f, -rho * 2.0f, -distance), 2.0f);
	Sphere sphere5(Vector(rho *2.0f* cos(M_PI / 6.0f), rho *2.0f* sin(M_PI / 6.0f), -distance), 2.0f);
	Sphere sphere6(Vector(-rho *2.0f* cos(M_PI / 6.0f), rho *2.0f* sin(M_PI / 6.0f), -distance), 2.0f);

	float f = .7f;

	sphere1.setMaterial(mat);

	sphere2.setMaterial(material);
	sphere2.getMaterial().color = PURPLE * f;

	sphere3.setMaterial(material);
	sphere3.getMaterial().color = MAGIC_MINT * f;

	sphere4.setMaterial(material);
	sphere4.getMaterial().color = INDIGO * f;

	sphere5.setMaterial(material);
	sphere5.getMaterial().color = PURPLE * f;

	sphere6.setMaterial(material);
	sphere6.getMaterial().color = MAGIC_MINT * f;

	sphere7.setMaterial(material);
	sphere7.getMaterial().color = INDIGO * f;



	Light light1(Vector(-3.0f, 10.0f, 0.f), Vector(1.0f));
	Light light2(Vector(3.0f, 10.0f, 0.f), Vector(1.0f));
	
	std::vector<Hittable*> hittables = {
					    &sphere1,
					    &sphere2,
					    &sphere3,
					    &sphere4,
					    &sphere5,
					    &sphere6,
					    &sphere7
					    };
	std::vector<Light*> lights = {&light1, &light2};

	
	float a = .06f;
	int N = 26;

	DepthOfField dof(Vector(), a);
	dof.render(hittables, lights, renderer, camera, colors, N);	

//	renderer.findColors(hittables, lights, camera, colors);

	saveJpg(address, renderer.getWidth(), renderer.getHeight(), colors);
	

	
	return 0;
}
