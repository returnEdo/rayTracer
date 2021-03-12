#include "Scene.h"


Scene::Scene(const std::vector<Hittable*>& hittables_, const std::vector<Light>& lights_):
		hittables(hittables_),
		lights(lights_)		{}

Scene::Scene(Scene& other):
		Scene(other.getHittables(), other.getLights())	{}
