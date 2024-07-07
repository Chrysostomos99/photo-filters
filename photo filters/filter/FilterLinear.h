#ifndef FILTERLINEAR_H
#define FILTERLINEAR_H

#include "Filter.h"
#include "Vec3.h"

class FilterLinear : public Filter {

private:
	math::Vec3<float> a, c;

public:

	/*
	*Default constructor
	*/
	FilterLinear();
	
	/*
	*Constructor with a and c specification
	*/
	FilterLinear(math::Vec3<float> a, math::Vec3<float> b);
	
	/*
	*Copy constructor
	*/
	FilterLinear(const FilterLinear &src);

	/*
	*Destructor
	*/
	~FilterLinear();

	/*
	*Mutators
	*/
	void setA(math::Vec3<float> a);
	void setC(math::Vec3<float> c);
	
	/*
	*Accessors
	*/
	math::Vec3<float> getA();
	math::Vec3<float> getC();

	/*
	*Operator
	*/
	imaging::Image operator << (const imaging::Image & image);
};

#endif