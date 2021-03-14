#pragma once

#include "Vector.h"
#include "RayTracerConstants.h"

class Light{

	protected:
	
	Vector position;
	Vector color = DEF_LIGHT_COL; 

	public:

	Light(const Vector& position_, const Vector& color);

	/* setters */
	inline void setPosition(const Vector& position_) 	{ position = position_; }
	inline void setColor(const Vector& color_)		{ color = color_; }

	/* getters */
	inline const Vector& getPosition(void) const 	{ return position; }
	inline const Vector& getColor(void) const	{ return color; }
	
	inline virtual float getIntensityAt(const Vector& x) const  { return 1.0f; }

};
