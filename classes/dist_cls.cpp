//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include "stdafx.h"

dist_cls::dist_cls()
{
	feet_m = 0;
	inches_m = 0;
} // default ctor
dist_cls::dist_cls(int feet, int inches)
{
	feet_m = feet;
	inches_m = inches;
	is_dirty_m = true;
} // dist_cls

int dist_cls::get_feet() const
{
	normalize();
	return feet_m;
} // get_feet
void dist_cls::put_feet(int feet)
{
	feet_m = feet;
	is_dirty_m = true;
} // put_feet

int dist_cls::get_inches() const
{
	normalize();
	return inches_m;
} // get_inches
void dist_cls::put_inches(int inches)
{
	inches_m = inches;
	is_dirty_m = true;
} // put_inches

#if 0
string dist_cls::to_string() const
{
	string ans;
	normalize();
	ans = std::to_string(feet_m) + " feet, " + 
			std::to_string(inches_m) + " inches";
	return ans;
} // to_string
#endif

dist_cls::operator std::string() const
{
	string ans;
	normalize();
	ans = std::to_string(feet_m) + " feet, " + 
			std::to_string(inches_m) + " inches";
	return ans;
} // operator std::string



void dist_cls::normalize() const
{
	if(is_dirty_m)
	{
		while(inches_m < 0)
		{
			--feet_m;
			inches_m += 12;
		}
		while(inches_m >= 12)
		{
			++feet_m;
			inches_m -= 12;
		}
		is_dirty_m = false;
	} // is_dirty_m
} // normalize

int &dist_cls::operator[](int ndx)
{
	if(ndx < 0 || ndx > 1)
	{
		string err_str;
		err_str = string("dist_cls[] supports 0 (feet) or 1 (inches), not ") +
				std::to_string(ndx);
		throw out_of_range(err_str);
	}

	normalize();
	is_dirty_m = true;

	if(0 == ndx)
		return feet_m;
	else
		return inches_m;
} // operator []

int const &dist_cls::operator[](int ndx) const
{
	if(ndx < 0 || ndx > 1)
	{
		string err_str;
		err_str = string("dist_cls[] supports 0 (feet) or 1 (inches), not ") +
				std::to_string(ndx);
		throw out_of_range(err_str);
	}

	normalize();

	if(0 == ndx)
		return feet_m;
	else
		return inches_m;
} // operator [] const

ostream &operator<<(ostream &output, dist_cls const &the_dist)
{
	//output << the_dist.to_string();
	output << string(the_dist);
	return output;
} // ostream

istream &operator>>(istream &input, dist_cls &the_dist)
{
	input >> the_dist.feet_m >> the_dist.inches_m;
	the_dist.is_dirty_m = true;
	return input;
} // istream

