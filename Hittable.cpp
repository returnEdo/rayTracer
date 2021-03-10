#include "Hittable.h"

#include "JPGTools.h"

void Hittable::setTexture(const std::string& addr){

	readJpg(addr, &textWidth, &textHeight, texture);

	colorType = Color::TEXTURE;
}
