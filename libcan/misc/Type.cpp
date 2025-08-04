#include "Type.h"
//static std::atomic<size_t> total;

can::Msg::Msg(int id,
	int dlc,
	std::initializer_list<uint8_t> dataList,
	int sendCycle,
	SendType sendType,
	int sendCount,
	int addInterval,
	std::function<void(Msg& msg)> sendProc,
	int channelIndex,
	ProtoType protoType,
	bool expFrame,
	bool remFrame,
	int timeStamp,
	bool sendValid,
	int sendTime,
	std::function<void(const Msg& msg)> eventProc)
	: id(id), dlc(dlc), sendCycle(sendCycle), sendType(sendType), sendCount(sendCount),
	addInterval(addInterval), sendProc(sendProc), channelIndex(channelIndex),
	protoType(protoType), expFrame(expFrame), remFrame(remFrame), timeStamp(timeStamp),
	sendValid(sendValid), sendTime(sendTime), eventProc(eventProc) {
	data = new unsigned char[CAN_MAX_MSG_DATA_SIZE];
	memset(data, 0, CAN_MAX_MSG_DATA_SIZE);
	size_t size = std::min<size_t>(dataList.size(), CAN_MAX_MSG_DATA_SIZE);
	for (size_t i = 0; i < size; ++i) {
		data[i] = dataList.begin()[i];
	}
	//printf("%s %lu\n", __FUNCTION__, ++total);
}

can::Msg::~Msg()
{
	if (data) {
		delete[] data;
		data = nullptr;
	}
	//printf("%s %lu\n", __FUNCTION__, --total);
}

can::Msg::Msg(const Msg& other)
	:data(nullptr)
{
	id = other.id;
	dlc = other.dlc;
	if (!data) {
		data = new unsigned char[CAN_MAX_MSG_DATA_SIZE];
	}
	memcpy(data, other.data, CAN_MAX_MSG_DATA_SIZE);
	sendCycle = other.sendCycle;
	sendType = other.sendType;
	sendCount = other.sendCount;
	addInterval = other.addInterval;
	sendProc = other.sendProc;
	channelIndex = other.channelIndex;
	protoType = other.protoType;
	expFrame = other.expFrame;
	remFrame = other.remFrame;
	timeStamp = other.timeStamp;
	sendValid = other.sendValid;
	sendTime = other.sendTime;
	eventProc = other.eventProc;
	//printf("%s %lu\n", __FUNCTION__, ++total);
}

can::Msg& can::Msg::operator=(const Msg& other)
{
	if (this == &other) {
		return *this;
	}
	id = other.id;
	dlc = other.dlc;
	if (!data) {
		data = new unsigned char[CAN_MAX_MSG_DATA_SIZE];
	}
	memcpy(data, other.data, CAN_MAX_MSG_DATA_SIZE);
	sendCycle = other.sendCycle;
	sendType = other.sendType;
	sendCount = other.sendCount;
	addInterval = other.addInterval;
	sendProc = other.sendProc;
	channelIndex = other.channelIndex;
	protoType = other.protoType;
	expFrame = other.expFrame;
	remFrame = other.remFrame;
	timeStamp = other.timeStamp;
	sendValid = other.sendValid;
	sendTime = other.sendTime;
	eventProc = other.eventProc;
	//printf("%s %lu\n", __FUNCTION__, ++total);
	return *this;
}

can::Msg::Msg(Msg&& other) noexcept
	:data(nullptr)
{
	id = other.id;
	other.id = 0;
	dlc = other.dlc;
	other.dlc = 0;
	data = other.data;
	other.data = nullptr;
	sendCycle = other.sendCycle;
	sendType = other.sendType;
	sendCount = other.sendCount;
	addInterval = other.addInterval;
	sendProc = other.sendProc;
	channelIndex = other.channelIndex;
	other.channelIndex = 0;
	protoType = other.protoType;
	expFrame = other.expFrame;
	remFrame = other.remFrame;
	timeStamp = other.timeStamp;
	sendValid = other.sendValid;
	sendTime = other.sendTime;
	eventProc = other.eventProc;
	//printf("%s %lu\n", __FUNCTION__, ++total);
}

