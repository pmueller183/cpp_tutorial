//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include <vector>
#include <thread>
#include <iostream>

int const sleep_mlls_kf = 100;

typedef std::vector<std::thread> thread_vec;

using std::cout;
using std::endl;

static void _hello_hf()
{
	cout << "func thread " << std::this_thread::get_id() << endl;;
} // _hello_hf

struct counter_sct
{
    int val_m;
    counter_sct() : val_m(0){}
    void increment()
	 {
        ++val_m;
    }
}; // counter_sct

void _counter_hf(counter_sct *val)
{
	for(int ii = 0; ii < 20; ++ii)
	{
		val->increment();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
} // _counter_hf

int main()
{
	{
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
	{
		thread_vec the_threads;
		counter_sct the_counter;
		for(auto ii = 0; ii < 5; ++ii)
			the_threads.push_back(std::thread(_counter_hf, &the_counter));
		for(auto &ii : the_threads)
			ii.join();
		cout << "val " << the_counter.val_m << endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_kf));
		cout << "hopefully done\n\n";
	} // counter

} // main

