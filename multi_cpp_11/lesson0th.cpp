//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <vector>

#include <thread>
typedef std::vector<std::thread> thread_vec;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

static void _hello_hf()
{
	cout << "func thread " << std::this_thread::get_id() << endl;;
} // _hello_hf

void lesson0th()
{
	thread_vec func_threads, lambda_threads;
	for(auto ii = 0; ii < 5; ++ii)
	{
		func_threads.push_back(std::thread(_hello_hf));
		lambda_threads.push_back(std::thread(([](){
				cout << "lambda thread " << std::this_thread::get_id() << endl;}))
				);
	} // for ii
	for(auto &ii: lambda_threads)
		ii.join();
	for(auto &ii: func_threads)
		ii.join();

	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_ke));
	cout << "hopefully done\n\n";
} // main

