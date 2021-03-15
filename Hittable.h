#pragma once

#include <vector>

#include "Vector.h"
#include "Material.h"
#include "Ray.h"
#include "Collision.h"



enum class Color{

	MONOCHROME,
	TEXTURE
};


class Hittable{

	protected:

	Material material;
	Color colorType = Color::MONOCHROME;

	std::vector<Vector> texture;

	int textWidth;
	int textHeight;

	public:
	
	/* getters */
	inline Material& getMaterial(void) 	{ return material; }

	/* setters */
	void setMaterial(const Material& material_)	{ material = material_; }
	void setTexture(const std::string& addr);

	/* fills the collision object */
	virtual void checkCollision(const Ray& ray, Collision& collision) = 0;
	virtual const Vector& sampleTexture(float u, float v) const = 0;

	virtual bool isInside(const Vector& x) const = 0;
};	
