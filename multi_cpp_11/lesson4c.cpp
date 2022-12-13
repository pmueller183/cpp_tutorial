//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <future>
#include <chrono>
#include <random>
#include <algorithm>

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

typedef std::chrono::duration<_int64, std::nano> duration_type;

static int _future_func_hf(duration_type const &duration, int rv)
{
	std::this_thread::sleep_for(duration);
	return rv;
} // _future_func_hf

void lesson4c()
{
	cout << "lesson4c:\n";

	std::mt19937 rnd_eng;
	_make_rnd_eng_hf(&rnd_eng);

	auto beg_time = std::chrono::high_resolution_clock::now();
	
	std::vector<std::future<int>> the_futures;

	for(auto ii = 0; ii < 10; ++ii)
	{
		int const duration_mlls = _uniform_int_hf(rnd_eng, 50, 1500);
		auto the_duration = std::chrono::milliseconds(duration_mlls);
		the_futures.emplace_back(std::async(
				std::launch::async, _future_func_hf, the_duration, ii));
	} // for ii building threads

	cout << "Start querying\n";

	auto const &ready_status = std::future_status::ready;
	auto const timeout_k = std::chrono::milliseconds(10); // 0 means no waiting

	while(std::any_of(the_futures.begin(), the_futures.end(), 
			[](std::future<int>&f){return f.valid();}))
	{
		for(auto &ii : the_futures)
		{
			if(ii.valid() && ready_status == ii.wait_for(timeout_k))
				std::cout << "finished: " << ii.get() << std::endl;
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();
	auto total_time = end_time - beg_time;
	auto time_in_mlls = 
			std::chrono::duration_cast<std::chrono::milliseconds>(total_time);
	_int64 mlls_taken = time_in_mlls.count();
	cout << "took " << mlls_taken << " milliseconds\n";

	cout << "lesson4c hopefully done\n";
} // lesson4c

