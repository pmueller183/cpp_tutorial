//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <string>

#include "lessons.h"



static std::string const _lesson_ndx_kf = "2";

int main()
{
	if("0" == _lesson_ndx_kf)
		lesson0th();
	else if("1" == _lesson_ndx_kf)
		lesson1st();
	else if("2" == _lesson_ndx_kf)
		lesson2nd();

} // main

