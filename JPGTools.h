#pragma once

#include <vector>

#include "Vector.h"

void readJpg(const std::string& addr, int* width, int* height, std::vector<Vector>& data);
void saveJpg(const std::string& addr, int width, int height, const std::vector<Vector>& data, int quality = 100);
