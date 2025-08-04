#include "Base.h"
#include <cassert>

int can::Base::s_totalBaseCounter = 0;
can::Base::Base(DeviceType deviceType)
	:m_deviceType(deviceType)
{
	m_deviceChannelCount = getDeviceChannelCount(deviceType);
	for (int i = 0; i < m_deviceChannelCount; ++i) {
		m_msgs[i] = new can::Msg[CAN_MAX_SEND_BUFFER_SIZE];
		m_msgsBackup[i] = new can::Msg[CAN_MAX_SEND_BUFFER_SIZE];
	}

	for (int i = 0; i < m_deviceChannelCount; ++i) {
		m_future.send[i] = std::async(&Base::onSendMsg, this, i);
		m_future.recv[i] = std::async(&Base::onRecvMsg, this, i);
	}
	m_time.send.getStartTime();
	m_time.recv.getStartTime();
	m_currentBaseId = s_totalBaseCounter++;
}

can::Base::~Base()
{
	m_quit = true;
	for (int i = 0; i < m_deviceChannelCount; ++i) {
		m_future.recv[i].wait();
		m_future.send[i].wait();
	}

	for (int i = 0; i < m_deviceChannelCount; ++i) {
		delete[] m_msgs[i];
		delete[] m_msgsBackup[i];
	}
	--s_totalBaseCounter;
}

void can::Base::setMatrix(can::Matrix* matrix)
{
	m_matrix = matrix;
}

can::Matrix* can::Base::getMatrix() const
{
	return m_matrix;
}

bool can::Base::reset()
{
	setLastError("子类尚未实现复位功能");
	return false;
}

bool can::Base::isOpen() const
{
	return m_open;
}

bool can::Base::sendMsg(const can::Msg* msg, size_t size, int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		setLastError("设备通道超出可用范围");
		return false;
	}
	return send(msg, size, channel);
}

size_t can::Base::recvMsg(can::Msg* msg, size_t size, int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return 0;
	}
	return m_canChannel[channel].msgBuffer->pop(msg, size);
}

void can::Base::addMsg(const can::Msg& msg, int channel)
{
	do
	{
		if (channel < 0 || channel > m_deviceChannelCount - 1) {
			break;
		}
		bool ceFind = false, ceSending = false;
		if (msg.sendType == SendType::ST_CE) {
			for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
				if (m_msgs[channel][i].sendValid) {
					if (m_msgs[channel][i].id == msg.id && m_msgs[channel][i].sendType == SendType::ST_CE /*&& m_msgs[channel][i].channelIndex == channel*/) {
						if (m_msgs[channel][i].sendCount > 0) {
							ceSending = true;
							break;
						}

						for (int j = 0; j < CAN_MAX_SEND_BUFFER_SIZE; ++j) {
							if (!m_msgsBackup[channel][j].sendValid) {
								m_msgsBackup[channel][j] = m_msgs[channel][i];
								break;
							}
						}
						m_msgs[channel][i] = msg;
						m_msgs[channel][i].sendValid = true;
						m_msgs[channel][i].channelIndex = channel;
						ceFind = true;
						break;
					}
				}
			}
		}

		if (!ceFind && !ceSending) {
			bool find = false;
			for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
				if (m_msgs[channel][i].sendValid) {
					if (m_msgs[channel][i].equal(msg) && msg.sendType != SendType::ST_EVENT) {
						m_msgs[channel][i] = msg;
						m_msgs[channel][i].sendValid = true;
						m_msgs[channel][i].channelIndex = channel;
						find = true;
						break;
					}
				}
			}

			if (!find) {
				for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
					if (!m_msgs[channel][i].sendValid) {
						m_msgs[channel][i] = msg;
						m_msgs[channel][i].sendValid = true;
						m_msgs[channel][i].channelIndex = channel;
						find = true;
						break;
					}
				}
			}

			if (!find) {
				break;
			}

			if (msg.addInterval) {
				std::this_thread::sleep_for(std::chrono::milliseconds(msg.addInterval));
			}
		}

	} while (false);
}

void can::Base::addMsg(int id, SendProc proc, int period, SendType type, int count, int interval, int channel)
{
	addMsg({ id, 8, { 0 }, period, type, count, interval, proc, channel });
}

void can::Base::addMsg(const std::initializer_list<can::Msg>& msg, int channel)
{
	for (size_t i = 0; i < msg.size(); ++i) {
		addMsg(msg.begin()[i], channel);
	}
}

void can::Base::addMsg(const can::Msg& msg, int start, int length, uint64_t data, int channel)
{
	if (!m_matrix) {
		fprintf(stderr, "addMsg can::Matrix is nullptr!\n");
		return;
	}

	can::Msg _msg = msg;
	if (!m_matrix->pack(_msg.data, start, length, data)) {
		fprintf(stderr, "addMsg can::Matrix::pack error!\n");
		return;
	}

	addMsg(_msg, channel);
}

void can::Base::deleteMsg(int id, int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}

	for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
		if (m_msgs[channel][i].id == id) {
			m_msgs[channel][i].sendValid = false;
			break;
		}
	}
}

