#include "FilterLinear.h"
#include <vector>

FilterLinear::FilterLinear() : a(), c() {}

FilterLinear::FilterLinear(math::Vec3<float> a, math::Vec3<float> c) : a(a), c(c) {}

FilterLinear::FilterLinear(const FilterLinear &src) {
	a = src.a;
	c = src.c;
}

FilterLinear::~FilterLinear() {}

void FilterLinear::setA(math::Vec3<float> a) {
	this->a = a;
}

void FilterLinear::setC(math::Vec3<float> c) {
	this->c = c;
}

math::Vec3<float> FilterLinear::getA() {
	return a;
}

math::Vec3<float> FilterLinear::getC() {
	return c;
}

imaging::Image FilterLinear::operator << (const imaging::Image & image) {

	imaging::Image newImage(image);
	
	for (unsigned int i = 0; i < image.getWidth(); i++) { // for every pixel in the image
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			math::Vec3<float> current = image.getPixel(i, j);
			math::Vec3<float> newColor = getA()*current + getC(); //finds the new color of the pixel
			newColor = newColor.clampToLowerBound(0);
			newColor = newColor.clampToUpperBound(1);
			newImage.setPixel(i, j, newColor);
		}
	}

	return newImage;
}