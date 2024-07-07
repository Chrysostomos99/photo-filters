#ifndef FILTERGAMMA_H
#define FILTERGAMMA_H

#include "Filter.h"

class FilterGamma : public Filter {

private:
	float y;

public:

	/*
	*Default constructor
	*/
	FilterGamma();
	
	/*
	*Constructor with y specification
	*/
	FilterGamma(float y);
	
	/*
	*Copy constructor
	*/
	FilterGamma(const FilterGamma &src);

	/*
	*Destructor
	*/
	~FilterGamma();
	
	/*
	*Mutators
	*/
	void setY(float y);
	
	/*
	*Accessors
	*/
	float getY();

	/*
	*Operator
	*/
	imaging::Image operator << (const imaging::Image & image);
};



#endif