#include "Ray.h" 

Ray::Ray(const Vector& o_, const Vector& d_):
		o(o_), d(d_) 	{ d.normalize(); }

Ray::Ray(const Ray& other):
		o(other.o),
		d(other.d)	{ d.normalize(); }



void Ray::setDirection(const Vector& d_){

	d = d_;
	d.normalize();
}


std::ostream& operator <<(std::ostream& os, const Ray& ray){

	os << "\n\tOrigin:\t" << ray.o 
	   << "\n\tDirection:\t" << ray.d << std::endl;

	return os;
}
