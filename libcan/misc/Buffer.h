#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

#include "Type.h"

namespace can {	
#if 0
	/*
	* @brief 缓冲区
	*/
	class CAN_DLL_EXPORT Buffer
	{
	public:
		/*
		* @brief 构造
		* @param[in] size 缓冲区大小
		*/
		Buffer(size_t size = 4096);

		/*
		* @brief 析构
		*/
		~Buffer();

		/*
		* @brief 放入
		* @param[in] msg 保存的报文缓冲区地址
		* @param[in] size 保存的报文缓冲区大小
		* @return void
		*/
		void push(const can::Msg* msg, size_t size);

		/*
		* @brief 弹出
		* @param[out] msg 获取的报文缓冲区地址
		* @param[in] size 获取的报文缓冲区大小
		* @param[in] timeout 获取超时ms
		* @return size_t
		*/
		size_t pop(can::Msg* msg, size_t size, size_t timeout = 10);

		/*
		* @brief 清空
		* @return void
		*/
		void clear();

	private:
		std::mutex mutex_;
		std::queue<can::Msg> queue_;
		std::condition_variable cond_var_;
		size_t size_;
		bool stop_;
	};
#else
	/*
	* @brief 缓冲区
	*/
	class CAN_DLL_EXPORT Buffer
	{
	public:
		/*
		* @brief 构造
		* @param[in] size 缓冲区大小
		*/
		Buffer(size_t size = 4096);

		/*
		* @brief 析构
		*/
		~Buffer();

		/*
		* @brief 放入
		* @param[in] msg 保存的报文缓冲区地址
		* @param[in] size 保存的报文缓冲区大小
		* @return void
		*/
		void push(const can::Msg* msg, size_t size);

		/*
		* @brief 弹出
		* @param[out] msg 获取的报文缓冲区地址
		* @param[in] size 获取的报文缓冲区大小
		* @return size_t
		*/
		size_t pop(can::Msg* msg, size_t size);

		/*
		* @brief 清空
		* @return void
		*/
		void clear();

	private:
		std::mutex mutex_;
		std::queue<can::Msg> queue_;
		size_t size_;
	};
#endif
}


