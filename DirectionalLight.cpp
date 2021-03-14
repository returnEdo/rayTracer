#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(const Vector& position_, const Vector& color_, const std::array<float, 3>& k_):
		Light(position_, color_),
		k(k_)	{

}



float DirectionalLight::getIntensityAt(const Vector& x) const{
	
	Vector diff = x - position;
	float d = norm(diff);
	
	return 1.0f / (k[0] + k[1] * d + k[2] * d * d);
}
