#ifndef NET_CONFIG_H_
#define NET_CONFIG_H_

/* �豸���� */
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

typedef void* DEV_HANDLE;                       ///< �豸���
#define INVALID_DEV_HANDLE              0       ///< ��Ч�豸���

/* �������� */
#define ZN_ERR_CODE int
#define ZN_SUCCESS                      0       ///< ִ�гɹ�
#define ZN_ERR_GENERAL                  1       ///< ִ��ʧ��
#define ZN_ERR_PARAM                    2       ///< �����������
#define ZN_ERR_COMMUNICATE              3       ///< ͨѶ����
#define ZN_ERR_NOT_CONNECT              4       ///< δ��������
#define ZN_ERR_DEV_RESPONSE             5       ///< �豸��Ӧ����
#define ZN_ERR_DEV_TYPE_NOT_SUPPORT     6       ///< �豸���Ͳ�֧��
#define ZN_ERR_DEV_NOT_LOAD_INFO        7       ///< �豸����δ����
#define ZN_ERR_PROPERTY_NOT_SUPPORT     8       ///< �����֧��
#define ZN_ERR_PASSWORD_CHECK           9       ///< ����У��ʧ��
#define ZN_ERR_PARSE_DEV_DATA           10      ///< �豸���ݽ�������
#define ZN_ERR_OPERATE_NOT_SUPPORT      11      ///< �������֧��
#define ZN_ERR_UPGRADE_FILE_CHECK       12      ///< �����ļ�У��ʧ��
#define ZN_ERR_OPEN_COM                 13      ///< ���ڴ�ʧ��
#define ZN_ERR_OPERATE_STOPED           14      ///< ��������ֹ

//ble�豸����
#define ZN_ERR_BLE_DATA                 19      ///< ��������Ϊ��

// ���豸���� 
#define ZN_ERR_CLOUD_LIB_ACCESS			51		///< ���豸��������ػ��߻�ȡ�ӿ�ʧ��
#define ZN_ERR_CLOUD_CONNECT_HTTP_SVR   52		///< HTTP�Ʒ���������ʧ��
#define ZN_ERR_CLOUD_CONNECT_MQTT_SVR   53		///< MQTT����������ʧ��
#define ZN_ERR_CLOUD_LOGIN				54		///< �û���½�Ʒ�����ʧ��


/* �ṹ�尴1�ֽڶ��� */
#pragma pack(push,1)

/* �豸������ */ 
typedef struct _ZN_PROPERTY
{
    char name[64];
    char value[512];
} ZN_PROPERTY;

/* �豸���ӷ�ʽ */
typedef enum _ZN_COMM_TYPE 
{
    ZN_COMM_UDP = 0,
    ZN_COMM_TCP,
    ZN_COMM_COM,
    ZN_COMM_CLOUD,
	ZN_COMM_BLE,
} ZN_COMM_TYPE;

/* �豸���Ӳ�����Ϣ */
typedef struct _ZN_COMM_INFO
{
    ZN_COMM_TYPE commType;
    union {
        /* TCPͨ�� */
        struct
        {
            char ip[16];
            uint16 port;
        }tcp;        
        /* ����ͨ�� */                
        struct
        {
            char port[32];              ///< ������, �� COM1(windows)��/dev/ttyS0(linux)
            int baudrate;               ///< ������, �� 115200
            int dataBits;               ///< ����λ 5,6,7,8
            int stopBits;               ///< ֹͣλ 1-1, 2-2, 3-1.5
            int parity;                 ///< У��λ 0-��У��, 1-��У��, 2-żУ��
            int timeout;                ///< ͨ�ų�ʱ��ms��
        }com;
        /* ���豸ͨ�� */
        struct 
        {
			int devIndex;			    ///< ���豸������
            char id[64];			    ///< ���豸ID
        }cloud;

		/* ble�豸ͨ�� */
		struct
		{
			char device_name[64];			    ///< �豸��
			char device_mac[64];			    ///< �豸MAC
		}ble;
    };
    
} ZN_COMM_INFO;

/* �豸��־ */
typedef struct _ZN_DEV_LOG
{
    char* log;                          ///< ��־�����ַ, ��Ӧ�������ڴ�
    int size;                           ///< �����ַ��С
} ZN_DEV_LOG;

