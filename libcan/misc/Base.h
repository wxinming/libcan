#pragma once
#include <list>
#include <future>
#include <map>
#include "Buffer.h"
#include "Matrix.hpp"

namespace can {
	//����
	class CAN_DLL_EXPORT Base 
	{
	public:
		//���ͻص�
		using SendProc = std::function<void(can::Msg& msg)>;

		//�¼��ص�
		using EventProc = std::function<void(const can::Msg& msg)>;

		//���Ļص�
		using MsgProc = std::function<void(const char* direction, const can::Msg& msg)>;

		/*
		* @brief ����
		*/
		Base(DeviceType deviceType);

		/*
		* @brief ������
		*/
		virtual ~Base();

		//��������ɾ��
		Base(const Base&) = delete;

		//��ֵ����ɾ��
		Base& operator=(const Base&) = delete;

		/*
		* @brief ����CAN�����㷨
		* @param[in] matrix CAN����
		* @return void
		*/
		void setMatrix(can::Matrix* matrix);

		/*
		* @brief ��ȡCAN�����㷨
		* @return CanMatrix*
		*/
		can::Matrix* getMatrix() const;

		/*
		* @brief ��
		* @param[in] device CAN�豸
		* @return bool
		*/
		virtual bool open(const can::Device& device) = 0;

		/*
		* @brief ���´�
		* @return bool
		*/
		virtual bool reopen() = 0;

		/*
		* @brief �ر�CAN��
		* @return bool
		*/
		virtual bool close() = 0;

		/*
		* @brief ��λ�豸
		* @return bool
		*/
		virtual bool reset();

		/*
		* @brief �Ƿ��
		* @return bool
		*/
		bool isOpen() const;

		/*
		* @brief ���ͱ���(ͬ��)
		* @param[in] msg ����
		* @param[in] size ��С
		* @param[in] channel ͨ��
		* @return bool
		*/
		bool sendMsg(const can::Msg* msg, size_t size, int channel = 0);

		/*
		* @brief ���ձ���
		* @param[out] msg ����
		* @param[in] size ���Ĵ�С
		* @param[in] channel ͨ��
		* @return ����ʵ�ʽ��յ�����
		* @note �ӻ�������ȡ��
		*/
		size_t recvMsg(can::Msg* msg, size_t size, int channel = 0);

		/*
		* @brief ��ӱ���(�첽)
		* @param[in] msg ����
		* @param[in] channel ͨ��
		* @return void
		*/
		void addMsg(const can::Msg& msg, int channel = 0);

		/*
		* @brief ��ӱ���(�첽)
		* @param[in] id ����ID
		* @param[in] proc ���ʹ���[lambda]
		* @param[in] period ��������
		* @param[in] type ��������
		* @param[in] count ���ʹ���
		* @param[in] interval ���ͼ��
		* @param[in] channel ͨ��
		* @return void
		*/
		void addMsg(int id, SendProc proc, int period, SendType type = SendType::ST_CYCLE, int count = 0, int interval = 0, int channel = 0);

		/*
		* @brief ��ӱ���(�첽)
		* @param[in] msg ���ĳ�ʼ���б�
		* @param[in] channel ͨ��
		* @return void
		*/
		void addMsg(const std::initializer_list<can::Msg>& msg, int channel = 0);

		/*
		* @brief ��ӱ���(�첽)
		* @param[in] msg ����
		* @param[in] start ��ʼλ��
		* @param[in] length ���ݳ���
		* @param[in] data ����
		* @param[in] channel ͨ��
		* @return void
		*/
		void addMsg(const can::Msg& msg, int start, int length, uint64_t data, int channel = 0);

		/*
		* @brief ɾ������
		* @param[in] id ����id
		* @param[in] channel ͨ��
		* @return void
		*/
		void deleteMsg(int id, int channel = 0);

		/*
		* @brief ɾ������
		* @param[in] msg ����
		* @param[in] channel ͨ��
		* @return void
		*/
		void deleteMsg(const can::Msg& msg, int channel = 0);

		/*
		* @brief ɾ�����б���
		* @param[in] channel ͨ��
		* @return void
		*/
		void deleteAllMsgs(int channel = 0);

		/*
		* @brief ��ʼ�첽���ͱ���
		* @return void
		*/
		void startAsyncSendMsg();

		/*
		* @brief ֹͣ�첽���ͱ���
		* @return void
		*/
		void stopAsyncSendMsg();

		/*
		* @brief ��ȡ���մ���
		* @return std::string
		*/
		std::string getLastError() const;

		/*
		* @brief ���ù���ID
		* @param[in] filter ��־����ID�б�
		* @return void
		*/
		void setFilterId(const std::list<int>& filter);

		/*
		* @brief ��ȡ����ID
		* @return std::list<int>
		*/
		std::list<int> getFilterId() const;

		/*
		* @brief ���������־
		* @param[in] on �Ƿ����
		* @return void
		* @note ��ӡ��visual studio�������̨��
		*/
		void setOutputLog(bool on);

		/*
		* @brief �Ƿ������־
		* @return bool
		*/
		bool isOutputLog() const;

		/*
		* @brief ���ñ��Ĵ���
		* @param[in] proc lambda���ʽ,���ڴ�����(����/����)������
		* @param[in] channel ͨ������
		* @return void
		*/
		void setMsgProc(MsgProc proc = nullptr, int channel = 0);

