#pragma once
#include <list>
#include <future>
#include <map>
#include "Buffer.h"
#include "Matrix.hpp"

namespace can {
	//基类
	class CAN_DLL_EXPORT Base 
	{
	public:
		//发送回调
		using SendProc = std::function<void(can::Msg& msg)>;

		//事件回调
		using EventProc = std::function<void(const can::Msg& msg)>;

		//报文回调
		using MsgProc = std::function<void(const char* direction, const can::Msg& msg)>;

		/*
		* @brief 构造
		*/
		Base(DeviceType deviceType);

		/*
		* @brief 虚析构
		*/
		virtual ~Base();

		//拷贝构造删除
		Base(const Base&) = delete;

		//赋值构造删除
		Base& operator=(const Base&) = delete;

		/*
		* @brief 设置CAN矩阵算法
		* @param[in] matrix CAN矩阵
		* @return void
		*/
		void setMatrix(can::Matrix* matrix);

		/*
		* @brief 获取CAN矩阵算法
		* @return CanMatrix*
		*/
		can::Matrix* getMatrix() const;

		/*
		* @brief 打开
		* @param[in] device CAN设备
		* @return bool
		*/
		virtual bool open(const can::Device& device) = 0;

		/*
		* @brief 重新打开
		* @return bool
		*/
		virtual bool reopen() = 0;

		/*
		* @brief 关闭CAN卡
		* @return bool
		*/
		virtual bool close() = 0;

		/*
		* @brief 复位设备
		* @return bool
		*/
		virtual bool reset();

		/*
		* @brief 是否打开
		* @return bool
		*/
		bool isOpen() const;

		/*
		* @brief 发送报文(同步)
		* @param[in] msg 报文
		* @param[in] size 大小
		* @param[in] channel 通道
		* @return bool
		*/
		bool sendMsg(const can::Msg* msg, size_t size, int channel = 0);

		/*
		* @brief 接收报文
		* @param[out] msg 报文
		* @param[in] size 报文大小
		* @param[in] channel 通道
		* @return 返回实际接收的数量
		* @note 从缓冲区中取出
		*/
		size_t recvMsg(can::Msg* msg, size_t size, int channel = 0);

		/*
		* @brief 添加报文(异步)
		* @param[in] msg 报文
		* @param[in] channel 通道
		* @return void
		*/
		void addMsg(const can::Msg& msg, int channel = 0);

		/*
		* @brief 添加报文(异步)
		* @param[in] id 报文ID
		* @param[in] proc 发送处理[lambda]
		* @param[in] period 发送周期
		* @param[in] type 发送类型
		* @param[in] count 发送次数
		* @param[in] interval 发送间隔
		* @param[in] channel 通道
		* @return void
		*/
		void addMsg(int id, SendProc proc, int period, SendType type = SendType::ST_CYCLE, int count = 0, int interval = 0, int channel = 0);

		/*
		* @brief 添加报文(异步)
		* @param[in] msg 报文初始化列表
		* @param[in] channel 通道
		* @return void
		*/
		void addMsg(const std::initializer_list<can::Msg>& msg, int channel = 0);

		/*
		* @brief 添加报文(异步)
		* @param[in] msg 报文
		* @param[in] start 起始位置
		* @param[in] length 数据长度
		* @param[in] data 数据
		* @param[in] channel 通道
		* @return void
		*/
		void addMsg(const can::Msg& msg, int start, int length, uint64_t data, int channel = 0);

		/*
		* @brief 删除报文
		* @param[in] id 报文id
		* @param[in] channel 通道
		* @return void
		*/
		void deleteMsg(int id, int channel = 0);

		/*
		* @brief 删除报文
		* @param[in] msg 报文
		* @param[in] channel 通道
		* @return void
		*/
		void deleteMsg(const can::Msg& msg, int channel = 0);

		/*
		* @brief 删除所有报文
		* @param[in] channel 通道
		* @return void
		*/
		void deleteAllMsgs(int channel = 0);

		/*
		* @brief 开始异步发送报文
		* @return void
		*/
		void startAsyncSendMsg();

		/*
		* @brief 停止异步发送报文
		* @return void
		*/
		void stopAsyncSendMsg();

		/*
		* @brief 获取最终错误
		* @return std::string
		*/
		std::string getLastError() const;

		/*
		* @brief 设置过滤ID
		* @param[in] filter 日志过滤ID列表
		* @return void
		*/
		void setFilterId(const std::list<int>& filter);

		/*
		* @brief 获取过滤ID
		* @return std::list<int>
		*/
		std::list<int> getFilterId() const;

		/*
		* @brief 设置输出日志
		* @param[in] on 是否调试
		* @return void
		* @note 打印到visual studio输出控制台中
		*/
		void setOutputLog(bool on);

		/*
		* @brief 是否输出日志
		* @return bool
		*/
		bool isOutputLog() const;

		/*
		* @brief 设置报文处理
		* @param[in] proc lambda表达式,用于处理所(发送/接收)的内容
		* @param[in] channel 通道索引
		* @return void
		*/
		void setMsgProc(MsgProc proc = nullptr, int channel = 0);

