#include "Buffer.h"

#if 0
can::Buffer::Buffer(size_t size)
	:size_(size), stop_(false)
{

}

can::Buffer::~Buffer()
{
	{
		std::unique_lock<std::mutex> lock(mutex_);
		stop_ = true;
	}
}

void can::Buffer::push(const can::Msg* msg, size_t size)
{
	std::unique_lock<std::mutex> lock(mutex_);
	for (size_t i = 0; i < size; ++i) {
		if (queue_.size() > size_ - 1) {
			queue_.pop();
		}
		queue_.push(msg[i]);
	}
	cond_var_.notify_one();
}

size_t can::Buffer::pop(can::Msg* msg, size_t size, size_t timeout)
{
	size_t i = 0;
	for (i = 0; i < size; ++i) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (!cond_var_.wait_for(lock, std::chrono::milliseconds(timeout), [this]() { return !queue_.empty() || stop_; })) {
			break;
		}

		if (queue_.empty() && stop_) {
			break;
		}

		msg[i] = queue_.front();
		queue_.pop();
	}
	return i;
}

void can::Buffer::clear()
{
	std::unique_lock<std::mutex> lock(mutex_);
	while (!queue_.empty()) {
		queue_.pop();
	}
}
#else
can::Buffer::Buffer(size_t size)
	:size_(size)
{

}

can::Buffer::~Buffer()
{

}

void can::Buffer::push(const can::Msg* msg, size_t size)
{
	std::lock_guard<std::mutex> lock(mutex_);
	for (size_t i = 0; i < size; ++i) {
		if (queue_.size() > size_ - 1) {
			queue_.pop();
		}
		queue_.push(msg[i]);
	}
}

size_t can::Buffer::pop(can::Msg* msg, size_t size)
{
	std::lock_guard<std::mutex> lock(mutex_);
	size_t i = 0;
	for (i = 0; i < size; ++i) {
		if (queue_.empty()) {
			break;
		}

		msg[i] = queue_.front();
		queue_.pop();
	}
	return i;
}

void can::Buffer::clear()
{
	std::lock_guard<std::mutex> lock(mutex_);
	while (!queue_.empty()) {
		queue_.pop();
	}
}
#endif
