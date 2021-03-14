#pragma once

#include <array>

#include "Light.h"
#include "Vector.h"


class SpotLight: public Light{

	private:

	std::array<float, 3> k;			// attenuations

	float p;				// concentration exponent
	
	Vector direction;			// spotlight direction

	public:

	SpotLight(const Vector& position_, const Vector& color_, const std::array<float, 3>& k_, const Vector& direction_, float p_);

	/* setters */
	inline void setAttenuationConstants(const std::array<float, 3>& k_)	{ k = k_; }
	inline void setDirection(const Vector& direction_)			{ direction = direction_; }
	inline void setExponent(float p_)					{ p = p_; }

	/* getters */
	inline const std::array<float, 3>& getAttenuationCoefficients(void) 	const { return k; }
	inline const Vector& getDirection(void)					const { return direction; }
	inline float getExponent(void) 						const { return p; }
	virtual float getIntensityAt(const Vector& x) const override;
};
