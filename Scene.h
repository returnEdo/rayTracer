#pragma once

#include <vector>

#include "Hittable.h"
#include "Light.h"


/* To be used in the postrpocessing process */


class Scene{

	private:

	std::vector<Hittable*> hittables;
	std::vector<Light*>	lights;


	public:

	Scene(std::vector<Hittable*>& hittables_, std::vector<Light*>& lights_);
	Scene(Scene& other);

	/* getters */

	inline std::vector<Hittable*>& getHittables(void) 	{ return hittables; }
	inline std::vector<Light*>&	getLights(void)		{ return lights; }


	/* setters */

	inline void addHittable(Hittable& hittable)	{ hittables.push_back(&hittable); }
	inline void addLight(Light& light)		{ lights.push_back(&light); }
};