		/*
		* @brief 获取报文处理
		* @param[in] channel 通道索引
		* @return MessageProc
		*/
		MsgProc getMsgProc(int channel = 0) const;

		/*
		* @brief 格式化报文
		* @param[in] direction 方向
		* @param[in] msg 报文
		* @return std::string
		*/
		std::string fmtMsg(const char* direction, const can::Msg& msg) const;

		/*
		* @brief 是否支持CANFD
		* @return bool
		*/
		bool isSupportFd() const;

		/*
		* @brief 清空缓冲区
		* @param[in] channel 通道
		* @return void
		*/
		virtual void clearBuffer(int channel = 0);

	protected:
		/*
		* @brief 发送多帧报文
		* @param[in] msg can::Msg结构体
		* @param[in] size 发送大小
		* @param[in] channel 通道索引
		* @return bool 
		*/
		virtual bool send(const can::Msg* msg, size_t size, int channel = 0) = 0;

		/*
		* @brief 接收多帧报文
		* @param[out] msg can::Msg结构体
		* @param[in] size can::Msg数组大小
		* @param[in] channel 通道索引
		* @param[in] timeout 超时时间ms
		* @return size_t 
		*/
		virtual size_t recv(can::Msg* msg, size_t size, int channel = 0, size_t timeout = 10) = 0;

	protected:
		/*
		* @brief 翻译仲裁域波特率
		* @param[in] baud 波特率
		* @return ArbiBaud
		*/
		ArbiBaud translateArbiBaud(int baud) const;

		/*
		* @brief 翻译数据域波特率
		* @param[in] baud 波特率
		* @return DataBaud
		*/
		DataBaud translateDataBaud(int baud) const;

		/*
		* @brief 处理报文
		* @param[in] type 发送类型
		* @param[in] msg can::Msg结构体
		* @param[in] size can::Msg的大小
		* @param[in] channel 通道索引
		* @return void
		*/
		void processMsg(const char* type, const can::Msg* msg, size_t size, int channel);

		/*
		* @brief 格式化报文
		* @param[in] type 类型[S:SEND,R:RECEIVE,F:FAILED]
		* @param[in] msg can::Msg结构体
		* @param[out] text 需要格式化的缓冲区
		* @param[in] size 格式化缓冲区大小
		* @return void
		*/
		void formatMsg(const char* type, const can::Msg& msg, char* text, size_t size) const;

		/*
		* @brief 输出报文
		* @param[in] type 类型[S:SEND,R:RECEIVE,F:FAILED]
		* @param[in] msg can::Msg结构体
		* @return void
		*/
		void outputMsg(const char* type, const can::Msg& msg) const;

		/*
		* @brief 获取数据长度代码,DLC[data length code]
		* @param[in] msg can::Msg结构体
		* @return 实际长度
		*/
		int getDlc(const can::Msg* msg) const;

		/*
		* @brief 设置最终错误
		* @param[in] fmt 格式化字符串
		* @param[in] ... 可变参数
		* @return void
		*/
		void setLastError(const char* fmt, ...);

		/*
		* @brief 获取协议数量
		* @param[in] msg 报文
		* @param[in] size 大小
		* @return ProtCount
		*/
		ProtoCount getProtoCount(const can::Msg* msg, size_t size) const;

		/*
		* @brief 关闭上锁
		* @param[in] channel 通道
		* @return void
		*/
		void closeLock(int channel);

		/*
		* @brief 关闭解锁
		* @param[in] channel 通道
		* @return void
		*/
		void closeUnlock(int channel);

	private:
		/*
		* @brief 发送报文线程
		* @param[in] channel 通道
		* @return void
		*/
		void onSendMsg(int channel);

		/*
		* @brief 接收报文线程
		* @param[in] channel 通道
		* @return void
		*/
		void onRecvMsg(int channel);

	protected:
		//设备类型
		DeviceType m_deviceType;

		//设备通道数
		int m_deviceChannelCount = 0;

		//是否打开
		bool m_open = false;

		//设备
		can::Device m_canDevice;

		//时间
		can::Time m_time;

		//互斥锁
		can::Mutex m_mutex;

		//支持CANFD(flexible data-rate)
		bool m_supportFd = false;

	private:
		//是否退出
		bool m_quit = false;

		//是否输出日志
		bool m_outputLog = false;

		//是否异步发送报文
		bool m_asyncSendMsg = false;

		//CAN矩阵算法
		can::Matrix* m_matrix = nullptr;

		//报文列表
		can::Msg* m_msgs[CAN_MAX_CHANNEL_COUNT] = { nullptr };
		
		//报文备份列表
		can::Msg* m_msgsBackup[CAN_MAX_CHANNEL_COUNT] = { nullptr };

		//过滤ID
		std::list<int> m_filterId;

		//最终错误
		std::string m_lastError;

		//期望
		can::Future m_future;

		//CAN通道
		can::Channel m_canChannel[CAN_MAX_CHANNEL_COUNT];

		//总基类计数器,用于统计new了多少类,用于判断当前为第几个设备
		static int s_totalBaseCounter;

		//当前基类编号
		int m_currentBaseId = 0;
	};
}
