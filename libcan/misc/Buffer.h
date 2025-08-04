#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

#include "Type.h"

namespace can {	
#if 0
	/*
	* @brief ������
	*/
	class CAN_DLL_EXPORT Buffer
	{
	public:
		/*
		* @brief ����
		* @param[in] size ��������С
		*/
		Buffer(size_t size = 4096);

		/*
		* @brief ����
		*/
		~Buffer();

		/*
		* @brief ����
		* @param[in] msg ����ı��Ļ�������ַ
		* @param[in] size ����ı��Ļ�������С
		* @return void
		*/
		void push(const can::Msg* msg, size_t size);

		/*
		* @brief ����
		* @param[out] msg ��ȡ�ı��Ļ�������ַ
		* @param[in] size ��ȡ�ı��Ļ�������С
		* @param[in] timeout ��ȡ��ʱms
		* @return size_t
		*/
		size_t pop(can::Msg* msg, size_t size, size_t timeout = 10);

		/*
		* @brief ���
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
	* @brief ������
	*/
	class CAN_DLL_EXPORT Buffer
	{
	public:
		/*
		* @brief ����
		* @param[in] size ��������С
		*/
		Buffer(size_t size = 4096);

		/*
		* @brief ����
		*/
		~Buffer();

		/*
		* @brief ����
		* @param[in] msg ����ı��Ļ�������ַ
		* @param[in] size ����ı��Ļ�������С
		* @return void
		*/
		void push(const can::Msg* msg, size_t size);

		/*
		* @brief ����
		* @param[out] msg ��ȡ�ı��Ļ�������ַ
		* @param[in] size ��ȡ�ı��Ļ�������С
		* @return size_t
		*/
		size_t pop(can::Msg* msg, size_t size);

		/*
		* @brief ���
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


