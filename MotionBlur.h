#pragma once

#include <vector>

#include "Scene.h"
#include "Hittable.h"
#include "Light.h"

/* for each hittable specify the velocity, at each iteration 
   progress the objects and then blur the images (constant velocity) */

class MotionBlur{

	private:
	
	Scene scene;
	
	std::vector<bool> mask;
	std::vector<Vector> v;			// velocities
	
	float dt;				// delta time between frames
	int N;					// number of steps
	int n = 0;				// current step
	
	void updateScene(void);


	public:

	MotionBlur(Scene& scene_, const std::vector<Vector>& v_, const std::vector<bool>& mask_, float dt, int N);
};
