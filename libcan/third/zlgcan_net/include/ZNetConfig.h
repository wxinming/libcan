#ifndef NET_CONFIG_H_
#define NET_CONFIG_H_

/* 设备类型 */
#define ZN_TYPE_CANET_E                     0xA0
#define ZN_TYPE_CANET_2E                    0x90
#define ZN_TYPE_CANET_4E                    0x80
#define ZN_TYPE_CANET_8E                    0x88
#define ZN_TYPE_ZNE100TL                    0x22
#define ZN_TYPE_ZNE100TA                    0x25
#define ZN_TYPE_ZBNET_300C_U                0x33
#define ZN_TYPE_CANFDWIFI_100U              0x64
#define ZN_TYPE_CANFDWIFI_200U              0x65
#define ZN_TYPE_CANFDBLUE_200U              0x70
#define ZN_TYPE_CANFDNET_200U               0x60
#define ZN_TYPE_CANFDNET_400U               0x6A
#define ZN_TYPE_CANFDNET_100MINI            0x5F
#define ZN_TYPE_CANFDDTU_400ER              0x6C
#define ZN_TYPE_CANFDDTU_400EWGR            0x6B
#define ZN_TYPE_CANFDNET_800U               0x6E
#define ZN_TYPE_CANFDDTU_600EWGR            0x6F
#define ZN_TYPE_CANFDDTU_800ER              0x71
#define ZN_TYPE_CANFDDTU_800EWGR            0x72
#define ZN_TYPE_CANFDDTU_1200EWGR           0x73
#define ZN_TYPE_CANFDDTU_2400EWGR           0x74
#define ZN_TYPE_CANFDNET_400H               0x75


#define ZN_TYPE_CLOUD_DEV                   0xEE

#define ZN_TYPE_BLE_DEV                     0xCC



typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;

typedef void* DEV_HANDLE;                       ///< 设备句柄
#define INVALID_DEV_HANDLE              0       ///< 无效设备句柄

/* 错误类型 */
#define ZN_ERR_CODE int
#define ZN_SUCCESS                      0       ///< 执行成功
#define ZN_ERR_GENERAL                  1       ///< 执行失败
#define ZN_ERR_PARAM                    2       ///< 参数传入错误
#define ZN_ERR_COMMUNICATE              3       ///< 通讯错误
#define ZN_ERR_NOT_CONNECT              4       ///< 未建立连接
#define ZN_ERR_DEV_RESPONSE             5       ///< 设备响应错误
#define ZN_ERR_DEV_TYPE_NOT_SUPPORT     6       ///< 设备类型不支持
#define ZN_ERR_DEV_NOT_LOAD_INFO        7       ///< 设备属性未加载
#define ZN_ERR_PROPERTY_NOT_SUPPORT     8       ///< 属性项不支持
#define ZN_ERR_PASSWORD_CHECK           9       ///< 密码校验失败
#define ZN_ERR_PARSE_DEV_DATA           10      ///< 设备数据解析错误
#define ZN_ERR_OPERATE_NOT_SUPPORT      11      ///< 操作命令不支持
#define ZN_ERR_UPGRADE_FILE_CHECK       12      ///< 升级文件校验失败
#define ZN_ERR_OPEN_COM                 13      ///< 串口打开失败
#define ZN_ERR_OPERATE_STOPED           14      ///< 操作被中止

//ble设备错误
#define ZN_ERR_BLE_DATA                 19      ///< 搜索数据为空

// 云设备错误 
#define ZN_ERR_CLOUD_LIB_ACCESS			51		///< 云设备操作库加载或者获取接口失败
#define ZN_ERR_CLOUD_CONNECT_HTTP_SVR   52		///< HTTP云服务器连接失败
#define ZN_ERR_CLOUD_CONNECT_MQTT_SVR   53		///< MQTT服务器连接失败
#define ZN_ERR_CLOUD_LOGIN				54		///< 用户登陆云服务器失败


/* 结构体按1字节对齐 */
#pragma pack(push,1)

/* 设备属性项 */ 
typedef struct _ZN_PROPERTY
{
    char name[64];
    char value[512];
} ZN_PROPERTY;

/* 设备连接方式 */
typedef enum _ZN_COMM_TYPE 
{
    ZN_COMM_UDP = 0,
    ZN_COMM_TCP,
    ZN_COMM_COM,
    ZN_COMM_CLOUD,
	ZN_COMM_BLE,
} ZN_COMM_TYPE;

