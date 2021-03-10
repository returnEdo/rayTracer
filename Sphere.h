#pragma once

#include "Hittable.h"
#include "Ray.h"
#include "Material.h"
#include "Collision.h"
#include "Vector.h"


class Sphere: public Hittable{

	private:

	Vector center;
	float radius;

	public:

	Sphere(const Vector& center_, float radius_ = 1.0f);

	/* getters */
	inline const Vector& getCenter(void) 	const { return center; }
	inline float getRadius(void) { return radius; }
	void getNormal(const Vector& v, Vector& n) const;

	virtual void checkCollision(const Ray& ray, Collision& collision) override;
	virtual const Vector& sampleTexture(float theta, float y) const override;
};

