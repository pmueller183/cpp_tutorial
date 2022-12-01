#include <iostream>
using namespace std;

int main()
{
	if(true)
	{
		int *a;
		a = new int;
		*a = 38;

		cout << "Hello World!" << *a;
		delete a;
		return 0;
	}
} // main