/* 设备连接参数信息 */
typedef struct _ZN_COMM_INFO
{
    ZN_COMM_TYPE commType;
    union {
        /* TCP通信 */
        struct
        {
            char ip[16];
            uint16 port;
        }tcp;        
        /* 串口通信 */                
        struct
        {
            char port[32];              ///< 串口名, 如 COM1(windows)、/dev/ttyS0(linux)
            int baudrate;               ///< 波特率, 如 115200
            int dataBits;               ///< 数据位 5,6,7,8
            int stopBits;               ///< 停止位 1-1, 2-2, 3-1.5
            int parity;                 ///< 校验位 0-无校验, 1-奇校验, 2-偶校验
            int timeout;                ///< 通信超时（ms）
        }com;
        /* 云设备通信 */
        struct 
        {
			int devIndex;			    ///< 云设备索引号
            char id[64];			    ///< 云设备ID
        }cloud;

		/* ble设备通信 */
		struct
		{
			char device_name[64];			    ///< 设备名
			char device_mac[64];			    ///< 设备MAC
		}ble;
    };
    
} ZN_COMM_INFO;

/* 设备日志 */
typedef struct _ZN_DEV_LOG
{
    char* log;                          ///< 日志缓存地址, 由应用申请内存
    int size;                           ///< 缓存地址大小
} ZN_DEV_LOG;

/* 设备数据 */
typedef struct _ZN_DEV_DATA
{
    int cloudStatus;                    ///< 设备连接云状态，0-未连接，1-已连接
    char reserve[96];                   ///< 保留，以后扩展数据时修改保留字节大小，保持总共100字节，为了向后兼容
} ZN_DEV_DATA;

/* 云服务器信息 */ 
typedef struct _ZN_CLOUD_SVR_INFO
{
	char httpSvr[128];					///< 用户服务器地址
	uint16 httpSvrPort;					///< 用户服务器端口
	char dataSvr[128];					///< 数据服务器地址
	uint16 dataSvrPort;					///< 数据服务器端口
	char username[128];					///< 登陆用户名
	char password[128];					///< 用户密码
	char reserve[512];					///< 保留						
} ZN_CLOUD_SVR_INFO;		

#define ZN_CLOUD_MAX_DEVICES  100
#define ZN_CLOUD_MAX_CHANNEL  16

/* 云设备通道信息 */
typedef struct _ZN_CLOUD_CHNINFO
{
	uint8 enable;                       ///< 通道使能, 0-disable, 1-enable
	uint8 type;                         ///< 控制器类型, 0-CAN, 1-ISO CANFD, 2-Non-ISO CANFD
	uint8 isUpload;                     ///< 设备数据云上送使能, 0-不上送, 1-上送
	uint8 isDownload;                   ///< 数据下发至设备使能, 0-不支持下发, 1-支持下发
} ZN_CLOUD_CHNINFO;

/* 云设备信息 */
typedef struct _ZN_CLOUD_DEVINFO
{
	int devIndex;                       ///< 云设备索引号
    char name[64];                      ///< 云设备显示名称
	char type[64];                      ///< 云设备类型, 如can-common
	char id[64];                        ///< 设备云ID
	char owner[64];                     ///< 设备拥有者
	char model[64];                     ///< 设备模块类型, 如CANFDNET-400U
	char fwVer[16];                     ///< 固件版本号
	char hwVer[16];                     ///< 硬件版本号
	char serial[64];                    ///< 设备序列号
	int status;                         ///< 连接状态 0-在线, 1-离线
	uint8 bGpsUpload;                   ///< GPS数据上送使能, 0-不上送, 1-上送
	uint8 channelCnt;                   ///< 通道数量
	ZN_CLOUD_CHNINFO channels[ZN_CLOUD_MAX_CHANNEL]; ///< 通道信息
} ZN_CLOUD_DEVINFO;

/* 云用户信息 */
typedef struct _ZN_CLOUD_USER_DATA
{
	char username[64];                  ///< 用户名        
	char mobile[64];                    ///< 电话号码
	uint32 devCnt;                      ///< 设备数量
	ZN_CLOUD_DEVINFO devices[ZN_CLOUD_MAX_DEVICES]; ///< 设备信息
} ZN_CLOUD_USER_DATA;

