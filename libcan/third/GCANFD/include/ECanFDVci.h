#ifndef _ECANFDVCI_H_

#define _ECANFDVCI_H_

/*
#ifndef _WIN64
typedef unsigned char     uint8_t;
typedef signed   char     int8_t;
typedef unsigned short    uint16_t;
typedef signed   short    int16_t;
typedef unsigned long     uint32_t;
typedef signed   long     int32_t;
#else
typedef unsigned __int8   uint8_t;
typedef signed __int8     int8_t;
typedef unsigned __int16  uint16_t;
typedef signed __int16    int16_t;
typedef unsigned __int32  uint32_t;
typedef signed __int32    int32_t;
#endif
typedef unsigned __int64  uint64_t;
typedef signed __int64    int64_t;
*/

typedef unsigned long long U64;


//接口卡类型定义
#define USBCANFD		6		// 不可更改

#define CANFD_DEVICE_MAX_NUMBER				16			// 定义一台电脑最大可以连接的USBCANFD的数量，用户可根据需求进行修改
#define CANFD_ERRFRAME_MAX_NUMBER			1000		// 定义错误帧缓冲的大小，用户可根据需求进行修改
#define CANFD_RECEFBUFFER_MAX_NUMBER		10000		// 定义数据帧缓冲的大小，用户可根据需求进行修改 

#define CAN_0			0		// CANFD设备通道1的宏定义
#define CAN_1			1		// CANFD设备通道2的宏定义

#define NONUSE			0
#define USED			1

// 无错误时为0
#define	CAN_STATUS_OK				0
//CAN错误码
#define	ERR_CAN_NOINIT			0x0001	// CAN未初始化就被用于发送
#define	ERR_CAN_DISABLE			0x0002	// CAN未使能就被用于发送
#define	ERR_CAN_BUSOFF			0x0004	// CAN已经离线

#define	ERR_DATA_LEN			0x0010	// 数据长度错误
#define	ERR_USB_WRITE			0x0020	// USB写数据失败
#define	ERR_USB_READ			0x0040	// USB读数据失败

//通用错误码
#define	ERR_DEVICEOPENED			0x0100	//设备已经打开
#define	ERR_DEVICEOPEN				0x0200	//打开设备错误
#define	ERR_DEVICENOTOPEN			0x0400	//设备没有打开
#define	ERR_BUFFEROVERFLOW			0x0800	//缓冲区溢出
#define	ERR_DEVICENOTEXIST			0x1000	//此设备不存在
#define ERR_DEVICECLOSE				0x2000	//关闭设备失败



// 定义发送模式选择
typedef enum {
	POSITIVE_SEND = 0,
	PASSIVE_SEND,
} SEND_MODE;
// 定义接收模式选择
typedef enum {
	SPECIFIED_RECEIVE = 0,
	GLOBAL_STANDARD_RECEIVE,
	GLOBAL_EXTENDED_RECEIVE,
	GLOBAL_STANDARD_AND_EXTENDED_RECEIVE,
} RECEIVE_MODE;
// 定义CAN波特率的选择类型
typedef enum {
	BAUDRATE_1M = 0,
	BAUDRATE_800K,
	BAUDRATE_500K,
	BAUDRATE_400K,
	BAUDRATE_250K,
	BAUDRATE_200K,
	BAUDRATE_125K,
	BAUDRATE_100K,
	BAUDRATE_80K,
	BAUDRATE_62500,
	BAUDRATE_50K,
	BAUDRATE_40K,
	BAUDRATE_25K,
	BAUDRATE_20K,
	BAUDRATE_10K,
	BAUDRATE_5K,
} BAUD_RATE;
// 定义数据波特率的选择类型
typedef enum {
	DATARATE_5M = 0,
	DATARATE_4M,
	DATARATE_2M,
	DATARATE_1M,
	DATARATE_800K,
	DATARATE_500K,
	DATARATE_400K,
	DATARATE_250K,
	DATARATE_200K,
	DATARATE_125K,
	DATARATE_100K,
	DATARATE_80K,
	DATARATE_62500,
	DATARATE_50K,
	DATARATE_40K,
	DATARATE_25K,
	DATARATE_20K,
	DATARATE_10K,
	DATARATE_5K,
} DATA_RATE;


//1.系列接口卡信息的数据类型。共75字节
typedef  struct  _BOARD_INFO{	
	USHORT	hw_Version;		// 2
	USHORT	fw_Version;		// 2
	USHORT	dr_Version;		// 2
	USHORT	in_Version;		// 2
	USHORT	irq_Num;		// 2
	BYTE	can_Num;		// 1
	CHAR	str_Serial_Num[20];		// 20
	CHAR	str_hw_Type[40];		// 40
	USHORT	Reserved[4];			// 4
} BOARD_INFO, *P_BOARD_INFO;




