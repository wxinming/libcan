#pragma once
#include "misc/Base.h"

namespace can {
	/*
	* @brief �Զ��ͷ�new
	* @param[in] type �豸����
	* @return std::shared_ptr<can::Base>
	*/
	CAN_DLL_EXPORT std::shared_ptr<can::Base> autoReleaseNew(can::DeviceType type);

	/*
	* @brief ��ȡ֧�ֵ��豸����
	* @return std::vector<std::string>
	*/
	CAN_DLL_EXPORT std::vector<std::string> getSupportDeviceType();
}