/* 命令列表 */
typedef enum _ZN_CMD
{
    ZN_CMD_BIND_IP = 0,                         ///< 绑定网卡IP, arg1->char* 传入IP字符串。
    ZN_CMD_CLEAR_BIND_IP = 1,                   ///< 清除网卡绑定。
    ZN_CMD_GET_DEV_LOG_SIZE = 2,                ///< 获取设备日志数据长度, arg1->int* 传出日志长度。
    ZN_CMD_GET_DEV_LOG = 3,                     ///< 获取设备日志数据，arg1->ZN_DEV_LOG* 传出日志数据。
    ZN_CMD_CLEAR_DEV_LOG = 4,                   ///< 清除设备日志，arg1->char* 传入密码字符串。
    ZN_CMD_QUERY_DEV_DATA = 5,                  ///< 查询设备状态数据，arg1->ZN_DEV_DATA* 传出设备数据。
    ZN_CMD_TRY_STOP_OPERATE = 6,                ///< 尝试停止正在执行的操作,使操作立即返回。某些操作可能无法中止，应用仍需等待操作自行结束。
    ZN_CMD_CONN_BLUE_MASTER = 7,                ///< CANFDBlue设备连接其他蓝牙设备，arg1->char* 传入目标MAC字符串; arg2->int 传入响应超时时间ms; arg3->int* 传出连接结果，0-连接成功，1-连接失败。
    ZN_CMD_DISCONN_BLUE_MASTER = 8,             ///< CANFDBlue设备断开连接的蓝牙设备，arg1->char* 传入目标MAC字符串。

    ZN_CMD_CLOUD_SERVER_LOGIN = 51,             ///< 登陆云服务器，获取云设备列表, arg1->ZN_CLOUD_SVR_INFO* 传入服务器信息; arg2->ZN_CLOUD_USER_DATA* 传出用户设备信息。
	ZN_CMD_CLOUD_SERVER_LOGOUT = 52,	        ///< 登出云服务器

    /* 测试指令 */
	ZN_CMD_TEST_MODE_SWITCH = 100,              ///< 切换生产测试模式，arg1->int 传入控制, 1-进入测试模式，0-退出测试模式。
	ZN_CMD_TEST_START_SELF_TEST = 101,          ///< 启动设备自测项，测试项目由设备自行定义。测试时间可能比较久，需预留足够的超时时间。
	ZN_CMD_TEST_QUERY_SELF_TEST = 102,          ///< 查询设备自测项结果, arg1->int* 传出测试结果代码, 结果代码具体参考配置协议文档。
	ZN_CMD_TEST_LED = 103,                      ///< 测试LED灯，arg1->int 传入控制，1-执行测试，0-停止测试。（CANFDNET、CANFDWIFI）
    ZN_CMD_TEST_WRITE_MAC = 104,                ///< 烧写MAC地址，arg1->char* 传入字符串。
    ZN_CMD_TEST_WRITE_SECRET_KEY = 105,         ///< 烧写加密密钥，arg1->char* 传入秘钥字符串。
    ZN_CMD_TEST_START_CAN_TEST = 106,           ///< 启动CAN通讯设备自测。
    ZN_CMD_TEST_QUERY_CAN_TEST = 107,           ///< 查询CAN通讯测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_FLASH_TEST = 108,         ///< 启动FALSH设备自测。
    ZN_CMD_TEST_QUERY_FLASH_TEST = 109,         ///< 查询FALSH测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_KEY_TEST = 110,           ///< 启动按键测试。
    ZN_CMD_TEST_QUERY_KEY_TEST = 111,           ///< 查询按键测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_EMMC_TEST = 112,          ///< 启动eMMC设备自测。
    ZN_CMD_TEST_QUERY_EMMC_TEST = 113,          ///< 查询eMMC测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_SD_TEST = 114,            ///< 启动SD卡测试。
    ZN_CMD_TEST_QUERY_SD_TEST = 115,            ///< 查询SD卡测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_RTC_TEST = 116,           ///< 启动RTC测试，arg1->char* 传入当前系统时间(格式为"2020-07-28T20:40:36.125")。
    ZN_CMD_TEST_QUERY_RTC_TEST = 117,           ///< 查询RTC测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_BUZZER = 118,                   ///< 蜂鸣器测试。arg1->int 传入控制，1-执行测试，0-停止测试。
	ZN_CMD_TEST_START_LIN_TEST = 119,			///< 启动LIN测试。
	ZN_CMD_TEST_QUERY_LIN_TEST = 120,			///< 查询LIN测试结果，arg1->int* 传出测试结果代码。
	ZN_CMD_TEST_START_DIDO_TEST = 121,			///< 启动DIDO测试。
	ZN_CMD_TEST_QUERY_DIDO_TEST = 122,			///< 查询DIDO测试结果，arg1->int* 传出测试结果代码。
	ZN_CMD_TEST_START_4G_TEST = 123,			///< 启动4G测试。
	ZN_CMD_TEST_QUERY_4G_TEST = 124,			///< 查询4G测试结果，arg1->int* 传出测试结果代码。
	ZN_CMD_TEST_START_WIFI_TEST = 125,			///< 启动WIFI测试。
	ZN_CMD_TEST_QUERY_WIFI_TEST = 126,			///< 查询WIFI测试结果，arg1->int* 传出测试结果代码。
	ZN_CMD_TEST_START_CARNET_TEST = 127,		///< 启动车载以太网测试。
	ZN_CMD_TEST_QUERY_CARNET_TEST = 128,		///< 查询车载以太网测试结果，arg1->int* 传出测试结果代码。
	ZN_CMD_TEST_START_GPS_TEST = 129,			///< 启动GPS测试。
	ZN_CMD_TEST_QUERY_GPS_TEST = 130,			///< 查询GPS测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_BLUETH_TEST = 131,		///< 启动蓝牙测试，arg1->char* 传入辅助设备MAC地址(如“00:14:97:00:00:01”)。
	ZN_CMD_TEST_QUERY_BLUETH_TEST = 132,		///< 查询蓝牙测试结果，arg1->int* 传出测试结果代码。
    ZN_CMD_TEST_START_ETHERNET_TEST = 133,		///< 启动以太网测试。
	ZN_CMD_TEST_QUERY_ETHERNET_TEST = 134,		///< 查询以太网测试结果，arg1->int* 传出测试结果代码。
    
	/* 老化测试指令 */
	ZN_CMD_TEST_START_AGING_TEST = 200,         ///< 启动设备老化测试, arg1->char* 传入当前系统时间(格式为"2020-07-28T20:40:36.125"); CANFDBLUE传入辅助设备MAC地址(如“00:14:97:00:00:01”)。
	ZN_CMD_TEST_CLEAR_AGING_DATA = 201,         ///< 清除设备老化测试数据。
	ZN_CMD_TEST_QUERY_AGING_DATA = 202,         ///< 查询设备老化测试数据，arg1->char[] 传出测试结果json字符串, arg2->int 为arg1数组大小。

} ZN_CMD;

