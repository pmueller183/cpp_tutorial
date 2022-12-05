//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#pragma once

#include <iostream>
using namespace std;

class dist_cls 
{
private:
	int feet_m;             // 0 to infinite
	int inches_m;           // 0 to 12

public:
	// required constructors
	dist_cls() 
	{
		feet_m = 0;
		inches_m = 0;
	}
	dist_cls(int feet, int inches)
	{
		feet_m = feet;
		inches_m = inches;
	}
	
	friend ostream &operator<<(ostream &output, dist_cls const &the_dist) 
	{
		output << "F : " << the_dist.feet_m << " I : " << the_dist.inches_m;
		return output;
	}

	friend istream &operator>>(istream &input, dist_cls &the_dist) 
	{
		input >> the_dist.feet_m >> the_dist.inches_m;
		return input;
	}
}; // dist_cls

