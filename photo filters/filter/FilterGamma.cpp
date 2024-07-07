#include "FilterGamma.h"
#include "vector"
#include <math.h>
FilterGamma::FilterGamma() : y() {}

FilterGamma::FilterGamma(float y) : y(y) {}

FilterGamma::FilterGamma(const FilterGamma &src) {
	y = src.y;
}

FilterGamma::~FilterGamma() {}

void FilterGamma::setY(float y) {
	this->y = y;
}

float FilterGamma::getY() {
	return y;
}

imaging::Image FilterGamma::operator << (const imaging::Image & image) {

	imaging::Image newImage(image);
	
	for (unsigned int i = 0; i < image.getWidth(); i++) { // for every pixel in the image
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			math::Vec3<float> current = image.getPixel(i, j);
			float red = pow(current[0], getY());
			float green = pow(current[1], getY());
			float blue = pow(current[2], getY());
			math::Vec3<float> newColor(red,green,blue); //finds the gative of the pixel color
			newColor = newColor.clampToLowerBound(0);
			newColor = newColor.clampToUpperBound(1);
			newImage.setPixel(i, j, newColor);
		}
	}
	
	return newImage;
}

