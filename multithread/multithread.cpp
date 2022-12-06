// multithread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

typedef std::unique_lock<std::mutex> unique_lock_mutex;
typedef std::lock_guard<std::mutex>  lock_guard_mutex;

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
		sync_cls *the_sync)
{
	// don't start until caller sets sync variable to 1
	{
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->cv_m.wait(
				the_lock, [the_sync]{return the_sync->val_m >= 1;});
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

	// tell caller we finished initializing (sync var 2)
	// wait until call sets state to 2
	{
		lock_guard_mutex the_lock(the_sync->mutex_m);
		the_sync->val_m = 2;
		the_sync->cv_m.notify_one();
	}

	// wait until call sets state to 3
	{
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->cv_m.wait(the_lock, 
				[the_sync]{return the_sync->val_m >= 3;});
	}

	scrstr = std::to_string(data);
	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::cout << "The function call ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "by worker thread " << scrstr << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << "has ended.\n";
	}

	// tell caller we're done state 4
	{
		lock_guard_mutex the_lock(the_sync->mutex_m);
		the_sync->val_m = 4;
		the_sync->cv_m.notify_one();
	}

} // _do_some_work_hf

int main()
{
	std::vector<int> the_states;
	std::vector<sync_cls_ptr> the_syncs;
	std::vector<std::thread> the_threads;
	std::mutex cout_guard;

	for(int ii = 0; ii < 10; ++ii)
	{
		sync_cls_ptr the_sync;
		the_sync = new sync_cls;
		the_syncs.push_back(the_sync);
		the_threads.push_back(
				std::thread(_do_some_work_hf, ii, &cout_guard, the_sync));
		the_states.push_back(0);
	} // for ii

	for(int ii = 9; ii >= 0; --ii)
	{
		lock_guard_mutex the_lock(the_syncs[ii]->mutex_m);
		the_states[ii] = 1;
		the_syncs[ii]->val_m = 1;
	}

	while(the_states[0] != 4)
	{
		for(int ii = 9; ii >= 0; --ii)
		{
			sync_cls *the_sync = the_syncs[ii];
			{
				unique_lock_mutex the_lock(the_sync->mutex_m);
				the_sync->cv_m.wait_for(the_lock,
						std::chrono::seconds(0),
						[the_sync]{return the_sync->val_m >= 2;});
				the_states[ii] = the_sync->val_m;
				int const qq = 77;
			}
			if(2 == the_states[ii])
			{
				if(9 == ii || the_states[ii+1] >= 3)
				{
					lock_guard_mutex the_lock(the_sync->mutex_m);
					the_states[ii] = 3;
					the_sync->val_m = 3;
					the_sync->cv_m.notify_one();
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
		}
	} // the_states[0] != 4

	for(auto &ii:the_threads)
		ii.join();

} // main

