#include "CSG.h"

#include "RayTracerConstants.h"

 CSG::CSG():
		h1(h1_),
		h2(h2_),
		type(type_) {

}


void findIntersections(const Ray& ray, Hittable* hittable, std::vector<Collision>& collisions){
	/* finds all the collisions (max 2 are expected since the basic shapes are convex) */

	Collision tempCollision;
	hittable -> checkCollision(ray, tempCollision);
	
	/* there is no hope for a second collision */
	if (not tempCollision.hasCollided)	{ return; }

	collisions.push_back(tempCollision);

	float t = tempCollision.distance;
	Vector newOrigin = collision.v + ray.getDirection() * DELTA;		// shift the origin forward

	Ray tempRay(newOrigin, ray.getDirection());
	hittable -> checkCollision(tempRay, tempCollision);

	if (not tempCollision.hasCollided)	{ return; }

	tempCollision.distance += t + DELTA;					// distance is from ray.getOrigin()
	collisions.push_back(tempCollision);
}


void CSG::checkCollision(const Ray& ray, Collision& collision){

	bool inside = isInside(ray.getOrigin());

	std::vector<Collision>& h1_collisions;
	std::vector<Collision>& h2_collisions;

	findIntersections(ray, h1, h1_collisions);
	findIntersections(ray, h2, h2_collisions);
}


const Vector& CSG::sampleTexture() const{

	return h1.material.color;
}


bool CSG::isInside(const Vector& x) const{o

	
	bool isIn_h1 = h1 -> isInside(x);
	bool isIn_h2 = h2 -> isInside(x);
	

	switch(this -> type){

		case (BOperation::UNION):

			return (isIn_h1 or isIn_h2);


		case (BOperation::DIFFERENCE):

			return (isIn_h1 and not isIn_h2);


		case (BOperation::INTERSECTION):

			return (isIn_h1 and isIn_h2);
	}
}

