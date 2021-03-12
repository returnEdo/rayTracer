#include "Renderer.h"

#include <cmath>
#include <iostream>

#include "RayTracerConstants.h"
#include "ProgressBar.h"


float randf(float vmax){

	return static_cast<float>(rand() / static_cast<float>(RAND_MAX)) * vmax;
}


Renderer::Renderer(int width_, int height_):
		width(width_), height(height_) {
	

}


void Renderer::setSkybox(const Skybox& skybox_){

	skybox = &skybox_;
	bckType = BkgType::SKYBOX;
}


void Renderer::setRays(const Camera& cam){
	/* sets the rays vector */

	if (rays.size() != 0)

		rays.erase(rays.begin(), rays.end());

	float alpha = (static_cast<float>(width) - 1.0f) / (static_cast<float>(height) - 1.0f);
	
	float deltax = 2.0f * cam.getPlaneDistance() * tan(cam.getFOV() / 2.0f);
	float deltay = deltax / alpha;

	float step = deltax / (static_cast<float>(width) - 1.0f);

	Vector temp;
	for (int j = 0; j < height; j++){

		for (int i = 0; i < width; i++){
			
			temp.x = -deltax / 2.0f + i * step;
			temp.y = deltay / 2.0f - j * step;
			temp.z = - cam.getPlaneDistance();

			temp.normalize();
			
			/* change to world for later use */
			temp = cam.getCamToWorld() * temp;

			rays.push_back({cam.getPosition(), temp});
		}
	}
}


bool Renderer::getScatteredRays(Ray& r, Ray& e, const Vector& n, const Vector& v, const Vector& d, float eta){
	
	float scl = n * d;
	bool inside = (scl > .0f);


	r.setDirection(d - 2.0f * scl * n);
	
	Vector q(1.0f, .0f, .0f);
	if (abs(scl) < 1.0f){

		q = d - scl * n;
		q.normalize();
	}

	float A = 1 - scl * scl;

	if (not inside){
		/* ray origin outside */
		
		/* reflection */
		r.setOrigin(v + n * DELTA);
				
		/* refraction */
		e.setOrigin(v - n * DELTA);
		e.setDirection( -sqrt(1 - A / (eta * eta)) * n + sqrt(A) / eta * q);

		return true;
	}
	else{
		/* ray origin inside */

		/* reflection */
		r.setOrigin(v - n * DELTA);

		/* refraction */
		if (A >= 1 / (eta * eta)){
			/* above or equal to critical angle */

			return false;
		}
		else{
			e.setOrigin(v + n * DELTA);
			e.setDirection(n * sqrt(1 - A * eta * eta) + sqrt(A) * eta * q);
			
			return true;
		}

	}
}

	
void Renderer::checkIntersections(const Ray& ray, std::vector<Hittable*>& hittables, Collision& collision) const{
	/* finds the closest collision if any */

	Collision temp;

	for (Hittable* hittable: hittables){
		/* FIXME: has to check each hittable */

		hittable -> checkCollision(ray, temp);

		if (temp.hasCollided and temp.distance < collision.distance){

			collision = temp;
		}
	}
}


