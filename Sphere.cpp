#include "Sphere.h"

#include <cmath>


Sphere::Sphere(const Vector& center_, float radius_):
		center(center_), radius(radius_)	{}


const Vector& Sphere::sampleTexture(float theta, float y) const{

	theta += M_PI;

	theta = (theta < .0f? .0f: theta);
	theta = (theta > 2.0f * M_PI? 2.0f * M_PI: theta);

	y = (y > radius? radius: y);
	y = (y < -radius? -radius: y);
	
	int wi = static_cast<int>(static_cast<float>(textWidth) * theta / (2.0f * M_PI));
	int hi = static_cast<int>((radius - y) * (static_cast<float>(textHeight)) / (2.0f * radius));

	return texture[hi * textWidth + wi]; 
}


 void Sphere::checkCollision(const Ray& ray, Collision& collision){
	
	Vector m = ray.getOrigin() - center;

	float b = ray.getDirection() * m;
	float c = norm2(m) - radius * radius;

	float delta2 = b * b - c;			// discriminant

	if (delta2 < .0f){
			
		collision.hasCollided = false;
	}
	else {
		/* two possible distance (t >= 0) */
		float t1 = -b + sqrt(delta2);
		float t2 = -b - sqrt(delta2);
		float t;

		if (t1 > .0f and t2 > .0f){

			t = t2;				// the smallest one
		}
		else if (t1 > .0f and t2 < .0f){

			t = t1;
		}
		else{
			/* intersections are behind rays origin */
			collision.hasCollided = false;
			return;
		}

		collision.v = ray.getOrigin() + t * ray.getDirection();
		getNormal(collision.v, collision.n);

		collision.hasCollided = true;
		collision.distance = t;
	
		collision.material = &material;
		
		if (colorType == Color::TEXTURE){
			/* the surface is textured: so we need to sample it */

			Vector vl = collision.v - center;

			float theta = atan2(vl.x, vl.z);
			float y = vl.y;

			collision.material -> color = sampleTexture(theta, y);
		}
	}
}




void Sphere::getNormal(const Vector& v, Vector& n) const{
	
	n = v - center;
	n.normalize();
}



bool Sphere::isInside(const Vector& x) const{

	Vector diff = x - center;
	
	return norm(diff) <= radius;
}


