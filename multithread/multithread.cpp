// multithread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>


static void _do_some_work_hf(int thread_id, std::mutex *cout_guard)
{
	int data;
	std::string scrstr;

	data = thread_id;

	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "the _do_some_work_hf ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "function is running on another ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "thread.\n";
	};

	scrstr = std::to_string(data);
	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::cout << "The function call ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "by worker thread " << scrstr << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "has ended.\n";
	}
} // _do_some_work_hf

int main()
{
	std::cout << "Hello World!\n";
	std::vector<std::thread> the_threads;
	std::mutex cout_guard;

	for(int ii = 0; ii < 10; ++ii)
	{
		the_threads.push_back(std::thread(
				_do_some_work_hf, ii, &cout_guard));
	} // for ii

	for(auto &ii:the_threads)
		ii.join();

} // main

