#include "SpotLight.h"

#include <cmath>

SpotLight::SpotLight(const Vector& position_, const Vector& color_, const std::array<float, 3>& k_, const Vector& direction_, float p_):
		Light(position_, color_),
		k(k_),
		direction(direction_),
		p(p_) {
	
	direction.normalize();
}


float SpotLight::getIntensityAt(const Vector& x) const{

	
	Vector lightVec = x - position;
	float d = lightVec.norm();
	lightVec /= d;

	float scl = lightVec * direction;
	
	if (scl <= .0f){

		return .0f;
	}
	else{	
	
		return pow(scl, p) / (k[0] + d * k[1] + d * d * k[2]);
	}
}
