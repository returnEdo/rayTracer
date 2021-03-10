#pragma once

#include <iostream>

#include "Vector.h"

class Ray{

	private:

	Vector o;		// origin in world coord.
	Vector d;		// direction in world coord.

	public:

	Ray(const Vector& o_, const Vector& d_);
	Ray(const Ray& other);
	Ray(void)	{}

	/* getters */

	inline const Vector& getOrigin(void)	const { return o; }
	inline const Vector& getDirection(void)	const { return d; }


	/* setters */

	inline void setOrigin(const Vector& o_)		{ o = o_; }
	void setDirection(const Vector& d_);

	friend std::ostream& operator <<(std::ostream& os, const Ray& ray); 
};
