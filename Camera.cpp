#include "Camera.h"


Camera::Camera(const Vector& position_, const Vector& lookAt, float p_, float FOV_):
		position(position_), p(p_), FOV(FOV_) {
	
	/* these are the cols of Rcw (rows of Rwc)*/
	Vector z = position - lookAt;
	z.normalize();

	/* always aligned with the y axis */
	Vector x = Vector(.0f, 1.0f, .0f) ^ z;
	x.normalize();

	Vector y = z ^ x;
	
	Rwc = Matrix(x, y, z);
	Rcw = transpose(Rwc);
}

