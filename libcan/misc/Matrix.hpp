#pragma once
#include <cstring>
#include <cmath>
#include <bitset>

#define CAN_MATRIX_MAX_LENGTH 64

namespace can {
	/*
	* @brief CAN矩阵
	* 此类库可以用于处理CAN矩阵的计算及解析
	*/
	class CAN_DLL_EXPORT Matrix 
	{
	public:
		/*
		* @brief 类型
		*/
		enum Type {
			//摩托罗拉最低有效位
			MOTOROLA_LSB,

			//摩托罗拉最高有效位
			MOTOROLA_MSB,

			//因特尔
			INTEL,
		};

		/*
		* @brief 构造
		* @param[in] type 矩阵类型
		*/
		inline Matrix(Type type = MOTOROLA_LSB) :type_(type) {}

		/*
		* @brief 析构
		*/
		inline ~Matrix() {}

		/*
		* @brief,获取最终错误
		* @return,const char*
		*/
		inline std::string getLastError() const { return error_; }

		/*
		* @brief 设置矩阵类型
		* @param[in] type 矩阵类型
		* @return void
		*/
		inline void setType(Type type) { type_ = type; }

		/*
		* @brief 获取矩阵类型
		* @return Type
		*/
		inline Type getType() const { return type_; }

		/*
		* @brief 获取矩阵名
		* @return std::string
		*/
		inline std::string getName() const
		{
			std::string name = "Unknown";
			switch (type_)
			{
			case MOTOROLA_LSB:name = "Motorola LSB"; break;
			case MOTOROLA_MSB:name = "Motorola MSB"; break;
			case INTEL:name = "Intel"; break;
			default:break;
			}
			return name;
		}

