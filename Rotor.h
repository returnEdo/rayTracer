#pragma once

#include "Vector.h"
#include "Matrix.h"



struct Rotor{
	
	private:
	
	float a;
	float b;
	float c;
	float d;

	public:
	Rotor(float aa = .0, float bb = 1.0, float cc = .0, float dd = .0);
	Rotor(const Vector& k, float theta);
	
	float norm(void);
	void normalize(void);
	void EulerRodrigues(Matrix& S) const;
};


