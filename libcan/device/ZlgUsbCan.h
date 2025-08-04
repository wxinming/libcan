#pragma once
#include "../misc/Base.h"

namespace can {

	class CAN_DLL_EXPORT ZlgUsbCan : public Base
	{
	public:
		ZlgUsbCan(DeviceType deviceType);
		~ZlgUsbCan();
		bool open(const can::Device& device) override;
		bool reopen() override;
		bool close() override;
		bool reset() override;
		void clearBuffer(int channel) override;

	protected:
		bool send(const can::Msg* msg, size_t size, int channel) override;
		size_t recv(can::Msg* msg, size_t size, int channel, size_t timeout) override;

	private:
		void* m_deviceHandle = nullptr;
		void* m_channelHandle[CAN_MAX_CHANNEL_COUNT] = { nullptr };
	};

}