/* 升级进度, ctx-上下文参数，progress-进度（0~100) */
typedef void(*ZN_UpgradeCb)(void* ctx, float progress);
#pragma pack(pop)

#ifdef WIN32
#define FUNCALL __stdcall 
#else
#define FUNCALL 
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 搜索设备(UDP)
 * @note 不清除上次搜索缓存，可多次调用。
 * @param[in] timeout 接收超时(ms)。 
 * @param[in] ip 指定IP搜索，为空时采用255.255.255.255广播搜索。 
 * @return 返回错误码
 */  
ZN_ERR_CODE FUNCALL ZN_SearchDevice(uint32 timeout = 2000, const char* ip = 0);

/**
* @brief 搜索ble设备, 暂不支持
* @note 清除上次搜索缓存，可多次调用。
* @param[in] scanTimes 蓝牙搜索时间(ms)。
* @param[out] flag_count 指定搜索设备数量，在规定时间内把实际搜索到的设备数量返回
* @param[out] device 扫描结果返回设备名数组
* @return 返回错误码
*/
// ZN_ERR_CODE FUNCALL ZN_GetBluetoothList(uint32 scanTimes = 5000, uint32 *flag_count = (uint32 *)20, char *device_name[] = { 0 }, char *device_mac[] = { 0 });

/**
 * @brief 手动添加设备
 * @note 如串口设备、云设备，先手动添加设备，再连接设备。
 * @param[in] devType 设备类型。
 * @return 返回设备句柄，失败时返回INVALID_DEV_HANDLE。
 */
DEV_HANDLE FUNCALL ZN_AddDevice(uint8 devType);

/**
 * @brief 移除指定设备
 * @param[in] hDev 设备句柄。
 * @return 返回错误码
 */
