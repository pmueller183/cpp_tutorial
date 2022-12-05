//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include "stdafx.h"

dist_cls::dist_cls()
{
	feet_m = 0;
	inches_m = 0;
}
dist_cls::dist_cls(int feet, int inches)
{
	feet_m = feet;
	inches_m = inches;
	normalize();
} // dist_cls

ostream &operator<<(ostream& output, dist_cls const& the_dist)
{
	output << the_dist.feet_m << " feet, " << the_dist.inches_m << " inches";
	return output;
}

istream &operator>>(istream& input, dist_cls& the_dist)
{
	input >> the_dist.feet_m >> the_dist.inches_m;
	the_dist.normalize();
	return input;
}

void dist_cls::normalize()
{
	while (inches_m < 0)
	{
		--feet_m;
		inches_m += 12;
	}
	while (inches_m >= 12)
	{
		++feet_m;
		inches_m -= 12;
	}
} // normalize

