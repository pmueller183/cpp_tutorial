//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;

typedef std::vector<int> int_vec;
typedef std::list<int> int_lst;

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

static bool _lt_3_hf(int val)
{
	return val < 3;
}

// returns lesser or larger value
template<class ordered>
inline ordered lesser(ordered ab, ordered cd)
{
	return ab < cd ? ab : cd;
}



template <class agg_cls, typename fptr>
static void _erase_bool_hf(agg_cls *the_vec, fptr func)
{
	typename agg_cls::iterator ii, prev;
	ii = the_vec->end();
	--ii;
	while(ii != the_vec->begin())
	{
		prev = ii;
		--prev;
		if((func)(*ii))
			the_vec->erase(ii);
		ii = prev;
	}
	if((func)(*ii))
		the_vec->erase(ii);

} // _erase_bool_hf

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
		int_vec the_vec;
		print_ftr<int> print_int;
		for(int ii = 0; ii < 10; ++ii)
			the_vec.push_back(ii);
		std::for_each(the_vec.begin(), the_vec.end(), print_int);
		cout << endl;
		cout << endl;
	}

	{
		int const size_k = 5;
		print_ftr<int> print_int;
		int_vec the_vec;
		for(int ii = 0; ii < size_k; ++ii)
			the_vec.push_back(ii);
		std::for_each(the_vec.begin(), the_vec.end(), print_int);
		cout << endl;
		std::for_each(the_vec.begin(), the_vec.end(), incr_val<2>);
		std::for_each(the_vec.begin(), the_vec.end(), print_int);
		cout << endl;
		cout << endl;
	}

	{
		int const size_k = 5;
		print_ftr<int> print_int;
		int_vec the_vec, multiplicand, ans;
		for(int ii = 0; ii < size_k; ++ii)
		{
			the_vec.push_back(ii);
			multiplicand.push_back(1 + ii);
			ans.push_back(-100);
		}
		std::for_each(the_vec.begin(), the_vec.end(), print_int);
		cout << endl;
		std::transform(
				the_vec.begin(), the_vec.end(),
				the_vec.begin(),
				std::negate<void>());
		std::for_each(the_vec.begin(), the_vec.end(), print_int);
		cout << endl;

		cout << endl;
		std::transform(
				the_vec.begin(), the_vec.end(),
				multiplicand.begin(),
				ans.begin(),
				std::multiplies<void>());
		print_agg(the_vec, 3);
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

	{ // bind2nd
		cout << "int_vec bind2nd\n";
		int const size_k = 6;
		int_lst the_vec, backup_vec;
		for(auto ii = 0; ii < size_k; ++ii)
			the_vec.push_back(ii);
		print_agg(the_vec, 4);
		std::replace_if(the_vec.begin(), the_vec.end(),
				std::bind2nd(std::equal_to<int>(),0), 101);
		print_agg(the_vec, 4);

		the_vec.push_back(1);
		the_vec.insert(the_vec.begin(), -1);
		print_agg(the_vec, 4);

		// this remove values less than 3
		// if I have to write a comment, it's too complicated
		cout << "using overly complicated expression:\n";
		backup_vec = the_vec;
		the_vec.erase(
				std::remove_if(the_vec.begin(), the_vec.end(),
						std::bind2nd(std::less<int>(), 3)), the_vec.end());
		print_agg(the_vec, 4);
		cout << endl;

		cout << "using boolean function:\n";
		the_vec = backup_vec;
		print_agg(the_vec, 4);
		_erase_bool_hf(&the_vec, _lt_3_hf);
		print_agg(the_vec, 4);
		cout << endl;

		cout << "using std::less predicate:\n";
		the_vec = backup_vec;
		print_agg(the_vec, 4);
		_erase_bool_hf(&the_vec, std::bind2nd(std::less<int>(), 3));
		print_agg(the_vec, 4);
		cout << endl;

		cout << endl;
	} // bind2nd

	{ // bind2nd
		cout << "int_lst bind2nd\n";
		int const size_k = 6;
		int_vec the_vec, backup_vec;
		for(auto ii = 0; ii < size_k; ++ii)
			the_vec.push_back(ii);
		print_agg(the_vec, 4);
		std::replace_if(the_vec.begin(), the_vec.end(),
				std::bind2nd(std::equal_to<int>(),0), 101);
		print_agg(the_vec, 4);

		the_vec.push_back(1);
		the_vec.insert(the_vec.begin(), -1);
		print_agg(the_vec, 4);

		// this remove values less than 3
		// if I have to write a comment, it's too complicated
		cout << "using overly complicated expression:\n";
		backup_vec = the_vec;
		the_vec.erase(
				std::remove_if(the_vec.begin(), the_vec.end(),
						std::bind2nd(std::less<int>(), 3)), the_vec.end());
		print_agg(the_vec, 4);
		cout << endl;

		cout << "using boolean function:\n";
		the_vec = backup_vec;
		print_agg(the_vec, 4);
		_erase_bool_hf(&the_vec, _lt_3_hf);
		print_agg(the_vec, 4);
		cout << endl;

		cout << "using std::less predicate:\n";
		the_vec = backup_vec;
		print_agg(the_vec, 4);
		_erase_bool_hf(&the_vec, std::bind2nd(std::less<int>(), 3));
		print_agg(the_vec, 4);
		cout << endl;

		cout << endl;
	} // bind2nd


} // main

