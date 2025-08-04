#pragma once
#include <cstring>
#include <cmath>
#include <bitset>

#define CAN_MATRIX_MAX_LENGTH 64

namespace can {
	/*
	* @brief CAN����
	* �����������ڴ���CAN����ļ��㼰����
	*/
	class CAN_DLL_EXPORT Matrix 
	{
	public:
		/*
		* @brief ����
		*/
		enum Type {
			//Ħ�����������Чλ
			MOTOROLA_LSB,

			//Ħ�����������Чλ
			MOTOROLA_MSB,

			//���ض�
			INTEL,
		};

		/*
		* @brief ����
		* @param[in] type ��������
		*/
		inline Matrix(Type type = MOTOROLA_LSB) :type_(type) {}

		/*
		* @brief ����
		*/
		inline ~Matrix() {}

		/*
		* @brief,��ȡ���մ���
		* @return,const char*
		*/
		inline std::string getLastError() const { return error_; }

		/*
		* @brief ���þ�������
		* @param[in] type ��������
		* @return void
		*/
		inline void setType(Type type) { type_ = type; }

		/*
		* @brief ��ȡ��������
		* @return Type
		*/
		inline Type getType() const { return type_; }

		/*
		* @brief ��ȡ������
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
		* @brief ���
		* @param[in] buffer ����Ļ�����
		* @param[in] start ������ʼλ
		* @param[in] length ���ݳ���
		* @tparam[in] data ���������
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

						//��һ��ƫ������,Ϊ��С�±���<<
						const int firstOffset = bitPos;

						//��һ�����ݳ���
						const int firstDataLen = 8 - firstOffset;

						//���һ��ƫ������,Ϊ����±���>>
						const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

						//���һ�����ݳ���
						const int lastDataLen = length - lastOffset;

						//��ʼλ
						const int startPos = bytePos;

						//����λ
						const int endPos = bytePos + index;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								buffer[i] &= (0xff >> firstDataLen);
								//������&
								buffer[i] |= (data & setBit1(firstDataLen)) << firstOffset;
							}
							else if (i == endPos) {
								buffer[i] &= (0xff << lastDataLen);
								//������>>
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

						//��һ��ƫ������,Ϊ��С�±���>>
						const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

						//��һ�����ݳ���
						const int firstDataLen = length - firstOffset;

						//���һ��ƫ������,Ϊ����±���<<
						const int lastOffset = bitPos;

						//���һ�����ݳ���
						const int lastDataLen = 8 - lastOffset;

						//��ʼλ
						const int startPos = bytePos - index;

						//����λ
						const int endPos = bytePos;

						for (int i = startPos; i <= endPos; i++) {
							if (i == startPos) {
								buffer[i] &= (0xff << firstDataLen);
								//������>>
								buffer[i] |= ((data >> firstOffset) & setBit1(firstDataLen));
							}
							else if (i == endPos) {
								buffer[i] &= (0xff >> lastDataLen);
								//������&
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
						//�����±�
						int index = 0;

						offset = abs(offset);

						//��һ��ƫ������,Ϊ��С�±���>>
						const int firstOffset = offset;

						//��ȡ��Ҫ�������������
						while ((offset -= 8) > 0) {
							index++;
						}

						//�����������,�����ۼ�
						offset = abs(offset);
						if (offset > 0) {
							index++;
						}

						//���һ��ƫ������,Ϊ����±���<<
						const int lastOffset = offset;

						//��ʼλ�ó���
						const int firstDataLen = bitPos + 1;

						//����λ�ó���
						const int lastDataLen = 8 - offset;

						//��ʼλ
						const int startPos = bytePos;

						//����λ
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
		* @brief ���
		* @param[in] buffer ����Ļ�����
		* @param[in] start ������ʼλ
		* @param[in] length ���ݳ���
		* @tparam[out] data ���������
		* @return bool
		*/
		template <class T> inline bool unpack(const unsigned char* buffer, int start, int length, T& data) {
			bool result = false;
			do
			{
				//����Ҫ����
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

						//��һ��ƫ������,Ϊ��С�±���<<
						const int firstOffset = bitPos;

						//��һ�����ݳ���
						const int firstDataLen = 8 - firstOffset;

						//���һ��ƫ������,Ϊ����±���>>
						const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

						//���һ�����ݳ���
						const int lastDataLen = length - lastOffset;

						//��ʼλ
						const int startPos = bytePos;

						//����λ
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
						//�����±�
						int index = 0;

						while ((offset -= 8) > 8) {
							index++;
						}

						if (offset > 0) {
							index++;
						}

						//��һ��ƫ������,Ϊ��С�±���<<
						const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

						//��һ�����ݳ���,Ŀǰ��ʱ�ò���
						const int firstDataLen = length - firstOffset;

						//���һ��ƫ������,Ϊ����±���>>
						const int lastOffset = bitPos;

						//���һ�����ݳ���
						const int lastDataLen = 8 - lastOffset;

						//��ʼλ
						const int startPos = bytePos - index;

						//����λ
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
						//�����±�
						int index = 0;

						offset = abs(offset);

						//��һ��ƫ������,Ϊ��С�±���>>
						const int firstOffset = offset;

						//��ȡ��Ҫ�������������
						while ((offset -= 8) > 0) {
							index++;
						}

						//�����������,�����ۼ�
						offset = abs(offset);
						if (offset > 0) {
							index++;
						}

						//���һ��ƫ������,Ϊ����±���<<
						const int lastOffset = offset;

						//��ʼλ�ó���
						const int firstDataLen = bitPos + 1;

						//����λ�ó���
						const int lastDataLen = 8 - offset;

						//��ʼλ
						const int startPos = bytePos;

						//����λ
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
		* @brief �������մ���
		* @param[in] error ������Ϣ
		* @return void
		*/
		inline void setLastError(const std::string& error) { error_ = error; }

		/*
		* @brief ����λΪ1
		* @param[in] length λ����
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
		* @brief ����λΪ0
		* @param[in] length λ����
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
		* @brief ��ȡλ��
		* @param[in] startPos ��ʼλ��
		* @param[out] bytePos �����ֽ�λ��
		* @param[out] bitPos ����λλ��
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
		* @brief ��鳤��
		* @param[in] bytePos �ֽ�λ��
		* @param[in] bitPos λλ��
		* @param[in] dataLen ���ݳ���
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
		* @brief ��ʼ��
		* @param[in] start ��ʼλ��
		* @param[in] length ���ݳ���
		* @tparam[in] data ����
		* @param[out] bytePos �����ֽ�λ��
		* @param[out] bitPos ����λλ��
		* @return bool
		*/
		template<class T> inline bool initialize(int start, int length, T data, int* bytePos, int* bitPos)
		{
			bool result = false;
			do
			{
				if (type_ != INTEL && type_ != MOTOROLA_LSB && type_ != MOTOROLA_MSB) {
					setLastError("��Ч�ľ�������");
					break;
				}

				if (start < 0 || start > 63) {
					setLastError("��ʼλ�ò���0~63��Χ��");
					break;
				}

				if (length <= 0 || length > 64) {
					setLastError("���ݳ��Ȳ���1~64��Χ��");
					break;
				}

				if (setBit1(length) < data) {
					setLastError("λ����û���㹻�Ŀռ�������");
					break;
				}

				if (!getPosition(start, bytePos, bitPos)) {
					setLastError("��ʼλ�ò���0~63��Χ��");
					break;
				}

				if (!checkLength(*bytePos, *bitPos, length)) {
					setLastError("���ݳ��Ȳ���1~64��Χ��");
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
