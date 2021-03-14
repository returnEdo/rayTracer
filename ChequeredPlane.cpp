#include "ChequeredPlane.h"

#include <cmath>


ChequeredPlane::ChequeredPlane(float a_, const Vector& col1_, const Vector& col2_):
		a(a_), col1(col1_), col2(col2_) {}


void ChequeredPlane::setColor(float x, float z){

	int ev = static_cast<int>(floor(x) + floor(z));
	
	material.color = (ev % 2 == 0? col1: col2);

}



void ChequeredPlane::checkCollision(const Ray& ray, Collision& collision){

	float t = (a - ray.getOrigin().y) / ray.getDirection().y;

	if (t < .0f){

		collision.hasCollided = false;
	}
	else{
		
		collision.v = ray.getOrigin() + t * ray.getDirection();
		collision.n = Vector(.0f, 1.0f, .0f);
	
		collision.hasCollided = true;
		collision.distance = t;

		collision.material = &material;

		setColor(collision.v.x, collision.v.z);

	}


}
