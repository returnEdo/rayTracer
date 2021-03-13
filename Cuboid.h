#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Hittable.h"
#include "Collision.h"
#include "Ray.h"


class Cuboid: public Hittable{

	private:

	Vector r;		// sides of the cuboid

	Vector x;		// world position
	Matrix R;		// world to local

	bool isInsideLocal(const Vector& v) const;
	
	public:

	Cuboid(const Vector& sides, const Vector& x_, const Vector& k, float theta);

	/* getters */
	inline const Vector& getPosition(void) 	const 	{ return x; }
	inline const Matrix& getAttitude(void) 	const 	{ return R; }
	inline const Vector& getSides(void)	const 	{ return r; }

	virtual void checkCollision(const Ray& ray, Collision& collision) override;
	virtual const Vector& sampleTexture(float u, float v) const override;
};

