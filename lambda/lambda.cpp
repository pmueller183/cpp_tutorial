//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
typedef std::vector<int> int_vec;

#include <algorithm> // for_each

void _print_vec_hf(int_vec const &the_vec)
{
#if 1
	// lambda
	std::for_each(the_vec.begin(), the_vec.end(),
			[](int ii) { cout << ii << " "; }
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
	int_vec the_vec = {4, 1, 3, 5, 2, 3, 1, 7};
	_print_vec_hf(the_vec);

	// below snippet find first number greater than 4
	// find_if searches for an element for which
	// function (third argument) returns true
	int_vec::const_iterator this_one = std::find_if(
			the_vec.begin(), the_vec.end(), 
					[](int ii) { return ii > 4; }
					);
	cout << "First number greater than 4 is : " << *this_one << endl;

	// function to sort vector; lambda expression is for sorting in
	// non-increasing order.  Compiler can make out return type as
	// bool, but shown here just for explanation.
	std::sort(the_vec.begin(), the_vec.end(), 
			[](int a, int b) -> bool { return a > b; }
			);

	_print_vec_hf(the_vec);

	return 0;
} // main
