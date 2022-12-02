#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string const filename_k = "my_file.txt";
	ofstream my_file;

	my_file.open(filename_k);

	my_file << "this be a test\n";

	my_file.close();

	cout << "hopefully created " << filename_k << endl;

} // main

