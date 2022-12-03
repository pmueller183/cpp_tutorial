// exception_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void _try_catch_work_hf()
{
	char the_err;
	cout << "a: int error\nb: double error\nc: string error\nd: other error\n"
			"e: no error\n";
	cin >> the_err;

	if('a' == the_err)
		throw 7;
	else if('b' == the_err)
		throw -13.3;
	else if('c' == the_err)
		throw string("this be an error");
	else if('d' == the_err)
		throw false;
	else if('e' == the_err)
		int const qq = 77; //do nothing
	else
	{
		string err_str;
		err_str = "unknown option >";
		err_str += the_err;
		err_str += "<";
		throw err_str;
	} // bad option
} // _try_catch_work_hf

void _try_outside_catch_work_hf()
{

	try
	{
		_try_catch_work_hf();
	}
	catch(double)
	{
		cout << "caught double error; made good\n";
	}
	catch(...)
	{
		cout << "caught error; rethrowing\n";
		throw;
	}
} // _try_outside_catch_work_hf

int main()
{
	bool is_good;

	try
	{
		is_good = true;
		_try_outside_catch_work_hf();
	} // try block
	catch(int int_val) 
	{
		is_good = false;
		cout << "int error " << int_val << endl;
	}
	catch(double dbl_val)
	{
		is_good = false;
		cout << "double error " << dbl_val << endl;
	}
	catch(string &str_val)
	{
		is_good = false;
		cout << "string error >" << str_val << "<\n";
	} // catch string
	catch(...)
	{
		is_good = false;
		cout << "unknown exception\n";
	}
	cout << (is_good ? "Good\n" : "bad :-(\n");

} // main
