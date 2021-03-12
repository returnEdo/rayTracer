#include "JPGTools.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void readJpg(const std::string& addr, int* width, int* height, std::vector<Vector>& data){
	/* reads jpg to vector of vector */

	const char* rawAddr = addr.data();			// returns raw address
	
	int N;
	unsigned char* rawData = stbi_load(rawAddr, width, height, &N, 0);

	if (N != 3)

		throw "\n\tBadly formatted jpeg!!";
	

	if (data.size() != 0)
		
		data.erase(data.begin(), data.end());

	for (int i = 0; i < (*width) * (*height) * 3; i += 3){

		data.push_back({static_cast<float>(rawData[i]) / 255.0f,
				static_cast<float>(rawData[i + 1]) / 255.0f,
				static_cast<float>(rawData[i + 2]) / 255.0f
		});
	}

	stbi_image_free(rawData);
}



void saveJpg(const std::string& addr, int width, int height, const std::vector<Vector>& data, int quality){
	/* writes vector of Vector to jpg */
	
	std::vector<unsigned char> rawData;

	for (int i = 0, j = 0; i < width * height; i++, j += 3){

		rawData.push_back(static_cast<unsigned char>(data[i].x));
		rawData.push_back(static_cast<unsigned char>(data[i].y));
		rawData.push_back(static_cast<unsigned char>(data[i].z));
	}
	
	const char* rawAddr = addr.data();

	stbi_write_jpg(rawAddr, width, height, 3, rawData.data(), quality);
}

