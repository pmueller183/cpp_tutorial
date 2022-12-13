//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#pragma once

#include <mutex>

class bounded_buffer_cls
{
public:
	int *buffer_m;
	int capacity_m;

	int front_m, rear_m;
	int count_m;

	std::mutex lock_m;

	std::condition_variable not_full_m,
	                        not_empty_m;

	bounded_buffer_cls(int capacity);
	~bounded_buffer_cls();

	void deposit(int data);
	int fetch();

}; // bounded_buffer_cls
