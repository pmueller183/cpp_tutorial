//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-


#include <iostream>
using std::cout;
using std::endl;

#include <string>

#include <iterator>
#include <vector>
typedef std::vector<int> int_vec;

#include <algorithm> // for_each
#include <numeric> // accumulate

void _print_vec_hf(int_vec const &the_vec)
{
	// lambda
	std::for_each(the_vec.cbegin(), the_vec.cend(),
			[](int ii) {cout << ii << " ";}
			);
	cout << endl;
} // _print_vec_hf

void _print_vec_hf(std::string const &prepend, int_vec const &the_vec)
{
	if(prepend != "")
		cout << prepend << " ";
	_print_vec_hf(the_vec);
} // _print_vec_hf

static double _product_hf(double ii, double jj)
{
	return static_cast<double>(ii * jj);
}

int main()
{
	int_vec the_vec = {4, 1, 3, 5, 3, 7, 2, 3, 1, 7};
	int_vec::const_iterator the_vec_ptr;
	_print_vec_hf(the_vec);

	// below snippet find first number greater than 4
	// find_if searches for an element for which
	// function (third argument) returns true
	the_vec_ptr = std::find_if(the_vec.begin(), the_vec.end(), 
					[](int ii) {return ii > 4;}
					);
	cout << "First number greater than 4 is : " << *the_vec_ptr << endl;

	// function to sort vector; lambda expression is for sorting in
	// non-increasing order.  Compiler can make out return type as
	// bool, but shown here just for explanation.
	std::sort(the_vec.begin(), the_vec.end(), 
			[](int ii, int jj) -> bool {return ii > jj;}
			);
	_print_vec_hf(the_vec);

	// function to count numbers greater than or equal to 5
	auto count_5 = std::count_if(
			the_vec.begin(), the_vec.end(),
			[](int ii) {return ii >= 5;}
			);
	cout << "The number of elements greater than or equal to 5 is " <<
			count_5 << endl;

	_print_vec_hf(the_vec);
	// function for removing duplicate element (note: std::unique needs 
	// sorting for all duplicates next to each other)
	// (note: need to resize afterwards)
	the_vec_ptr = std::unique(the_vec.begin(), the_vec.end(),
			[](int ii, int jj) { return ii == jj; }
			);
	the_vec.resize(std::distance(the_vec.cbegin(), the_vec_ptr));
	_print_vec_hf(the_vec);

	// accumulate function accumulate the container on the basis of
	// function provided as third argument
	auto product = std::accumulate(the_vec.begin(), the_vec.end(), 1.0,
			[](double ii, double jj) { return ii * jj; });
	cout << "sizeof(product) " << sizeof(product) << " product is " << product << endl;

	// We can also access function by storing this into variable
	auto square_fptr = [](int val) {return val * val;};

	cout << "square of 5 is : " << square_fptr(5) << endl;

	int_vec v0th = { 3, 1, 7, 9};
	int_vec v1st = {10, 2, 7, 16, 9};

	_print_vec_hf("v0th", v0th);
	_print_vec_hf("v1st", v1st);

	//  access v0th and v1st by reference
	auto pushinto = [&] (int m)
	{
		v0th.push_back(m);
		v1st.push_back(m);
	}; // pushinto

	pushinto(20);

	_print_vec_hf("v0th", v0th);
	_print_vec_hf("v1st", v1st);

	// access v1 by copy
	auto show_arrays = [=](bool do_show_names)
	{
		if(do_show_names)
			cout << "v0th: ";
		for(auto ii = v0th.begin(); ii != v0th.end(); ++ii)
			cout << *ii << " ";
		cout << endl;
		if(do_show_names)
			cout << "v1st: ";
		for(auto ii = v1st.begin(); ii != v1st.end(); ++ii)
			cout << *ii << " ";
		cout << endl;
	}; // show_arrays


	show_arrays(true);
	show_arrays(false);

	return 0;
} // main
