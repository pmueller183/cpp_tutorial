#include <iostream>
#include <fstream>
using namespace std;

static void _did_it_close_hf(string const &filepath)
{
	ofstream my_file;

	my_file.open(filepath);
	my_file << "this be a test\n";
//	my_file.close();

} // _did_it_close_hf


int main()
{
	string const filename_k = "my_file.txt";
	_did_it_close_hf(filename_k);
	cout << "hopefully created " << filename_k << endl;

} // main