/* �豸���� */
typedef struct _ZN_DEV_DATA
{
    int cloudStatus;                    ///< �豸������״̬��0-δ���ӣ�1-������
    char reserve[96];                   ///< �������Ժ���չ����ʱ�޸ı����ֽڴ�С�������ܹ�100�ֽڣ�Ϊ��������
} ZN_DEV_DATA;

/* �Ʒ�������Ϣ */ 
typedef struct _ZN_CLOUD_SVR_INFO
{
	char httpSvr[128];					///< �û���������ַ
	uint16 httpSvrPort;					///< �û��������˿�
	char dataSvr[128];					///< ���ݷ�������ַ
	uint16 dataSvrPort;					///< ���ݷ������˿�
	char username[128];					///< ��½�û���
	char password[128];					///< �û�����
	char reserve[512];					///< ����						
} ZN_CLOUD_SVR_INFO;		

#define ZN_CLOUD_MAX_DEVICES  100
#define ZN_CLOUD_MAX_CHANNEL  16

/* ���豸ͨ����Ϣ */
typedef struct _ZN_CLOUD_CHNINFO
{
	uint8 enable;                       ///< ͨ��ʹ��, 0-disable, 1-enable
	uint8 type;                         ///< ����������, 0-CAN, 1-ISO CANFD, 2-Non-ISO CANFD
	uint8 isUpload;                     ///< �豸����������ʹ��, 0-������, 1-����
	uint8 isDownload;                   ///< �����·����豸ʹ��, 0-��֧���·�, 1-֧���·�
} ZN_CLOUD_CHNINFO;

/* ���豸��Ϣ */
typedef struct _ZN_CLOUD_DEVINFO
{
	int devIndex;                       ///< ���豸������
    char name[64];                      ///< ���豸��ʾ����
	char type[64];                      ///< ���豸����, ��can-common
	char id[64];                        ///< �豸��ID
	char owner[64];                     ///< �豸ӵ����
	char model[64];                     ///< �豸ģ������, ��CANFDNET-400U
	char fwVer[16];                     ///< �̼��汾��
	char hwVer[16];                     ///< Ӳ���汾��
	char serial[64];                    ///< �豸���к�
	int status;                         ///< ����״̬ 0-����, 1-����
	uint8 bGpsUpload;                   ///< GPS��������ʹ��, 0-������, 1-����
	uint8 channelCnt;                   ///< ͨ������
	ZN_CLOUD_CHNINFO channels[ZN_CLOUD_MAX_CHANNEL]; ///< ͨ����Ϣ
} ZN_CLOUD_DEVINFO;

/* ���û���Ϣ */
typedef struct _ZN_CLOUD_USER_DATA
{
	char username[64];                  ///< �û���        
	char mobile[64];                    ///< �绰����
	uint32 devCnt;                      ///< �豸����
	ZN_CLOUD_DEVINFO devices[ZN_CLOUD_MAX_DEVICES]; ///< �豸��Ϣ
} ZN_CLOUD_USER_DATA;

