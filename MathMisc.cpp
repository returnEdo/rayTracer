#include "MathMisc.h"

#include <cstdlib>


bool comparef(float a, float b){

	float diff = (a - b > .0f? a - b: b - a);

	return (diff < EPSILON); 
}



float randf(float M){

	return randf(.0f, M);
}



float randf(float m, float M){
	
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (M - m) + m);

}
