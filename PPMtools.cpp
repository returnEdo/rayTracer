#include "PPMtools.h"

#include "ProgressBar.h"

void Vector_to_string(const Vector& vec, std::string& str){

	str = std::to_string(static_cast<int>(vec.x)) + " " +
	      std::to_string(static_cast<int>(vec.y)) + " " +
	      std::to_string(static_cast<int>(vec.z));
}


bool savePPM(const std::string& address,
	     const std::vector<Vector>& framebuffer,
	     unsigned int width,
	     unsigned int height){

	std::cout << "\tSaving..." << std::endl;
	ProgressBar bar(30, static_cast<int>(width * height));

	std::ofstream file(address);

	if (file.is_open()){

		file << "P3" << std::endl;
		file << std::to_string(width) << " " << std::to_string(height) << std::endl;
		file << "255" << std::endl;

		std::string temp;
		
		for (int h = 0; h < height; h++){

			for (int w = 0; w < width; w++){

				Vector_to_string(framebuffer[h * width + w], temp);
				file << temp << std::endl;
				bar.update(w + h * width + 1);
			}
		}

		file.close();

		return true;
	}
	
	return false;
}
