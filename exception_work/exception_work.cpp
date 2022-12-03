// exception_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void _try_catch_work_hf()
{
	char the_err;
	cout << "a: int error; b: double error; c: string error; d: other error;"
			"e: no error";
	cin >> the_err;

	if('a' == the_err)
		throw 7;
	else if('b' == the_err)
		throw -13.3;
	else if('c' == the_err)
		throw "this be an error";
	else if('d' == the_err)
		throw false;
	else
		; // do nothing
} // _try_catch_work_hf

int main()
{
	bool is_good;

	is_good = false;
	try 
	{
		is_good = true;
		_try_catch_work_hf();
	} // try block
	catch(int err_num) 
	{
		cout << "int error " << err_num << endl;
	}
	catch(...)
	{
		cout << "some other error\n";
	}
	cout << is_good ? "Good]n" : "bad :-(\n";

} // main
