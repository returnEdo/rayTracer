#pragma once

#include <vector>

#include "Hittable.h"
#include "Collision.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.h"
#include "Matrix.h"
#include "Vector.h"
#include "Skybox.h"
#include "Scene.h"


enum class BkgType{

	DEFAULT,
	SKYBOX,
	CUBEMAP
};


class Renderer{

	private:

	int width;			// number of rays
	int height;

	int na;				// samples per pixel
	int no = 10;			// number of feelers for ambient occlusion

	std::vector<Ray> rays;

	bool isBar = false;
	bool isOcclusion = false;
	
	float alpha = 5.0f;			// occlusion exponent

	/* background */
	BkgType bckType = BkgType::DEFAULT;
	const Skybox* skybox;

	void clamp(Vector& vec) const;
	Vector perturbDirection(const Vector& vec, float rho) const;

	public:

	Renderer(int width_, int height_, int na_ = 3);

	/* setters */
	inline void setIsBar(bool isBar_)		{ isBar = isBar_; }
	inline void setSamples(int na_) 		{ na = (na_ > 0? na_: -na_); }
	inline void setAmbientOcclusionSamples(int no_)	{ no = (no_ > 0? no_: -no_); }
	inline void setIsOcclusion(bool isOcclusion_)	{ isOcclusion = isOcclusion_; }
	inline void setOcclusionExponent(float alpha_)	{ alpha = (alpha_ > .0f? alpha_: -alpha_); }
	void setSkybox(const Skybox& skybox_);
	void setRays(const Camera& cam);

	/* getters */
	inline int getWidth(void) 	const { return width; }
	inline int getHeight(void) 	const { return height; }

	bool getScatteredRays(Ray& r, Ray& e, const Vector& n, const Vector& v, const Vector& d, float eta);
	void checkIntersections(const Ray& ray, std::vector<Hittable*>& hittables, Collision& collision) const;

	Vector findColor(const Ray& ray, std::vector<Hittable*>& hittables, std::vector<Light*>& lights, int depth = 0);
	void findColors(std::vector<Hittable*>& hittables, std::vector<Light*>& lights, const Camera& cam, std::vector<Vector>& colors, bool accumulation = false);
	void findColors(Scene& scene, const Camera& cam, std::vector<Vector>& colors, bool accumulation = false);
	float findOcclusionFactor(const Vector& v, const Vector& n, std::vector<Hittable*>& hittables);
};
