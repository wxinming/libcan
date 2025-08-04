#include "ZlgUsbCan.h"

#include "../third/zlgcan_usb/include/zlgcan.h"
#ifdef _WIN64
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x64/zlgcan.lib")
#else
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x86/zlgcan.lib")
#endif

can::ZlgUsbCan::ZlgUsbCan(DeviceType deviceType)
	: Base(deviceType)
{

}

can::ZlgUsbCan::~ZlgUsbCan()
{
	close();
}

bool can::ZlgUsbCan::open(const can::Device& device)
{
	bool result = false;
	do
	{
		uint32_t deviceType = ZCAN_USBCAN2;
		switch (m_deviceType)
		{
		case can::DT_ZLG_USBCAN1:
			deviceType = ZCAN_USBCAN1;
			break;
		case can::DT_ZLG_USBCAN2:
			deviceType = ZCAN_USBCAN2;
			break;
		default:
			break;
		}

		m_deviceHandle = ZCAN_OpenDevice(deviceType, device.deviceIndex, 0);
		if (m_deviceHandle == INVALID_DEVICE_HANDLE) {
			setLastError("打开CAN卡设备%d失败", device.deviceIndex);
			break;
		}

		bool success = true;
		for (int i = 0; i < m_deviceChannelCount; ++i) {
			if (!device.enableChannel[i]) {
				continue;
			}

			int baudrate = 0;
			switch (translateArbiBaud(device.arbiBaud[i]))
			{
			case AB_1Mbps:
				baudrate = 1000000;
				break;
			case AB_800Kbps:
				baudrate = 800000;
				break;
			case AB_500Kbps:
				baudrate = 500000;
				break;
			case AB_250Kbps:
				baudrate = 250000;
				break;
			case AB_125Kbps:
				baudrate = 125000;
				break;
			case AB_100Kbps:
				baudrate = 100000;
				break;
			case AB_50Kbps:
				baudrate = 50000;
				break;
			default:
				baudrate = 500000;
				break;
			}

			/*
			* @note
			* 不要把zlg的dll放到C盘中, 调用ZCAN_SetValue会修改devices_property目录下面的xml文件,
			* 放在C盘如果不以管理员权限运行,会导致修改xml文件,然后返回失败.
			*/
			char path[256] = { 0 }, value[256] = { 0 };
			sprintf_s(path, "%d/baud_rate", i);
			sprintf_s(value, "%d", baudrate);
			if (ZCAN_SetValue(m_deviceHandle, path, value) != STATUS_OK) {
				success = false;
				setLastError("设置CAN卡设备%d,通道%d波特率失败", device.deviceIndex, i);
				break;
			}

			ZCAN_CHANNEL_INIT_CONFIG config = { 0 };
			config.can_type = TYPE_CAN;
			config.can.mode = 0;
			config.can.filter = 0;
			config.can.acc_code = 0;
			config.can.acc_mask = 0xffffffff;

			m_channelHandle[i] = ZCAN_InitCAN(m_deviceHandle, i, &config);
			if (m_channelHandle[i] == INVALID_CHANNEL_HANDLE) {
				success = false;
				setLastError("初始化CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

			if (ZCAN_StartCAN(m_channelHandle[i]) != STATUS_OK) {
				success = false;
				setLastError("开启CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

			ZCAN_ClearBuffer(m_channelHandle[i]);
			clearBuffer(i);
		}

		if (!success) {
			close();
			break;
		}

		m_canDevice = device;
		m_open = true;

		result = true;
	} while (false);
	return result;
}

bool can::ZlgUsbCan::reopen()
{
	close();
	return open(m_canDevice);
}

bool can::ZlgUsbCan::close()
{
	if (m_deviceHandle) {
		for (int i = 0; i < m_deviceChannelCount; ++i) {
			closeLock(i);
			m_canDevice.enableChannel[i] = false;
			if (m_channelHandle[i]) {
				ZCAN_ResetCAN(m_channelHandle[i]);
				m_channelHandle[i] = nullptr;
			}
			closeUnlock(i);
		}
		ZCAN_CloseDevice(m_deviceHandle);
		m_deviceHandle = nullptr;
	}
	m_open = false;
	return true;
}

bool can::ZlgUsbCan::reset()
{
	bool result = true;
	for (int i = 0; i < m_deviceChannelCount; ++i) {
		if (!m_canDevice.enableChannel[i]) {
			continue;
		}

		if (ZCAN_ResetCAN(m_channelHandle[i]) != STATUS_OK ||
			ZCAN_StartCAN(m_channelHandle[i]) != STATUS_OK) {
			result = false;
		}
	}
	return result;
}

void can::ZlgUsbCan::clearBuffer(int channel)
{
	__super::clearBuffer(channel);
	if (channel < m_deviceChannelCount && m_channelHandle[channel]) {
		ZCAN_ClearBuffer(m_channelHandle[channel]);
	}
}

bool can::ZlgUsbCan::send(const can::Msg* msg, size_t size, int channel)
{
	bool result = false;
	do
	{
		std::unique_ptr<ZCAN_Transmit_Data[]> data(new ZCAN_Transmit_Data[size]);
		memset(data.get(), 0, sizeof(ZCAN_Transmit_Data) * size);
		for (size_t i = 0; i < size; ++i) {
			data[i].frame.can_id = MAKE_CAN_ID(static_cast<canid_t>(msg[i].id), m_canDevice.isExpandFrame ? 1 : 0, 0, 0);
			data[i].frame.can_dlc = getDlc(&msg[i]);
			memcpy(data[i].frame.data, msg[i].data, getDlc(&msg[i]));
			data[i].transmit_type = 0;
			const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
			const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
			const_cast<can::Msg*>(&msg[i])->channelIndex = channel;
		}

		m_mutex.send.lock();
		auto count = ZCAN_Transmit(m_channelHandle[channel], data.get(), size);
		m_mutex.send.unlock();
		if (count != size) {
			processMsg("F", msg, size, channel);
			break;
		}
		processMsg("S", msg, size, channel);
		result = true;
	} while (false);
	return result;
}


size_t can::ZlgUsbCan::recv(can::Msg* msg, size_t size, int channel, size_t timeout)
{
	do
	{
		if (!ZCAN_GetReceiveNum(m_channelHandle[channel], TYPE_CAN)) {
			size = 0;
			break;
		}

		std::unique_ptr<ZCAN_Receive_Data[]> data(new ZCAN_Receive_Data[size]);
		memset(data.get(), 0, sizeof(ZCAN_Receive_Data) * size);
		m_mutex.recv.lock();
		size = ZCAN_Receive(m_channelHandle[channel], data.get(), size, timeout);
		m_mutex.recv.unlock();

		for (size_t i = 0; i < size; ++i) {
			msg[i].id = GET_ID(data[i].frame.can_id);
			msg[i].dlc = data[i].frame.can_dlc;
			memcpy(msg[i].data, data[i].frame.data, data[i].frame.can_dlc);
			msg[i].expFrame = IS_EFF(data[i].frame.can_id);
			msg[i].remFrame = IS_RTR(data[i].frame.can_id);
			msg[i].timeStamp = static_cast<int>(m_time.recv.getEndTime());
			msg[i].channelIndex = channel;
		}
		processMsg("R", msg, size, channel);
	} while (false);
	return size;
}

