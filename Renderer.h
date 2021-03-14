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

float randf(float);
float randf(float, float);


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

	std::vector<Ray> rays;

	bool isBar = false;

	/* background */
	BkgType bckType = BkgType::DEFAULT;
	const Skybox* skybox;

	void clamp(Vector& vec) const;

	public:

	Renderer(int width_, int height_, int na_ = 3);

	/* setters */
	inline void setIsBar(bool isBar_)	{ isBar = isBar_; }
	inline void setSamples(int na_) 	{ na = (na_ > 0? na_: -na_); }
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
};
