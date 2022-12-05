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

static void _caller_hf()
{
	dist_cls dist0th(11, 14), dist1st(5, -5), dist2nd;
	
	cout << "Enter the value of object: ";
	cin >> dist2nd;
	cout << "zeroth dist_cls : " << dist0th << endl;
	cout << "first  dist_cls : " << dist1st << endl;
	cout << "second dist_cls : " << dist2nd << endl;
	cout << dist0th[0] << endl;
	cout << dist0th[1] << endl;
	cout << dist0th[-1] << endl;
} // _caller_hf

int main()
{
	try
	{
		_readwrite_hf();
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

