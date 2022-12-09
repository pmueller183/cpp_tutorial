//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

struct abs_value_ftr
{
	float operator()(float val) { return val >= 0 ? val : -val; }
	int   operator()(int   val) { return val >= 0 ? val : -val; }
}; // abs_value_ftr

class line_ftr
{
private:
	double m, b;
public:
	line_ftr(double slope = 1.0, double intercept = 0.0): m(slope), b(intercept){};
	inline double operator()(double exx) {return m * exx + b;}
}; // line_ftr

template <typename T>
struct print_ftr
{
	std::ostream &operator()(T const &val) { return cout << val << " "; }
}; // print_ftr

template <int val>
void incr_val(int &elem)
{
	elem += val;
} // set_val

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

	line_ftr line0th, line1st(5.0, 10.0);

	double const why0th = line0th(20.0);
	double const why1st = line1st(5.0);

	cout << "whys are " << why0th << ", " << why1st << endl;
	cout << endl;

	{
		std::vector<int> int_vec;
		print_ftr<int> print_int;
		for(int ii = 0; ii < 10; ++ii)
			int_vec.push_back(ii);
		std::for_each(int_vec.begin(), int_vec.end(), print_int);
		cout << endl;
		cout << endl;
	}

	{
		int const size_k = 5;
		print_ftr<int> print_int;
		std::vector<int> int_vec;
		for(int ii = 0; ii < size_k; ++ii)
			int_vec.push_back(ii);
		std::for_each(int_vec.begin(), int_vec.end(), print_int);
		cout << endl;
		std::for_each(int_vec.begin(), int_vec.end(), incr_val<2>);
		std::for_each(int_vec.begin(), int_vec.end(), print_int);
		cout << endl;
		cout << endl;
	}

} // main

