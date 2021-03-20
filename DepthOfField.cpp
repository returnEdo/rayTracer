#include "DepthOfField.h"

#include <cmath>

#include "MathMisc.h"

DepthOfField::DepthOfField(const Vector& f_, float a_):
		f(f_),
		a(a_) {

}


void DepthOfField::render(std::vector<Hittable*>& hittables, std::vector<Light*>& lights, 
	    		  Renderer& renderer, const Camera& cam, std::vector<Vector>& colors, int N) const{
	
	/* preallocation */
	colors = std::vector<Vector>(renderer.getWidth() * renderer.getHeight());

	Vector diff = cam.getPosition() - f;
	float psi = norm(diff);						// focal distance

	for (int i = 0; i < N; i++){
		
		/* compute camera perturbations */
		float rho = randf(a);
		float theta = randf(2 * M_PI);
		
		Vector uc(rho * cos(theta), rho * sin(theta), .0f);
		Vector uw = cam.getCamToWorld() * uc + cam.getPosition();

		Vector d = f - uw;
		d.normalize();

		Vector camPos = f - d * psi;
		
		/* perturbed camera */
		Camera tempCam(camPos, f, cam.getPlaneDistance(), cam.getFOV());
		
		/* fills the colors vector in accumulation mode */
		renderer.findColors(hittables, lights, tempCam, colors, true);
	}
	
	/* averaging */
	for (int i = 0; i < colors.size(); i++)

		colors[i] /= static_cast<float>(N);

}
