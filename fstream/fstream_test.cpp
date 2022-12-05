//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static void _did_it_close_hf(string const &filepath)
{
	ofstream my_file;
	my_file.open(filepath);
	my_file << "this be a test\n";
} // _did_it_close_hf

static void _copy_file_hf(string const &inp_path, string const &out_path)
{
	ifstream inp_file;
	ofstream out_file;
	string the_line;

	inp_file.open(inp_path);
	out_file.open(out_path);

	while(getline(inp_file, the_line))
		out_file << the_line << endl;

} // _copy_file_hf


int main()
{
	string const filename_k = "my_file.txt";
	_did_it_close_hf(filename_k);
	cout << "hopefully created " << filename_k << endl;

	string const inp_path_k = "d:\\Standard\\cpp_tutorials\\fstream\\fstream_test.cpp";
	string const out_name_k = "copy_of_fstream_test.txt";
	_copy_file_hf(inp_path_k, out_name_k);
	cout << "hopefully created " << out_name_k << endl;
} // main

