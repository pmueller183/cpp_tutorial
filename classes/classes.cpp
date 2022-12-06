//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include "stdafx.h"

static void _readwrite_hf()
{
	string data;

	// open a file in write mode.
	ofstream outfile;
	outfile.open("afile.dat");

	cout << "Writing to the file" << endl;
	cout << "Enter your name: ";
	getline(cin, data);

	// write inputted data into the file.
	outfile << data << endl;

	cout << "Enter your age: ";
	cin >> data;
	cin.ignore();

	// again write inputted data into the file.
	outfile << data << endl;

	// close the opened file.
	outfile.close();

	// open a file in read mode.
	ifstream infile;
	infile.open("afile.dat");

	cout << "Reading from the file" << endl;
	getline(infile, data);

	// write the data at the screen.
	cout << data << endl;

	// again read the data from the file and display it.
	getline(infile, data);
	cout << data << endl;
} // _readwrite_hf()

static void _caller_const_hf(dist_cls *foo, dist_cls const &ans)
{
	cout << "foo " << *foo << endl;
	(*foo)[1] = (*foo)[1] + 23;
	cout << "foo " << *foo << endl;
	(*foo)[1] = ans[1] + 23;
	cout << "foo " << *foo << endl;
	cout << endl;

	cout << "ans " << ans << endl;
//	ans[1] = ans[1] + 23;
//	cout << endl << "ans " << ans << endl;

} // _caller_const_hf

static void _caller_hf()
{
	dist_cls dist0th(-1, 14), dist1st(5, -5), dist2nd;
	
	_caller_const_hf(&dist0th, dist1st);

	cout << "Enter the value of object: ";
	cin >> dist2nd;
	cout << "zeroth dist_cls : " << dist0th << endl;
	cout << "first  dist_cls : " << dist1st << endl;
	cout << "second dist_cls : " << dist2nd << endl;
	dist1st[1] = 3;
	cout << "after assignment 3 inches first dist_cls : " << dist1st << endl;
	dist1st[1] = 23;
	cout << "after assignment 23 inches first dist_cls : " << dist1st << endl;
	cout << "dist0th[0] " << dist0th[0] << endl;
	cout << "dist1st[1] " << dist0th[1] << endl;
	cout << "dist1st[2] " << dist0th[2] << endl;
} // _caller_hf

int main()
{
	try
	{
		_caller_hf();
	}
	catch(exception const &e)
	{
		cerr << "Exception caught: >" << e.what() << "<" << endl;
	}
	catch(...)
	{
		cerr << "unknown exception; someone is not using std::exception";
		throw;
	}
	return 0;
} // main