void can::Base::deleteMsg(const can::Msg& msg, int channel)
{
	deleteMsg(msg.id, channel);
}

void can::Base::deleteAllMsgs(int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}

	for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
		if (m_msgs[channel][i].sendValid) {
			m_msgs[channel][i].sendValid = false;
		}
	}
}

void can::Base::startAsyncSendMsg()
{
	m_asyncSendMsg = true;
}

void can::Base::stopAsyncSendMsg()
{
	m_asyncSendMsg = false;
}

std::string can::Base::getLastError() const
{
	return m_lastError;
}

void can::Base::setFilterId(const std::list<int>& filter)
{
	m_filterId = filter;
}

std::list<int> can::Base::getFilterId() const
{
	return m_filterId;
}

void can::Base::setOutputLog(bool on)
{
	m_outputLog = on;
}

bool can::Base::isOutputLog() const
{
	return m_outputLog;
}

void can::Base::setMsgProc(MsgProc proc, int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}
	m_mutex.proc[channel].lock();
	m_canChannel[channel].msgProc = proc;
	m_mutex.proc[channel].unlock();
}

can::Base::MsgProc can::Base::getMsgProc(int channel) const
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return nullptr;
	}
	return m_canChannel[channel].msgProc;
}

std::string can::Base::fmtMsg(const char* direction, const can::Msg& msg) const
{
	char text[4096] = { 0 };
	formatMsg(direction, msg, text, sizeof(text));
	return text;
}

bool can::Base::isSupportFd() const
{
	return m_supportFd;
}

void can::Base::clearBuffer(int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}
	m_canChannel[channel].msgBuffer->clear();
}

can::ArbiBaud can::Base::translateArbiBaud(int value) const
{
	ArbiBaud baud = AB_0Kbps;
	switch (value)
	{
	case 50:
		baud = AB_50Kbps;
		break;
	case 100:
		baud = AB_100Kbps;
		break;
	case 125:
		baud = AB_125Kbps;
		break;
	case 200:
		baud = AB_200Kbps;
		break;
	case 250:
		baud = AB_250Kbps;
		break;
	case 400:
		baud = AB_400Kbps;
		break;
	case 500:
		baud = AB_500Kbps;
		break;
	case 800:
		baud = AB_800Kbps;
		break;
	case 1000:
		baud = AB_1Mbps;
		break;
	default:
		break;
	}
	return baud;
}

can::DataBaud can::Base::translateDataBaud(int value) const
{
	DataBaud baud = DB_0Kbps;
	switch (value)
	{
	case 5000:
		baud = DB_5Mbps;
		break;
	case 4000:
		baud = DB_4Mbps;
		break;
	case 2000:
		baud = DB_2Mbps;
		break;
	case 1000:
		baud = DB_1Mbps;
		break;
	case 800:
		baud = DB_800Kbps;
		break;
	case 500:
		baud = DB_500Kbps;
		break;
	case 250:
		baud = DB_250Kbps;
		break;
	case 125:
		baud = DB_125Kbps;
		break;
	case 100:
		baud = DB_100Kbps;
		break;
	default:
		break;
	}
	return baud;
}

void can::Base::processMsg(const char* type, const can::Msg* msg, size_t size, int channel)
{
	if (size == 0) {
		return;
	}

	for (size_t i = 0; i < size; ++i) {
		if (m_filterId.size()) {
			if (std::find(m_filterId.begin(), m_filterId.end(), msg[i].id) != m_filterId.end()) {
				if (m_outputLog) {
					outputMsg(type, msg[i]);
				}

				m_mutex.proc[channel].lock();
				if (m_canChannel[channel].msgProc && msg[i].channelIndex == channel) {
					m_canChannel[channel].msgProc(type, msg[i]);
				}
				m_mutex.proc[channel].unlock();
			}
		}
		else {
			if (m_outputLog) {
				outputMsg(type, msg[i]);
			}

			m_mutex.proc[channel].lock();
			if (m_canChannel[channel].msgProc && msg[i].channelIndex == channel) {
				m_canChannel[channel].msgProc(type, msg[i]);
			}
			m_mutex.proc[channel].unlock();
		}
	}
}

void can::Base::formatMsg(const char* type, const can::Msg& msg, char* text, size_t size) const
{
	std::string data;
	char str[32] = { 0 };
	for (int i = 0; i < msg.dlc; ++i) {
		if (i != msg.dlc - 1) {
			sprintf_s(str, "%02x:", msg.data[i]);
		}
		else {
			sprintf_s(str, "%02x", msg.data[i]);
		}
		data.append(str);
	}

	SYSTEMTIME time;
	GetLocalTime(&time);
	sprintf_s(text, size,
		"[%02d:%02d:%02d.%03d],"
		"[%d],"
		"[%d],"
		"[%s],"
		"[%s],"
		"[0x%x],"
		"[%s],"
		"[%06d],"
		"[%s],"
		"[%s]\n",
		time.wHour,
		time.wMinute,
		time.wSecond,
		time.wMilliseconds,
		m_currentBaseId,
		msg.channelIndex,
		type,
		msg.protoType == ProtoType::PT_CAN ? "CAN" : "CANFD",
		msg.id,
		data.c_str(),
		msg.timeStamp,
		msg.expFrame ? "true" : "false",
		msg.remFrame ? "true" : "false"
		);
}

