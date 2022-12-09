//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>

using std::cout;
using std::endl;

struct abs_value_ftr
{
	float operator()(float val) { return val >= 0 ? val : -val; }
	int   operator()(int   val) { return val >= 0 ? val : -val; }
}; // abs_value_ftr

int main()
{
	cout << endl;

	float flt_val;
	int int_val;
	abs_value_ftr abs_value;

	flt_val = static_cast<float>(-13.111);
	int_val = -13;
	cout << "flt_val " << flt_val << " abs " << abs_value(flt_val) << endl;
	cout << "int_val " << int_val << " abs " << abs_value(int_val) << endl;
} // main

