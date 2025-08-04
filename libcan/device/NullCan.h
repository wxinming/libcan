#pragma once
#include "../misc/Base.h"

namespace can {

	class CAN_DLL_EXPORT NullCan : public Base
	{
	public:
		NullCan(DeviceType deviceType);
		~NullCan();
		bool open(const can::Device& device) override;
		bool reopen() override;
		bool close() override;
		bool reset() override;

	protected:
		bool send(const can::Msg* msg, size_t size, int channel) override;
		size_t recv(can::Msg* msg, size_t size, int channel, size_t timeout) override;
	};

}
