#pragma once


#include <vector>
#include <fstream>
#include <ostream>

#include "Vector.h"
#include "RayTracerConstants.h"




/* ppm saver having a Vector frame buffer */
void Vector_to_string(const Vector& vec, std::string& str);

bool savePPM(const std::string& address,
	     const std::vector<Vector>& framebuffer,
	     unsigned int width = WIDTH,
	     unsigned int height = HEIGHT);


void readPPM(const std::string& address,
	     std::vector<float>& framebuffer);


