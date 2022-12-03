// exception_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
	try 
	{
		int const age = 31;
		if(age >= 18) 
			cout << "Access granted - you are old enough.";
		else
			throw age;
	} // try block
	catch (int err_num) 
	{
		cout << "Access denied - You must be at least 18 years old.\n";
		cout << "Age is: " << err_num;
	}
} // main
