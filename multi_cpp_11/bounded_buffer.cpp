//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-

#pragma once

#include "bounded_buffer.h"

bounded_buffer_cls::bounded_buffer_cls(int capacity) :
			capacity_m(capacity), front_m(0), rear_m(0), count_m(0)
{
	buffer_m = new int[capacity];
}
bounded_buffer_cls::~bounded_buffer_cls()
{
	delete []buffer_m;
}

void bounded_buffer_cls::deposit(int data)
{
	std::unique_lock<std::mutex> ul(lock_m);

	not_full_m.wait(ul, [this](){return count_m != capacity_m; });

	buffer_m[rear_m] = data;
	rear_m = (rear_m + 1) % capacity_m;
	++count_m;

	ul.unlock();
	not_empty_m.notify_one();
} // deposit

int bounded_buffer_cls::fetch()
{
	int rv;
	std::unique_lock<std::mutex> ul(lock_m);

	not_empty_m.wait(ul, [this](){return count_m != 0; });

	rv = buffer_m[front_m];
	front_m = (front_m + 1) % capacity_m;
	--count_m;

	ul.unlock();
	not_full_m.notify_one();

	return rv;
} // fetch

