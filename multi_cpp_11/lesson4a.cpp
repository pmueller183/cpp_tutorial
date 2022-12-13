//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#include "lessons.h"

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <future>

static void _future_func_hf()
{
	cout << "I'm a thread\n";
} // _future_func_hf

void lesson4a()
{
	cout << "lesson4a:\n";

	auto future_thread = std::async(std::launch::async, _future_func_hf);

	future_thread.get();

	cout << "lesson4a hopefully done\n";
} // lesson4a

