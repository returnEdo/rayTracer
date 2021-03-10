#include "JPGTools.h"
#include "Vector.h"
#include <iostream>
#include <string>


int main(){

	int width;
	int height;
	int N;			// number of color channel

	std::string addr = "earth.jpg";
	std::string saveAddr = "earth2.jpg";

	/* parse raw */
	
	std::vector<Vector> data;
	readJpg(addr, &width, &height, data);

//	for (int i = 0; i < data.size(); i++)

//		std::cout << data[i] << std::endl;

	//stbi_image_free(rawData);

	saveJpg(saveAddr, width, height, data, 5);
	


	return 0;
}
