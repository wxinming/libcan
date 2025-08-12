#pragma once
#include <functional>
#include <future>
#include <iostream>
#include "Export.h"
#include "Timer.h"

//最大通道数
#define CAN_MAX_CHANNEL_COUNT 8

//最大报文数据大小
#define CAN_MAX_MSG_DATA_SIZE 64

//最大接收缓冲区大小
#define CAN_MAX_RECV_BUFFER_SIZE 128

//最大发送缓冲区大小
#define CAN_MAX_SEND_BUFFER_SIZE 128

//最大队列缓冲区大小
#define CAN_MAX_QUEUE_BUFFER_SIZE 4096

namespace can {
	//设备类型
	enum DeviceType {
		//空用于在没有CAN卡的情况下调试使用
		NULL_CAN,

		//周立功USBCAN
		ZLG_USBCAN1,
		ZLG_USBCAN2,

		//周立功USBCANFD
		ZLG_USBCANFDMINI,
		ZLG_USBCANFD100U,
		ZLG_USBCANFD200U,
		ZLG_USBCANFD400U,
		ZLG_USBCANFD800U,

		//周立功NETCANFD
		ZLG_NETCANFD200U,
		ZLG_NETCANFD400U,
		ZLG_NETCANFD800U,

		//广成USBCANFD
		GC_USBCANFD,
	};

	//协议类型
	enum ProtoType {
		//标准CAN
		CAN,

		//CANFD
		CANFD,
	};

	//仲裁域波特率
	enum ArbiBaud {
		ARBI_1Mbps,
		ARBI_800Kbps,
		ARBI_500Kbps,
		ARBI_400Kbps,
		ARBI_250Kbps,
		ARBI_200Kbps,
		ARBI_125Kbps,
		ARBI_100Kbps,
		ARBI_50Kbps,
		ARBI_0Kbps
	};

	//数据域波特率
	enum DataBaud {
		DATA_5Mbps,
		DATA_4Mbps,
		DATA_2Mbps,
		DATA_1Mbps,
		DATA_800Kbps,
		DATA_500Kbps,
		DATA_250Kbps,
		DATA_125Kbps,
		DATA_100Kbps,
		DATA_0Kbps
	};

	//发送类型
	enum SendType {
		//周期
		CYCLE,

		//事件
		EVENT,

		//周期/事件
		CE,

		//激活(尚未支持)
		IFACTIVE,
	};

	//报文
	struct LIBCAN_DLL_EXPORT Msg {
		/*
		* @brief 构造
		*/
		Msg(int id = 0, int dlc = 8, std::initializer_list<uint8_t> dataList = { 0 }, int sendCycle = 100,
			SendType sendType = SendType::CYCLE, int sendCount = 0, int addInterval = 0,
			std::function<void(Msg& msg)> sendProc = nullptr, int channelIndex = 0,
			ProtoType protType = ProtoType::CAN, bool expFrame = false, bool remFrame = false,
			int timeStamp = 0, bool sendValid = false, int sendTime = 0,
			std::function<void(const Msg& msg)> eventProc = nullptr);

		/*
		* @brief 析构
		*/
		~Msg();

		/*
		* @brief 拷贝构造
		* @param[in] other 其他
		*/
		Msg(const Msg& other);

		/*
		* @brief 赋值构造
		* @param[in] other 其他
		* @return Msg&
		*/
		Msg& operator=(const Msg& other);

		/*
		* @brief 移动构造
		*/
		Msg(Msg&& other) noexcept;

		/*
		* @brief 移动赋值
		* @param[in] other 其他
		* @return Msg&
		*/
		Msg& operator=(Msg&& other) noexcept;

		//CANID
		int id;

		//数据长度编码
		int dlc;

		//数据
		unsigned char* data;

		//发送周期
		int sendCycle;

		//发送类型
		SendType sendType;

		//发送次数
		int sendCount;

		//[第N帧与第N+1帧的间隔]
		int addInterval;

