//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#pragma once

class dist_cls 
{
public:
	// required constructors
	dist_cls();
	dist_cls(int feet, int inches);
	friend ostream &operator<<(ostream &output, dist_cls const &the_dist);
	friend istream &operator>>(istream &input, dist_cls &the_dist);

private:
	int feet_m;             // 0 to infinite
	int inches_m;           // 0 to 12
	void normalize();
}; // dist_cls

