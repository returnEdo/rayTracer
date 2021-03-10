#include "PPMtools.h"
#include "Vector.h"
#include "Sphere.h"
#include "ChequeredPlane.h"
#include "Light.h"
#include "Renderer.h"
#include "Material.h"

#include <vector>
#include <string>
#include <memory>


int main(int argc, char* argv[]){

	std::vector<Vector> data;
	std::string addr = "renderings/trial.ppm";
	
	Light light(Vector(.0f, 2.0f, -2.0f));

	unsigned int dim = 500;		// 1250

	Renderer renderer(dim, dim);

//	std::vector<std::unique_ptr<Hittable> > spheres;
//	spheres.push_back(std::make_unique<Sphere>(Vector(2.0f, -1.0f, -3.5f), 1.0f));
//	spheres.push_back(std::make_unique<Sphere>(Vector(0.0f, 2.0f, -3.5f), 1.0f));
//	spheres.push_back(std::make_unique<Sphere>(Vector(-2.0f, -1.0f, -3.5f), 1.0f));
//
//	(spheres[0] -> setMaterial(Material(Vector(1.0f, .0f, .0f), 100.0f, .20f, .50f, 1.0f, 1.0f, 1.0f)));
//	(spheres[1] -> setMaterial(Material(Vector(.0f, .0f, 1.0f), 100.0f, .20f, .50f, 1.0f, 1.0f, 1.0f)));
//	(spheres[2] -> setMaterial(Material(Vector(.0f, 1.0f, .0f), 100.0f, 0.90f, .0f, .0f, 1.0f, .0f)));
//
//	std::vector<Light> lights = {
//		Light(Vector(6.0f, -1.0f, -3.5f)),
//		Light(Vector(4.5f, 4.5f, -3.5f), Vector(1.0f, 1.0f, .0f)),
//		Light(Vector(.0f, .0f, .0f), Vector(.2f, .2f, .2f))
//	};

	std::vector<std::unique_ptr<Hittable> > spheres;
	spheres.push_back(std::make_unique<Sphere>(Vector(.0f, .0f, -4.0f), 2.0f));
	spheres.push_back(std::make_unique<Sphere>(Vector(0.0f, .5f, -5.0f), 1.0f));

	(spheres[0] -> setMaterial(Material(Vector(1.0f, .0f, .0f), 100.0f, 0.01f, .95f, .0f, 1.0f, .6f)));	// red rubber
	(spheres[1] -> setMaterial(Material(Vector(.2f, .9f, .2f), 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, .6f)));	// mirror

	std::vector<Light> lights = {
		Light(Vector(20.0f, 20.0f, 20.0f)),
	};

	renderer.assembleFrameBuffer(spheres, lights, data);

	savePPM(addr, data, dim, dim);
	


	return 0;
}