		//发送回调
		std::function<void(Msg& msg)> sendProc;

		//通道索引(代表第几个通道发送/接收)
		int channelIndex;

		//CAN类型
		ProtoType protoType;

		//拓展帧
		bool expFrame;

		//远程帧
		bool remFrame;

		//时间戳
		int timeStamp;

		//发送有效
		bool sendValid;

		//发送时间
		int sendTime;

		//事件回调
		std::function<void(const Msg& msg)> eventProc;

		/*
		* @brief 是否相等
		* @return bool
		*/
		bool equal(const Msg& other) const;

		/*
		* @brief 是否为空
		* @return bool
		*/
		bool empty() const;

		/*
		* @brief 设置数据
		* @return void
		*/
		void setData(const std::initializer_list<uint8_t>& data);

		/*
		* @brief 重载==
		* @param[in] msg 报文
		* @return bool
		*/
		bool operator==(const can::Msg& msg);

		/*
		* @brief 重载==
		* @param[in] msg 报文
		* @return bool
		*/
		bool operator==(const can::Msg& msg) const;

		/*
		* @brief 重载!=
		* @param[in] msg 报文
		* @return bool
		*/
		bool operator!=(const can::Msg& msg);

		/*
		* @brief 重载!=
		* @param[in] msg 报文
		* @return bool
		*/
		bool operator!=(const can::Msg& msg) const;
	};

	//CAN设备
	struct LIBCAN_DLL_EXPORT Device {
		//构造
		Device();

		//析构
		~Device();

		//设备编号
		int deviceIndex;

		//启用通道N,默认启用通道0
		bool enableChannel[CAN_MAX_CHANNEL_COUNT];

		//仲裁域波特率
		int arbiBaud[CAN_MAX_CHANNEL_COUNT];

		//数据域波特率,只有CANFD才会用到
		int dataBaud[CAN_MAX_CHANNEL_COUNT];

		//是否启用拓展帧
		bool isExpandFrame;

		//绑定地址,为网络CAN/CANFD所保留(绑定一个网卡去连接CAN/CANFD设备)
		std::string bindAddress;

		//对端地址,为网络CAN/CANFD所保留
		std::string peerAddress;

		//对端端口,为网络CAN/CANFD所保留
		int peerPort;

		//连接超时(ms),为网络CAN/CANFD所保留
		int connectTimeout;
	};

	class Buffer;

	//CAN通道
	struct LIBCAN_DLL_EXPORT Channel {
		//构造
		Channel();

		//析构
		~Channel();

		//拷贝构造删除
		Channel(const Channel&) = delete;

		//赋值构造删除
		Channel& operator=(const Channel&) = delete;

		//CAN报文缓冲区
		can::Buffer* msgBuffer;

		//报文处理函数(方向, 报文)
		std::function<void(const char*, const can::Msg&)> msgProc;
	};

	//互斥锁
	struct LIBCAN_DLL_EXPORT Mutex {
		std::mutex send;
		std::mutex recv;
		std::mutex proc[CAN_MAX_CHANNEL_COUNT];
		std::mutex opens[CAN_MAX_CHANNEL_COUNT];
		std::mutex openr[CAN_MAX_CHANNEL_COUNT];
	};

	//时间
	struct LIBCAN_DLL_EXPORT Time {
		Timer send;
		Timer recv;
	};

	//期望
	struct LIBCAN_DLL_EXPORT Future {
		std::future<void> send[CAN_MAX_CHANNEL_COUNT];

		//单线程处理可能会有问题,uds接收连续帧时,可能会造成STMin超时,需要多线程对应多通道
		std::future<void> recv[CAN_MAX_CHANNEL_COUNT];
	};

	//协议数量
	struct LIBCAN_DLL_EXPORT ProtoCount {
		size_t can;
		size_t canfd;
	};

	//获取设备通道数
	int getDeviceChannelCount(DeviceType type);
}

LIBCAN_DLL_EXPORT std::ostream& operator<<(std::ostream& os, const can::Msg& msg);

