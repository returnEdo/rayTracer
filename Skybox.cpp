#include "Skybox.h"

#include <cmath>

#include "JPGTools.h"


Skybox::Skybox(const std::string& textAddr){

	readJpg(textAddr, &textWidth, &textHeight, texture);
}

const Vector& Skybox::sampleTexture(const Ray& ray) const{
	/* sky is considered at infty */

	float theta = atan2(ray.getDirection().x, ray.getDirection().z);
	float y = ray.getDirection().y;

	float radius = 1.0f;
	
	float psi = (theta > phi? theta - phi: (2.0f * M_PI + theta - phi));

	y = (y > radius? radius: y);
	y = (y < -radius? -radius: y);

	int wi = static_cast<int>(static_cast<float>(textWidth) * psi / (2.0f * M_PI));
	int hi = static_cast<int>((radius - y) * (static_cast<float>(textHeight)) / (2.0f * radius));
	
	int indx = hi * textWidth + wi;
	if (indx >= 0 and indx < texture.size()){
		return texture[hi * textWidth + wi]; 
	}
	else{
		return texture[0];
	}
}


void Skybox::setPhi(float phi_){

	if (phi_ > 0)

		phi = fmod(phi_, 2.0f * M_PI);
	
	else

		phi = 2.0f * M_PI - fmod(-phi_, 2.0f * M_PI);
}
