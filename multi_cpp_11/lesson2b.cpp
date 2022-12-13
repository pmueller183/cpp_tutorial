//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <vector>

#include <thread>
#include <mutex>
typedef std::vector<std::thread> thread_vec;
typedef std::lock_guard<std::mutex> lock_mutex;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

static void _call_once_hf(std::thread::id const &thread_id)
{
	cout << "called once by thread " << thread_id << endl;
} // _call_once_hf

static void _timed_work_hf(std::once_flag *the_flag, 
		std::mutex *cout_guard, std::timed_mutex *mutex)
{
	std::chrono::milliseconds const timeout_k(30);

	std::call_once(*the_flag, _call_once_hf, std::this_thread::get_id());

	for(auto ii = 0; ii < 5; ++ii)
	{
		if(mutex->try_lock_for(timeout_k))
		{
			std::chrono::milliseconds const sleep_duration_k(70);
			{
				std::lock_guard<std::mutex> lock(*cout_guard);
				cout << std::setw(7) << std::this_thread::get_id() << 
						": do work with the mutex\n";
			}
			std::this_thread::sleep_for(sleep_duration_k);
			mutex->unlock();
			std::this_thread::sleep_for(sleep_duration_k);
		} // try_lock_for success
		else 
		{
			std::chrono::milliseconds const sleep_duration_k(30);
			{
				std::lock_guard<std::mutex> lock(*cout_guard);
				cout << std::setw(7) << std::this_thread::get_id() << 
						": do work without mutex\n";
			}
			std::this_thread::sleep_for(sleep_duration_k);
		} // else try_lock_for failed
	} // while(true)
} // _timed_work_hf

void lesson2b()
{
	std::once_flag once_flag;
	std::mutex cout_guard;
	std::timed_mutex mutex;
	thread_vec the_threads;

	cout << "lesson2b:\n";

	for(auto ii = 0; ii < 4; ++ii)
		the_threads.push_back(std::thread(
				_timed_work_hf, &once_flag, &cout_guard, &mutex));
	for(auto &ii : the_threads)
		ii.join();

	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_ke));
	cout << "lesson2b hopefully done\n";

} // lesson2b