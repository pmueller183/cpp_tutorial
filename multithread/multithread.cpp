// multithread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <thread>
#include <iostream>
#include <vector>
#include <string>

static int count_f = 0;

static void _do_some_work_hf()
{
	int data;
	std::string scrstr;

	data = count_f;
	++count_f;

	std::cout << "the _do_some_work_hf function is running on another thread.\n";

	// pause for a moment to provide a delay to make threads mor apparent
	std::this_thread::sleep_for(std::chrono::seconds(2));
	scrstr = std::to_string(data);
	std::cout << "The function call by worker thread " << scrstr << " has ended.\n";
} // _do_some_work_hf

int main()
{
	std::cout << "Hello World!\n";
	std::vector<std::thread> the_threads;

	for(int ii = 0; ii < 10; ++ii)
	{
		the_threads.push_back(std::thread(_do_some_work_hf));
		std::cout << "the main() thread call this after starting the new thread.\n";
	} // for ii

	for(auto &ii:the_threads)
	{
		ii.join();
	}


} // main

