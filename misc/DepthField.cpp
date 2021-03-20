#include "DepthField.h"

#include <vector>
#include <cmath>

#include "Matrix.h"



float randf(float vmax){
	/* random float between 0 and vmax */

	return static_cast<float>(std::rand() / static_cast<float>(RAND_MAX)) * vmax;
}



void depthOfField(const Camera& cam, const CameraProperties& prop, const std::string& addr, unsigned int N){

	
	float psi = norm(cam.getPosition() - prop.f);		// focal distance

	/* compute camera origins */
	std::vector<Vector> camPositions;
	
	for (unsigned int i = 0; i < N; i++){

		float rho = randf(prop.a);
		float theta = randf(2 * M_PI);
		
		Vector uc(rho * cos(theta), rho * sin(theta), .0f);
		Vector uw = cam.getCamToWorld() * uc + cam.getPosition();

		Vector d = f - uw;
		d.normalize();

		camPositions.push_back(f - d * psi);
		std::cout << (f - d * psi) << std::endl;
		std::cout << norm(f - d * psi) << std::endl;

	}
}



