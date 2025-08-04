#include "ZlgNetCanFd.h"
#include "../third/zlgcan_usb/include/zlgcan.h"
#include "../third/zlgcan_net/include/PropertyNameDef.h"
#include "../third/zlgcan_net/include/ZNetConfig.h"

#ifdef _WIN64
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x64/zlgcan.lib")
#pragma comment(lib, "libcan/third/zlgcan_net/lib/x64/znetconfig.lib")
#else
#pragma comment(lib, "libcan/third/zlgcan_usb/lib/x86/zlgcan.lib")
#pragma comment(lib, "libcan/third/zlgcan_net/lib/x86/znetconfig.lib")
#endif

#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

can::ZlgNetCanFd::ZlgNetCanFd(DeviceType deviceType)
	:Base(deviceType)
{
	m_supportFd = true;
}

can::ZlgNetCanFd::~ZlgNetCanFd()
{
	close();
}

bool can::ZlgNetCanFd::open(const can::Device& device)
{
	bool result = false, changed = false;
	do
	{
		sockaddr_in sa;
		if (!device.peerAddress || inet_pton(AF_INET, device.peerAddress, &sa.sin_addr) != 1) {
			setLastError("对端地址无效");
			break;
		}

		std::string bindAddress;
		if (device.bindAddress) {
			bindAddress = device.bindAddress;
			if (inet_pton(AF_INET, bindAddress.c_str(), &sa.sin_addr) != 1) {
				setLastError("绑定地址无效");
				break;
			}

			auto ret = ZN_ExecCmd(ZN_CMD_BIND_IP, INVALID_DEV_HANDLE, (void*)bindAddress.c_str());
			if (ret != ZN_SUCCESS) {
				setLastError("绑定地址失败,%s", errorCodeString(ret));
				break;
			}
		}
		else {
			auto find = false;
			auto addresses = getLocalHostAddresses();
			std::string peerAddress = device.peerAddress;
			auto npos0 = peerAddress.rfind('.');
			if (npos0 != std::string::npos) {
				auto segment0 = peerAddress.substr(0, npos0);
				for (auto& x : addresses) {
					auto npos1 = x.rfind('.');
					if (npos1 == std::string::npos) {
						continue;
					}

					auto segment1 = x.substr(0, npos1);
					if (segment0 == segment1) {
						bindAddress = x;
						find = true;
						break;
					}
				}
			}

			if (find) {
				auto ret = ZN_ExecCmd(ZN_CMD_BIND_IP, INVALID_DEV_HANDLE, (void*)bindAddress.c_str());
				if (ret != ZN_SUCCESS) {
					setLastError("绑定地址失败,%s", errorCodeString(ret));
					break;
				}
			}
		}

		auto ret = ZN_SearchDevice(device.connectTimeout, device.peerAddress);
		if (ret != ZN_SUCCESS) {
			setLastError("搜索设备失败,%s", errorCodeString(ret));
			break;
		}

		auto count = ZN_GetDeviceCount();
		if (count == 0) {
			setLastError("无可用设备");
			break;
		}

		ZN_PROPERTY getproperty = { 0 }, setproperty = { 0 };
		bool error = false, find = false;
		for (decltype(count) i = 0; i < count; ++i) {
			auto deviceHandle = ZN_GetDeviceAt(i);
			if (deviceHandle == INVALID_DEV_HANDLE) {
				error = true;
				setLastError("CAN卡设备%d句柄无效", i);
				break;
			}

			ret = ZN_LoadInfo(deviceHandle);
			if (ret != ZN_SUCCESS) {
				error = true;
				setLastError("加载CAN卡设备%d信息失败,%s", i, errorCodeString(ret));
				break;
			}

			ret = ZN_GetProperty(deviceHandle, NAME_CANFDNET_NIC_GENNIC_IP, &getproperty);
			if (ret != ZN_SUCCESS) {
				error = true;
				setLastError("获取CAN卡设备%d地址失败,%s", i, errorCodeString(ret));
				break;
			}

			if (!strcmp(getproperty.value, device.peerAddress)) {
				m_deviceHandle = deviceHandle;
				find = true;
				break;
			}
		}

		if (error) {
			break;
		}

		if (!find) {
			setLastError("无可用设备,ip地址匹配不成功");
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
			sprintf_s(getproperty.name, NAME_CANFDNET_CAN_N_NBAUD, i + 1);
			ret = ZN_GetProperty(m_deviceHandle, getproperty.name, &getproperty);
			if (ret != ZN_SUCCESS) {
				success = false;
				setLastError("获取CAN卡设备%d,通道%d仲裁域波特率失败,%s",
					device.deviceIndex, i, errorCodeString(ret));
				break;
			}

			if (atoi(getproperty.value) != baudrate) {
				changed = true;
				sprintf_s(setproperty.name, NAME_CANFDNET_CAN_N_NBAUD, i + 1);
				sprintf_s(setproperty.value, "%d", baudrate);
				ret = ZN_SetProperty(m_deviceHandle, &setproperty);
				if (ret != ZN_SUCCESS) {
					success = false;
					setLastError("设置CAN卡设备%d,通道%d仲裁域波特率失败,%s",
						device.deviceIndex, i, errorCodeString(ret));
					break;
				}
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
			sprintf_s(getproperty.name, NAME_CANFDNET_CAN_N_DBAUD, i + 1);
			ret = ZN_GetProperty(m_deviceHandle, getproperty.name, &getproperty);
			if (ret != ZN_SUCCESS) {
				success = false;
				setLastError("获取CAN卡设备%d,通道%d数据域波特率失败,%s",
					device.deviceIndex, i, errorCodeString(ret));
				break;
			}

			if (atoi(getproperty.value) != baudrate) {
				changed = true;
				sprintf_s(setproperty.name, NAME_CANFDNET_CAN_N_DBAUD, i + 1);
				sprintf_s(setproperty.value, "%d", baudrate);
				ret = ZN_SetProperty(m_deviceHandle, &setproperty);
				if (ret != ZN_SUCCESS) {
					success = false;
					setLastError("设置CAN卡设备%d,通道%d数据域波特率失败,%s",
						device.deviceIndex, i, errorCodeString(ret));
					break;
				}
			}
		}

		if (!success) {
			ZN_ClearDevice();
			break;
		}

		if (changed) {
			ret = ZN_SubmitInfo(m_deviceHandle, "88888");
			if (ret != ZN_SUCCESS) {
				success = false;
				setLastError("CAN卡设备%d,提交修改信息失败,%s",
					device.deviceIndex, errorCodeString(ret));
				ZN_ClearDevice();
				break;
			}
		}

		ZN_ClearDevice();

		m_deviceHandle = ZCAN_OpenDevice(ZCAN_CANFDNET_400U_TCP, device.deviceIndex, 0);
		if (m_deviceHandle == INVALID_DEVICE_HANDLE) {
			success = false;
			setLastError("打开CAN卡设备%d失败", device.deviceIndex);
			break;
		}

		for (int i = 0; i < m_deviceChannelCount; ++i) {
			if (!device.enableChannel[i]) {
				continue;
			}

			char path[64] = { 0 }, value[64] = { 0 };
			sprintf_s(path, "%d/work_mode", i);
			sprintf_s(value, "%d", 0);
			ZCAN_SetValue(m_deviceHandle, path, value);

			sprintf_s(path, "%d/ip", i);
			sprintf_s(value, "%s", device.peerAddress);
			ZCAN_SetValue(m_deviceHandle, path, value);


			sprintf_s(path, "%d/work_port", i);
			sprintf_s(value, "%d", device.peerPort);
			ZCAN_SetValue(m_deviceHandle, path, value);

			ZCAN_CHANNEL_INIT_CONFIG config = { 0 };
			m_channelHandle[i] = ZCAN_InitCAN(m_deviceHandle, i, &config);
			if (m_channelHandle[i] == INVALID_CHANNEL_HANDLE) {
				success = false;
				setLastError("初始化CAN卡%d,通道%d失败", device.deviceIndex, i);
				ZCAN_CloseDevice(m_deviceHandle);
				break;
			}

			if (ZCAN_StartCAN(m_channelHandle[i]) != STATUS_OK) {
				success = false;
				setLastError("开启CAN卡%d,通道%d失败", device.deviceIndex, i);
				ZCAN_CloseDevice(m_deviceHandle);
				break;
			}

			clearBuffer(i);
		}

		if (!success) {
			break;
		}
		m_canDevice = device;
		m_open = true;
		result = true;
	} while (false);
	return result;
}

bool can::ZlgNetCanFd::reopen()
{
	close();
	return open(m_canDevice);
}

bool can::ZlgNetCanFd::close()
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

bool can::ZlgNetCanFd::reset()
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

void can::ZlgNetCanFd::clearBuffer(int channel)
{
	__super::clearBuffer(channel);
	if (channel < m_deviceChannelCount && m_channelHandle[channel]) {
		ZCAN_ClearBuffer(m_channelHandle[channel]);
	}
}

bool can::ZlgNetCanFd::send(const can::Msg* msg, size_t size, int channel)
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
				const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
				const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
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
				const_cast<can::Msg*>(&msg[i])->timeStamp = static_cast<int>(m_time.send.getEndTime());
				const_cast<can::Msg*>(&msg[i])->expFrame = m_canDevice.isExpandFrame;
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


size_t can::ZlgNetCanFd::recv(can::Msg* msg, size_t size, int channel, size_t timeout)
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
				msg[i].protoType = can::PT_CAN;
				msg[i].id = GET_ID(data[i].frame.can_id);
				msg[i].dlc = data[i].frame.can_dlc;
				memcpy(msg[i].data, data[i].frame.data, data[i].frame.can_dlc);
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
				msg[index].protoType = can::PT_CANFD;
				msg[index].id = GET_ID(data[i].frame.can_id);
				msg[index].dlc = data[i].frame.len;
				memcpy(msg[index].data, data[i].frame.data, data[i].frame.len);
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

const char* can::ZlgNetCanFd::errorCodeString(int code) const
{
	switch (code)
	{
	case ZN_SUCCESS: return "执行成功";
	case ZN_ERR_GENERAL: return "执行失败";
	case ZN_ERR_PARAM: return "参数传入错误";
	case ZN_ERR_COMMUNICATE: return "通讯错误";
	case ZN_ERR_NOT_CONNECT: return "未建立连接";
	case ZN_ERR_DEV_RESPONSE: return "设备响应错误";
	case ZN_ERR_DEV_TYPE_NOT_SUPPORT: return "设备类型不支持";
	case ZN_ERR_DEV_NOT_LOAD_INFO: return "设备属性未加载";
	case ZN_ERR_PROPERTY_NOT_SUPPORT: return "属性项不支持";
	case ZN_ERR_PASSWORD_CHECK: return "密码校验失败";
	case ZN_ERR_PARSE_DEV_DATA: return "设备数据解析错误";
	case ZN_ERR_OPERATE_NOT_SUPPORT: return "操作命令不支持";
	case ZN_ERR_UPGRADE_FILE_CHECK: return "升级文件校验失败";
	}
	return "未知错误";
}

std::vector<std::string> can::ZlgNetCanFd::getLocalHostAddresses() const
{
	std::vector<std::string> ips;
	ULONG outBufLen = 0;
	DWORD dwRetVal = 0;
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	if (GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
		pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
	}

	if (pAddresses) {
		dwRetVal = GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &outBufLen);
		if (dwRetVal == NO_ERROR) {
			PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
			while (pCurrAddresses != NULL) {
				if (pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD ||
					pCurrAddresses->IfType == IF_TYPE_IEEE80211) {
					std::string adapterName = pCurrAddresses->AdapterName;
					std::wstring friendlyName = pCurrAddresses->FriendlyName;

					if (adapterName.find("VMware") != std::string::npos ||
						adapterName.find("VirtualBox") != std::string::npos ||
						friendlyName.find(L"VMware") != std::wstring::npos ||
						friendlyName.find(L"VirtualBox") != std::wstring::npos) {
						pCurrAddresses = pCurrAddresses->Next;
						continue;
					}

					for (PIP_ADAPTER_UNICAST_ADDRESS pUnicast = pCurrAddresses->FirstUnicastAddress;
						pUnicast != NULL;
						pUnicast = pUnicast->Next) {
						struct sockaddr_in* sa_in = (struct sockaddr_in*)pUnicast->Address.lpSockaddr;
						std::string addr = inet_ntoa(sa_in->sin_addr);
						if (addr.find("169.254") != std::string::npos) {
							continue;
						}
						ips.push_back(addr);
					}
				}
				pCurrAddresses = pCurrAddresses->Next;
			}
		}
		free(pAddresses);
	}

	return ips;
}

