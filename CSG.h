#pragma once

#include "Hittable.h"
#include "Ray.h"
#include "Collision.h"
#include "Vector.h"
	
/* constructive solid geometry */

enum class BOperation{

	UNION,
	DIFFERENCE,
	INTERSECTION
};


class CSG: public Hittable{

	private:

	Hittable* h1;
	Hittable* h2;

	BOperation type;

	void findIntersections(const Ray& ray, std::vector<Collision>& collisions);

	public:

	CSG(Hittable* h1_, Hittable* h2_, const BOperation& type_);

	/* getters */
	inline const BOperation& getOperation(void) const { return type; }

	virtual void checkCollision(const Ray& ray, Collision& collision) override;
	virtual const Vector& sampleTexture(float u, float v) const override;

	virtual bool isInside(const Vector& x) const override;
};
