#include "Matrix.h"

#include <assert.h>
#include <math.h>

Matrix::Matrix(const Vector& r1, const Vector& r2, const Vector& r3):
		row1(r1), row2(r2), row3(r3)			{this -> buildCol();}	

Matrix::Matrix(const Matrix& other):
	row1(other.row1), row2(other.row2), row3(other.row3)	{this -> buildCol();}

Matrix::Matrix(void):				
	row1(Vector(1.0, .0, .0)), row2(Vector(.0, 1.0, .0)), row3(Vector(.0, .0, 1.0))
	{this -> buildCol();}

Matrix::Matrix(const Vector& diag):
	row1(Vector(diag.x, .0, .0)), row2(Vector(.0, diag.y, .0)), row3(Vector(.0, .0, diag.z))
	{this -> buildCol();}

Matrix::Matrix(const Vector& n, float t){

	row1 = Vector(cos(t) + (1 - cos(t)) * n.x * n.x, -sin(t) * n.z + (1 - cos(t)) * n.x * n.z, sin(t) * n.y + (1 - cos(t)) * n.x * n.z);
	row2 = Vector(sin(t) * n.z + (1 - cos(t)) * n.x * n.z, cos(t) + (1 - cos(t)) * n.y * n.y, -sin(t) * n.x + (1 - cos(t)) * n.y * n.z);
	row3 = Vector(-sin(t) * n.y + (1 - cos(t)) * n.x * n.z, sin(t) * n.x + (1 - cos(t)) * n.y * n.z, cos(t) + (1 - cos(t)) * n.z * n.z);

	this -> buildCol();
}

void Matrix::buildCol(void){
	
	this -> col1 = Vector(row1.x, row2.x , row3.x);
	this -> col2 = Vector(row1.y, row2.y , row3.y);
	this -> col3 = Vector(row1.z, row2.z , row3.z);
}


void Matrix::getColumnMajorOrder(float* data) const{

	col1.getRaw(data);
	col2.getRaw(data + 3);
	col3.getRaw(data + 6);
}


Matrix operator *(const Matrix& a, float b){
	
	return Matrix(a.row1 * b, a.row2 * b, a.row3 * b);
}


Matrix operator *(const Matrix& a, const Matrix& b){

	Vector res1 = Vector(a.row1 * b.col1, a.row1 * b.col2, a.row1 * b.col3);
	Vector res2 = Vector(a.row2 * b.col1, a.row2 * b.col2, a.row2 * b.col3);
	Vector res3 = Vector(a.row3 * b.col1, a.row3 * b.col2, a.row3 * b.col3);

	return Matrix(res1, res2, res3);
}


Vector operator *(const Matrix& a, const Vector& b){
	
	return Vector(a.row1 * b, a.row2 * b, a.row3 * b);
}


void Matrix::operator *=(float b){
	
	*this = *this * b;
}


void Matrix::operator *=(const Matrix& b){
	
	*this = *this * b;
}


Matrix operator /(const Matrix& a, float b){
	
	assert(b != .0);
	
	return Matrix(a.row1 / b, a.row2 / b, a.row3 / b);
}


void Matrix::operator /=(float b){
	
	*this = *this / b;
}


Matrix operator +(const Matrix& a, const Matrix& b){
	
	return Matrix(a.row1 + b.row1, a.row2 + b.row2, a.row3 + b.row3);
}

void Matrix::operator +=(const Matrix& b){
	
	*this = *this + b;
}

Matrix operator -(const Matrix& a, const Matrix& b){
	
	return Matrix(a.row1 - b.row1, a.row2 - b.row2, a.row3 - b.row3);
}

void Matrix::operator -=(const Matrix& b){
	
	*this = *this - b;
}



float det(const Matrix& a){
	
	return a.row1.x * a.row2.y * a.row3.z + 
		   a.row1.y * a.row2.z * a.row3.x + 
		   a.row1.z * a.row2.x * a.row3.y - 
		   a.row1.z * a.row2.y * a.row3.x - 
		   a.row1.x * a.row2.z * a.row3.y - 
		   a.row1.y * a.row2.x * a.row3.z;
} 


Matrix transpose(const Matrix& a){
	
	return Matrix(a.col1, a.col2, a.col3);
}


Matrix inv(const Matrix& a){
	
	float dt = det(a);
	
	assert(dt != .0);
	
	Vector r1 = Vector(a.row2.y * a.row3.z - a.row2.z * a.row3.y,
					   a.row2.z * a.row3.x - a.row2.x * a.row3.z,
					   a.row2.x * a.row3.y - a.row2.y * a.row3.x);
	
	Vector r2 = Vector(a.row3.y * a.row1.z - a.row3.z * a.row1.y,
					   a.row3.z * a.row1.x - a.row3.x * a.row1.z,
					   a.row3.x * a.row1.y - a.row3.y * a.row1.x);
	
	Vector r3 = Vector(a.row1.y * a.row2.z - a.row1.z * a.row2.y,
    				   a.row1.z * a.row2.x - a.row1.x * a.row2.z,
    				   a.row1.x * a.row2.y - a.row1.y * a.row2.x);
    
    return transpose(Matrix(r1, r2, r3)) / dt;
}

Matrix diagonalInv(const Matrix& mat){

	return Matrix(Vector(1.0f / mat.row1.x, 1.0f / mat.row2.y, 1.0f / mat.row3.z));
}

    
std::ostream& operator <<(std::ostream& os, const Matrix& a){
	
	os << a.row1.x << ' ' << a.row1.y << ' ' << a.row1.z << '\n' <<
		  a.row2.x << ' ' << a.row2.y << ' ' << a.row2.z << '\n' <<
		  a.row3.x << ' ' << a.row3.y << ' ' << a.row3.z << '\n';
	
	return os;
}
		



