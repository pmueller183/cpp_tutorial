//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>

#include "box_cls.h"
#include "dist_cls.h"

int main() 
{
	dist_cls dist0th(11, 14), dist1st(5, -5), dist2nd;

	cout << "Enter the value of object: ";
	cin >> dist2nd;
	cout << "zeroth dist_cls : " << dist0th << endl;
	cout << "first  dist_cls : " << dist1st << endl;
	cout << "second dist_cls : " << dist2nd << endl;

	return 0;
}