ZN_ERR_CODE FUNCALL ZN_DeleteDevice(DEV_HANDLE hDev);

/**
 * @brief 清空设备
 * @return 返回错误码
 */
ZN_ERR_CODE FUNCALL ZN_ClearDevice();

/**
 * @brief 获取设备数量
 * @note 包含搜索到的设备和手动添加的设备。
 * @return 返回设备数量
 */
uint32 FUNCALL ZN_GetDeviceCount();

/**
 * @brief 获取设备句柄
 * @param[in] idx 设备索引号。
 * @return 返回设备句柄，失败时返回INVALID_DEV_HANDLE。
 */
DEV_HANDLE FUNCALL ZN_GetDeviceAt(uint32 idx);

/**
 * @brief 建立设备连接
 * @note UDP通信设备可以不执行此操作。
 * @param[in] hDev 设备句柄。
 * @param[in] info 通信方式及参数。
 * @return 返回错误码
 */
ZN_ERR_CODE FUNCALL ZN_Connect(DEV_HANDLE hDev, const ZN_COMM_INFO* info);

/**
 * @brief 设备连接是否建立
 * @param[in] hDev 设备句柄。
 * @return 返回1-是，0-否。
 */
int FUNCALL ZN_IsConnected(DEV_HANDLE hDev);

/**
 * @brief 断开设备连接
 * @param[in] hDev 设备句柄。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_Disonnect(DEV_HANDLE hDev);

/**
 * @brief 加载设备属性
 * @note 从设备端读取所有参数属性信息。
 * @param[in] hDev 设备句柄。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_LoadInfo(DEV_HANDLE hDev);

/**
 * @brief 获取属性项
 * @note 从已加载的设备属性中，根据传入的属性名，获取相应的属性值。
 * @param[in] hDev 设备句柄。
 * @param[in] propName 属性名称。
 * @param[out] prop 属性项结构。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_GetProperty(DEV_HANDLE hDev, const char* propName, ZN_PROPERTY* prop);

/**
 * @brief 更改属性项
 * @note 在已加载的设备属性中修改指定的属性值，此时还并未修改设备端的属性。
 * @param[in] hDev 设备句柄。
 * @param[in] prop 属性项结构。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_SetProperty(DEV_HANDLE hDev, const ZN_PROPERTY* prop);

/**
 * @brief 提交设备属性修改
 * @note 将所有更改的属性项提交至设备端。
 * @param[in] hDev 设备句柄。
 * @param[in] pwd 设备操作密码, 云设备无需密码。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_SubmitInfo(DEV_HANDLE hDev, const char* pwd);

/**
 * @brief 复位设备
 * @note 成功执行此命令后，设备将立即重启。
 * @param[in] hDev 设备句柄。
 * @param[in] pwd 设备操作密码。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_Reset(DEV_HANDLE hDev, const char* pwd); 

/**
 * @brief 设备恢复出厂设置
 * @note 成功执行此命令后，设备将还原所有属性值为初始状态，并重启设备。
 * @param[in] hDev 设备句柄。
 * @param[in] pwd 设备操作密码。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_FactoryReset(DEV_HANDLE hDev, const char* pwd); 

/**
 * @brief 设备固件升级
 * @param[in] hDev 设备句柄。
 * @param[in] data 固件数据; 云设备时传入固件文件路径字符串。
 * @param[in] len 固件数据长度。
 * @param[in] arg 额外参数，设备操作密码字符串。
 * @param[in] cb 升级进度回调函数。
 * @param[in] ctx 回调函数上下文参数。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_Upgrade(DEV_HANDLE hDev, const uint8* data, uint32 len, void* arg, 
    ZN_UpgradeCb cb = 0, void* ctx = 0);

/**
 * @brief 操作命令通用接口
 * @note 扩展命令接口，用于提供各类型设备实现其特有功能。
 * @param[in] cmd 命令码。
 * @param[in] hDev 设备句柄，如无需指定设备可为INVALID_DEV_HANDLE。
 * @param[in,out] arg1 ~ arg5 额外参数信息，根据不同的命令码传入对应的参数信息。
 * @return 返回错误码。
 */
ZN_ERR_CODE FUNCALL ZN_ExecCmd(ZN_CMD cmd, DEV_HANDLE hDev, void* arg1 = 0, void* arg2 = 0, void* arg3 = 0, void* arg4 = 0, void* arg5 = 0);


#ifdef __cplusplus
}
#endif

#endif