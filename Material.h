#pragma once

#include "Vector.h"
#include "RayTracerConstants.h"

/* Hittable material class with some physical properties */

class Material{

	public:

	Vector color 	= DEF_COLOR;
	
	float	rhor	= DEF_REFL;		// reflectivity -> set to 1 for mirror like
	float	rhoe 	= DEF_REFR;		// refractivity -> set to 1 for glass  like

	float	psid	= DEF_DIFF;		// diffusivity -> sets opaqueness
	float	psis	= DEF_SPEC;		// specularity -> sets shiness intensity
	float	psia	= DEF_AMB;		// ambientivity
	float	f	= DEF_EXP;		// specular exponent -> sets shiness dimension
	float 	eta 	= DEF_ETA;		// snell law ratio (>= 1.0f)

	void operator =(const Material& other);
};
