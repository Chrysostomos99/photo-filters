#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

class Filter {

public:
	virtual imaging::Image operator << (const imaging::Image & image) = 0;

	/*
	*Default constructor
	*/
	Filter();

	/*
	*Copy constructor
	*/
	Filter(const Filter &src);
	
	/*
	*Destructor
	*/
	virtual ~Filter();

};

#endif