#pragma once

#include <iostream>
#include "Vector.h"


class Matrix{
	
	public:
	
	Vector row1;
	Vector row2;
	Vector row3;
	
	Vector col1;
	Vector col2;
	Vector col3;
	
	Matrix(const Vector& r1, const Vector& r2, const Vector& r3);
	Matrix(const Matrix& other);
	Matrix(const Vector& axis, float theta);
	Matrix(const Vector& diag);
	Matrix(void);

	void buildCol(void);
	void getColumnMajorOrder(float* data) const;

	friend Matrix operator *(const Matrix& a, float b);
	friend Matrix operator *(const Matrix& a, const Matrix& b);
	friend Vector operator *(const Matrix& a, const Vector& b);
	void operator *=(float b);
	void operator *=(const Matrix& b);
	
	friend Matrix operator /(const Matrix& a, float b);
	void operator /=(float b);
	
	friend Matrix operator +(const Matrix& a, const Matrix& b);
	void operator +=(const Matrix& b);
	
	friend Matrix operator -(const Matrix& a, const Matrix& b);
	void operator -=(const Matrix& b);
	
	
	friend float det(const Matrix& a);
	friend bool isSingular(const Matrix& a)	{ return (det(a) == .0); }
	
	friend Matrix transpose(const Matrix& a);
	friend Matrix inv(const Matrix& a);
	friend Matrix diagonalInv(const Matrix& mat);

	friend std::ostream& operator <<(std::ostream& os, const Matrix& a);
	
};