typedef struct _BYTE_TYPE
{
	BYTE	Bit0 : 1;
	BYTE	Bit1 : 1;
	BYTE	Bit2 : 1;
	BYTE	Bit3 : 1;
	BYTE	Bit4 : 1;
	BYTE	Bit5 : 1;
	BYTE   	Bit6 : 1;
	BYTE   	Bit7 : 1;
} BYTE_TYPE;

typedef struct _CANFDFRAME_TYPE
{
	BYTE	proto			: 1;		// CAN/CANFD
	BYTE	format			: 1;	// STD/EXD
	BYTE	type			: 1;		// DATA/RTR
	BYTE	bitratemode		: 1;	// bitrateswitch on/off
	BYTE	reserved		: 4;
}CANFDFRAME_TYPE;

// 定义初始化CANFD的数据类型
typedef struct _INIT_CONFIG{		// 78字节
	BYTE	CanReceMode;				// 接收模式设置
	BYTE	CanSendMode;				// 发送模式设置
	DWORD	NominalBitRate;		// 不需要用户设定	Nominal Bit Rate
	DWORD	DataBitRate;		// 不需要用户设定	Data Bit Rate 在数据波特率可变时才是有意义的
	BYTE_TYPE	FilterUsedBits;			// 定义接收模式为 SPECIFIED_RECEIVE 时，决定滤波器1~8的是否被使用		
	BYTE_TYPE	StdOrExdBits;			// 定义接收模式为 SPECIFIED_RECEIVE 时，决定滤波器1~8属于标准还是扩展
	BYTE	NominalBitRateSelect;		// 需要用户设定
	BYTE	DataBitRateSelect;			// 需要用户设定
	// 定义接收模式为 SPECIFIED_RECEIVE 时，下面的8个滤波器的配置才有意义，并且至少需要使用和配置一个
	// 滤波器1的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter1;			// Standard Or Extended filter1
	DWORD	StandardORExtendedfilter1Mask;		// Standard Or Extended filter1 Mask
	// 滤波器2的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter2;			// Extended Or Extended filter2
	DWORD	StandardORExtendedfilter2Mask;		// Extended Or Extended filter2 Mask	
	// 滤波器3的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter3;			// Standard Or Extended filter3
	DWORD	StandardORExtendedfilter3Mask;		// Standard Or Extended filter3 Mask
	// 滤波器4的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter4;			// Extended Or Extended filter4	
	DWORD	StandardORExtendedfilter4Mask;		// Extended Or Extended filter4 Mask
	// 滤波器5的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter5;			// Standard Or Extended filter5
	DWORD	StandardORExtendedfilter5Mask;		// Standard Or Extended filter5 Mask
	// 滤波器6的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter6;			// Extended Or Extended filter6
	DWORD	StandardORExtendedfilter6Mask;		// Extended Or Extended filter6 Mask	
	// 滤波器7的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter7;			// Standard Or Extended filter5
	DWORD	StandardORExtendedfilter7Mask;		// Standard Or Extended filter5 Mask
	// 滤波器8的CANID设置和屏蔽设置
	DWORD	StandardORExtendedfilter8;			// Extended Or Extended filter6
	DWORD	StandardORExtendedfilter8Mask;		// Extended Or Extended filter6 Mask	
}INIT_CONFIG,*P_INIT_CONFIG;

#define STANDARD_FORMAT		0		// 标准帧
#define EXTENDED_FORMAT		1 		// 扩展帧  

#define DATA_TYPE		0		// 数据帧
#define RTR_TYPE		1		// 远程帧

#define CAN_TYPE		0		// 标准CAN
#define CANFD_TYPE		1		// CANFD

#define BITRATESITCH_ON		1		// 数据波特率可变
#define BITRATESITCH_OFF	0		// 数据波特率不变

typedef struct _TIMESTAMP_TYPE
{
	BYTE	mday;
	BYTE	hour;
	BYTE	minute;
	BYTE	second;
	WORD	millisecond;
	WORD	microsecond;
} TIMESTAMP_TYPE;


//定义CANFD信息帧的数据类型
typedef  struct  _CANFD_OBJ{			// 80字节
	CANFDFRAME_TYPE	CanORCanfdType; // 定义帧的类型
	BYTE	DataLen;				// 有效数据长度
	BYTE	Reserved[2];			// 保留
	DWORD	ID;				// CANID
	TIMESTAMP_TYPE TimeStamp;		// 时间戳
	BYTE	Data[64];				// 数据字节
}CANFD_OBJ,*P_CANFD_OBJ;

