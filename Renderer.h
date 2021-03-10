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

float randf(float);


enum class BkgType{

	DEFAULT,
	SKYBOX,
	CUBEMAP
};


class Renderer{

	private:

	int width;
	int height;

	std::vector<Ray> rays;

	bool isBar = false;

	/* background */
	BkgType bckType = BkgType::DEFAULT;
	const Skybox* skybox;

	void clamp(Vector& vec) const;

	public:

	Renderer(int width_, int height_);

	/* setters */
	inline void setIsBar(bool isBar_)	{ isBar = isBar_; }
	void setSkybox(const Skybox& skybox_);
	void setRays(const Camera& cam);

	bool getScatteredRays(Ray& r, Ray& e, const Vector& n, const Vector& v, const Vector& d, float eta);
	void checkIntersections(const Ray& ray, std::vector<Hittable*>& hittables, Collision& collision) const;

	Vector findColor(const Ray& ray, std::vector<Hittable*>& hittables, const std::vector<Light>& lights, int depth = 0);
	void findColors(std::vector<Hittable*>& hittables, const std::vector<Light>& lights, std::vector<Vector>& colors);
	void findColorsAppend(std::vector<Hittable*>& hittables, const std::vector<Light>& lights, std::vector<Vector>& colors, float oneN);

	void depthOfField(const Camera& baseCam, const Vector& f, float a, unsigned int N,
			  std::vector<Hittable*>& hittables, const std::vector<Light>& lights, std::vector<Vector>& colors);
};
