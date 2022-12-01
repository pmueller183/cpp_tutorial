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

	int aa;
	cout << endl;
	cout << "Type in a number: ";
	cin >> aa;
	cout << "You typed " << aa << endl;
	cout << endl;

	float const fval  = 35e3;
	double const dval = 12e4;

	cout << "fval " << fval << " dval " << dval << endl;

	string first_name;
	string second_name;
	string full_name;

	first_name = "John";
	second_name = "Doe";

	full_name = first_name + " " + second_name;
	cout << '>' << full_name << "<\n";
	full_name = "";
	cout << '>' << full_name << "<\n";
	full_name = first_name + ' ' + second_name;
	cout << '>' << full_name << "<\n";



	return 0;
} // main

