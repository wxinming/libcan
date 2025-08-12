#pragma once
#include "misc/Base.h"

namespace can {
	/*
	* @brief 自动释放new
	* @param[in] type 设备类型
	* @return std::shared_ptr<can::Base>
	*/
	LIBCAN_DLL_EXPORT std::shared_ptr<can::Base> autoReleaseNew(can::DeviceType type);

	/*
	* @brief 获取支持的设备名称
	* @return std::vector<std::string>
	*/
	LIBCAN_DLL_EXPORT std::vector<std::string> getSupportDeviceNames();
}

