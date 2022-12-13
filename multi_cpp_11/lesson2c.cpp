//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <vector>

#include <thread>
#include <mutex>
typedef std::vector<std::thread> thread_vec;
typedef std::lock_guard<std::mutex> lock_mutex;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "bounded_buffer.h"

void _consumer_hf(int ndx,
		std::mutex *cout_guard, bounded_buffer_cls *buffer)
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

void _producer_hf(int ndx,
		std::mutex *cout_guard, bounded_buffer_cls *buffer)
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

void lesson2c()
{
	{ // consumer / producer
		std::mutex cout_guard;
		bounded_buffer_cls buffer(20);

		std::thread c0(_consumer_hf, 0, &cout_guard, &buffer);
		std::thread c1(_consumer_hf, 1, &cout_guard, &buffer);
		std::thread c2(_consumer_hf, 2, &cout_guard, &buffer);
		std::thread p0(_producer_hf, 0, &cout_guard, &buffer);
		std::thread p1(_producer_hf, 1, &cout_guard, &buffer);

		c0.join(); c1.join(); c2.join(); p0.join(); p1.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mlls_ke));
		cout << "hopefully done\n\n";
	} // consumer / producer

} // lesson2c
