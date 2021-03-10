#pragma once

#include <vector>
#include <string>

#include "Ray.h"
#include "Vector.h"

class Skybox{

	private:

	std::vector<Vector> texture;

	float phi = 0.0f;
	
	int textWidth;
	int textHeight;

	public:

	Skybox(const std::string& textAddr);

	const Vector& sampleTexture(const Ray& ray) const;

	/* getters */

	inline int getTextureWidth(void) const 	{ return textWidth; }
	inline int getTextureHeight(void) const { return textHeight; }


	/* setters */
	void setPhi(float phi_);
};