		/*
		* @brief 打包
		* @param[in] buffer 打包的缓存区
		* @param[in] start 数据起始位
		* @param[in] length 数据长度
		* @tparam[in] data 打包的数据
		* @return bool
		*/
		template <class T> inline bool pack(unsigned char* buffer, int start, int length, T data) {
			bool result = false;
			do
			{
				int bytePos = 0, bitPos = 0;
				if (!initialize(start, length, data, &bytePos, &bitPos)) {
					break;
				}

				if (type_ == INTEL) {
					int offset = bitPos + length;
					if (offset > 8) {
						int index = 0;
						while ((offset -= 8) > 8) {
							index++;
						}

						if (offset > 0) {
							index++;
						}

						//第一个偏移数量,为最小下标所<<
						const int firstOffset = bitPos;

						//第一个数据长度
						const int firstDataLen = 8 - firstOffset;

						//最后一个偏移数量,为最大下标所>>
						const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

						//最后一个数据长度
						const int lastDataLen = length - lastOffset;

						//起始位
						const int startPos = bytePos;

						//结束位
						const int endPos = bytePos + index;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								buffer[i] &= (0xff >> firstDataLen);
								//必须先&
								buffer[i] |= (data & setBit1(firstDataLen)) << firstOffset;
							}
							else if (i == endPos) {
								buffer[i] &= (0xff << lastDataLen);
								//必须先>>
								buffer[i] |= (data >> lastOffset) & setBit1(lastDataLen);
							}
							else {
								buffer[i] &= 0;
								const int tempOffset = (i - startPos - 1) * 8 + firstDataLen;
								buffer[i] |= (data >> tempOffset) & 0xff;
							}
						}
					}
					else {
						buffer[bytePos] &= ((0xff << offset) | setBit1(bitPos));
						buffer[bytePos] |= (data & setBit1(length)) << bitPos;
					}
				}
				else if (type_ == MOTOROLA_LSB) {
					int offset = bitPos + length;
					if (offset > 8) {
						int index = 0;

						while ((offset -= 8) > 8) {
							index++;
						}

						if (offset > 0) {
							index++;
						}

						//第一个偏移数量,为最小下标所>>
						const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

						//第一个数据长度
						const int firstDataLen = length - firstOffset;

						//最后一个偏移数量,为最大下标所<<
						const int lastOffset = bitPos;

						//最后一个数据长度
						const int lastDataLen = 8 - lastOffset;

						//起始位
						const int startPos = bytePos - index;

						//结束位
						const int endPos = bytePos;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								buffer[i] &= (0xff << firstDataLen);
								//必须先>>
								buffer[i] |= ((data >> firstOffset) & setBit1(firstDataLen));
							}
							else if (i == endPos) {
								buffer[i] &= (0xff >> lastDataLen);
								//必须先&
								buffer[i] |= ((data & setBit1(lastDataLen)) << lastOffset);
							}
							else {
								buffer[i] &= 0;
								const int tempOffset = (endPos - i - 1) * 8 + lastDataLen;
								buffer[i] |= ((data >> tempOffset) & 0xff);
							}
						}
					}
					else {
						buffer[bytePos] &= ((0xff << (length + bitPos)) | setBit1(bitPos));
						buffer[bytePos] |= (data & setBit1(length)) << bitPos;
					}
				}
				else if (type_ == MOTOROLA_MSB) {
					int offset = bitPos - length + 1;

					if (offset < 0) {
						//数组下标
						int index = 0;

						offset = abs(offset);

						//第一个偏移数量,为最小下标所>>
						const int firstOffset = offset;

						//获取需要计算数组的数量
						while ((offset -= 8) > 0) {
							index++;
						}

						//如果存在余数,继续累加
						offset = abs(offset);
						if (offset > 0) {
							index++;
						}

						//最后一个偏移数量,为最大下标所<<
						const int lastOffset = offset;

						//起始位置长度
						const int firstDataLen = bitPos + 1;

						//结束位置长度
						const int lastDataLen = 8 - offset;

						//起始位
						const int startPos = bytePos;

						//结束位
						const int endPos = bytePos + index;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								buffer[i] &= (0xff << firstDataLen);
								buffer[i] |= (data >> firstOffset) & setBit1(firstDataLen);
							}
							else if (i == endPos) {
								buffer[i] &= (0xff >> lastDataLen);
								buffer[i] |= (data & setBit1(lastDataLen)) << lastOffset;
							}
							else {
								buffer[i] &= 0;
								const int tempOffset = (i - startPos - 1) * 8 + lastDataLen;
								buffer[i] |= (data >> tempOffset) & 0xff;
							}
						}
					}
					else {
						buffer[bytePos] &= ((0xff << (bitPos + 1)) | setBit1(offset));
						buffer[bytePos] |= (data & setBit1(length)) << offset;
					}
				}
				result = true;
			} while (false);
			return result;
		}

		/*
		* @brief 解包
		* @param[in] buffer 解包的缓存区
		* @param[in] start 数据起始位
		* @param[in] length 数据长度
		* @tparam[out] data 解包的数据
		* @return bool
		*/
		template <class T> inline bool unpack(const unsigned char* buffer, int start, int length, T& data) {
			bool result = false;
			do
			{
				//必须要清零
				memset(&data, 0, sizeof(T));
				int bytePos = 0, bitPos = 0;
				if (!initialize(start, length, 0, &bytePos, &bitPos)) {
					break;
				}

				if (type_ == INTEL) {
					int offset = bitPos + length;
					if (offset > 8) {
						int index = 0;
						while ((offset -= 8) > 8) {
							index++;
						}

						if (offset > 0) {
							index++;
						}

						//第一个偏移数量,为最小下标所<<
						const int firstOffset = bitPos;

						//第一个数据长度
						const int firstDataLen = 8 - firstOffset;

						//最后一个偏移数量,为最大下标所>>
						const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

						//最后一个数据长度
						const int lastDataLen = length - lastOffset;

						//起始位
						const int startPos = bytePos;

						//结束位
						const int endPos = bytePos + index;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								data |= (buffer[i] >> firstOffset) & setBit1(firstDataLen);
							}
							else if (i == endPos) {
								data |= static_cast<T>(buffer[i] & setBit1(lastDataLen)) << lastOffset;
							}
							else {
								const int tempOffset = (i - startPos - 1) * 8 + firstDataLen;
								data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
							}
						}
					}
					else {
						data |= (buffer[bytePos] >> bitPos) & setBit1(length);
					}
				}
				else if (type_ == MOTOROLA_LSB) {
					int offset = (bitPos + length);
					if (offset > 8) {
						//数组下标
						int index = 0;

						while ((offset -= 8) > 8) {
							index++;
						}

						if (offset > 0) {
							index++;
						}

						//第一个偏移数量,为最小下标所<<
						const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

						//第一个数据长度,目前暂时用不到
						const int firstDataLen = length - firstOffset;

						//最后一个偏移数量,为最大下标所>>
						const int lastOffset = bitPos;

						//最后一个数据长度
						const int lastDataLen = 8 - lastOffset;

						//起始位
						const int startPos = bytePos - index;

						//结束位
						const int endPos = bytePos;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								data |= static_cast<T>(buffer[i] & setBit1(firstDataLen)) << firstOffset;
							}
							else if (i == endPos) {
								data |= (buffer[i] >> lastOffset) & setBit1(lastDataLen);
							}
							else {
								const int tempOffset = (endPos - i - 1) * 8 + lastDataLen;
								data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
							}
						}
					}
					else {
						data |= (buffer[bytePos] >> bitPos) & setBit1(length);
					}
				}
				else if (type_ == MOTOROLA_MSB) {
					int offset = bitPos - length + 1;

					if (offset < 0) {
						//数组下标
						int index = 0;

						offset = abs(offset);

						//第一个偏移数量,为最小下标所>>
						const int firstOffset = offset;

						//获取需要计算数组的数量
						while ((offset -= 8) > 0) {
							index++;
						}

						//如果存在余数,继续累加
						offset = abs(offset);
						if (offset > 0) {
							index++;
						}

						//最后一个偏移数量,为最大下标所<<
						const int lastOffset = offset;

						//起始位置长度
						const int firstDataLen = bitPos + 1;

						//结束位置长度
						const int lastDataLen = 8 - offset;

						//起始位
						const int startPos = bytePos;

						//结束位
						const int endPos = bytePos + index;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								data |= static_cast<T>(buffer[i] & setBit1(firstDataLen)) << firstOffset;
							}
							else if (i == endPos) {
								data |= (buffer[i] >> lastOffset) & setBit1(lastDataLen);
							}
							else {
								const int tempOffset = (i - startPos - 1) * 8 + lastDataLen;
								data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
							}
						}
					}
					else {
						data |= (buffer[bytePos] >> offset) & setBit1(length);
					}
				}
				result = true;
			} while (false);
			return result;
		}

	protected:
		/*
		* @brief 设置最终错误
		* @param[in] error 错误信息
		* @return void
		*/
		inline void setLastError(const std::string& error) { error_ = error; }

		/*
		* @brief 设置位为1
		* @param[in] length 位长度
		* @return unsigned long long
		*/
		inline unsigned long long setBit1(size_t length) const
		{
			std::bitset<CAN_MATRIX_MAX_LENGTH> bit;
			for (size_t i = 0; i < length; i++) {
				bit.set(i);
			}
			return bit.to_ullong();
		}

		/*
		* @brief 设置位为0
		* @param[in] length 位长度
		* @return unsigned long long
		*/
		inline unsigned long long setBit0(size_t length) const
		{
			std::bitset<CAN_MATRIX_MAX_LENGTH> bit;
			for (size_t i = 0; i < length; i++) {
				bit.set(i, false);
			}
			return bit.to_ullong();
		}

		/*
		* @brief 获取位置
		* @param[in] startPos 起始位置
		* @param[out] bytePos 所得字节位置
		* @param[out] bitPos 所得位位置
		* @return bool
		*/
		inline bool getPosition(int startPos, int* bytePos, int* bitPos) const
		{
			bool result = false;
			do
			{
				if (!startPos) {
					*bytePos = *bitPos = 0;
				}
				else if (!(startPos % 8) && startPos) {
					*bytePos = startPos / 8;
					bitPos = 0;
				}
				else if ((startPos % 8) && startPos) {
					if (startPos < 8) {
						*bytePos = 0;
						*bitPos = startPos;
					}
					else {
						*bytePos = startPos / 8;
						*bitPos = startPos - *bytePos * 8;
					}
				}
				else {
					break;
				}
				result = true;
			} while (false);
			return result;
		}

		/*
		* @brief 检查长度
		* @param[in] bytePos 字节位置
		* @param[in] bitPos 位位置
		* @param[in] dataLen 数据长度
		* @return bool
		*/
		inline bool checkLength(int bytePos, int bitPos, int dataLen) const
		{
			bool result = false;
			do
			{
				int bitLen = 0;
				if (type_ == MOTOROLA_LSB) {
					bitLen = (bytePos + 1) * 8 - bitPos;
				}
				else if (type_ == MOTOROLA_MSB) {
					bitLen = abs((bytePos + 1) * 8 - CAN_MATRIX_MAX_LENGTH) + bitPos + 1;
				}
				else {
					bitLen = abs((bytePos + 1) * 8 - CAN_MATRIX_MAX_LENGTH) + 8 - bitPos;
				}

				if (dataLen > bitLen) {
					break;
				}
				result = true;
			} while (false);
			return result;
		}

		/*
		* @brief 初始化
		* @param[in] start 起始位置
		* @param[in] length 数据长度
		* @tparam[in] data 数据
		* @param[out] bytePos 所得字节位置
		* @param[out] bitPos 所得位位置
		* @return bool
		*/
		template<class T> inline bool initialize(int start, int length, T data, int* bytePos, int* bitPos)
		{
			bool result = false;
			do
			{
				if (type_ != INTEL && type_ != MOTOROLA_LSB && type_ != MOTOROLA_MSB) {
					setLastError("无效的矩阵类型");
					break;
				}

				if (start < 0 || start > 63) {
					setLastError("起始位置不在0~63范围内");
					break;
				}

				if (length <= 0 || length > 64) {
					setLastError("数据长度不在1~64范围内");
					break;
				}

				if (setBit1(length) < data) {
					setLastError("位长度没有足够的空间存放数据");
					break;
				}

				if (!getPosition(start, bytePos, bitPos)) {
					setLastError("起始位置不在0~63范围内");
					break;
				}

				if (!checkLength(*bytePos, *bitPos, length)) {
					setLastError("数据长度不在1~64范围内");
					break;
				}
				result = true;
			} while (false);
			return result;
		}

	private:
		Type type_ = MOTOROLA_LSB;
		std::string error_;
	};
}
