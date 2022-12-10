//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

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
	std::ostream &operator()(T const &val)
	{ 
		return cout << std::setw(3) << val << " "; 
	}
}; // print_ftr

template <int val>
void incr_val(int &elem)
{
	elem += val;
} // set_val

template<class aggregate>
inline void print_agg(aggregate const &agg, int wdth = 6)
{
	for(auto const &ii : agg)
		cout << std::setw(wdth) << ii << " ";
		cout << endl;
}


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

	{
		int const size_k = 5;
		print_ftr<int> print_int;
		std::vector<int> int_vec;
		std::vector<int> multiplicand;
		std::vector<int> ans;
		for(int ii = 0; ii < size_k; ++ii)
		{
			int_vec.push_back(ii);
			multiplicand.push_back(1 + ii);
			ans.push_back(-100);
		}
		std::for_each(int_vec.begin(), int_vec.end(), print_int);
		cout << endl;
		std::transform(
				int_vec.begin(), int_vec.end(),
				int_vec.begin(),
				std::negate<void>());
		std::for_each(int_vec.begin(), int_vec.end(), print_int);
		cout << endl;

		cout << endl;
		std::transform(
				int_vec.begin(), int_vec.end(),
				multiplicand.begin(),
				ans.begin(),
				std::multiplies<void>());
		print_agg(int_vec, 3);
		cout << "mutiply by\n";
		print_agg(multiplicand, 3);
		cout << "gives\n";
		print_agg(ans, 3);
		cout << endl;
	}

	{
		int const size_k = 5;
		std::vector<float> flt_vec;
		std::vector<float> multiplicand;
		std::vector<float> ans;
		for (int ii = 0; ii < size_k; ++ii)
		{
			flt_vec.push_back(ii + 0.1f);
			multiplicand.push_back(1.0f + ii);
			ans.push_back(-100.0f);
		}
		print_agg(flt_vec);
		std::transform(
				flt_vec.begin(), flt_vec.end(),
				flt_vec.begin(),
				std::negate<void>());
		print_agg(flt_vec);
		cout << endl;

		std::transform(
				flt_vec.begin(), flt_vec.end(),
				flt_vec.begin(),
				std::negate<void>());
		print_agg(flt_vec);
		cout << endl;

		std::transform(
			flt_vec.begin(), flt_vec.end(),
			multiplicand.begin(),
			ans.begin(),
			std::multiplies<void>());
		print_agg(flt_vec);
		cout << "mutiply by\n";
		print_agg(multiplicand);
		cout << "gives\n";
		print_agg(ans);
		cout << endl;
	}
} // main

