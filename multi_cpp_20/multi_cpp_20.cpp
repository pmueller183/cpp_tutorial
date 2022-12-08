//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#include <mutex>
#include <thread>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <random>

using std::cout;
using std::endl;

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

	~sync_cls()
	{
		cout << "ending sync\n";
	}

}; // sync_cls
typedef sync_cls *sync_cls_ptr;
typedef std::vector<sync_cls_ptr> sync_cls_vec;

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
		cout << "the _do_some_work_hf ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		cout << "id " << std::setw(2) << data << " function is running on another ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		cout << "thread\n";
	};

	// tell caller we finished initializing (sync var 2)
	{
		{
			unique_lock_mutex the_lock(the_sync->mutex_m);
			the_sync->val_m = 2;
		}
		the_sync->cv_m.notify_one();
	}

	// wait until caller sets state to 3
	{
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->cv_m.wait(the_lock, 
				[the_sync]{return the_sync->val_m >= 3;});
	}

	scrstr = std::to_string(data);
	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		cout << "The function call ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		cout << "by worker thread " << std::setw(2) << scrstr << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		cout << "has ended.\n";
	}

	// tell caller we're done state 4
	{
		{
			unique_lock_mutex the_lock(the_sync->mutex_m);
			the_sync->val_m = 4;
		}
		the_sync->cv_m.notify_one();
	}

} // _do_some_work_hf

static void _zap_syncs_hf(sync_cls_vec *the_syncs)
{
	for(sync_cls_vec::reverse_iterator ii = the_syncs->rbegin();
	    ii != the_syncs->rend();
		 ++ii)
	{
		delete *ii;
		*ii = 0;
	} // for ii
} // _zap_syncs_hf

static void _make_rnd_eng_hf(std::mt19937 *rnd_eng)
{
	std::random_device rnd_dev;
	std::seed_seq rnd_seed{rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev(),
			rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev()};

	*rnd_eng = std::mt19937(rnd_seed);
}


int main()
{
	sync_cls_vec the_syncs;
	std::vector<std::thread> the_threads;

	try
	{

		int const num_threads_k = 6;
		std::vector<int> the_states;
		std::mutex cout_guard;
		std::mt19937 rnd_eng;

		_make_rnd_eng_hf(&rnd_eng);

		for(int ii = 0; ii < num_threads_k; ++ii)
		{
			sync_cls_ptr the_sync;
			the_sync = new sync_cls;
			the_syncs.push_back(the_sync);
			the_threads.push_back(
					std::thread(_do_some_work_hf, ii, &cout_guard, the_sync));
			the_states.push_back(0);
		} // for ii

		for(int ii = num_threads_k-1; ii >= 0; --ii)
		{
			{
				unique_lock_mutex the_lock(the_syncs[ii]->mutex_m);
				the_states[ii] = 1;
				the_syncs[ii]->val_m = 1;
			}
			the_syncs[ii]->cv_m.notify_one();
		}

		while(the_states[0] != 4)
		{
			for(int ii = 0; ii < num_threads_k; ++ii)
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
					// for each thread to wait until later thread finishes
					if(num_threads_k-1 == ii || the_states[ii+1] >= 4)
					{
						{
							unique_lock_mutex the_lock(the_sync->mutex_m);
							the_sync->val_m = 3;
						}
						the_states[ii] = 3;
						the_sync->cv_m.notify_one();
					}
				}
			}
		} // the_states[0] != 4

		if(0 == rnd_eng() % 4)
			throw 3;

		cout << "end of try\n";
	} // try
	catch(...)
	{
		std::cerr << "CATCH err\n";
		// Need to tell all the threads to terminate, which I don't feel
		// like doing right now.
		for(auto &ii:the_threads)
			ii.join();
		_zap_syncs_hf(&the_syncs);
		throw;
	}

	for(auto &ii:the_threads)
		ii.join();
	_zap_syncs_hf(&the_syncs);
	cout << "end of main\n";

} // main
