#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

namespace math {

	template <typename T>
	class Array {

	protected:
		std::vector<T> buffer;
		unsigned int width, height;

	public:

		const unsigned int getWidth() const {
			return width;
		}

		const unsigned int getHeight() const {
			return height;
		}

		std::vector<T> getRawDataPtr() {
			return buffer;
		}

		T getPoint(unsigned int x, unsigned int y) const {
			if ((x > getWidth()) || (y > getHeight())) { //check if coordinates are inside the bounds
				return T();
			}
			return buffer.at((getWidth()*y) + x); //(row size * column index) + row index
		}

		void setPoint(unsigned int x, unsigned int y, T & value) {
			if ((x > getWidth()) || (y > getHeight())) { //check if coordinates are inside the bounds
				return;
			}
			buffer.at((getWidth()*y) + x) = value;
		}

		void setData(const std::vector<T> & data_ptr) {
			if (getWidth() == 0 || getHeight() == 0 || data_ptr.empty()) {
				return;
			}

			buffer.clear();
			for (unsigned int i = 0; i < getWidth() * getHeight(); i++) {
				buffer.push_back(data_ptr.at(i));
			}

		}

		/*
		*Default constructor
		*/
		Array() {
			height = 0;
			width = 0;
			buffer.clear();
		}

		/*
		*Constructor with width and height specification
		*/
		Array(unsigned int width, unsigned int height){
			this->width = width;
			this->height = height;
			buffer.assign(width * height);
		}

		/*
		*Constructor with data initialization
		*/
		Array(unsigned int width, unsigned int height, const std::vector<T> data_ptr){
			this->width = width;
			this->height = height;
			setData(data_ptr); //changes the location where *buffer is linked
		}

		/*
		*Copy constructor
		*/
		Array(const Array &src) {
			width = src.width;
			height = src.height;
			setData(src.buffer);
		}

		/*
		*Destructor
		*/
		~Array() {
			buffer.clear();
		}

		/*
		*Copy assignment operator
		*/
		Array & operator = (const Array & right) {

			unsigned int size = getWidth() * getHeight(); //current image size
			unsigned int newSize = right.getWidth() * right.getHeight(); //size of image that is passed 
			if (&right != this) { // avoid inserting the same object 
				if (size != newSize) { //if the 2 images are defferent 
					buffer.clear();
					size = newSize;
					buffer.assign(size, 0);
				}
			}
			width = right.getWidth();
			height = right.getHeight();
			setData(right.buffer);
			return *this;
		}

		/*
		*@return a reference to object T at position with coordinates i, j
		*/
		T & operator () (unsigned int i, unsigned int j) const {
			return buffer.at((getWidth()*j) + i);
		}

	};
}

#endif