can::Msg& can::Msg::operator=(Msg&& other) noexcept
{
	if (this == &other) {
		return *this;
	}
	id = other.id;
	other.id = 0;
	dlc = other.dlc;
	other.dlc = 0;
	delete[] data;
	data = other.data;
	other.data = nullptr;
	sendCycle = other.sendCycle;
	sendType = other.sendType;
	sendCount = other.sendCount;
	addInterval = other.addInterval;
	sendProc = other.sendProc;
	channelIndex = other.channelIndex;
	other.channelIndex = 0;
	protoType = other.protoType;
	expFrame = other.expFrame;
	remFrame = other.remFrame;
	timeStamp = other.timeStamp;
	sendValid = other.sendValid;
	sendTime = other.sendTime;
	eventProc = other.eventProc;
	//printf("%s %lu\n", __FUNCTION__, ++total);
	return *this;
}

bool can::Msg::equal(const Msg& other) const
{
	return (id == other.id) && (!memcmp(data, other.data, CAN_MAX_MSG_DATA_SIZE)) /*&& (channelIndex == other.channelIndex)*/;
}

bool can::Msg::empty() const
{
	char temp[CAN_MAX_MSG_DATA_SIZE] = { 0 };
	return (!id) && (!memcmp(data, temp, sizeof(data)));
}

void can::Msg::setData(const std::initializer_list<uint8_t>& data)
{
	memset(this->data, 0, CAN_MAX_MSG_DATA_SIZE);
	for (size_t i = 0; i < std::min<size_t>(CAN_MAX_MSG_DATA_SIZE, data.size()); ++i) {
		this->data[i] = data.begin()[i];
	}
}

bool can::Msg::operator==(const can::Msg& msg)
{
	return equal(msg);
}

bool can::Msg::operator==(const can::Msg& msg) const
{
	return equal(msg);
}

bool can::Msg::operator!=(const can::Msg& msg)
{
	return !equal(msg);
}

bool can::Msg::operator!=(const can::Msg& msg) const
{
	return !equal(msg);
}

can::Device::Device()
{
	deviceIndex = 0;
	memset(enableChannel, 0x00, sizeof(enableChannel));
	enableChannel[0] = true;
	for (int i = 0; i < CAN_MAX_CHANNEL_COUNT; ++i) {
		arbiBaud[i] = 500;
		dataBaud[i] = 2000;
	}
	isExpandFrame = false;
	bindAddress = nullptr;
	peerAddress = nullptr;
	peerPort = 8000;
	connectTimeout = 100;
}

can::Device::~Device()
{

}

#include "Buffer.h"
can::Channel::Channel()
{
	msgBuffer = new can::Buffer(CAN_MAX_QUEUE_BUFFER_SIZE);
	msgProc = nullptr;
}

can::Channel::~Channel()
{
	if (msgBuffer) {
		delete msgBuffer;
		msgBuffer = nullptr;
	}
}

std::ostream& operator<<(std::ostream& os, const can::Msg& msg)
{
	std::string data;
	char str[32] = { 0 };
	for (int i = 0; i < msg.dlc; ++i) {
		if (i != msg.dlc - 1) {
			sprintf_s(str, "%02x:", msg.data[i]);
		}
		else {
			sprintf_s(str, "%02x", msg.data[i]);
		}
		data.append(str);
	}

	char buffer[4096] = { 0 };
	sprintf_s(buffer,
		"[%d],"
		"[%s],"
		"[0x%x],"
		"[%s]\n",
		msg.channelIndex,
		msg.protoType == can::ProtoType::PT_CAN ? "CAN" : "CANFD",
		msg.id,
		data.c_str()
	);

	os << buffer;
	return os;
}

int can::getDeviceChannelCount(DeviceType type)
{
	int result = 0;
	switch (type)
	{
	case can::DT_NULL_CAN:
		result = 1;
		break;
	case can::DT_ZLG_USBCAN1:
		result = 1;
		break;
	case can::DT_ZLG_USBCAN2:
		result = 2;
		break;
	case can::DT_ZLG_USBCANFDMINI:
		result = 1;
		break;
	case can::DT_ZLG_USBCANFD100U:
		result = 1;
		break;
	case can::DT_ZLG_USBCANFD200U:
		result = 2;
		break;
	case can::DT_ZLG_USBCANFD400U:
		result = 4;
		break;
	case can::DT_ZLG_USBCANFD800U:
		result = 8;
		break;
	case can::DT_ZLG_NETCANFD200U:
		result = 2;
		break;
	case can::DT_ZLG_NETCANFD400U:
		result = 4;
		break;
	case can::DT_ZLG_NETCANFD800U:
		result = 8;
		break;
	case can::DT_GC_USBCANFD:
		result = 2;
		break;
	default:
		result = 1;
		break;
	}
	return result;
}
