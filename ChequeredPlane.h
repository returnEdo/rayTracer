#pragma once

#include "Hittable.h"
#include "Ray.h"
#include "Collision.h"
#include "Vector.h"


class ChequeredPlane: public Hittable{

	private:

	float a;

	Vector col1;
	Vector col2;

	void setColor(float x, float z);

	public:

	ChequeredPlane(float a_, const Vector& col1_, const Vector& col2_);

	void checkCollision(const Ray& ray, Collision& collision);
	virtual const Vector& sampleTexture(float u, float v) const override { return material.color; }

	inline virtual bool isInside(const Vector& x) const override { return (x.y < a); }
};
