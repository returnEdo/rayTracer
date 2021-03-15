#include "Cylinder.h"

#include <cmath>
#include <limits>
#include <algorithm>


Cylinder::Cylinder(float h_, float r_, const Vector& x_, const Vector& k, float theta):
		h(h_),
		r(r_),
		x(x_) {
	
	R = Matrix(k, theta);
	R = transpose(R);
}


bool Cylinder::isInsideLocal(const Vector& v) const{

	return ((v.x * v.x + v.z * v.z - r * r) < .0f and v.y > .0f and v.y < h);
}


void Cylinder::checkCollision(const Ray& ray, Collision& collision){

	/* ray in local coordinates */
	Vector o = R * (ray.getOrigin() - x);
	Vector d = R * ray.getDirection();

	bool inside = isInsideLocal(o);
	
	float a = d.x * d.x + d.z * d.z;
	float e = o.x * d.x + o.z * d.z;
	float c = o.x * o.x + o.z * o.z - r * r;

	float delta = e * e - a * c;

	/* negative discrimanant */
	if (delta < .0f)

		return;

	float t = (inside? -e + sqrt(delta): -e - sqrt(delta)) / a;
	t = (t < .0f? std::numeric_limits<float>::max(): t);

	float tcapup = std::numeric_limits<float>::max();
	float tcaplow = std::numeric_limits<float>::max();
	
	if (d.y != 0.0f){

		tcapup = (h - o.y) / d.y;
		tcaplow = -o.y / d.y;

		tcapup = (tcapup < .0f? std::numeric_limits<float>::max(): tcapup);
		tcaplow = (tcaplow < .0f? std::numeric_limits<float>::max(): tcaplow);
	}

	std::vector<Vector> vv = {
		o + d * t,
		o + d * tcapup,
		o + d * tcaplow
	};

	std::vector<bool> mask = {
		(vv[0].y >= .0f and vv[0].y <= h),
		(vv[1].x * vv[1].x + vv[1].z * vv[1].z <= r*r),
		(vv[2].x * vv[2].x + vv[2].z * vv[2].z <= r*r),
	};
	
	std::vector<float> tt = { t, tcapup, tcaplow };
	std::vector<Vector> nn = {
		Vector(vv[0].x / r, .0f, vv[0].z / r),
		Vector(.0f, 1.0f, .0f),
		Vector(.0f, -1.0f, .0f)
	};
	
	float min = std::numeric_limits<float>::max();
	int i;
	
	for (int j = 0; j < tt.size(); j++){

		if (tt[j] < min and mask[j]){

			min = tt[j];
			i = j;
		}
	}
	

	if (min < std::numeric_limits<float>::max() - 1.0f){
		
		collision.v = transpose(R) * vv[i] + x;
		collision.n = transpose(R) * nn[i];
		collision.distance = tt[i];
		collision.material = &material;
		collision.hasCollided = true;
	}

}


const Vector& Cylinder::sampleTexture(float l, float theta) const{

	return x;
}



bool Cylinder::isInside(const Vector& v) const{

	Vector vl = R * (v - x);

	return isInsideLocal(vl);
}




