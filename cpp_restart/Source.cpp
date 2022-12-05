//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

int main()
{
	std::cout << "int min " << std::numeric_limits<int>::min() << endl;
	std::cout << "int max " << std::numeric_limits<int>::max() << endl;
	std::cout << "unsigned int min " << std::numeric_limits<unsigned int>::min() << endl;
	std::cout << "unsigned int max " << std::numeric_limits<unsigned int>::max() << endl;
	std::cout << endl;

	std::cout << "long int min " << std::numeric_limits<long int>::min() << endl;
	std::cout << "long int max " << std::numeric_limits<long int>::max() << endl;
	std::cout << endl;

	std::cout << "long long int min " <<
			std::numeric_limits<long long int>::min() << endl;
	std::cout << "long long int max " <<
			std::numeric_limits<long long int>::max() << endl;

	std::cout << "unsigned long long int min " <<
		std::numeric_limits<unsigned long long int>::min() << endl;
	std::cout << "unsigned long long int max " <<
		std::numeric_limits<unsigned long long int>::max() << endl;

} // main

#if 0
static void _show_name_hf(string const &the_name)
{
	cout << the_name << endl;
} // _show_name_hf

int main()
{
	string my_text = "this be a test";
	double const my_val = -33.3;
	cout << "Hollow World!\n";
	cout << "I be learning C++\n";
	cout << "my_val be " << my_val << endl;
	cout << "my_text be >" << my_text << "<\n";

#if 0
	int aa;
	cout << endl;
	cout << "Type in a number: ";
	cin >> aa;
	cout << "You typed " << aa << endl;
	cout << endl;
#endif

	float const fval  = 35e3;
	double const dval = 12e4;

	cout << "fval " << fval << " dval " << dval << endl;

	string zeroth_name;
	string first_name;
	string full_name;

	zeroth_name = "John";
	first_name = "Peanut";

	full_name = zeroth_name + " " + first_name;
	cout << '>' << full_name << "<\n";
	full_name = "";
	cout << '>' << full_name << "<\n";
	full_name = zeroth_name + ' ' + first_name;
	cout << '>' << full_name << "<\n";
	full_name = "";
	full_name.append(zeroth_name);
	full_name.append(" ");
	full_name.append(first_name);
	cout << '>' << full_name << "<\n";
	cout << "full_name length is " << full_name.length() << endl;

	full_name[2] = 'n';
	cout << full_name << " length is " << full_name.length() << endl;

	for(int ii = 0; ii < full_name.length(); ++ii)
		cout << full_name[ii] << endl;

#if 0
	cout << "Type in your full name: ";
	getline(cin, full_name);
	cout << full_name << " length is " << full_name.length() << endl;
#endif

	cout << (10 > 9) << endl;
	cout << bool(10 > 9) << endl;
	cout << (9 > 10) << endl;
	cout << bool(9 > 10) << endl;

	string my_strs[] = {"This", "be", "a", "test", "aldsjf"};
	cout << sizeof(my_strs) / sizeof(my_strs[0]) << "(" << _countof(my_strs) << "): ";
	for(string const &ii : my_strs)
		cout << ii << " ";

	
	cout << endl;
	int my_ints[4][2] = 
	{
		{ 00, 01 },
		{ 10, 11 },
		{ 20, 21 },
		{ 30, 31 }
	};

	for(auto &a : my_ints)
	{
		for(auto &b : a)
			cout << setw(2) << setfill('0') << b << " ";
		cout << endl;
	}

	cout << endl;

	_show_name_hf("a name");
	_show_name_hf("another name");
	_show_name_hf(zeroth_name);
	_show_name_hf(full_name);
	for(string const &ii : my_strs)
		_show_name_hf(ii);


	return 0;
} // main
#endif
