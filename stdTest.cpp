#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string>


int main(){

	int width;
	int height;
	int N;			// number of color channel

	std::string addr = "earth.jpg";

	/* parse raw */
	unsigned char* rawData = stbi_load(addr, &width, &height, &N, 0);
	
	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << N << std::endl;

	return 0;
}
