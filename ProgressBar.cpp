#include "ProgressBar.h"

#include <iostream>

ProgressBar::ProgressBar(int len, int r):
	length(len),
	roof(r){
	std::cout << HIDE_CURSOR;	
}

ProgressBar::~ProgressBar(void){
	
	std::cout << SHOW_CURSOR << std::endl;
}

void ProgressBar::update(int val) const{

	int valPerc = static_cast<int>(static_cast<float>(val) / static_cast<float>(roof) * 100.0f);
	int valLen  = static_cast<int>(static_cast<float>(val) / static_cast<float>(roof) * length);

	std::string percStr = " " + std::to_string(valPerc) + "%";
	std::string bar = "";

	for (int k = 0; k < length; k++)

		bar += (k <= valLen? "#": " ");
	
	std::cout << "\r\t";
	std::cout << RED("[") << GREEN(bar) << RED("]") << percStr;
}