/* �����б� */
typedef enum _ZN_CMD
{
    ZN_CMD_BIND_IP = 0,                         ///< ������IP, arg1->char* ����IP�ַ�����
    ZN_CMD_CLEAR_BIND_IP = 1,                   ///< ��������󶨡�
    ZN_CMD_GET_DEV_LOG_SIZE = 2,                ///< ��ȡ�豸��־���ݳ���, arg1->int* ������־���ȡ�
    ZN_CMD_GET_DEV_LOG = 3,                     ///< ��ȡ�豸��־���ݣ�arg1->ZN_DEV_LOG* ������־���ݡ�
    ZN_CMD_CLEAR_DEV_LOG = 4,                   ///< ����豸��־��arg1->char* ���������ַ�����
    ZN_CMD_QUERY_DEV_DATA = 5,                  ///< ��ѯ�豸״̬���ݣ�arg1->ZN_DEV_DATA* �����豸���ݡ�
    ZN_CMD_TRY_STOP_OPERATE = 6,                ///< ����ֹͣ����ִ�еĲ���,ʹ�����������ء�ĳЩ���������޷���ֹ��Ӧ������ȴ��������н�����
    ZN_CMD_CONN_BLUE_MASTER = 7,                ///< CANFDBlue�豸�������������豸��arg1->char* ����Ŀ��MAC�ַ���; arg2->int ������Ӧ��ʱʱ��ms; arg3->int* �������ӽ����0-���ӳɹ���1-����ʧ�ܡ�
    ZN_CMD_DISCONN_BLUE_MASTER = 8,             ///< CANFDBlue�豸�Ͽ����ӵ������豸��arg1->char* ����Ŀ��MAC�ַ�����

    ZN_CMD_CLOUD_SERVER_LOGIN = 51,             ///< ��½�Ʒ���������ȡ���豸�б�, arg1->ZN_CLOUD_SVR_INFO* �����������Ϣ; arg2->ZN_CLOUD_USER_DATA* �����û��豸��Ϣ��
	ZN_CMD_CLOUD_SERVER_LOGOUT = 52,	        ///< �ǳ��Ʒ�����

    /* ����ָ�� */
	ZN_CMD_TEST_MODE_SWITCH = 100,              ///< �л���������ģʽ��arg1->int �������, 1-�������ģʽ��0-�˳�����ģʽ��
	ZN_CMD_TEST_START_SELF_TEST = 101,          ///< �����豸�Բ��������Ŀ���豸���ж��塣����ʱ����ܱȽϾã���Ԥ���㹻�ĳ�ʱʱ�䡣
	ZN_CMD_TEST_QUERY_SELF_TEST = 102,          ///< ��ѯ�豸�Բ�����, arg1->int* �������Խ������, ����������ο�����Э���ĵ���
	ZN_CMD_TEST_LED = 103,                      ///< ����LED�ƣ�arg1->int ������ƣ�1-ִ�в��ԣ�0-ֹͣ���ԡ���CANFDNET��CANFDWIFI��
    ZN_CMD_TEST_WRITE_MAC = 104,                ///< ��дMAC��ַ��arg1->char* �����ַ�����
    ZN_CMD_TEST_WRITE_SECRET_KEY = 105,         ///< ��д������Կ��arg1->char* ������Կ�ַ�����
    ZN_CMD_TEST_START_CAN_TEST = 106,           ///< ����CANͨѶ�豸�Բ⡣
    ZN_CMD_TEST_QUERY_CAN_TEST = 107,           ///< ��ѯCANͨѶ���Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_FLASH_TEST = 108,         ///< ����FALSH�豸�Բ⡣
    ZN_CMD_TEST_QUERY_FLASH_TEST = 109,         ///< ��ѯFALSH���Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_KEY_TEST = 110,           ///< �����������ԡ�
    ZN_CMD_TEST_QUERY_KEY_TEST = 111,           ///< ��ѯ�������Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_EMMC_TEST = 112,          ///< ����eMMC�豸�Բ⡣
    ZN_CMD_TEST_QUERY_EMMC_TEST = 113,          ///< ��ѯeMMC���Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_SD_TEST = 114,            ///< ����SD�����ԡ�
    ZN_CMD_TEST_QUERY_SD_TEST = 115,            ///< ��ѯSD�����Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_RTC_TEST = 116,           ///< ����RTC���ԣ�arg1->char* ���뵱ǰϵͳʱ��(��ʽΪ"2020-07-28T20:40:36.125")��
    ZN_CMD_TEST_QUERY_RTC_TEST = 117,           ///< ��ѯRTC���Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_BUZZER = 118,                   ///< ���������ԡ�arg1->int ������ƣ�1-ִ�в��ԣ�0-ֹͣ���ԡ�
	ZN_CMD_TEST_START_LIN_TEST = 119,			///< ����LIN���ԡ�
	ZN_CMD_TEST_QUERY_LIN_TEST = 120,			///< ��ѯLIN���Խ����arg1->int* �������Խ�����롣
	ZN_CMD_TEST_START_DIDO_TEST = 121,			///< ����DIDO���ԡ�
	ZN_CMD_TEST_QUERY_DIDO_TEST = 122,			///< ��ѯDIDO���Խ����arg1->int* �������Խ�����롣
	ZN_CMD_TEST_START_4G_TEST = 123,			///< ����4G���ԡ�
	ZN_CMD_TEST_QUERY_4G_TEST = 124,			///< ��ѯ4G���Խ����arg1->int* �������Խ�����롣
	ZN_CMD_TEST_START_WIFI_TEST = 125,			///< ����WIFI���ԡ�
	ZN_CMD_TEST_QUERY_WIFI_TEST = 126,			///< ��ѯWIFI���Խ����arg1->int* �������Խ�����롣
	ZN_CMD_TEST_START_CARNET_TEST = 127,		///< ����������̫�����ԡ�
	ZN_CMD_TEST_QUERY_CARNET_TEST = 128,		///< ��ѯ������̫�����Խ����arg1->int* �������Խ�����롣
	ZN_CMD_TEST_START_GPS_TEST = 129,			///< ����GPS���ԡ�
	ZN_CMD_TEST_QUERY_GPS_TEST = 130,			///< ��ѯGPS���Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_BLUETH_TEST = 131,		///< �����������ԣ�arg1->char* ���븨���豸MAC��ַ(�硰00:14:97:00:00:01��)��
	ZN_CMD_TEST_QUERY_BLUETH_TEST = 132,		///< ��ѯ�������Խ����arg1->int* �������Խ�����롣
    ZN_CMD_TEST_START_ETHERNET_TEST = 133,		///< ������̫�����ԡ�
	ZN_CMD_TEST_QUERY_ETHERNET_TEST = 134,		///< ��ѯ��̫�����Խ����arg1->int* �������Խ�����롣
    
	/* �ϻ�����ָ�� */
	ZN_CMD_TEST_START_AGING_TEST = 200,         ///< �����豸�ϻ�����, arg1->char* ���뵱ǰϵͳʱ��(��ʽΪ"2020-07-28T20:40:36.125"); CANFDBLUE���븨���豸MAC��ַ(�硰00:14:97:00:00:01��)��
	ZN_CMD_TEST_CLEAR_AGING_DATA = 201,         ///< ����豸�ϻ��������ݡ�
	ZN_CMD_TEST_QUERY_AGING_DATA = 202,         ///< ��ѯ�豸�ϻ��������ݣ�arg1->char[] �������Խ��json�ַ���, arg2->int Ϊarg1�����С��

} ZN_CMD;

