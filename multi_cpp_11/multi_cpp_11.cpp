//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

static int const _lesson_ndx_kf = 0;

#include <vector>

#include <random>

#include <thread>
#include <mutex>
typedef std::lock_guard<std::mutex> lock_mutex;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "bounded_buffer.h"

static void _make_rnd_eng_hf(std::mt19937 *rnd_eng)
{
	std::random_device rnd_dev;
	std::seed_seq rnd_seed{rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev(),
			rnd_dev(), rnd_dev(), rnd_dev(), rnd_dev()};

	*rnd_eng = std::mt19937(rnd_seed);
} // _make_rnd_eng_hf

template<class rnd_generator>
static int _uniform_int_hf(rnd_generator &the_rnd, int min, int max)
{
	std::uniform_int_distribution<int> distribution(min,max);
	return distribution(the_rnd);
} // _uniform_int_hf


int const sleep_mlls_kf = 100;

typedef std::vector<std::thread> thread_vec;

struct counter_sct
{
	std::mutex mutex_m;
	int val_m;
	int num_exceptions_m;
	counter_sct() : val_m(0), num_exceptions_m(0) {}
	template<class rnd_generator>
	void increment(rnd_generator &the_rnd)
	{
		std::lock_guard<std::mutex> lock(mutex_m);
		if(0 == _uniform_int_hf(the_rnd, 0, 8))
			throw std::exception("ha ha failed");
		++val_m;
	}
}; // counter_sct

static void _counter_hf(counter_sct *val)
{
	std::mt19937 rnd_eng;
	_make_rnd_eng_hf(&rnd_eng);

	for(int ii = 0; ii < 20; ++ii)
	{
		try
		{
			val->increment(rnd_eng);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		catch(std::exception &)
		{
			++val->num_exceptions_m;
		}
	}
} // _counter_hf

struct cpx_sct
{
	std::recursive_mutex mutex_m;
	int val_m;

	cpx_sct() : val_m(100) {}

	void mul(int x)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_m);
		val_m *= x;
	} // mul

	void div(int x)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_m);
		val_m /= x;
	} // div

	void muldiv(int x, int y)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex_m);
		mul(x);
		div(y);
	} // muldiv
}; // cpx_sct

static void _call_once_hf(std::thread::id const &thread_id)
{
	cout << "called once by thread " << thread_id << endl;
} // _call_once_hf

static void _timed_work_hf(std::once_flag *the_flag, std::mutex *cout_guard, std::timed_mutex *mutex)
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

void _consumer_hf(int ndx, std::mutex *cout_guard, bounded_buffer_cls *buffer)
{
	for(auto ii = 0; ii < 50; ++ii)
	{
		int const val = buffer->fetch();
		{
			lock_mutex dummy(*cout_guard);
			cout << "consumer " << ndx << " fetched  " << std::setw(4) << val << endl;	
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	} // for ii
} // _consumer_hf

void _producer_hf(int ndx, std::mutex *cout_guard, bounded_buffer_cls *buffer)
{
	for(auto ii = 0; ii < 75; ++ii)
	{
		int const val = ndx * 100 + ii;
		buffer->deposit(val);
		{
			lock_mutex dummy(*cout_guard);
			cout << "producer " << ndx << " produced " << std::setw(4) << val << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	} // for ii
} // _producer_hf

int main()
{
	if(0 == _lesson_ndx_kf)
		lesson0th();
#if 0
	{ // counter
		thread_vec the_threads;
		counter_sct the_counter;
		for(auto ii = 0; ii < 5; ++ii)
			the_threads.push_back(std::thread(_counter_hf, &the_counter));
		for(auto &ii : the_threads)
			ii.join();
		cout << "val " << the_counter.val_m << "; exceptions caught " <<
				the_counter.num_exceptions_m << endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_kf));
		cout << "hopefully done\n\n";
	} // counter

	{ // complex
		cpx_sct the_cpx;
		int backup_val;
		backup_val = the_cpx.val_m;

		the_cpx.val_m = backup_val;
		the_cpx.mul(10);
		the_cpx.div(20);
		cout << "the_cpx " << the_cpx.val_m << endl;

		the_cpx.val_m = backup_val;
		the_cpx.muldiv(10, 20);
		cout << "the_cpx " << the_cpx.val_m << endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_kf));
		cout << "hopefully done\n\n";
	} // complex
	
	{ // timed_work
		std::once_flag once_flag;
		std::mutex cout_guard;
		std::timed_mutex mutex;
		thread_vec the_threads;

		for(auto ii = 0; ii < 4; ++ii)
			the_threads.push_back(std::thread(
					_timed_work_hf, &once_flag, &cout_guard, &mutex));
		for(auto &ii : the_threads)
			ii.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_kf));
		cout << "hopefully done\n\n";
	} // timed_work

	{ // consumer / producer
		std::mutex cout_guard;
		bounded_buffer_cls buffer(20);

		std::thread c0(_consumer_hf, 0, &cout_guard, &buffer);
		std::thread c1(_consumer_hf, 1, &cout_guard, &buffer);
		std::thread c2(_consumer_hf, 2, &cout_guard, &buffer);
		std::thread p0(_producer_hf, 0, &cout_guard, &buffer);
		std::thread p1(_producer_hf, 1, &cout_guard, &buffer);

		c0.join(); c1.join(); c2.join(); p0.join(); p1.join();
		
	} // consumer / producer
#endif

} // main

