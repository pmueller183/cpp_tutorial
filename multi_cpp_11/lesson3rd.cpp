//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <atomic>

#include <vector>
typedef std::vector<std::thread> thread_vec;

#include <random>

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

class counter_cls
{
public:

	std::atomic<int> val_m, num_exceptions_m;

	counter_cls() : val_m(0) {};
	template<class rnd_generator>
	void increment(rnd_generator &the_rnd)
	{
		if(0 == _uniform_int_hf(the_rnd, 0, 8))
			throw std::exception("ha ha failed");
		++val_m;
	}

	int get() const
	{
		return val_m;
	}
}; // counter_cls

static void _counter_hf(counter_cls *val)
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

void lesson3rd()
{
	cout << "lesson3rd:\n";

	thread_vec the_threads;
	counter_cls the_counter;
	for(auto ii = 0; ii < 5; ++ii)
		the_threads.push_back(std::thread(_counter_hf, &the_counter));
	for(auto &ii : the_threads)
		ii.join();
	cout << "val " << the_counter.get() << "; exceptions caught " <<
			the_counter.num_exceptions_m << endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_ke));
	cout << "lesson3rd: hopefully done\n";

} // lesson3rd
