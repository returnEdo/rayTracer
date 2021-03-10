#include "Rotor.h"

#include <cmath>


Rotor::Rotor(float aa, float bb, float cc, float dd):
	a(aa), b(bb), c(cc), d(dd)	{}

Rotor::Rotor(const Vector& k, float theta):
    a(cos(theta / 2)),
    b(sin(theta / 2))
	

float Rotor::norm(void){

	return sqrt(a*a + b*b + c*c + d*d);
}


void Rotor::normalize(void){

	float nrm = this -> norm(); 
	
	this -> a /= nrm;
	this -> b /= nrm;
	this -> c /= nrm;
	this -> d /= nrm;
}


void Rotor::EulerRodrigues(Matrix& S) const{

	S.row1 = Vector((a * a - b * b + c * c - d * d),
			   2.0 * (-a *  b +  c *  d),
		       	   2.0 * (a *  d +  b *  c));
	S.row2 = Vector(2.0 * (a *  b +  c *  d),
			   (a *  a -  b *  b - c * c + d * d),
			   2.0 * (-a *  c +  b *  d));
	S.row3 = Vector(2.0 * (-a *  d +  b *  c),
		           2.0 * (a *  c +  b *  d),
			   (a *  a +  b *  b - c * c - d * d));
	S.buildCol();
}

