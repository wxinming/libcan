#pragma once
#include <functional>
#include <future>
#include <iostream>
#include "Export.h"
#include "Timer.h"

//���ͨ����
#define CAN_MAX_CHANNEL_COUNT 8

//��������ݴ�С
#define CAN_MAX_MSG_DATA_SIZE 64

//�����ջ�������С
#define CAN_MAX_RECV_BUFFER_SIZE 128

//����ͻ�������С
#define CAN_MAX_SEND_BUFFER_SIZE 128

//�����л�������С
#define CAN_MAX_QUEUE_BUFFER_SIZE 4096

namespace can {
	//�豸����
	enum DeviceType {
		//��������û��CAN��������µ���ʹ��
		DT_NULL_CAN,

		//������USBCAN
		DT_ZLG_USBCAN1,
		DT_ZLG_USBCAN2,

		//������USBCANFD
		DT_ZLG_USBCANFDMINI,
		DT_ZLG_USBCANFD100U,
		DT_ZLG_USBCANFD200U,
		DT_ZLG_USBCANFD400U,
		DT_ZLG_USBCANFD800U,

		//������NETCANFD
		DT_ZLG_NETCANFD200U,
		DT_ZLG_NETCANFD400U,
		DT_ZLG_NETCANFD800U,

		//���USBCANFD
		DT_GC_USBCANFD,
	};

	//Э������
	enum ProtoType {
		//��׼CAN
		PT_CAN,

		//CANFD
		PT_CANFD,
	};

	//�ٲ�������
	enum ArbiBaud {
		AB_1Mbps,
		AB_800Kbps,
		AB_500Kbps,
		AB_400Kbps,
		AB_250Kbps,
		AB_200Kbps,
		AB_125Kbps,
		AB_100Kbps,
		AB_50Kbps,
		AB_0Kbps
	};

	//����������
	enum DataBaud {
		DB_5Mbps,
		DB_4Mbps,
		DB_2Mbps,
		DB_1Mbps,
		DB_800Kbps,
		DB_500Kbps,
		DB_250Kbps,
		DB_125Kbps,
		DB_100Kbps,
		DB_0Kbps
	};

	//��������
	enum SendType {
		//����
		ST_CYCLE,

		//�¼�
		ST_EVENT,

		//����/�¼�
		ST_CE,

		//����(��δ֧��)
		ST_IFACTIVE,
	};

	//����
	struct CAN_DLL_EXPORT Msg {
		/*
		* @brief ����
		*/
		Msg(int id = 0, int dlc = 8, std::initializer_list<uint8_t> dataList = { 0 }, int sendCycle = 100,
			SendType sendType = SendType::ST_CYCLE, int sendCount = 0, int addInterval = 0,
			std::function<void(Msg& msg)> sendProc = nullptr, int channelIndex = 0,
			ProtoType protType = ProtoType::PT_CAN, bool expFrame = false, bool remFrame = false,
			int timeStamp = 0, bool sendValid = false, int sendTime = 0,
			std::function<void(const Msg& msg)> eventProc = nullptr);

		/*
		* @brief ����
		*/
		~Msg();

		/*
		* @brief ��������
		* @param[in] other ����
		*/
		Msg(const Msg& other);

		/*
		* @brief ��ֵ����
		* @param[in] other ����
		* @return Msg&
		*/
		Msg& operator=(const Msg& other);

		/*
		* @brief �ƶ�����
		*/
		Msg(Msg&& other) noexcept;

		/*
		* @brief �ƶ���ֵ
		* @param[in] other ����
		* @return Msg&
		*/
		Msg& operator=(Msg&& other) noexcept;

		//CANID
		int id;

		//���ݳ��ȱ���
		int dlc;

		//����
		unsigned char* data;

		//��������
		int sendCycle;

		//��������
		SendType sendType;

		//���ʹ���
		int sendCount;

		//[��N֡���N+1֡�ļ��]
		int addInterval;

		//���ͻص�
		std::function<void(Msg& msg)> sendProc;

