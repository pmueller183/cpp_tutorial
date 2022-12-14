//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
typedef std::vector<int> int_vec;

#include <algorithm> // for_each
#include <iterator>

void _print_vec_hf(int_vec const &the_vec)
{
#if 1
	// lambda
	std::for_each(the_vec.begin(), the_vec.end(),
			[](int ii) {cout << ii << " ";}
			);
#else
	// old
	for(auto const &ii : the_vec)
		cout << ii << " ";
#endif
	cout << endl;
} // _print_vec_hf

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
	// sorting for all duplicates next to each other
	the_vec_ptr = std::unique(the_vec.begin(), the_vec.end(),
			[](int ii, int jj) { return ii == jj; }
			);
	the_vec.resize(std::distance(the_vec.cbegin(), the_vec_ptr));
	_print_vec_hf(the_vec);

	return 0;
} // main