typedef struct _CANFD_ECR_TYPE
{
	DWORD	TEC			: 8;
	DWORD	REC			: 7;
	DWORD	RP			: 1;
	DWORD	CEL			: 8;
	DWORD				: 8;
} CANFD_ECR_TYPE;


typedef struct _CANFD_PSR_TYPE
{
	DWORD	LEC			: 3;
	DWORD	ACT			: 2;
	DWORD	EP			: 1;
	DWORD	EW			: 1;
	DWORD	BO			: 1;
	DWORD	DLEC		: 3;
	DWORD	RESI		: 1;
	DWORD	RBRS		: 1;
	DWORD	RFDF		: 1;
	DWORD	PXE			: 1;
	DWORD				: 1;
	DWORD	TDCV		: 7;
	DWORD				: 9;
} CANFD_PSR_TYPE;




//定义CANFD错误帧的数据类型
typedef  struct  _ERR_FRAME{				// 错误帧
	TIMESTAMP_TYPE 	can_timestamp;			// 时间戳
	CANFD_ECR_TYPE	can_ecr_register;		// 错误计数寄存器
	CANFD_PSR_TYPE	can_psr_register;		// 协议状态寄存器
}ERR_FRAME, *P_ERR_FRAME;


//定义CANFD设备状态的数据类型
typedef  struct  _CANFD_STATUS{	

	WORD LeftSendBufferNum;				// 未使用的发送缓冲数，被动发送模式使用发动缓冲，主动模式不使用
	TIMESTAMP_TYPE 	can0_timestamp;		// 时间戳
	CANFD_ECR_TYPE	can0_ecr_register;	// 错误计数寄存器
	CANFD_PSR_TYPE	can0_psr_register;	// 协议状态寄存器
	DWORD	can0_RxLost_Cnt;			// 接收失败计数	
	DWORD	can0_TxFail_Cnt;			// 发送失败计数	
	FLOAT	can0_Load_Rate;				// 负载率

	TIMESTAMP_TYPE 	can1_timestamp;		// 时间戳
	CANFD_ECR_TYPE	can1_ecr_register;	// 错误计数寄存器
	CANFD_PSR_TYPE	can1_psr_register;	// 协议状态寄存器
	DWORD	can1_RxLost_Cnt;			// 接收失败计数		
	DWORD	can1_TxFail_Cnt;			// 发送失败计数	
	FLOAT	can1_Load_Rate;				// 负载率

}CANFD_STATUS, *P_CANFD_STATUS;




#ifdef __cplusplus

extern "C"
{
#endif 

	DWORD __stdcall OpenDeviceFD(DWORD DeviceType, DWORD DeviceInd);			// 打开CANFD设备
	DWORD __stdcall CloseDeviceFD(DWORD DeviceType, DWORD DeviceInd);		// 关闭CANFD设备
	DWORD __stdcall InitCANFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, P_INIT_CONFIG pInitConfig);	// 初始化CANFD设备通道1或2
	DWORD __stdcall TransmitFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, P_CANFD_OBJ pCanfdMQ, DWORD Len);	// CANFD设备通道1或2发送数据 
	DWORD __stdcall Receive_buffer_thread(DWORD DeviceType, DWORD DeviceInd, DWORD WaitTime);					// CANFD设备通道1和2共用的接收线程，把数据帧和错误帧放入缓冲中，需要一直运行
	DWORD __stdcall ReceiveFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, P_CANFD_OBJ pCanfdMQ, DWORD *Len); // 从CANFD设备通道1或2的数据帧缓冲中读出数据帧
	DWORD __stdcall GetErrFrame(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, P_ERR_FRAME pCanfdErrbuffer, DWORD *Len); // 从CANFD设备通道1或2的错误帧缓冲中读出错误帧
	DWORD __stdcall ResetCANFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd);	// 复位CANFD设备通道1或2
	DWORD __stdcall StartCANFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd);	// 开始CANFD设备通道1或2 
	DWORD __stdcall StopCANFD(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd); // 停止CANFD设备通道1或2  
	DWORD __stdcall GetCanfdBusStatus(DWORD DeviceType, DWORD DeviceInd, P_CANFD_STATUS p_canfd_status);// 获取CANFD设备状态信息
	DWORD __stdcall GetReference(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, DWORD RefType, PVOID pData);
	DWORD __stdcall SetReference(DWORD DeviceType, DWORD DeviceInd, BYTE CANInd, DWORD RefType, PVOID pData);

#ifdef __cplusplus
}     
#endif

#endif