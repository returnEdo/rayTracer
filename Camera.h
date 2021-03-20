#pragma once

#include <cmath>

#include "Vector.h"
#include "Matrix.h"
#include "Rotor.h"


class Camera{

	private:

	Vector position;	// world position
	Matrix Rwc;		// world to cam
	Matrix Rcw;		// cam to world

	float p;		// projection plane distance
	float FOV;

	public:

	Camera(const Vector& position, const Vector& lookAt, float p_ = 2.0f, float FOV_ = M_PI / 2.0f);

	/* getters */
	inline const Vector& getPosition(void)   const { return position; }
	inline const Matrix& getWorldToCam(void) const { return Rwc; }
	inline const Matrix& getCamToWorld(void) const { return Rcw; }
	inline float getPlaneDistance(void)	 const { return p; }
	inline float getFOV(void)		 const { return FOV; }

	/* setters */
	inline void setPlaneDistance(float p_)		{ p = p_; }
	inline void setFOV(float FOV_)			{ FOV = FOV_; }
};
