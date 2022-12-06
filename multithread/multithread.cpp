// multithread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

typedef std::unique_lock<std::mutex> unique_lock_mutex;

class sync_cls
{
public:
	std::mutex mutex_m;
	std::condition_variable cv_m;
	int val_m;

	sync_cls()
	{
		std::mutex mutex_m;
		std::condition_variable cv_m;
		val_m = 0;
	}
}; // sync_cls

typedef sync_cls *sync_cls_ptr;

static void _do_some_work_hf(int thread_id, std::mutex *cout_guard, 
		sync_cls *sync)
{
	{
		unique_lock_mutex the_lock(sync->mutex_m);
		sync->cv_m.wait(the_lock, [sync]{return 1 == sync->val_m;});
	}

	int data;
	std::string scrstr;

	data = thread_id;

	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "the _do_some_work_hf ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "id " << data << " function is running on another ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "thread.\n";
	};

//	{
//		unique_lock_mutex the_lock(sync->mutex_m);
//		sync->cv_m.wait(the_lock, [sync]{return 2 == sync->val_m;});
//	}

	scrstr = std::to_string(data);
	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::cout << "The function call ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "by worker thread " << scrstr << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "has ended.\n";
	}
} // _do_some_work_hf

int main()
{
	std::vector<sync_cls_ptr> the_syncs;
	std::vector<std::thread> the_threads;
	std::mutex cout_guard;

	for(int ii = 0; ii < 10; ++ii)
	{
		sync_cls_ptr sync;
		sync = new sync_cls;
		the_syncs.push_back(sync);
		the_threads.push_back(
				std::thread(_do_some_work_hf, ii, &cout_guard, sync));
	} // for ii

	for(int ii = 9; ii >= 0; --ii)
	{
		unique_lock_mutex the_lock0(the_syncs[ii]->mutex_m);
		the_syncs[ii]->val_m = 1;
	}

	for(auto &ii:the_threads)
		ii.join();

} // main

