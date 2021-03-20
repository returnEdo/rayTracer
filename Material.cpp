#include "Material.h"


void Material::operator =(const Material& other){

	color = other.color;
	
	rhor = other.rhor;
	rhoe = other.rhoe;

	psid = other.psid;
	psis = other.psis;
	psia = other.psia;

	glossy_radius = other.glossy_radius;

	f = other.f;
	eta = other.eta;
}

