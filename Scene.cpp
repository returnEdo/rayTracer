#include "Scene.h"


Scene::Scene(std::vector<Hittable*>& hittables_, std::vector<Light*>& lights_):
		hittables(hittables_),
		lights(lights_)		{}

Scene::Scene(Scene& other):
		Scene(other.getHittables(), other.getLights())	{}
