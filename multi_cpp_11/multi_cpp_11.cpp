//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <vector>

#include <random>

#include <thread>
#include <mutex>

#include <iostream>
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
static int _uniform_int_hf(rnd_generator &the_rnd, int min, int max)
{
	std::uniform_int_distribution<int> distribution(min,max);
	return distribution(the_rnd);
} // _uniform_int_hf


int const sleep_mlls_kf = 100;

typedef std::vector<std::thread> thread_vec;

static void _hello_hf()
{
	cout << "func thread " << std::this_thread::get_id() << endl;;
} // _hello_hf

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

void _counter_hf(counter_sct *val)
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

int main()
{
	{ // startup
		thread_vec func_threads, lambda_threads;
		for(auto ii = 0; ii < 5; ++ii)
		{
			func_threads.push_back(std::thread(_hello_hf));
			lambda_threads.push_back(std::thread(([](){
					cout << "lambda thread " << std::this_thread::get_id() << endl;}))
					);
		} // for ii
		for(auto &ii: lambda_threads)
			ii.join();
		for(auto &ii: func_threads)
			ii.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_kf));
		cout << "hopefully done\n\n";
	} // startup

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

} // main