		/*
		* @brief ��ȡ���Ĵ���
		* @param[in] channel ͨ������
		* @return MessageProc
		*/
		MsgProc getMsgProc(int channel = 0) const;

		/*
		* @brief ��ʽ������
		* @param[in] direction ����
		* @param[in] msg ����
		* @return std::string
		*/
		std::string fmtMsg(const char* direction, const can::Msg& msg) const;

		/*
		* @brief �Ƿ�֧��CANFD
		* @return bool
		*/
		bool isSupportFd() const;

		/*
		* @brief ��ջ�����
		* @param[in] channel ͨ��
		* @return void
		*/
		virtual void clearBuffer(int channel = 0);

	protected:
		/*
		* @brief ���Ͷ�֡����
		* @param[in] msg can::Msg�ṹ��
		* @param[in] size ���ʹ�С
		* @param[in] channel ͨ������
		* @return bool 
		*/
		virtual bool send(const can::Msg* msg, size_t size, int channel = 0) = 0;

		/*
		* @brief ���ն�֡����
		* @param[out] msg can::Msg�ṹ��
		* @param[in] size can::Msg�����С
		* @param[in] channel ͨ������
		* @param[in] timeout ��ʱʱ��ms
		* @return size_t 
		*/
		virtual size_t recv(can::Msg* msg, size_t size, int channel = 0, size_t timeout = 10) = 0;

	protected:
		/*
		* @brief �����ٲ�������
		* @param[in] baud ������
		* @return ArbiBaud
		*/
		ArbiBaud translateArbiBaud(int baud) const;

		/*
		* @brief ��������������
		* @param[in] baud ������
		* @return DataBaud
		*/
		DataBaud translateDataBaud(int baud) const;

		/*
		* @brief ������
		* @param[in] type ��������
		* @param[in] msg can::Msg�ṹ��
		* @param[in] size can::Msg�Ĵ�С
		* @param[in] channel ͨ������
		* @return void
		*/
		void processMsg(const char* type, const can::Msg* msg, size_t size, int channel);

		/*
		* @brief ��ʽ������
		* @param[in] type ����[S:SEND,R:RECEIVE,F:FAILED]
		* @param[in] msg can::Msg�ṹ��
		* @param[out] text ��Ҫ��ʽ���Ļ�����
		* @param[in] size ��ʽ����������С
		* @return void
		*/
		void formatMsg(const char* type, const can::Msg& msg, char* text, size_t size) const;

		/*
		* @brief �������
		* @param[in] type ����[S:SEND,R:RECEIVE,F:FAILED]
		* @param[in] msg can::Msg�ṹ��
		* @return void
		*/
		void outputMsg(const char* type, const can::Msg& msg) const;

		/*
		* @brief ��ȡ���ݳ��ȴ���,DLC[data length code]
		* @param[in] msg can::Msg�ṹ��
		* @return ʵ�ʳ���
		*/
		int getDlc(const can::Msg* msg) const;

		/*
		* @brief �������մ���
		* @param[in] fmt ��ʽ���ַ���
		* @param[in] ... �ɱ����
		* @return void
		*/
		void setLastError(const char* fmt, ...);

		/*
		* @brief ��ȡЭ������
		* @param[in] msg ����
		* @param[in] size ��С
		* @return ProtCount
		*/
		ProtoCount getProtoCount(const can::Msg* msg, size_t size) const;

		/*
		* @brief �ر�����
		* @param[in] channel ͨ��
		* @return void
		*/
		void closeLock(int channel);

		/*
		* @brief �رս���
		* @param[in] channel ͨ��
		* @return void
		*/
		void closeUnlock(int channel);

	private:
		/*
		* @brief ���ͱ����߳�
		* @param[in] channel ͨ��
		* @return void
		*/
		void onSendMsg(int channel);

		/*
		* @brief ���ձ����߳�
		* @param[in] channel ͨ��
		* @return void
		*/
		void onRecvMsg(int channel);

	protected:
		//�豸����
		DeviceType m_deviceType;

		//�豸ͨ����
		int m_deviceChannelCount = 0;

		//�Ƿ��
		bool m_open = false;

		//�豸
		can::Device m_canDevice;

		//ʱ��
		can::Time m_time;

		//������
		can::Mutex m_mutex;

		//֧��CANFD(flexible data-rate)
		bool m_supportFd = false;

	private:
		//�Ƿ��˳�
		bool m_quit = false;

		//�Ƿ������־
		bool m_outputLog = false;

		//�Ƿ��첽���ͱ���
		bool m_asyncSendMsg = false;

		//CAN�����㷨
		can::Matrix* m_matrix = nullptr;

		//�����б�
		can::Msg* m_msgs[CAN_MAX_CHANNEL_COUNT] = { nullptr };
		
		//���ı����б�
		can::Msg* m_msgsBackup[CAN_MAX_CHANNEL_COUNT] = { nullptr };

		//����ID
		std::list<int> m_filterId;

		//���մ���
		std::string m_lastError;

		//����
		can::Future m_future;

		//CANͨ��
		can::Channel m_canChannel[CAN_MAX_CHANNEL_COUNT];

		//�ܻ��������,����ͳ��new�˶�����,�����жϵ�ǰΪ�ڼ����豸
		static int s_totalBaseCounter;

		//��ǰ������
		int m_currentBaseId = 0;
	};
}
