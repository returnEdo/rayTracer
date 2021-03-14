#pragma once

#include <iostream>
#include <vector>



class Vector{
	
	public:
	
	float x;
	float y;
	float z;
	
	Vector(float xx, float yy, float zz);
	Vector(const Vector& other);
	Vector(const std::vector<float>& other);
	Vector(float xyz);
	Vector(void);

	void getRaw(float* data) const;
	
	friend Vector operator +(const Vector& a, const Vector& b);
	friend Vector operator -(const Vector& a, const Vector& b);
	friend float operator *(const Vector& a, const Vector& b);	
	
	friend Vector operator *(const Vector& a, float c);
	inline friend Vector operator *(float c, const Vector& a) { return (a * c); }
	
	friend Vector operator /(const Vector& a, float c);
	
	friend Vector operator ^(const Vector& a, const Vector& b);
	friend bool operator ==(const Vector& a, const Vector& b);	
	friend Vector operator %(const Vector& a, const Vector& b);
	float& operator [](const int indx);			
	
	void operator =(const Vector& a);

	void operator +=(const Vector &a);
	void operator -=(const Vector &b);

	void operator *=(float c);

	void operator /=(float c);

	friend std::ostream& operator <<(std::ostream& os, const Vector& a);
	
	float norm(void) const;
	friend float norm(Vector& a);
	friend float norm2(const Vector& a);
	
	void normalize(void);
	friend Vector normalize(Vector& a);

	friend float distance(const Vector& a, const Vector& b);

	friend bool nonNegative(const Vector& a);
};


