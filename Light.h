#pragma once

#include "Vector.h"
#include "RayTracerConstants.h"

class Light{

	private:
	
	Vector position;
	Vector color;

	public:

	Light(const Vector& position_, const Vector& color_ = DEF_LIGHT_COL);

	/* getters */
	inline const Vector& getPosition(void) const 	{ return position; }
	inline const Vector& getColor(void) const	{ return color; }
};
