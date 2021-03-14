#pragma once

#include <array>

#include "Light.h"
#include "Vector.h"

class DirectionalLight: public Light{

	private:

	std::array<float, 3> k;		// attenuation constants ([2] is quadratic)
	
	public:

	DirectionalLight(const Vector& position_, const Vector& color_, const std::array<float, 3>& k_);
	
	/* setters */
	inline void setAttenuationConstants(const std::array<float, 3>& k_) 		{ k = k_; }
	
	/* getters */
	inline const std::array<float, 3>& getAttenuationCoefficients(void) const	{ return k; }
	virtual float getIntensityAt(const Vector& x) const override;
};