void can::Base::outputMsg(const char* type, const can::Msg& msg) const
{
	char text[4096] = { 0 };
	formatMsg(type, msg, text, sizeof(text));
	OutputDebugStringA(text);
}

int can::Base::getDlc(const can::Msg* msg) const
{
	return msg->dlc == 0 ? 8 : msg->dlc;
}

void can::Base::setLastError(const char* fmt, ...)
{
	va_list ap = nullptr;
	va_start(ap, fmt);
	auto length = _vscprintf_p(fmt, ap) + 1;
	std::unique_ptr<char[]> buffer(new char[length]);
	memset(buffer.get(), 0, length);
	_vsprintf_p(buffer.get(), length, fmt, ap);
	va_end(ap);
	m_lastError = buffer.get();
}

can::ProtoCount can::Base::getProtoCount(const can::Msg* msg, size_t size) const
{
	can::ProtoCount count = { 0 };
	for (size_t i = 0; i < size; ++i) {
		if (msg[i].protoType == PT_CAN) {
			++count.can;
		}
		else {
			++count.canfd;
		}
	}
	return count;
}

void can::Base::closeLock(int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}

	m_mutex.opens[channel].lock();
	m_mutex.openr[channel].lock();
}

void can::Base::closeUnlock(int channel)
{
	if (channel < 0 || channel > m_deviceChannelCount - 1) {
		return;
	}

	m_mutex.opens[channel].unlock();
	m_mutex.openr[channel].unlock();
}

void can::Base::onSendMsg(int channel)
{
	std::unique_ptr<can::Msg[]> msgs(new can::Msg[CAN_MAX_SEND_BUFFER_SIZE]);
	auto endTime = 0, count = 0;
	while (!m_quit) {
		while (m_open && m_asyncSendMsg) {
			endTime = (int)m_time.send.getEndTime();
			for (int i = 0; i < CAN_MAX_SEND_BUFFER_SIZE; ++i) {
				if (m_msgs[channel][i].sendValid && endTime - m_msgs[channel][i].sendTime >= m_msgs[channel][i].sendCycle) {
					m_msgs[channel][i].sendTime = endTime;
					if (m_msgs[channel][i].sendProc) {
						m_msgs[channel][i].sendProc(m_msgs[channel][i]);
					}
					msgs[count] = m_msgs[channel][i];
					if (m_msgs[channel][i].sendType == SendType::ST_EVENT) {
						if (--m_msgs[channel][i].sendCount <= 0) {
							m_msgs[channel][i].sendValid = false;
							if (m_msgs[channel][i].eventProc) {
								m_msgs[channel][i].eventProc(m_msgs[channel][i]);
							}
						}
					}
					else if (m_msgs[channel][i].sendType == SendType::ST_CE) {
						if (m_msgs[channel][i].sendCount > 0) {
							if (--m_msgs[channel][i].sendCount <= 0) {
								if (m_msgs[channel][i].eventProc) {
									m_msgs[channel][i].eventProc(m_msgs[channel][i]);
								}

								for (int j = 0; j < CAN_MAX_SEND_BUFFER_SIZE; ++j) {
									if (m_msgs[channel][i].id == m_msgsBackup[channel][j].id) {
										m_msgs[channel][i] = m_msgsBackup[channel][j];
										m_msgsBackup[channel][j].sendValid = false;
										break;
									}
								}
							}
						}
					}

					if (++count >= 100) {
						break;
					}
				}
			}

			if (count > 0) {
				//std::map<int, std::vector<can::Msg>> multi;
				//for (int i = 0; i < count; ++i) {
				//	multi[msgs[i].channelIndex].emplace_back(msgs[i]);
				//}

				//for (auto& x : multi) {
				//	m_mutex.opens[x.first].lock();
				//	if (m_canDevice.enableChannel[x.first]) {
				//		send(x.second.data(), x.second.size(), x.first);
				//	}
				//	m_mutex.opens[x.first].unlock();
				//}
				m_mutex.opens[channel].lock();
				if (m_canDevice.enableChannel[channel]) {
					send(msgs.get(), count, channel);
				}
				m_mutex.opens[channel].unlock();
				count = 0;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void can::Base::onRecvMsg(int channel)
{
	std::unique_ptr<can::Msg[]> msg(new can::Msg[CAN_MAX_RECV_BUFFER_SIZE]);
	while (!m_quit) {
		if (m_open) {
			m_mutex.openr[channel].lock();
			if (m_canDevice.enableChannel[channel]) {
				size_t count = recv(msg.get(), CAN_MAX_RECV_BUFFER_SIZE, channel);
				if (count > 0) {
					m_canChannel[channel].msgBuffer->push(msg.get(), count);
				}
			}
			m_mutex.openr[channel].unlock();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

