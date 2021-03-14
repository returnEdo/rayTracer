#include "Vector.h"

#include <assert.h>
#include <cmath>

Vector::Vector(float xx, float yy, float zz):  		x(xx),	y(yy),	z(zz)		{}
Vector::Vector(const Vector& other):			x(other.x), y(other.y), z(other.z)	{}		
Vector::Vector(const std::vector<float>& other): 	x(other[0]), y(other[1]), z(other[2])	{}
Vector::Vector(float xyz):				x(xyz), y(xyz), z(xyz)	{}
Vector::Vector(void):					x(.0),	y(.0),	z(.0)	{}

void Vector::getRaw(float* data) const{

	data[0] = x;
	data[1] = y;
	data[2] = z;
}

Vector operator +(const Vector& a, const Vector& b){
	
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator -(const Vector& a, const Vector& b){
	
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}


float operator *(const Vector& a, const Vector& b){
	
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
	

Vector operator *(const Vector& a, float c){
	
	return Vector(a.x * c, a.y * c, a.z * c);
} 

Vector operator /(const Vector& a, float c){
	
	//assert(c != .0);
	
	return Vector(a.x / c, a.y / c, a.z / c);
} 


Vector operator ^(const Vector& a, const Vector& b){
	
	Vector result;
	
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	
	return result;
}


bool operator ==(const Vector& a, const Vector& b){
	
	return (a.x == b.x and a.y == b.y and a.z == b.z);
}

Vector operator %(const Vector& a, const Vector& b){

	return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}



float& Vector::operator [](const int indx){
	
	assert(indx >= 0 and indx <= 2);
	
	switch (indx){
		
		case 0:			return (this -> x);
		case 1:			return (this -> y);
		case 2:			return (this -> z);
	}
	return x;
}

void Vector::operator =(const Vector& a){

	x = a.x;
	y = a.y;
	z = a.z;
}


void Vector::operator +=(const Vector &b){
	
	*this = *this + b;
}

void Vector::operator -=(const Vector &b){
	
	*this = *this - b;
}

void Vector::operator *=(float c){
	
	*this = *this * c;
}

void Vector::operator /=(float c){
	
	*this = *this / c;
}

std::ostream& operator <<(std::ostream& os, const Vector& a){
	
	os << '(' << a.x << ',' << a.y << ',' << a.z << ')';
	
	return os;
}

float Vector::norm(void) const{
	
	return sqrt((* this) * (* this));
}

float norm2(const Vector& a){

	return (a * a);
}


float norm(Vector& a){
	
	return a.norm();
}

void Vector::normalize(void){
	
	*this /= this -> norm();
}

Vector normalize(Vector& a){
	
	Vector result;
	
	result = a / a.norm();
	
	return result;
}


float distance(const Vector& a, const Vector& b){
	
	Vector c = a - b;
	
	return norm(c);
}

bool nonNegative(const Vector& a){

	return (a.x >= 0.0 and  a.y >= 0.0 and a.z >= 0.0);
}


