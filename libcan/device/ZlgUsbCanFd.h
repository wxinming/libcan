#pragma once
#include "../misc/Base.h"

namespace can {

	class CAN_DLL_EXPORT ZlgUsbCanFd : public Base
	{
	public:
		ZlgUsbCanFd(DeviceType type);
		~ZlgUsbCanFd();
		bool open(const can::Device& device) override;
		bool reopen() override;
		bool close() override;
		bool reset() override;
		void clearBuffer(int channel) override;

	protected:
		bool send(const can::Msg* msg, size_t size, int channelIndex) override;
		size_t recv(can::Msg* msg, size_t size, int channelIndex, size_t timeout) override;

	private:
		void* m_deviceHandle = nullptr;
		void* m_channelHandle[CAN_MAX_CHANNEL_COUNT] = { nullptr };
	};

}
