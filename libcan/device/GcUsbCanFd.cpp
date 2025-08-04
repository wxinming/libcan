#include "GcUsbCanFd.h"

#include "../third/GCANFD/include/ECanFDVci.h"
#ifdef _WIN64
#pragma comment(lib, "libcan/third/GCANFD/lib/x64/ECANFDVCI64.lib")
#else
#pragma comment(lib, "libcan/third/GCANFD/lib/x86/ECANFDVCI.lib")
#endif

can::GcUsbCanFd::GcUsbCanFd(DeviceType deviceType)
	:Base(deviceType)
{
	m_supportFd = true;
}

can::GcUsbCanFd::~GcUsbCanFd()
{
	close();
}

bool can::GcUsbCanFd::open(const can::Device& device)
{
	bool result = false;
	do
	{
		if (OpenDeviceFD(USBCANFD, device.deviceIndex) != CAN_STATUS_OK) {
			setLastError("打开CAN卡设备%d失败", device.deviceIndex);
			break;
		}

		bool success = true;
		for (int i = 0; i < m_deviceChannelCount; ++i) {
			if (!device.enableChannel[i]) {
				continue;
			}

			INIT_CONFIG config = { 0 };
			config.CanReceMode = GLOBAL_STANDARD_AND_EXTENDED_RECEIVE;
			config.CanSendMode = PASSIVE_SEND;

			int baudrate = 0;
			switch (translateArbiBaud(device.arbiBaud[i]))
			{
			case AB_100Kbps:
				baudrate = BAUDRATE_100K;
				break;
			case AB_125Kbps:
				baudrate = BAUDRATE_125K;
				break;
			case AB_200Kbps:
				baudrate = BAUDRATE_200K;
				break;
			case AB_250Kbps:
				baudrate = BAUDRATE_250K;
				break;
			case AB_400Kbps:
				baudrate = BAUDRATE_400K;
				break;
			case AB_500Kbps:
				baudrate = BAUDRATE_500K;
				break;
			case AB_800Kbps:
				baudrate = BAUDRATE_800K;
				break;
			case AB_1Mbps:
				baudrate = BAUDRATE_1M;
				break;
			default:
				baudrate = BAUDRATE_500K;
				break;
			}
			config.NominalBitRateSelect = baudrate;

			switch (translateDataBaud(device.dataBaud[i]))
			{
			case DB_1Mbps:
				baudrate = DATARATE_1M;
				break;
			case DB_2Mbps:
				baudrate = DATARATE_2M;
				break;
			case DB_4Mbps:
				baudrate = DATARATE_4M;
				break;
			case DB_5Mbps:
				baudrate = DATARATE_5M;
				break;
			default:
				baudrate = DATARATE_2M;
				break;
			}
			config.DataBitRateSelect = baudrate;

			if (CAN_STATUS_OK != InitCANFD(USBCANFD, device.deviceIndex, i, &config)) {
				success = false;
				setLastError("初始化CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

			if (CAN_STATUS_OK != StartCANFD(USBCANFD, device.deviceIndex, i)) {
				success = false;
				setLastError("启动CAN卡设备%d,通道%d失败", device.deviceIndex, i);
				break;
			}

			clearBuffer(i);
		}

		if (!success) {
			CloseDeviceFD(USBCANFD, device.deviceIndex);
			break;
		}

		m_canDevice = device;
		m_open = true;
		result = true;
	} while (false);
	return result;
}

bool can::GcUsbCanFd::reopen()
{
	close();
	return open(m_canDevice);
}

bool can::GcUsbCanFd::close()
{
	if (m_open) {
		for (int i = 0; i < m_deviceChannelCount; ++i) {
			closeLock(i);
			m_canDevice.enableChannel[i] = false;
			closeUnlock(i);
		}
		CloseDeviceFD(USBCANFD, m_canDevice.deviceIndex);
		m_open = false;
	}
	return true;
}

bool can::GcUsbCanFd::reset()
{
	bool result = true;
	for (int i = 0; i < m_deviceChannelCount; ++i) {
		if (!m_canDevice.enableChannel[i]) {
			continue;
		}

		if (!ResetCANFD(USBCANFD, m_canDevice.deviceIndex, m_canDevice.enableChannel[i]) ||
			!StartCANFD(USBCANFD, m_canDevice.deviceIndex, m_canDevice.enableChannel[i])) {
			result = false;
		}
	}
	return result;
}

bool can::GcUsbCanFd::send(const can::Msg* msg, size_t size, int channel)
{
	bool result = false;
	do
	{
		std::unique_ptr<CANFD_OBJ[]> data(new CANFD_OBJ[size]);
		memset(data.get(), 0, sizeof(CANFD_OBJ) * size);
		for (size_t i = 0; i < size; ++i) {
			data[i].ID = msg[i].id;
			data[i].DataLen = getDlc(&msg[i]);
			memcpy(data[i].Data, msg[i].data, getDlc(&msg[i]));
			data[i].CanORCanfdType.proto = msg[i].protoType;
			data[i].CanORCanfdType.format = m_canDevice.isExpandFrame;
			data[i].CanORCanfdType.type = DATA_TYPE;
			const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
			const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
			const_cast<can::Msg*>(&msg[i])->channelIndex = channel;
		}

		m_mutex.send.lock();
		auto status = TransmitFD(USBCANFD, m_canDevice.deviceIndex, channel, data.get(), size);
		m_mutex.send.unlock();
		if (status != CAN_STATUS_OK) {
			processMsg("F", msg, size, channel);
			break;
		}
		processMsg("S", msg, size, channel);
		result = true;
	} while (false);
	return result;
}

size_t can::GcUsbCanFd::recv(can::Msg* msg, size_t size, int channel, size_t timeout)
{
	do
	{
		std::unique_ptr<CANFD_OBJ[]> data(new CANFD_OBJ[size]);
		memset(data.get(), 0, sizeof(CANFD_OBJ) * size);
		m_mutex.recv.lock();
		auto status = ReceiveFD(USBCANFD, m_canDevice.deviceIndex, channel, data.get(), reinterpret_cast<DWORD*>(&size));
		m_mutex.recv.unlock();
		if (status != CAN_STATUS_OK) {
			size = 0;
			break;
		}

		for (size_t i = 0; i < size; ++i) {
			msg[i].id = data[i].ID;
			msg[i].dlc = data[i].DataLen;
			memcpy(msg[i].data, data[i].Data, data[i].DataLen);
			msg[i].protoType = static_cast<ProtoType>(data[i].CanORCanfdType.proto);
			msg[i].expFrame = static_cast<bool>(data[i].CanORCanfdType.format);
			msg[i].remFrame = static_cast<bool>(data[i].CanORCanfdType.type);
			msg[i].timeStamp = static_cast<int>(m_time.recv.getEndTime());
			msg[i].channelIndex = channel;
		}
		processMsg("R", msg, size, channel);
	} while (false);
	return size;
}

