#include "libcan.h"
#include "device/NullCan.h"
#include "device/ZlgUsbCan.h"
#include "device/ZlgUsbCanFd.h"
#include "device/ZlgNetCanFd.h"
#include "device/GcUsbCanFd.h"

std::shared_ptr<can::Base> can::autoReleaseNew(can::DeviceType type)
{
	std::shared_ptr<can::Base> base;
	switch (type)
	{
	case can::DeviceType::NULL_CAN:
		base = std::make_shared<NullCan>(type);
		break;
	case can::DeviceType::ZLG_USBCAN1:
	case can::DeviceType::ZLG_USBCAN2:
		base = std::make_shared<ZlgUsbCan>(type);
		break;
	case can::DeviceType::ZLG_USBCANFDMINI:
	case can::DeviceType::ZLG_USBCANFD100U:
	case can::DeviceType::ZLG_USBCANFD200U:
	case can::DeviceType::ZLG_USBCANFD400U:
	case can::DeviceType::ZLG_USBCANFD800U:
		base = std::make_shared<ZlgUsbCanFd>(type);
		break;
	case can::DeviceType::ZLG_NETCANFD200U:
	case can::DeviceType::ZLG_NETCANFD400U:
	case can::DeviceType::ZLG_NETCANFD800U:
		base = std::make_shared<ZlgNetCanFd>(type);
		break;
	case can::DeviceType::GC_USBCANFD:
		base = std::make_shared<GcUsbCanFd>(type);
		break;
	default:
		break;
	}

	return base;
}

std::vector<std::string> can::getSupportDeviceNames()
{
	return 
	{ 
		"NULL",
		"ZLG-USB-CAN1",
		"ZLG-USB-CAN2",
		"ZLG-USB-CANFDMINI",
		"ZLG-USB-CANFD100U",
		"ZLG-USB-CANFD200U",
		"ZLG-USB-CANFD400U",
		"ZLG-USB-CANFD800U",
		"ZLG-NET-CANFD200U",
		"ZLG-NET-CANFD400U",
		"ZLG-NET-CANFD800U",
		"GC-USB-CANFD"
	};
}