Vector Renderer::findColor(const Ray& ray, std::vector<Hittable*>& hittables, const std::vector<Light>& lights, int depth) {
	/* follows the ray to find its color */

	Collision collision;
	checkIntersections(ray, hittables, collision);

	if (not collision.hasCollided or depth == MAX_RECURSION_DEPTH){
		/* there is no collision */

		if (bckType == BkgType::DEFAULT){

			return BCK_COLOR;
		}
		else if (bckType == BkgType::SKYBOX){

			return skybox -> sampleTexture(ray);
		}
		else{
			/* TODO: cube map */
			return BCK_COLOR;
		}
	}
	else{
		/* recursive path floowing */

		Material m = *(collision.material);
		Vector color = m.psia * m.color;				// "base" color

		float scl = collision.n * ray.getDirection();
		bool inside = (scl > 0.0f);					// ray origin is inside the hittable

		/* build reflected and refracted rays */
		Ray r;								// reflected
		Ray e;								// refracted
		bool isRefracted = getScatteredRays(r, e, collision.n, collision.v, ray.getDirection(), collision.material -> eta);

		for (const Light& light: lights){

			Vector l = light.getPosition() - collision.v;
			l.normalize();

			float lightScl = l * collision.n;

			if (lightScl > 0.0f){
				/* there may be direct illumination */

				Ray shadowFeeler(collision.v + collision.n * DELTA, l);
				Collision shadowCollision;

				checkIntersections(shadowFeeler, hittables, shadowCollision);

				if (not shadowCollision.hasCollided){
					/* there is direct illumination */
					/* add diffusion and specular reflection effects */
					
					color += (m.color % light.getColor()) * (m.psid * (lightScl) + m.psis * pow((r.getDirection() * l), m.f) / (1.0f - m.rhor - m.rhoe));
				}
			}
		}
		
		
		if (isRefracted){
			return (1.0f - m.rhor - m.rhoe) * color
				+ m.rhor * findColor(r, hittables, lights, depth + 1)
				+ m.rhoe * findColor(e, hittables, lights, depth + 1);
		}
		else{
			return (1.0f - m.rhor - m.rhoe) * color
				+ m.rhor * findColor(r, hittables, lights, depth + 1);
		}
	}
}


void Renderer::clamp(Vector& vec) const{

	vec *= 255.0f;
	vec.x = (vec.x >= 0? vec.x: .0f);
	vec.y = (vec.y >= 0? vec.y: .0f);
	vec.z = (vec.z >= 0? vec.z: .0f);

	vec.x = (vec.x <= 255.0f? vec.x: 255.0f);
	vec.y = (vec.y <= 255.0f? vec.y: 255.0f);
	vec.z = (vec.z <= 255.0f? vec.z: 255.0f);
}


void Renderer::findColors(std::vector<Hittable*>& hittables, const std::vector<Light>& lights, std::vector<Vector>& colors){
	/* follows each ray generated in the constructor */

	ProgressBar bar(50, width * height);
	
	int i = 1;
	for (const Ray& ray: rays){

		Vector temp = findColor(ray, hittables, lights);
		clamp(temp);
		colors.push_back(temp);
		if (isBar)
			bar.update(i++);
	}
}


void Renderer::findColors(Scene& scene, std::vector<Vector>& colors){

	findColors(scene.getHittables(), scene.getLights(), colors);
}



void Renderer::findColorsAppend(std::vector<Hittable*>& hittables, const std::vector<Light>& lights, std::vector<Vector>& colors, float oneN){

	for (int i = 0; i < width * height; i++){

		Vector temp = findColor(rays[i], hittables, lights);
		clamp(temp);
		temp *= oneN;

		colors[i] += temp;
	}
}



void Renderer::depthOfField(const Camera& baseCam,
			    const Vector& f,					// focal point
			    float a,						// aperture
			    unsigned int N,
			    std::vector<Hittable*>& hittables, 
			    const std::vector<Light>& lights, 
			    std::vector<Vector>& colors){
	/* renders using depth of field */

	Vector diff = baseCam.getPosition() - f;
	float psi = norm(diff);							// focal distance
	
	colors = std::vector<Vector>(width * height, Vector());

	for (unsigned int i = 0; i < N; i++){
		
		/* compute randomized new cam position */
		float rho = randf(a);
		float theta = randf(2.0f * M_PI);

		Vector uc(rho * cos(theta), rho * sin(theta), .0f);
		Vector uw = baseCam.getCamToWorld() * uc + baseCam.getPosition();

		Vector d = f - uw;
		d.normalize();

		Camera newCam(f - psi * d, f);
		setRays(newCam);
		
		findColorsAppend(hittables, lights, colors, 1.0f / static_cast<float>(N));

	}
}





