#include "ZlgUsbCanFd.h"

#include "../third/zlgcan_usb/include/zlgcan.h"
#ifdef _WIN64
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x64/zlgcan.lib")
#else
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x86/zlgcan.lib")
#endif

can::ZlgUsbCanFd::ZlgUsbCanFd(DeviceType type)
	:Base(type)
{
	m_supportFd = true;
}

can::ZlgUsbCanFd::~ZlgUsbCanFd()
{
	close();
}

bool can::ZlgUsbCanFd::open(const can::Device& device)
{
	bool result = false;
	do
	{
		uint32_t deviceType = ZCAN_USBCANFD_200U;
		switch (m_deviceType)
		{
		case can::DT_ZLG_USBCANFDMINI:
			deviceType = ZCAN_USBCANFD_MINI;
			break;
		case can::DT_ZLG_USBCANFD100U:
			deviceType = ZCAN_USBCANFD_100U;
			break;
		case can::DT_ZLG_USBCANFD200U:
			deviceType = ZCAN_USBCANFD_200U;
			break;
		case can::DT_ZLG_USBCANFD400U:
			deviceType = ZCAN_USBCANFD_400U;
			break;
		case can::DT_ZLG_USBCANFD800U:
			deviceType = ZCAN_USBCANFD_800U;
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
		char path[256] = { 0 }, value[256] = { 0 };
		for (int i = 0; i < m_deviceChannelCount; ++i) {
			if (!device.enableChannel[i]) {
				continue;
			}

			/*
			* @note
			* 不要把zlg的dll放到C盘中, 调用ZCAN_SetValue会修改devices_property目录下面的xml文件,
			* 放在C盘如果不以管理员权限运行,会导致修改xml文件,然后返回失败.
			*/
			//控制器标准类型ISO或非ISO
			sprintf_s(path, "%d/canfd_standard", i);
			sprintf_s(value, "%d", 0);
			if (ZCAN_SetValue(m_deviceHandle, path, value) != STATUS_OK) {
				success = false;
				setLastError("设置CAN卡设备%d,通道%d通讯标准失败", device.deviceIndex, i);
				break;
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

			//设置仲裁域波特率
			sprintf_s(path, "%d/canfd_abit_baud_rate", i);
			sprintf_s(value, "%d", baudrate);
			if (ZCAN_SetValue(m_deviceHandle, path, value) != STATUS_OK) {
				success = false;
				setLastError("设置CAN卡设备%d,通道%d仲裁波特率失败", device.deviceIndex, i);
				break;
			}

			switch (translateDataBaud(device.dataBaud[i]))
			{
			case DB_5Mbps:
				baudrate = 5000000;
				break;
			case DB_4Mbps:
				baudrate = 4000000;
				break;
			case DB_2Mbps:
				baudrate = 2000000;
				break;
			case DB_1Mbps:
				baudrate = 1000000;
				break;
			case DB_800Kbps:
				baudrate = 800000;
				break;
			case DB_500Kbps:
				baudrate = 500000;
				break;
			case DB_250Kbps:
				baudrate = 250000;
				break;
			case DB_125Kbps:
				baudrate = 125000;
				break;
			case DB_100Kbps:
				baudrate = 100000;
				break;
			default:
				baudrate = 2000000;
				break;
			}

			//设置数据域波特率
			sprintf_s(path, "%d/canfd_dbit_baud_rate", i);
			sprintf_s(value, "%d", baudrate);
			if (ZCAN_SetValue(m_deviceHandle, path, value) != STATUS_OK) {
				success = false;
				setLastError("设置CAN卡设备%d,通道%d数据波特率失败", device.deviceIndex, i);
				break;
			}

			ZCAN_CHANNEL_INIT_CONFIG config = { 0 };
			config.can_type = TYPE_CANFD;
			config.canfd.mode = 0;
			config.canfd.acc_code = 0;
			config.canfd.acc_mask = 0xffffffff;
			config.canfd.brp = 0;
			config.canfd.filter = 1;

			m_channelHandle[i] = ZCAN_InitCAN(m_deviceHandle, i, &config);
			if (m_channelHandle[i] == INVALID_CHANNEL_HANDLE) {
				success = false;
				setLastError("初始化CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

			//设置终端电阻使能
			sprintf_s(path, "%d/initenal_resistance", i);
			sprintf_s(value, "%d", 1);
			if (ZCAN_SetValue(m_deviceHandle, path, value) != STATUS_OK) {
				success = false;
				setLastError("设置CAN卡设备%d,通道%d电阻使能失败", device.deviceIndex, i);
				break;
			}

			if (ZCAN_StartCAN(m_channelHandle[i]) != STATUS_OK) {
				success = false;
				setLastError("开启CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

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

bool can::ZlgUsbCanFd::reopen()
{
	close();
	return open(m_canDevice);
}

bool can::ZlgUsbCanFd::close()
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

bool can::ZlgUsbCanFd::reset()
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

void can::ZlgUsbCanFd::clearBuffer(int channel)
{
	__super::clearBuffer(channel);
	if (channel < m_deviceChannelCount && m_channelHandle[channel]) {
		ZCAN_ClearBuffer(m_channelHandle[channel]);
	}
}

bool can::ZlgUsbCanFd::send(const can::Msg* msg, size_t size, int channel)
{
	bool result = false;
	do
	{
		auto count = getProtoCount(msg, size);
		size = count.can;
		if (size) {
			std::unique_ptr<ZCAN_Transmit_Data[]> data(new ZCAN_Transmit_Data[size]);
			memset(data.get(), 0, sizeof(ZCAN_Transmit_Data) * size);
			for (size_t i = 0; i < size; ++i) {
				if (msg[i].protoType != PT_CAN) {
					continue;
				}
				data[i].frame.can_id = MAKE_CAN_ID(static_cast<canid_t>(msg[i].id), m_canDevice.isExpandFrame ? 1 : 0, 0, 0);
				data[i].frame.can_dlc = getDlc(&msg[i]);
				memcpy(data[i].frame.data, msg[i].data, getDlc(&msg[i]));
				data[i].transmit_type = 0;
				const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
				const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
				const_cast<can::Msg*>(&msg[i])->channelIndex = channel;
			}
			m_mutex.send.lock();
			auto temp = ZCAN_Transmit(m_channelHandle[channel], data.get(), size);
			m_mutex.send.unlock();
			if (temp != size) {
				processMsg("F", msg, size, channel);
				break;
			}
			processMsg("S", msg, size, channel);
		}

		size = count.canfd;
		if (size) {
			std::unique_ptr<ZCAN_TransmitFD_Data[]> data(new ZCAN_TransmitFD_Data[size]);
			memset(data.get(), 0, sizeof(ZCAN_TransmitFD_Data) * size);
			for (size_t i = 0; i < size; ++i) {
				if (msg[i].protoType != PT_CANFD) {
					continue;
				}
				data[i].frame.can_id = MAKE_CAN_ID(static_cast<canid_t>(msg[i].id), m_canDevice.isExpandFrame ? 1 : 0, 0, 0);
				data[i].frame.len = getDlc(&msg[i]);
				memcpy(data[i].frame.data, msg[i].data, getDlc(&msg[i]));
				data[i].frame.flags = CANFD_BRS;
				data[i].transmit_type = 0;
				const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
				const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
				const_cast<can::Msg*>(&msg[i])->channelIndex = channel;
			}
			m_mutex.send.lock();
			auto temp = ZCAN_TransmitFD(m_channelHandle[channel], data.get(), size);
			m_mutex.send.unlock();
			if (temp != size) {
				processMsg("F", msg, size, channel);
				break;
			}
			processMsg("S", msg, size, channel);
		}

		result = true;
	} while (false);
	return result;
}

size_t can::ZlgUsbCanFd::recv(can::Msg* msg, size_t size, int channel, size_t timeout)
{
	size_t offset = 0;
	do
	{
		if (ZCAN_GetReceiveNum(m_channelHandle[channel], TYPE_CAN)) {
			std::unique_ptr<ZCAN_Receive_Data[]> data(new ZCAN_Receive_Data[size]);
			memset(data.get(), 0, sizeof(ZCAN_Receive_Data) * size);
			m_mutex.recv.lock();
			auto temp = ZCAN_Receive(m_channelHandle[channel], data.get(), size, timeout);
			m_mutex.recv.unlock();

			for (size_t i = 0; i < temp; ++i) {
				msg[i].id = GET_ID(data[i].frame.can_id);
				msg[i].dlc = data[i].frame.can_dlc;
				memcpy(msg[i].data, data[i].frame.data, data[i].frame.can_dlc);
				msg[i].protoType = ProtoType::PT_CAN;
				msg[i].expFrame = IS_EFF(data[i].frame.can_id);
				msg[i].remFrame = IS_RTR(data[i].frame.can_id);
				msg[i].timeStamp = static_cast<int>(m_time.recv.getEndTime());
				msg[i].channelIndex = channel;
			}
			processMsg("R", msg, temp, channel);
			offset = temp;
		}

		if (ZCAN_GetReceiveNum(m_channelHandle[channel], TYPE_CANFD)) {
			std::unique_ptr<ZCAN_ReceiveFD_Data[]> data(new ZCAN_ReceiveFD_Data[size]);
			memset(data.get(), 0, sizeof(ZCAN_ReceiveFD_Data) * size);
			m_mutex.recv.lock();
			auto temp = ZCAN_ReceiveFD(m_channelHandle[channel], data.get(), size - offset, timeout);
			m_mutex.recv.unlock();

			for (size_t i = 0; i < temp; ++i) {
				size_t index = i + offset;
				msg[index].id = GET_ID(data[i].frame.can_id);
				msg[index].dlc = data[i].frame.len;
				memcpy(msg[index].data, data[i].frame.data, data[i].frame.len);
				msg[index].protoType = ProtoType::PT_CANFD;
				msg[index].expFrame = IS_EFF(data[i].frame.can_id);
				msg[index].remFrame = IS_RTR(data[i].frame.can_id);
				msg[index].timeStamp = static_cast<int>(m_time.recv.getEndTime());
				msg[index].channelIndex = channel;
			}
			processMsg("R", msg + offset, temp, channel);
			offset += temp;
		}

	} while (false);
	return offset;
}

