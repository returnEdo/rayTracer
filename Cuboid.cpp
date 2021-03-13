#include "Cuboid.h"


Cuboid::Cuboid(const Vector& r_, const Vector& x_, const Vector& k, float theta):
		r(r_),
		x(x_)	{
	
	R = Matrix(k, theta);
	R = transpose(R);
}



bool Cuboid::isInsideLocal(const Vector& v) const{
	
	return ((v.x >= .0f and v.x <= r.x) and
		(v.y >= .0f and v.y <= r.y) and
		(v.z >= .0f and v.z <= r.z));
}


void Cuboid::checkCollision(const Ray& ray, Collision& collision){
	
	/* ray in local coordinates */
	Vector o = R * (ray.getOrigin() - x);
	Vector d = R * ray.getDirection();

	bool inside = isInsideLocal(o);

	
	if (d.x != 0.0f and o.x * d.x <= .0f){
		
		bool frontface = (inside? (d.x > .0f): (o.x > .0f));
		float t = (frontface? (r.x - o.x) / d.x: -o.x / d.x);	

		if (t < collision.distance){
			/* the face is closer than the incumbent */

			Vector v = o + d * t;								// local coordinates
	
			//if (isInsideLocal(v)){							// we hit the cube
			if ((v.y >= .0f and v.y <= r.y) and (v.z >= .0f and v.z <= r.z)){

				collision.v = transpose(R) * v + x;
				collision.n = transpose(R) * (frontface? Vector(1.0f, .0f, .0f): Vector(-1.0f, .0f, .0f));
				collision.distance = t;
				collision.material = &material;
				collision.hasCollided = true;
			}
		}
	}

	if (d.y != 0.0f and o.y * d.y <= .0f){

		bool frontface = (inside? (d.y > .0f): (o.y > .0f));
		float t = (frontface? (r.y - o.y) / d.y: -o.y / d.y);	

		if (t < collision.distance){
			/* the face is closer than the incumbent */

			Vector v = o + d * t;					// local coordinates
	
			//if (isInsideLocal(v)){					// we hit the cube
			if ((v.x >= .0f and v.x <= r.x) and (v.z >= .0f and v.z <= r.z)){
				
				collision.v = transpose(R) * v + x;
				collision.n = transpose(R) * (frontface? Vector(.0f, 1.0f, .0f): Vector(.0f, -1.0f, .0f));
				collision.distance = t;
				collision.material = &material;
				collision.hasCollided = true;
			}
		}
	}

	if (d.z != 0.0f and o.z * d.z <= .0f){

		bool frontface = (inside? (d.z > .0f): (o.z > .0f));
		float t = (frontface? (r.z - o.z) / d.z: -o.z / d.z);	

		if (t < collision.distance){
			/* the face is closer than the incumbent */

			Vector v = o + d * t;					// local coordinates
	
			//if (isInsideLocal(v)){					// we hit the cube
			if ((v.y >= .0f and v.y <= r.y) and (v.x >= .0f and v.x <= r.x)){
				
				collision.v = transpose(R) * v + x;
				collision.n = transpose(R) * (frontface? Vector(.0f, .0f, 1.0f): Vector(.0f, .0f, -1.0f));
				collision.distance = t;
				collision.material = &material;
				collision.hasCollided = true;
			}
		}
	}

}




const Vector& Cuboid::sampleTexture(float u, float v) const{

	return x;
}
