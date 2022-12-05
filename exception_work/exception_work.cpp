//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <iostream>
using namespace std;

class tester_cls
{
public:
	tester_cls()  { cout << "constructing tester_cls\n"; }
	~tester_cls() { cout << "destructing tester_cls\n";}
}; // tester_cls

class counter_test_cls
{
	static int count_c;
	int id_m;

public:
	counter_test_cls() 
	{
		id_m = count_c;
		++count_c;
		cout << "Constructing object number " << id_m << endl;
		if (4 == id_m)
			throw 4;
	} // ctor
	~counter_test_cls() { cout << "Destructing object number " << id_m << endl; }
}; // counter_test_cls

int counter_test_cls::count_c = 0;

static void _counter_test_cls_hf()
{
	try
	{
		counter_test_cls array[8];
	}
	catch (int &ii) 
	{
		cout << "Caught " << ii << endl;
	}
	cout << endl;
} // _counter_test_cls_hf

void _try_catch_work_hf()
{
	tester_cls aa;
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

	cout << "\ngot to the end of input function\n\n";
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

	_counter_test_cls_hf();

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
