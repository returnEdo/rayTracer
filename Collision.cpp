#include "Collision.h"


void Collision::operator =(const Collision& col){

	v = col.v;
	n = col.n;
	material = col.material;
	distance = col.distance;
	hasCollided = col.hasCollided;
}