		//ͨ������(����ڼ���ͨ������/����)
		int channelIndex;

		//CAN����
		ProtoType protoType;

		//��չ֡
		bool expFrame;

		//Զ��֡
		bool remFrame;

		//ʱ���
		int timeStamp;

		//������Ч
		bool sendValid;

		//����ʱ��
		int sendTime;

		//�¼��ص�
		std::function<void(const Msg& msg)> eventProc;

		/*
		* @brief �Ƿ����
		* @return bool
		*/
		bool equal(const Msg& other) const;

		/*
		* @brief �Ƿ�Ϊ��
		* @return bool
		*/
		bool empty() const;

		/*
		* @brief ��������
		* @return void
		*/
		void setData(const std::initializer_list<uint8_t>& data);

		/*
		* @brief ����==
		* @param[in] msg ����
		* @return bool
		*/
		bool operator==(const can::Msg& msg);

		/*
		* @brief ����==
		* @param[in] msg ����
		* @return bool
		*/
		bool operator==(const can::Msg& msg) const;

		/*
		* @brief ����!=
		* @param[in] msg ����
		* @return bool
		*/
		bool operator!=(const can::Msg& msg);

		/*
		* @brief ����!=
		* @param[in] msg ����
		* @return bool
		*/
		bool operator!=(const can::Msg& msg) const;
	};

	//CAN�豸
	struct CAN_DLL_EXPORT Device {
		//����
		Device();

		//����
		~Device();

		//�豸���
		int deviceIndex;

		//����ͨ��N,Ĭ������ͨ��0
		bool enableChannel[CAN_MAX_CHANNEL_COUNT];

		//�ٲ�������
		int arbiBaud[CAN_MAX_CHANNEL_COUNT];

		//����������,ֻ��CANFD�Ż��õ�
		int dataBaud[CAN_MAX_CHANNEL_COUNT];

		//�Ƿ�������չ֡
		bool isExpandFrame;

		//�󶨵�ַ,Ϊ����CAN/CANFD������(��һ������ȥ����CAN/CANFD�豸)
		const char* bindAddress;

		//�Զ˵�ַ,Ϊ����CAN/CANFD������
		const char* peerAddress;

		//�Զ˶˿�,Ϊ����CAN/CANFD������
		int peerPort;

		//���ӳ�ʱ(ms),Ϊ����CAN/CANFD������
		int connectTimeout;
	};

	class Buffer;

	//CANͨ��
	struct CAN_DLL_EXPORT Channel {
		//����
		Channel();

		//����
		~Channel();

		//��������ɾ��
		Channel(const Channel&) = delete;

		//��ֵ����ɾ��
		Channel& operator=(const Channel&) = delete;

		//CAN���Ļ�����
		can::Buffer* msgBuffer;

		//���Ĵ�����(����, ����)
		std::function<void(const char*, const can::Msg&)> msgProc;
	};

	//������
	struct CAN_DLL_EXPORT Mutex {
		std::mutex send;
		std::mutex recv;
		std::mutex proc[CAN_MAX_CHANNEL_COUNT];
		std::mutex opens[CAN_MAX_CHANNEL_COUNT];
		std::mutex openr[CAN_MAX_CHANNEL_COUNT];
	};

	//ʱ��
	struct CAN_DLL_EXPORT Time {
		Timer send;
		Timer recv;
	};

	//����
	struct CAN_DLL_EXPORT Future {
		std::future<void> send[CAN_MAX_CHANNEL_COUNT];

		//���̴߳�����ܻ�������,uds��������֡ʱ,���ܻ����STMin��ʱ,��Ҫ���̶߳�Ӧ��ͨ��
		std::future<void> recv[CAN_MAX_CHANNEL_COUNT];
	};

	//Э������
	struct CAN_DLL_EXPORT ProtoCount {
		size_t can;
		size_t canfd;
	};

	//��ȡ�豸ͨ����
	int getDeviceChannelCount(DeviceType type);
}

std::ostream& operator<<(std::ostream& os, const can::Msg& msg);

