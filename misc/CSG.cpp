#include "CSG.h"

#include "RayTracerConstants.h"

 CSG::CSG(Hittable* h1_, Hittable* h2_, const BOperation& type_):
		h1(h1_),
		h2(h2_),
		type(type_) {

}


void CSG::findInterval(const Ray& ray, Hittable* hittable, Interval& interval){

	Collision collision;

	hittable -> checkCollision(ray, collision);

}
