//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
using std::cout;
using std::endl;

#include <iterator>
#include <vector>
typedef std::vector<int> int_vec;

#include <algorithm> // for_each
#include <numeric> // accumulate

void _print_vec_hf(int_vec const &the_vec)
{
#if 1
	// lambda
	std::for_each(the_vec.cbegin(), the_vec.cend(),
			[](int ii) {cout << ii << " ";}
			);
#else
	// old
	for(auto const &ii : the_vec)
		cout << ii << " ";
#endif
	cout << endl;
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

	return 0;
} // main
