#include <iostream>
#include "Image.h"
#include "ppm/ppm.h"

namespace imaging {


	math::Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {
		return getPoint(x, y);
	}

	void Image::setPixel(unsigned int x, unsigned int y, math::Vec3<float> & value) {
		setPoint(x, y, value);
	}

	bool Image::load(const std::string & filename, const std::string & format) {

		std::string format2;
		for (unsigned int i = 0; i < format.length(); i++) { //case insensitivity
			format2 = format2 + char(tolower(format[i]));
		}

		if (format2 != "ppm") { //the file can only open if it's .ppm
			std::cerr << "Unsupported format.";
			return false;
		}

		int newWidth = 0; int newHeight = 0; //re-initializing width, height, buffer

		//float array: contains the values for the r,g,b: later used to create the Color
		float *RGB = ReadPPM(filename.c_str(), &newWidth, &newHeight);
		
		width = newWidth;
		height = newHeight;

		if (RGB == nullptr) { //if the reading operation wasn't successfull break operation
			return false;
		}

		buffer.clear();
		buffer.assign(width*height, 0);//create new buffer suitable for the	Image that is loaded
		for (unsigned int i = 0, j = 0; i < 3 * getWidth() * getHeight(); i += 3, j++) {
			buffer[j] = math::Vec3<float>(RGB[i], RGB[i + 1], RGB[i + 2]); //creates new Color from the float values and inserts them to the Color::buffer
		}

		return true;
	}

	bool Image::save(const std::string & filename, const std::string & format) {

		if (getWidth() == 0 || getHeight() == 0 || buffer.empty()) { //Cannot create a ppm file with such values
			return false;

		}

		std::string format2;
		for (unsigned int i = 0; i < format.length(); i++) { //case insensitivity
			format2 = format2 + char(tolower(format[i]));
		}

		if (format2 != "ppm") { //Only ppm extension is acceptable
			return false;
		}

		float *RGB = new float[3 * getWidth() * getHeight()]; //float array for rgb values
		for (unsigned int i = 0, j = 0; i < getWidth() * getHeight(); i++, j += 3) { //breaks the color to its components and stores them into RGB array
			RGB[j] = buffer[i][0];
			RGB[j + 1] = buffer[i][1];
			RGB[j + 2] = buffer[i][2];

		}
		bool success = WritePPM(RGB, getWidth(), getHeight(), filename.c_str());
		if (success == false) { //if save operation wasn't successfull break operation
			return false;
		}
		std::cout << filename << std::endl;
		return true;
	}
}