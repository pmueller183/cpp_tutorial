//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <future>
#include <chrono>

typedef std::chrono::duration<_int64, std::nano> duration_type;

static int _future_func_hf(duration_type const &duration, int rv)
{
	std::this_thread::sleep_for(duration);
	return rv;
} // _future_func_hf

void lesson4b()
{
	cout << "lesson4b:\n";

	auto f0th = std::async(std::launch::async, _future_func_hf,
			std::chrono::seconds(9), 69);
	auto f1st = std::async(std::launch::async, _future_func_hf,
			std::chrono::seconds(3), 13);
	auto f2nd = std::async(std::launch::async, _future_func_hf,
			std::chrono::seconds(6), 25);

	auto const my_sleep_k = std::chrono::seconds(1);
	auto const timeout_k = std::chrono::milliseconds(0);
	auto const &ready_status = std::future_status::ready;
	while(f0th.valid() || f1st.valid() || f2nd.valid())
	{
		if(f0th.valid() && ready_status == f0th.wait_for(timeout_k))
			cout << "task0th returns " << f0th.get() << endl;

		if(f1st.valid() && ready_status == f1st.wait_for(timeout_k))
			cout << "task1st returns " << f1st.get() << endl;

		if(f2nd.valid() && ready_status == f2nd.wait_for(timeout_k))
			cout << "task2nd returns " << f2nd.get() << endl;

		if(!f0th.valid() && !f1st.valid() && !f2nd.valid())
			break;

		cout << "I'm doing my own work ... ";
		std::this_thread::sleep_for(my_sleep_k);
		cout << "done.\n";
	} // while f0th, f1st, f2nd

	cout << "lesson4b hopefully done\n";
} // lesson4b