/* ��������, ctx-�����Ĳ�����progress-���ȣ�0~100) */
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
 * @brief �����豸(UDP)
 * @note ������ϴ��������棬�ɶ�ε��á�
 * @param[in] timeout ���ճ�ʱ(ms)�� 
 * @param[in] ip ָ��IP������Ϊ��ʱ����255.255.255.255�㲥������ 
 * @return ���ش�����
 */  
ZN_ERR_CODE FUNCALL ZN_SearchDevice(uint32 timeout = 2000, const char* ip = 0);

/**
* @brief ����ble�豸, �ݲ�֧��
* @note ����ϴ��������棬�ɶ�ε��á�
* @param[in] scanTimes ��������ʱ��(ms)��
* @param[out] flag_count ָ�������豸�������ڹ涨ʱ���ڰ�ʵ�����������豸��������
* @param[out] device ɨ���������豸������
* @return ���ش�����
*/
// ZN_ERR_CODE FUNCALL ZN_GetBluetoothList(uint32 scanTimes = 5000, uint32 *flag_count = (uint32 *)20, char *device_name[] = { 0 }, char *device_mac[] = { 0 });

/**
 * @brief �ֶ�����豸
 * @note �紮���豸�����豸�����ֶ�����豸���������豸��
 * @param[in] devType �豸���͡�
 * @return �����豸�����ʧ��ʱ����INVALID_DEV_HANDLE��
 */
DEV_HANDLE FUNCALL ZN_AddDevice(uint8 devType);

/**
 * @brief �Ƴ�ָ���豸
 * @param[in] hDev �豸�����
 * @return ���ش�����
 */
ZN_ERR_CODE FUNCALL ZN_DeleteDevice(DEV_HANDLE hDev);

/**
 * @brief ����豸
 * @return ���ش�����
 */
ZN_ERR_CODE FUNCALL ZN_ClearDevice();

/**
 * @brief ��ȡ�豸����
 * @note �������������豸���ֶ���ӵ��豸��
 * @return �����豸����
 */
uint32 FUNCALL ZN_GetDeviceCount();

