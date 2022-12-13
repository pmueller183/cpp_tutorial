//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <vector>

#include <random>

#include <thread>
#include <mutex>
typedef std::vector<std::thread> thread_vec;
typedef std::lock_guard<std::mutex> lock_mutex;

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

#include "bounded_buffer.h"

int const sleep_mlls_kf = 100;

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

void lesson2a()
{
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
} // lesson2nd


