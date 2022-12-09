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

static void _make_rnd_eng_hf(std::mt19937 *rnd_eng)
{
	std::random_device rnd_dev;
	std::seed_seq rnd_seed{rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev(),
			rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev()};

	*rnd_eng = std::mt19937(rnd_seed);
} // _make_rnd_eng_hf

template<class rnd_generator>
static int _uniform_int_hf(rnd_generator &generator, int min, int max)
{
	std::uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
} // _uniform_int_hf

typedef std::unique_lock<std::mutex> unique_lock_mutex;

typedef enum{wait_for_start_kf, do_start_kf, ready_for_work_kf, do_work_kf, done_kf}
		sub_thread_enm;

class sync_cls
{
public:
	std::mutex mutex_m;
	std::condition_variable cv_m;
	sub_thread_enm state_m;

	sync_cls()
	{
		std::mutex mutex_m;
		std::condition_variable cv_m;
		state_m = wait_for_start_kf;
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
	int sleep_mlls;
	std::mt19937 rnd_eng;
	_make_rnd_eng_hf(&rnd_eng);

	// don't start until caller sets sync variable to 1
	{
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->cv_m.wait(
				the_lock, [the_sync]{return the_sync->state_m >= do_start_kf;});
	}

	int data;
	std::string scrstr;

	data = thread_id;

	// sleep for a random amount of time (simulate long initialization)
	sleep_mlls = _uniform_int_hf(rnd_eng, 100, 300);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls));

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
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->state_m = ready_for_work_kf;
	}
	the_sync->cv_m.notify_one();

	// wait until caller sets state to 3
	{
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->cv_m.wait(the_lock, 
				[the_sync]{return the_sync->state_m >= do_work_kf;});
	}
	 
	// sleep for a random amount of time (simulate long processing)
	sleep_mlls = _uniform_int_hf(rnd_eng, 100, 300);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls));

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
		unique_lock_mutex the_lock(the_sync->mutex_m);
		the_sync->state_m = done_kf;
	}
	the_sync->cv_m.notify_one();

} // _do_some_work_hf

int main()
{
	try
	{
		struct ensure_release_sct
		{
			std::vector<std::thread> the_threads;
			sync_cls_vec the_syncs;
			~ensure_release_sct()
			{
				std::cerr << "joining threads...";
				for(auto &ii:the_threads)
					ii.join();
				std::cerr << "done\n";
				for(sync_cls_vec::reverse_iterator ii = the_syncs.rbegin();
					 ii != the_syncs.rend();
					 ++ii)
				{
					delete *ii;
					*ii = 0;
				} // for ii
			}
		} ers; // ensure_release_struct

		int const num_threads_k = 6;
		std::vector<sub_thread_enm> the_states;
		std::mutex cout_guard;
		std::mt19937 rnd_eng;

		_make_rnd_eng_hf(&rnd_eng);

		for(int ii = 0; ii < num_threads_k; ++ii)
		{
			sync_cls_ptr the_sync;
			the_sync = new sync_cls;
			ers.the_syncs.push_back(the_sync);
			ers.the_threads.push_back(
					std::thread(_do_some_work_hf, ii, &cout_guard, the_sync));
			the_states.push_back(wait_for_start_kf);
		} // for ii

		for(int ii = num_threads_k-1; ii >= 0; --ii)
		{
			{
				unique_lock_mutex the_lock(ers.the_syncs[ii]->mutex_m);
				the_states[ii] = do_start_kf;
				ers.the_syncs[ii]->state_m = do_start_kf;
			}
			ers.the_syncs[ii]->cv_m.notify_one();
		}

		while(the_states[0] != done_kf)
		{
			for(int ii = 0; ii < num_threads_k; ++ii)
			{
				sync_cls *the_sync = ers.the_syncs[ii];
				{
					unique_lock_mutex the_lock(the_sync->mutex_m);
					the_sync->cv_m.wait_for(the_lock,
							std::chrono::seconds(0),
							[the_sync]{return the_sync->state_m >= ready_for_work_kf;});
					the_states[ii] = the_sync->state_m;
					int const qq = 77;
				}
				if(ready_for_work_kf == the_states[ii])
				{
					// for each thread to wait until later thread finishes
					if(num_threads_k-1 == ii || the_states[ii+1] >= done_kf)
					{
						{
							unique_lock_mutex the_lock(the_sync->mutex_m);
							the_sync->state_m = do_work_kf;
						}
						the_states[ii] = do_work_kf;
						the_sync->cv_m.notify_one();
					}
				}
			}
		} // the_states[0] != done_kf

		if(0 == _uniform_int_hf(rnd_eng, 0, 3))
			throw 3;

		cout << "end of try\n";
	} // try
	catch(...)
	{
		std::cerr << "CATCH err\n";
		// Need to tell all the threads to terminate, which I don't feel
		// like doing right now.
		throw;
	}

	cout << "end of main\n";

} // main

