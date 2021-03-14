#pragma once

#include <vector>

#include "Vector.h"
#include "Hittable.h"
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"


class DepthOfField{

	private:

	Vector f;			// focal point
	float a;			// aperture

	public:

	DepthOfField(const Vector& f_, float a_);

	void render(std::vector<Hittable*>& hittables, std::vector<Light*>& lights, 
		    Renderer& renderer, const Camera& cam, std::vector<Vector>& colors, int N = 10) const;
};
