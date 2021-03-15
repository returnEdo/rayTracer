#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Hittable.h"
#include "Ray.h"
#include "Collision.h"



class Cylinder: public Hittable{

	private:

	float h;		// height
	float r;		// radius

	Vector x;		// world position
	Matrix R;		// world to local

	bool isInsideLocal(const Vector& v) const;

	public:

	Cylinder(float h_, float r_, const Vector& x_, const Vector& k, float theta);

	/* getters */
	inline float getHeihgt(void) 	const { return h; }
	inline float getRadius(void) 	const { return r; }

	virtual void checkCollision(const Ray& ray, Collision& collision) override;
	virtual const Vector& sampleTexture(float l, float theta) const override;

	virtual bool isInside(const Vector& v) const;
};
