#pragma once

#include <string>

#include "Vector.h"
#include "Camera.h"
#include "Renderer.h"


struct CameraProperties{

	Vector f;		// focal point

	float a;		// aperture

	CameraProperties(const Vector& f_, float a_);
};


float randf(float vmax);

void depthOfField(const Camera& cam, const CameraProperties& prop, const std::string& addri, unsigned int N);
