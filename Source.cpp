#include <iostream>
#include <string>
using namespace std;

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

	int ii;
	for(ii = 0; ii < full_name.length(); ++ii)
		cout << full_name[ii] << endl;

	cout << "Type in your full name: ";
	getline(cin, full_name);
	cout << full_name << " length is " << full_name.length() << endl;





	return 0;
} // main