/**
 * @brief ��ȡ�豸���
 * @param[in] idx �豸�����š�
 * @return �����豸�����ʧ��ʱ����INVALID_DEV_HANDLE��
 */
DEV_HANDLE FUNCALL ZN_GetDeviceAt(uint32 idx);

/**
 * @brief �����豸����
 * @note UDPͨ���豸���Բ�ִ�д˲�����
 * @param[in] hDev �豸�����
 * @param[in] info ͨ�ŷ�ʽ��������
 * @return ���ش�����
 */
ZN_ERR_CODE FUNCALL ZN_Connect(DEV_HANDLE hDev, const ZN_COMM_INFO* info);

/**
 * @brief �豸�����Ƿ���
 * @param[in] hDev �豸�����
 * @return ����1-�ǣ�0-��
 */
int FUNCALL ZN_IsConnected(DEV_HANDLE hDev);

/**
 * @brief �Ͽ��豸����
 * @param[in] hDev �豸�����
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_Disonnect(DEV_HANDLE hDev);

/**
 * @brief �����豸����
 * @note ���豸�˶�ȡ���в���������Ϣ��
 * @param[in] hDev �豸�����
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_LoadInfo(DEV_HANDLE hDev);

/**
 * @brief ��ȡ������
 * @note ���Ѽ��ص��豸�����У����ݴ��������������ȡ��Ӧ������ֵ��
 * @param[in] hDev �豸�����
 * @param[in] propName �������ơ�
 * @param[out] prop ������ṹ��
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_GetProperty(DEV_HANDLE hDev, const char* propName, ZN_PROPERTY* prop);

/**
 * @brief ����������
 * @note ���Ѽ��ص��豸�������޸�ָ��������ֵ����ʱ����δ�޸��豸�˵����ԡ�
 * @param[in] hDev �豸�����
 * @param[in] prop ������ṹ��
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_SetProperty(DEV_HANDLE hDev, const ZN_PROPERTY* prop);

/**
 * @brief �ύ�豸�����޸�
 * @note �����и��ĵ��������ύ���豸�ˡ�
 * @param[in] hDev �豸�����
 * @param[in] pwd �豸��������, ���豸�������롣
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_SubmitInfo(DEV_HANDLE hDev, const char* pwd);

/**
 * @brief ��λ�豸
 * @note �ɹ�ִ�д�������豸������������
 * @param[in] hDev �豸�����
 * @param[in] pwd �豸�������롣
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_Reset(DEV_HANDLE hDev, const char* pwd); 

/**
 * @brief �豸�ָ���������
 * @note �ɹ�ִ�д�������豸����ԭ��������ֵΪ��ʼ״̬���������豸��
 * @param[in] hDev �豸�����
 * @param[in] pwd �豸�������롣
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_FactoryReset(DEV_HANDLE hDev, const char* pwd); 

/**
 * @brief �豸�̼�����
 * @param[in] hDev �豸�����
 * @param[in] data �̼�����; ���豸ʱ����̼��ļ�·���ַ�����
 * @param[in] len �̼����ݳ��ȡ�
 * @param[in] arg ����������豸���������ַ�����
 * @param[in] cb �������Ȼص�������
 * @param[in] ctx �ص����������Ĳ�����
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_Upgrade(DEV_HANDLE hDev, const uint8* data, uint32 len, void* arg, 
    ZN_UpgradeCb cb = 0, void* ctx = 0);

/**
 * @brief ��������ͨ�ýӿ�
 * @note ��չ����ӿڣ������ṩ�������豸ʵ�������й��ܡ�
 * @param[in] cmd �����롣
 * @param[in] hDev �豸�����������ָ���豸��ΪINVALID_DEV_HANDLE��
 * @param[in,out] arg1 ~ arg5 ���������Ϣ�����ݲ�ͬ�������봫���Ӧ�Ĳ�����Ϣ��
 * @return ���ش����롣
 */
ZN_ERR_CODE FUNCALL ZN_ExecCmd(ZN_CMD cmd, DEV_HANDLE hDev, void* arg1 = 0, void* arg2 = 0, void* arg3 = 0, void* arg4 = 0, void* arg5 = 0);


#ifdef __cplusplus
}
#endif

#endif