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
using std::atomic_wait;

typedef enum{wait_for_start_kf, do_start_kf, ready_for_work_kf, do_work_kf, done_kf}
		thread_state_enm;
typedef std::atomic<thread_state_enm> atomic_thread_state_enm;
typedef atomic_thread_state_enm *state_ptr;
typedef std::vector<state_ptr> state_vec;

static void _do_some_work_hf(int thread_id, std::mutex *cout_guard, 
		atomic_thread_state_enm *the_state)
{
	// don't start until caller sets state variable to 1
	atomic_wait(the_state, wait_for_start_kf);

	int data;
	std::string scrstr;

	data = thread_id;

	{
		std::lock_guard<std::mutex> lock(*cout_guard);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		cout << "the _do_some_work_hf ";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		cout << "id " << std::setw(2) << data << " function is running on another ";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		cout << "thread\n";
	};

	// tell caller we finished initializing (state var 2)
	*the_state = ready_for_work_kf;
	the_state->notify_one();

	// wait until caller sets state to 3
	atomic_wait(the_state, ready_for_work_kf);

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
	*the_state = done_kf;
	the_state->notify_one();

} // _do_some_work_hf

static void _zap_states_hf(state_vec *the_states)
{
	for(state_vec::reverse_iterator ii = the_states->rbegin();
	    ii != the_states->rend();
		 ++ii)
	{
		std::cerr << "delete state obj " << *ii << endl;
		delete *ii;
		*ii = 0;
	} // for ii
} // _zap_states_hf

static void _make_rnd_eng_hf(std::mt19937 *rnd_eng)
{
	std::random_device rnd_dev;
	std::seed_seq rnd_seed{rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev(),
			rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev()};

	*rnd_eng = std::mt19937(rnd_seed);
}


int main()
{
	state_vec the_states;
	std::vector<std::thread> the_threads;

	std::mutex cout_guard; // make sure cout calls are not interleaved
	std::mt19937 rnd_eng;
	std::vector<int> startup_order; // order the threads will start; this will
	                                // be randomized

	_make_rnd_eng_hf(&rnd_eng);

	try
	{
		int const num_threads_k = 8;

		for(int ii = 0; ii < num_threads_k; ++ii)
		{
			state_ptr the_state;
			the_state = new atomic_thread_state_enm;
			*the_state = wait_for_start_kf;
			the_states.push_back(the_state);
			the_threads.push_back(
					std::thread(_do_some_work_hf, ii, &cout_guard, the_state));
			startup_order.push_back(ii);
		} // for ii

		// startup threads in random order
		std::shuffle(startup_order.begin(), startup_order.end(), rnd_eng);
		for(auto &ii : startup_order)
		{
			*(the_states[ii]) = do_start_kf;
			the_states[ii]->notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		//this loop ensures that the threads will finish in inverse order
		while(*(the_states[0]) != done_kf)
		{
			for(int ii = num_threads_k - 1; ii >= 0; --ii)
			{
				atomic_thread_state_enm *the_state = the_states[ii];
				if(ready_for_work_kf == *the_state)
				{
					// for each thread to wait until later thread finishes
					// note that the last thread (num_threads_k-1) does not have to wait
					if(num_threads_k-1 == ii || *(the_states[ii+1]) >= done_kf)
					{
						*the_state = do_work_kf;
						the_state->notify_one();
					}
				}
			}
		} // *(the_states[0]) != done_kf

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
		_zap_states_hf(&the_states);
		throw;
	}

	for(auto &ii:the_threads)
		ii.join();
	_zap_states_hf(&the_states);
	cout << "end of main\n";

} // main
