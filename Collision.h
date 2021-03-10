#pragma once

#include <limits>

#include "Material.h"
#include "Vector.h"


class Collision{

	public:

	Material* material;
	
	Vector v;		// world position of collision
	Vector n;		// normal @ collision (v)

	bool hasCollided	= false;	// collision?
	float distance		= std::numeric_limits<float>::max();

	void operator =(const Collision& col);
};
