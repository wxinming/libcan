#include "NullCan.h"

can::NullCan::NullCan(DeviceType deviceType)
	:Base(deviceType)
{

}

can::NullCan::~NullCan()
{
}

bool can::NullCan::open(const can::Device& device)
{
	return true;
}

bool can::NullCan::reopen()
{
	return true;
}

bool can::NullCan::close()
{
	return true;
}

bool can::NullCan::reset()
{
	return true;
}

bool can::NullCan::send(const can::Msg* msg, size_t size, int channel)
{
	return true;
}

size_t can::NullCan::recv(can::Msg* msg, size_t size, int channel, size_t timeout)
{
	return 0;
}
