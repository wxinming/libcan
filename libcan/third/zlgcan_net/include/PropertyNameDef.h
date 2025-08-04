#ifndef PROPERTY_NAME_DEF_H_
#define PROPERTY_NAME_DEF_H_

///< ��������������
#define NAME_FIRMWARE_VER                           "FIRMWARE_VER"
#define NAME_HARDWARE_VER                           "HARDWARE_VER"
#define NAME_SERIES_NUM                             "SERIES_NUM"
#define NAME_DEVIP                                  "IP"
#define NAME_DEVMAC                                 "MAC"
#define NAME_DEVTYPE                                "DEV_TYPE"
#define NAME_IP_MODE                                "IP_MODE"
#define NAME_TCP_CFG_PORT                           "TCP_CFG_PORT"
#define NAME_CLOUD_SN								"CLOUD_SN"
#define NAME_DEVNAME                                "NAME"
#define NAME_PROTOCOL_VER                           "PROTOCOL_VER"

///< CANET
#define NAME_DEVPWD                                 "PASS"
#define NAME_SPEED_MODE                             "SPEED_MODE"
#define NAME_COM_COUNT                              "COM_COUNT"
#define NAME_DEVMASK                                "MASK"
#define NAME_DEVMARK                                "MARK"
#define NAME_GATE                                   "GATEWAY"
#define NAME_DNSSERVER                              "DNS"
#define NAME_CONN_NUM                               "CONN_NUM"
#define NAME_WEBPORT                                "WEB_PORT"
#define NAME_CMDPORT                                "CMD_PORT"
#define NAME_CANTCPDISCON                           "CANTCPDISCON"
#define NAME_CAN_N_CAN_ENABLE                       "CAN%d_CAN_ENABLE"
#define NAME_CAN_N_TCPWORKMD                        "CAN%d_TCPWORK_MD"
#define NAME_CAN_N_WORKPORT                         "CAN%d_WORK_PORT"
#define NAME_CAN_N_TIMEOUT                          "CAN%d_TIMEOUT"
#define NAME_CAN_N_AT                               "CAN%d_AT"
#define NAME_CAN_N_BAUD                             "CAN%d_BAUD"
#define NAME_CAN_N_LISTTENMD                        "CAN%d_LISTEN_MD"
#define NAME_CAN_N_PACK                             "CAN%d_PACK"
#define NAME_CAN_N_PACKTS                           "CAN%d_PACKTS"
#define NAME_CAN_N_BUFCLEAR                         "CAN%d_BUF_CLEAR"
#define NAME_CAN_N_AF                               "CAN%d_AF"            
#define NAME_CAN_N_STA_TOP                          "CAN%d_STANDARD_TOP"  
#define NAME_CAN_N_STA_LOW                          "CAN%d_STANDARD_LOW"  
#define NAME_CAN_N_ACC_CODE                         "CAN%d_ACC_CODE"  
#define NAME_CAN_N_ACC_MASK                         "CAN%d_ACC_MASK"  
#define NAME_CAN_N_EXT_TOP                          "CAN%d_EXTEND_TOP"    
#define NAME_CAN_N_EXT_LOW                          "CAN%d_EXTEND_LOW"    
#define NAME_CAN_N_TCPTURBO                         "CAN%d_TCP_TURBO"
#define NAME_CAN_N_TCPNOTIFY                        "CAN%d_NOTIFY_PORT"
#define NAME_CAN_N_RECVBUFF                         "CAN%d_RECIEVE_BUFF"
#define NAME_CAN_N_SENDBUFF                         "CAN%d_SEND_BUFF"
#define NAME_CAN_N_BUFFSTRATEGY                     "CAN%d_SENDBUFF_STRATEGY"
#define NAME_CAN_N_MININTERVAL                      "CAN%d_MININTERVAL"
#define NAME_CAN_N_ROUTE                            "CAN%d_ROUTE"
#define NAME_CAN_N_TIMER_TX_COUNT                   "CAN%d_TIMER_TX_COUNT"
#define NAME_CAN_N_TIMER_TX_N_INDEX                 "CAN%d_TIMER_TX%d_INDEX"
#define NAME_CAN_N_TIMER_TX_N_ENABLE                "CAN%d_TIMER_TX%d_ENABLE"
#define NAME_CAN_N_TIMER_TX_N_INTERVAL              "CAN%d_TIMER_TX%d_INTERVAL"
#define NAME_CAN_N_TIMER_TX_N_CANOBJ                "CAN%d_TIMER_TX%d_CANOBJ"
#define NAME_CAN_N_TCPCONN                          "CAN%d_TCP_CONN"
#define NAME_CAN_N_PORT_MD                          "CAN%d_IfFastenPort"
#define NAME_CAN_N_DESPORT_N                        "CAN%d_DES_PORT%d"     
#define NAME_CAN_N_DESMASK_N                        "CAN%d_MASK%d"         
#define NAME_CAN_N_DES_START_IP_N                   "CAN%d_DES_START_IP%d" 
#define NAME_CAN_N_DES_END_IP_N                     "CAN%d_DES_END_IP%d"

///< CANFDNET-200U     
#define NAME_CANFDNET_DEV_NAME                      NAME_DEVNAME                // �豸����
#define NAME_CANFDNET_DEV_PWD                       NAME_DEVPWD                 // �豸����
#define NAME_CANFDNET_CAN_N_ENABLE                  NAME_CAN_N_CAN_ENABLE       // ͨ��ʹ��
#define NAME_CANFDNET_CAN_N_TYPE                    "CAN%d_CAN_TYPE"            // ����������,CAN��Ŵ�1��ʼ
#define NAME_CANFDNET_CAN_N_MODE                    NAME_CAN_N_LISTTENMD        // ����ģʽ
#define NAME_CANFDNET_CAN_N_CLOCK                   "CAN%d_CLOCK"               // ������ʱ��
#define NAME_CANFDNET_CAN_N_TX_ATTEMPTS             "CAN%d_TX_ATTEMPTS"         // ����ʧ���ش���0-���ش�, 1-�ش�ֱ����ʱ
#define NAME_CANFDNET_CAN_N_NBAUD_TSEG1             "CAN%d_NBAUD_TSEG1"         // CAN�����ʻ�CANFD�ٲ���������λ��1
#define NAME_CANFDNET_CAN_N_NBAUD_TSEG2             "CAN%d_NBAUD_TSEG2"         // ��λ��2
#define NAME_CANFDNET_CAN_N_NBAUD_SJW               "CAN%d_NBAUD_SJW"           // ͬ����ת��� 
#define NAME_CANFDNET_CAN_N_NBAUD_BRP               "CAN%d_NBAUD_BRP"           // ʱ�ӷ�Ƶֵ
#define NAME_CANFDNET_CAN_N_DBAUD_TSEG1             "CAN%d_DBAUD_TSEG1"         // CANFD������������λ��1         
#define NAME_CANFDNET_CAN_N_DBAUD_TSEG2             "CAN%d_DBAUD_TSEG2"         // ��λ��2   
#define NAME_CANFDNET_CAN_N_DBAUD_SJW               "CAN%d_DBAUD_SJW"           // ͬ����ת��� 
#define NAME_CANFDNET_CAN_N_DBAUD_BRP               "CAN%d_DBAUD_BRP"           // ʱ�ӷ�Ƶֵ     
#define NAME_CANFDNET_CAN_N_USE_RESI                "CAN%d_USE_RESI"            // �ն˵��迪��
#define NAME_CANFDNET_CAN_N_NBAUD                   "CAN%d_NBAUD"               // �ٲ�������
#define NAME_CANFDNET_CAN_N_DBAUD                   "CAN%d_DBAUD"               // ����������
#define NAME_CANFDNET_CAN_N_BAUD_CUSTOM             "CAN%d_BAUD_CUSTOM"         // �Զ��岨����
#define NAME_CANFDNET_CAN_N_FILTER_MODE             "CAN%d_FILTER_MODE"         // �˲���ģʽ, ���16���˲�
#define NAME_CANFDNET_CAN_N_FILTER_N_ENABLE         "CAN%d_FILTER%d_ENABLE"     // �˲�����ʹ��, FILTER1~16
#define NAME_CANFDNET_CAN_N_FILTER_N_TYPE           "CAN%d_FILTER%d_TYPE"       // �˲�֡����
#define NAME_CANFDNET_CAN_N_FILTER_N_START          "CAN%d_FILTER%d_START"      // �˲���ʼID
#define NAME_CANFDNET_CAN_N_FILTER_N_END            "CAN%d_FILTER%d_END"        // �˲�����ID
#define NAME_CANFDNET_CAN_N_PSEND_ENABLE            "CAN%d_PSEND_ENABLE"        // ��ʱ����ʹ��, ���32����ʱ���ͣ����1��ʼ
#define NAME_CANFDNET_CAN_N_PSEND_N_ENABLE          "CAN%d_PSEND%d_ENABLE"      // ��Ϣʹ��
#define NAME_CANFDNET_CAN_N_PSEND_N_PERIOD          "CAN%d_PSEND%d_PERIOD"      // ���ķ�������
#define NAME_CANFDNET_CAN_N_PSEND_N_COUNT           "CAN%d_PSEND%d_COUNT"       // ���ķ��ʹ���
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGID           "CAN%d_PSEND%d_MSGID"       // ֡ID
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGFLAG         "CAN%d_PSEND%d_MSGFLAG"     // ֡��־
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGDATA         "CAN%d_PSEND%d_MSGDATA"     // ֡����, ʮ������������, �� "1,2,3,4"
#define NAME_CANFDNET_CAN_N_SEND_INTERVAL           NAME_CAN_N_MININTERVAL      // ���ķ��ͼ��
#define NAME_CANFDNET_CAN_N_SEND_BUFSIZE            NAME_CAN_N_SENDBUFF         // ���ͻ�������С
#define NAME_CANFDNET_CAN_N_SEND_BUFMODE            NAME_CAN_N_BUFFSTRATEGY     // ���ͻ���������
#define NAME_CANFDNET_CAN_N_BUSRATIO_ENABLE         "CAN%d_BUSRATIO_ENABLE"     // ����������ʹ��
#define NAME_CANFDNET_CAN_N_BUSRATIO_PERIOD         "CAN%d_BUSRATIO_PERIOD"     // ���������ʲɼ�����(ms)
#define NAME_CANFDNET_NIC_GENNIC_MAC                "GENNIC_MAC"                // ͨ������MAC��ַ
#define NAME_CANFDNET_NIC_GENNIC_DHCP               "GENNIC_DHCP"               // �Ƿ��Զ�����IP
#define NAME_CANFDNET_NIC_GENNIC_IP                 "GENNIC_IP"                 // IP��ַ
#define NAME_CANFDNET_NIC_GENNIC_MASK               "GENNIC_MASK"               // ��������
#define NAME_CANFDNET_NIC_GENNIC_GATEWAY            "GENNIC_GATEWAY"            // ����IP
#define NAME_CANFDNET_NIC_CARNIC_MAC                "CARNIC_MAC"                // ��������MAC��ַ
#define NAME_CANFDNET_NIC_CARNIC_DHCP               "CARNIC_DHCP"               // �Ƿ��Զ�����IP
#define NAME_CANFDNET_NIC_CARNIC_IP                 "CARNIC_IP"                 // IP��ַ
#define NAME_CANFDNET_NIC_CARNIC_MASK               "CARNIC_MASK"               // ��������
#define NAME_CANFDNET_NIC_CARNIC_GATEWAY            "CARNIC_GATEWAY"            // ����IP
#define NAME_CANFDNET_NIC_CARNIC_ISMASTER           "CARNIC_ISMASTER"           // ���ӻ�����
#define NAME_CANFDNET_NIC_CARNIC_SPEED              "CARNIC_SPEED"              // ���ʣ� 0�ǰ��ף�1��ǧ��
#define NAME_CANFDNET_NIC_DNS1                      "NIC_DNS1"                  // DNS1��ַ
#define NAME_CANFDNET_NIC_DNS2                      "NIC_DNS2"                  // DNS2��ַ
#define NAME_CANFDNET_CONVERT_N_ENABLE              "CONVERT%d_ENABLE"          // ����ת������ʹ��, ���18������ת�������1��ʼ
#define NAME_CANFDNET_CONVERT_N_MODE                "CONVERT%d_MODE"            // ����ģʽ
#define NAME_CANFDNET_CONVERT_N_NIC_SEL             "CONVERT%d_NIC_SEL"         // ����ѡ��
#define NAME_CANFDNET_CONVERT_N_LOCAL_PORT          "CONVERT%d_LOCAL_PORT"      // ���ض˿ں�
#define NAME_CANFDNET_CONVERT_N_REMOTE_IP           "CONVERT%d_REMOTE_IP"       // Զ��Ŀ��IP
#define NAME_CANFDNET_CONVERT_N_REMOTE_PORT         "CONVERT%d_REMOTE_PORT"     // Զ��Ŀ��˿�
#define NAME_CANFDNET_CONVERT_N_DC_TMO              "CONVERT%d_DC_TMO"          // ��ʱ�Ͽ�����ʱ��
#define NAME_CANFDNET_CONVERT_N_CHN_FLAG            "CONVERT%d_CHN_FLAG"        // CANͨ���������ͱ�ʶ
#define NAME_CANFDNET_CONVERT_N_ERR_FLAG            "CONVERT%d_ERR_FLAG"        // CANͨ����������ͱ�ʶ
#define NAME_CANFDNET_CONVERT_N_PACKET_CNT          "CONVERT%d_PACKET_CNT"      // CAN���ķ��֡��
#define NAME_CANFDNET_CONVERT_N_PACKET_TMO          "CONVERT%d_PACKET_TMO"      // ��ʱ������
#define NAME_CANFDNET_CONVERT_N_RECV_BUF_MODE       "CONVERT%d_RECV_BUF_MODE"   // ���ջ���������ʽ
#define NAME_CANFDNET_CONVERT_N_MULTICAST_ENABLE    "CONVERT%d_MULTICAST_ENABLE"// UDP�鲥ʹ��
#define NAME_CANFDNET_CONVERT_N_MULTICAST_ADDR      "CONVERT%d_MULTICAST_ADDR"  // UDP�鲥��ַ

#define NAME_CANFDNET_CARNET_N_ENABLE				"CARNET%d_ENABLE"			// ������̫��ת������ʹ�ܣ����1��ʼ
#define NAME_CANFDNET_CARNET_N_CARETH_MODE			"CARNET%d_CARETH_MODE"		// ������̫������ģʽ
#define NAME_CANFDNET_CARNET_N_CARETH_PORT			"CARNET%d_CARETH_PORT"		// ���ض˿ں�
#define NAME_CANFDNET_CARNET_N_CARETH_RMT_IP		"CARNET%d_CARETH_RMT_IP"	// Զ��Ŀ��IP
#define NAME_CANFDNET_CARNET_N_CARETH_RMT_PORT		"CARNET%d_CARETH_RMT_PORT"	// Զ��Ŀ��˿ں�
#define NAME_CANFDNET_CARNET_N_GENETH_MODE			"CARNET%d_GENETH_MODE"		// ͨ����̫������ģʽ
#define NAME_CANFDNET_CARNET_N_GENETH_PORT			"CARNET%d_GENETH_PORT"		// ���ض˿ں�
#define NAME_CANFDNET_CARNET_N_GENETH_RMT_IP		"CARNET%d_GENETH_RMT_IP"	// Զ��Ŀ��IP
#define NAME_CANFDNET_CARNET_N_GENETH_RMT_PORT		"CARNET%d_GENETH_RMT_PORT"	// Զ��Ŀ��˿ں�

#define NAME_CANFDNET_CLOUD_ENABLE					"CLOUD_ENABLE"				// ������ʹ��
#define NAME_CANFDNET_CLOUD_URL						"CLOUD_URL"					// �Ʒ�������ַ
#define NAME_CANFDNET_CLOUD_PORT					"CLOUD_PORT"				// �Ʒ������˿�
#define NAME_CANFDNET_CLOUD_DOWN_ENABLE				"CLOUD_DOWN_ENABLE"			// �����·�ʹ�ܣ�λͼ��ʶ
#define NAME_CANFDNET_CLOUD_UP_ENABLE				"CLOUD_UP_ENABLE"			// �����ϴ�ʹ�ܣ�λͼ��ʶ
#define NAME_CANFDNET_CLOUD_UP_MODE					"CLOUD_UP_MODE"				// �����ϴ�ģʽ
#define NAME_CANFDNET_CLOUD_COMPRESS_SIZE			"CLOUD_COMPRESS_SIZE"		// �������ݴﵽ��ֵѹ���ϴ�
#define NAME_CANFDNET_CLOUD_COMPRESS_TMO			"CLOUD_COMPRESS_TMO"		// �������ݳ�ʱѹ���ϱ���ms��

///< CANFDNET-400U
#define NAME_CANFDNET_FILTER_ENABLE					"FILTER_ENABLE"				// �˲�ʹ��
#define NAME_CANFDNET_FILTER_IS_WHITELIST			"FILTER_WHITE_LIST"			// �ڰ������� 0-�������� 1-������
#define NAME_CANFDNET_FILTER_N_BEGIN_ID             "RULE%d_START"				// �˲���ʼID�����32����˹���, ���1��ʼ��
#define NAME_CANFDNET_FILTER_N_END_ID				"RULE%d_END"				// �˲�����ID
#define NAME_CANFDNET_FILTER_N_CHANNEL				"RULE%d_CHN"				// ����ͨ��
#define NAME_CANFDNET_FILTER_N_CANFD				"RULE%d_CANFD"				// �Ƿ�CANFD
#define NAME_CANFDNET_FILTER_N_EXT_FRM				"RULE%d_EXT"				// ��չ֡
#define NAME_CANFDNET_FILTER_N_ERR_FRM				"RULE%d_ERR"				// ����֡
#define NAME_CANFDNET_FILTER_N_RTR_FRM				"RULE%d_RTR"				// Զ��֡
#define NAME_CANFDNET_FILTER_N_DATA_LEN				"RULE%d_LEN"				// ���ĳ��� 
#define NAME_CANFDNET_FILTER_N_BEGIN_TIME			"RULE%d_BEGIN_TIME"			// ������ʼʱ�䣬��λs
#define NAME_CANFDNET_FILTER_N_END_TIME				"RULE%d_END_TIME"			// ���˽���ʱ�䣬��λs
#define NAME_CANFDNET_FILTER_N_FILTER_DATA			"RULE%d_FILTER_DATA"		// ���Ĺ������ݣ�ʮ������������, �� "1,255,3,4"
#define NAME_CANFDNET_FILTER_N_MASK_DATA			"RULE%d_MASK_DATA"			// �����������ݣ�ʮ������������, �� "1,255,3,4"
#define NAME_CANFDNET_CONVERT_N_PROTOCOL            "CONVERT%d_PROTOCOL"        // Э��, 0-CANFDNET, 1-CANET
#define NAME_CANFDNET_CONVERT_N_COMPRESS_ENABLE     "CONVERT%d_COMPRESS_ENABLE" // ѹ��ʹ��, 0-����, 1-ʹ��
#define NAME_CANFDNET_CONVERT_N_COMPRESS_SIZE       "CONVERT%d_COMPRESS_SIZE"   // ѹ����С(֡), ��Χ10~600
#define NAME_CANFDNET_CONVERT_N_COMPRESS_TMO        "CONVERT%d_COMPRESS_TIMEOUT"// ѹ�����ݳ�ʱ(ms), ��Χ500-60000
#define NAME_CANFDNET_CAN_N_TX_ECHO                 "CAN%d_TX_ECHO"             // ���ͻ���: 0-�ر�, 1-����
#define NAME_CANFDNET_CAN_N_TX_TIMEOUT              "CAN%d_TX_TIMEOUT"          // ����ʧ���ش���ʱ: 1~1000ms
///< CANFDNET-400U base information
#define NAME_CANFDNET_DEVTYPE                       NAME_DEVTYPE                // �豸�ͺŴ��� 
#define NAME_CANFDNET_DEV_MODEL                     "DEV_MODEL"                 // �豸�ͺ�����
#define NAME_CANFDNET_FIRMWARE_VER                  NAME_FIRMWARE_VER           // �̼��汾��
#define NAME_CANFDNET_HARDWARE_VER                  NAME_HARDWARE_VER           // Ӳ���汾��
#define NAME_CANFDNET_SN                            NAME_SERIES_NUM             // �豸���к�
#define NAME_CANFDNET_CLOUD_SN                      NAME_CLOUD_SN				// �豸�����к�
#define NAME_CANFDNET_UBOOT_VER                     "UBOOT_VER"                 // Uboot�汾��
#define NAME_CANFDNET_KERNEL_VER                    "KERNEL_VER"                // �ں˰汾��
#define NAME_CANFDNET_ROOTFS_VER                    "ROOTFS_VER"                // �ļ�ϵͳ�汾��
#define NAME_CANFDNET_FPGA_VER                      "FPGA_VER"                  // FPGA�汾�� 

///< ZNE-100TA
#define NAME_ZNE_DEV_NAME                           NAME_DEVNAME                // �豸����
#define NAME_ZNE_DEV_PWD                            NAME_DEVPWD                 // �豸����
#define NAME_ZNE_IP_MODE                            NAME_IP_MODE                // IPģʽ����̬���û�̬��ȡ
#define NAME_ZNE_NET_CFG_SWITCH                     "NET_CFG_SWITCH"            // ��������ʹ��
#define NAME_ZNE_CMDPORT                            NAME_CMDPORT                // ���ö˿ڣ�����˿ڣ�
#define NAME_ZNE_WEBPORT                            NAME_WEBPORT                // ��ҳ�˿�
#define NAME_ZNE_IO_STASETTOE                       "IOSTASETTOE"               // IO����
#define NAME_ZNE_DEV_IP                             NAME_DEVIP                  // �豸IP��ַ
#define NAME_ZNE_DEV_MASK                           NAME_DEVMASK                // ��������
#define NAME_ZNE_GATEWAY                            NAME_GATE                   // ���ص�ַ
#define NAME_ZNE_DNS                                NAME_DNSSERVER              // ����������
#define NAME_ZNE_DEV_MAC                            NAME_DEVMAC                 // MAC��ַ
#define NAME_ZNE_SPEED_MODE                         NAME_SPEED_MODE             // �ٶ�ģʽ
#define NAME_ZNE_FILTER_ENABLE			            "FILTER_ENABLE"             // ����ʹ��
#define NAME_ZNE_FILTER_N_IP			            "FILTER%d_IP"               // ����IP������������FILTER1~FILTER8
#define NAME_ZNE_FILTER_N_MASK			            "FILTER%d_MASK"             // ����IP��������
#define NAME_ZNE_COM_N_WORKPORT			            "C%d_PORT"                  // ���ض˿ڣ������˿�)
#define NAME_ZNE_COM_N_DST_PORT_N			        "C%d_DST_PORT%d"            // Ŀ��˿�
#define NAME_ZNE_COM_N_DST_IP_N			            "C%d_DST_IP%d"              // Ŀ��IP
#define NAME_ZNE_COM_N_WORKTYPE			            "C%d_OP"                    // ����ģʽ
#define NAME_ZNE_COM_N_TCPCONPWD			        "C%d_LINK_P"                // �Ƿ���֤��������
#define NAME_ZNE_COM_N_MAXTCPCT			            "C%d_LINK_NUM"              // ��������
#define NAME_ZNE_COM_N_TCPTURBO			            "C%d_TCP_TURBO"             // TCP_TUBO
#define NAME_ZNE_COM_N_CLEARBUF			            "C%d_BUF_CLS"               // ��մ���
#define NAME_ZNE_COM_N_TCPCONSEND			        "C%d_LINK_S"                // ���ӷ�����Ϣ
#define NAME_ZNE_COM_N_DISCONNECT			        "C%d_TCP_CLS"               // TCP�Ͽ�����
#define NAME_ZNE_COM_N_DB_SWITCH			        "C%d_DB_SWITCH"             // �ಥʹ��
#define NAME_ZNE_COM_N_DB_IP   			            "C%d_DB_IP"                 // �ಥIP
#define NAME_ZNE_COM_N_DB_PORT 			            "C%d_DB_PORT"               // �ಥ�˿�
#define NAME_ZNE_COM_N_TCPTMOUT			            "C%d_TCPAT"                 // TCP����ʱ��
#define NAME_ZNE_COM_N_TIMEOUT			            "C%d_IT"                    // ��ʱʱ��
#define NAME_ZNE_COM_N_CNN_SEND			            "C%d_CNN_SEND"              // ������ʾ
#define NAME_ZNE_COM_N_BAUD				            "C%d_BAUD"                  // ������
#define NAME_ZNE_COM_N_DATABITS			            "C%d_DATAB"                 // ����λ
#define NAME_ZNE_COM_N_STOPBITS			            "C%d_STOPB"                 // ֹͣλ
#define NAME_ZNE_COM_N_CHECKBITS			        "C%d_PARITY"                // У��λ
#define NAME_ZNE_COM_N_PACKGAPTM			        "C%d_SER_T"                 // �ְ�ʱ��
#define NAME_ZNE_COM_N_PACKLEN			            "C%d_SER_LEN"               // �ְ�����
#define NAME_ZNE_COM_N_TCPCONSEND_C		            "C%d_LINK_C"                // TCP���ӿ���
#define NAME_ZNE_COM_N_MODBUS_SWITCH			    "C%d_MODBUS_SWITCH"         // Modbusת��
#define NAME_ZNE_COM_N_MODBUS_POLL			        "C%d_MODBUS_POLL"           // Modbus��ѯ
#define NAME_ZNE_COM_N_MODBUS_POLL_TIMEOUT	        "C%d_MODBUS_POLL_TIMEOUT"   // Modbus��ѯ��ʱ
#define NAME_ZNE_COM_N_HTTPD_OPTION			        "C%d_HTTPD_OPTION"          // Httpd����
#define NAME_ZNE_COM_N_TRIP_HEADER			        "C%d_TRIP_HEADER"           // Httpd����ȥ��ͷ
#define NAME_ZNE_COM_N_HTTPD_URL				    "C%d_HTTPD_URL"             // Httpd URL
#define NAME_ZNE_COM_N_HTTPD_CLIENT_HEADER	        "C%d_HTTPD_CLIENT_HEADER"   // Httpd �Զ����

///< ZNE-100TL
#define NAME_ZNE_COM_ENABLEST			            "C%d_ENABLEST"              // ֡��ʹ��
#define NAME_ZNE_COM_START				            "C%d_D1"                    // ֡��ʼ�ֽ�
#define NAME_ZNE_COM_END				            "C%d_D2"                    // ֡�����ֽ�
#define NAME_ZNE_COM_FLOWCTRL			            "C%d_SER_C"                 // ����
#define NAME_ZNE_PPPOE_USERNAME		                "PPPOE_USERNAME"            // PPPOE�û���
#define NAME_ZNE_PPPOE_PWD			                "PPPOE_PWD"                 // PPPOE����
#define NAME_ZNE_PPPOE_ENABLE		                "PPPOE_ENABLE"              // PPPOEʹ��
#define NAME_ZNE_PPPOE_IP			                "PPPOE_IP"                  // PPPOE IP


///< CANFDWIFI     
#define NAME_CANFDWIFI_DEV_NAME                     NAME_DEVNAME					// �豸����
#define NAME_CANFDWIFI_DEV_PWD                      NAME_CANFDNET_DEV_PWD			// �豸����
#define NAME_CANFDWIFI_CAN_N_MODE                   "CAN%d_LISTEN_MD"				// ����ģʽ, ����ģʽ��ֻ��ģʽ���Է�����, CAN��Ŵ�1��ʼ
#define NAME_CANFDWIFI_CAN_N_ENABLE                 "CAN%d_CAN_ENABLE"              // ͨ��ʹ��, CAN��Ŵ�1��ʼ
#define NAME_CANFDWIFI_CAN_N_TYPE                   "CAN%d_CAN_TYPE"				// ����������
#define NAME_CANFDWIFI_CAN_N_CLOCK                  "CAN%d_CLOCK"					// ������ʱ��
#define NAME_CANFDWIFI_CAN_N_NBAUD_TSEG1            "CAN%d_NBAUD_TSEG1"				// CAN�����ʻ�CANFD�ٲ���������λ��1
#define NAME_CANFDWIFI_CAN_N_NBAUD_TSEG2            "CAN%d_NBAUD_TSEG2"				// ��λ��2
#define NAME_CANFDWIFI_CAN_N_NBAUD_SJW              "CAN%d_NBAUD_SJW"				// ͬ����ת��� 
#define NAME_CANFDWIFI_CAN_N_NBAUD_BRP              "CAN%d_NBAUD_BRP"				// ʱ�ӷ�Ƶֵ
#define NAME_CANFDWIFI_CAN_N_DBAUD_TSEG1            "CAN%d_DBAUD_TSEG1"				// CANFD������������λ��1         
#define NAME_CANFDWIFI_CAN_N_DBAUD_TSEG2            "CAN%d_DBAUD_TSEG2"				// ��λ��2   
#define NAME_CANFDWIFI_CAN_N_DBAUD_SJW              "CAN%d_DBAUD_SJW"				// ͬ����ת��� 
#define NAME_CANFDWIFI_CAN_N_DBAUD_BRP              "CAN%d_DBAUD_BRP"				// ʱ�ӷ�Ƶֵ     
#define NAME_CANFDWIFI_CAN_N_USE_RESI               "CAN%d_USE_RESI"				// �ն˵��迪��
#define NAME_CANFDWIFI_CAN_N_NBAUD                  "CAN%d_NBAUD"					// �ٲ�������(�� 1000000)
#define NAME_CANFDWIFI_CAN_N_DBAUD                  "CAN%d_DBAUD"					// ����������(�� 5000000)
#define NAME_CANFDWIFI_CAN_N_BAUD_CUSTOM            "CAN%d_BAUD_CUSTOM"				// �Զ��岨����(�� "500Kbps(75%),4.0Mbps(80%),(2,1,1,20,3,1,1,2)")
#define NAME_CANFDWIFI_CAN_N_FILTER_MODE            "CAN%d_FILTER_MODE"				// �˲���ģʽ, ���6���˲�
#define NAME_CANFDWIFI_CAN_N_FILTER_N_ENABLE        "CAN%d_FILTER%d_ENABLE"			// �˲�����ʹ��
#define NAME_CANFDWIFI_CAN_N_FILTER_N_TYPE          "CAN%d_FILTER%d_TYPE"			// �˲�֡����
#define NAME_CANFDWIFI_CAN_N_FILTER_N_START         "CAN%d_FILTER%d_START"			// �˲���ʼID
#define NAME_CANFDWIFI_CAN_N_FILTER_N_END           "CAN%d_FILTER%d_END"			// �˲�����ID
#define NAME_CANFDWIFI_CAN_N_SEND_INTERVAL			"CAN%d_SEND_PERIOD"				// ���ķ��ͼ����ms��
#define NAME_CANFDWIFI_CAN_N_SEND_BUFSIZE			"CAN%d_SEND_BUF_SIZE"			// ���ͻ�������֡����
#define NAME_CANFDWIFI_CAN_N_SEND_BUFMODE			"CAN%d_SEND_BUF_MODE"			// ���ͻ��������ԣ����������ݡ�����������

#define NAME_CANFDWIFI_CAN_N_PSEND_ENABLE           "CAN%d_PSEND_ENABLE"            // ��ʱ����ʹ��, ���32����ʱ���ͣ����1��ʼ
#define NAME_CANFDWIFI_CAN_N_PSEND_N_ENABLE         "CAN%d_PSEND%d_ENABLE"          // ��Ϣʹ��
#define NAME_CANFDWIFI_CAN_N_PSEND_N_PERIOD         "CAN%d_PSEND%d_PERIOD"          // ���ķ�������
#define NAME_CANFDWIFI_CAN_N_PSEND_N_PERIOD_UNIT    "CAN%d_PSEND%d_PERIOD_UNIT"     // ���ķ������ڵ�λ���޸ò���ʱΪms��
#define NAME_CANFDWIFI_CAN_N_PSEND_N_COUNT          "CAN%d_PSEND%d_COUNT"           // ���ķ��ʹ���
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGID          "CAN%d_PSEND%d_MSGID"           // ֡ID
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGFLAG        "CAN%d_PSEND%d_MSGFLAG"         // ֡��־
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGDATA        "CAN%d_PSEND%d_MSGDATA"         // ֡����, ʮ������������, �� "1,2,3,4"
 
#define NAME_CANFDWIFI_CAN_N_BUSRATIO_ENABLE        "CAN%d_BUSRATIO_ENABLE"         // ����������ʹ��
#define NAME_CANFDWIFI_CAN_N_BUSRATIO_PERIOD        "CAN%d_BUSRATIO_PERIOD"         // ���������ʲɼ�����(ms)
 
#define NAME_CANFDWIFI_NIC_GENNIC_MAC               "GENNIC_MAC"                    // ͨ������MAC��ַ
#define NAME_CANFDWIFI_NIC_GENNIC_DHCP              "GENNIC_DHCP"                   // �Ƿ��Զ�����IP
#define NAME_CANFDWIFI_NIC_GENNIC_IP                "GENNIC_IP"                     // IP��ַ
#define NAME_CANFDWIFI_NIC_GENNIC_MASK              "GENNIC_MASK"                   // ��������
#define NAME_CANFDWIFI_NIC_GENNIC_GATEWAY           "GENNIC_GATEWAY"                // ����IP
#define NAME_CANFDWIFI_NIC_WIFI_MAC                 "NIC_WIFI_MAC"                  // WIFI����MAC��ַ
#define NAME_CANFDWIFI_NIC_WIFI_DHCP                "NIC_WIFI_DHCP"                 // �Ƿ��Զ�����IP
#define NAME_CANFDWIFI_NIC_WIFI_IP                  "NIC_WIFI_IP"                   // IP��ַ
#define NAME_CANFDWIFI_NIC_WIFI_MASK                "NIC_WIFI_MASK"                 // ��������
#define NAME_CANFDWIFI_NIC_WIFI_GATEWAY             "NIC_WIFI_GATEWAY"              // ����IP
#define NAME_CANFDWIFI_NIC_DNS1                     "NIC_DNS1"                      // DNS1��ַ
#define NAME_CANFDWIFI_NIC_DNS2                     "NIC_DNS2"                      // DNS2��ַ

#define NAME_CANFDWIFI_WIFI_EN_WLAN					"WIFI_EN_WLAN"					// ��������ʹ��
#define NAME_CANFDWIFI_WIFI_SSID					"WIFI_SSID"						// �����豸����
#define NAME_CANFDWIFI_WIFI_WPA_PWD					"WIFI_WPA_PWD"					// �����豸����
#define NAME_CANFDWIFI_WIFI_FREQ					"WIFI_FREQ"						// ����Ƶ��
#define NAME_CANFDWIFI_WIFI_CHANNEL					"WIFI_CHANNEL"					// �����ŵ�
#define NAME_CANFDWIFI_WIFI_WLAN_MODE				"WIFI_WLAN_MODE"				// ����ģʽ��AP���ȵ����Station���豸
#define NAME_CANFDWIFI_WIFI_WPA_MODE				"WIFI_WPA_MODE"					// ���ܷ�ʽ

#define NAME_CANFDWIFI_CONVERT_N_ENABLE             "CONVERT%d_ENABLE"              // ����ת������ʹ��, ���18������ת�������1��ʼ
#define NAME_CANFDWIFI_CONVERT_N_MODE               "CONVERT%d_MODE"                // ����ģʽ
#define NAME_CANFDWIFI_CONVERT_N_NIC_SEL            "CONVERT%d_NIC_SEL"             // ����ѡ��
#define NAME_CANFDWIFI_CONVERT_N_LOCAL_PORT         "CONVERT%d_LOCAL_PORT"          // ���ض˿ں�
#define NAME_CANFDWIFI_CONVERT_N_REMOTE_IP          "CONVERT%d_REMOTE_IP"           // Զ��Ŀ��IP
#define NAME_CANFDWIFI_CONVERT_N_REMOTE_PORT        "CONVERT%d_REMOTE_PORT"         // Զ��Ŀ��˿�
#define NAME_CANFDWIFI_CONVERT_N_DC_TMO             "CONVERT%d_DC_TMO"              // ��ʱ�Ͽ�����ʱ��
#define NAME_CANFDWIFI_CONVERT_N_CHN_FLAG           "CONVERT%d_CHN_FLAG"            // CANͨ���������ͱ�ʶ
#define NAME_CANFDWIFI_CONVERT_N_ERR_FLAG           "CONVERT%d_ERR_FLAG"            // CANͨ����������ͱ�ʶ
#define NAME_CANFDWIFI_CONVERT_N_PACKET_CNT         "CONVERT%d_PACKET_CNT"          // CAN���ķ��֡��
#define NAME_CANFDWIFI_CONVERT_N_PACKET_TMO         "CONVERT%d_PACKET_TMO"          // ��ʱ������
#define NAME_CANFDWIFI_CONVERT_N_RECV_BUF_MODE      "CONVERT%d_RECV_BUF_MODE"       // ���ջ���������ʽ
#define NAME_CANFDWIFI_CONVERT_N_MULTICAST_ENABLE   "CONVERT%d_MULTICAST_ENABLE"    // UDP�鲥ʹ��
#define NAME_CANFDWIFI_CONVERT_N_MULTICAST_ADDR     "CONVERT%d_MULTICAST_ADDR"      // UDP�鲥��ַ
#define NAME_CANFDWIFI_CONVERT_N_HEARTBEAT_TIME     "CONVERT%d_HEARTBEAT_TIME"      // TCP����ʱ��(��λ10ms)
#define NAME_CANFDWIFI_CONVERT_N_CLASSIC_PROTO      "CONVERT%d_CLASSIC_PROTO"       // ����CANWIFIЭ��ʹ��

#define NAME_CANFDWIFI_CLOUD_ENABLE                 "CLOUD_ENABLE"                  // ������ʹ��
#define NAME_CANFDWIFI_CLOUD_URL                    "CLOUD_URL"                     // �Ʒ�������ַ
#define NAME_CANFDWIFI_CLOUD_PORT                   "CLOUD_PORT"                    // �Ʒ������˿�
#define NAME_CANFDWIFI_CLOUD_DOWN_ENABLE            "CLOUD_DOWN_ENABLE"             // �����·�ʹ�ܣ�λͼ��ʶ
#define NAME_CANFDWIFI_CLOUD_UP_ENABLE              "CLOUD_UP_ENABLE"               // �����ϴ�ʹ�ܣ�λͼ��ʶ
#define NAME_CANFDWIFI_CLOUD_UP_MODE                "CLOUD_UP_MODE"                 // �����ϴ�ģʽ
#define NAME_CANFDWIFI_CLOUD_COMPRESS_SIZE          "CLOUD_COMPRESS_SIZE"           // �������ݴﵽ��ֵѹ���ϴ�
#define NAME_CANFDWIFI_CLOUD_COMPRESS_TMO           "CLOUD_COMPRESS_TMO"            // �������ݳ�ʱѹ���ϱ���ms��

#define NAME_CANFDWIFI_LOG_LEVEL                    "LOG_LEVEL"                     // ��־����

#define NAME_CANFDWIFI_CANCFGWIFI_ENABLE            "CANCFGWIFI_ENABLE"             // CAN����WIFI����ʹ��
#define NAME_CANFDWIFI_CANCFGWIFI_CHN               "CANCFGWIFI_CHN"                // ����CANͨ��
#define NAME_CANFDWIFI_CANCFGWIFI_EXT               "CANCFGWIFI_EXT"                // ����ID�Ƿ�Ϊ��չ֡
#define NAME_CANFDWIFI_CANCFGWIFI_CFG_ID            "CANCFGWIFI_CFG_ID"             // ������˳�����ID
#define NAME_CANFDWIFI_CANCFGWIFI_ACK_ID            "CANCFGWIFI_ACK_ID"             // ����Ӧ���Ӧ����ID
#define NAME_CANFDWIFI_CANCFGWIFI_SSID_ID           "CANCFGWIFI_SSID_ID"            // ���� WIFI SSID �����Ӧ���� ID
#define NAME_CANFDWIFI_CANCFGWIFI_PWD_ID            "CANCFGWIFI_PWD_ID"             // ���� WIFI ���������Ӧ���� ID
#define NAME_CANFDWIFI_CANCFGWIFI_CHN_ID            "CANCFGWIFI_CHN_ID"             // ���� WIFI �ŵ������Ӧ���� ID
#define NAME_CANFDWIFI_CANCFGWIFI_MAC_ID            "CANCFGWIFI_MAC_ID"             // ��ȡ WIFI �� MAC ��ַ�����Ӧ���� ID



///< CANFDBLUE (��Ϊ�����豸������������)     
#define NAME_CANFDBLUE_DEV_NAME                     NAME_DEVNAME					// �豸����
#define NAME_CANFDBLUE_DEVTYPE                      "DEV_TYPE"						// �豸����
#define NAME_CANFDBLUE_DEVMAC                       "MAC"							// MAC��ַ
#define NAME_CANFDBLUE_FIRMWARE_VER                 "FIRMWARE_VER"					// �̼��汾
#define NAME_CANFDBLUE_HARDWARE_VER                 "HARDWARE_VER"					// Ӳ���汾
#define NAME_CANFDBLUE_SERIES_NUM                   "SERIES_NUM"					// ���к�
#define NAME_CANFDBLUE_DEV_PWD                      NAME_CANFDNET_DEV_PWD			// �豸����
#define NAME_CANFDBLUE_CAN_N_ENABLE                 "CAN%d_ENABLE"				    // CAN��ʹ��, CAN��Ŵ�1��ʼ
#define NAME_CANFDBLUE_CAN_N_CTRL_TYPE              "CAN%d_CONTROLLER_TYPE"			// ����������, 0-CANFD, 1-CAN
#define NAME_CANFDBLUE_CAN_N_CANFD_STD              "CAN%d_CANFD_STANDARD"			// CANFD��׼, 0-ISO, 1-Non ISO
#define NAME_CANFDBLUE_CAN_N_MODE                   "CAN%d_LISTEN_MD"				// ����ģʽ, ����ģʽ��ֻ��ģʽ���Է�����
#define NAME_CANFDBLUE_CAN_N_CLOCK                  "CAN%d_CLOCK"					// ������ʱ��
#define NAME_CANFDBLUE_CAN_N_NBAUD_TSEG1            "CAN%d_NBAUD_TSEG1"				// CAN�����ʻ�CANFD�ٲ���������λ��1
#define NAME_CANFDBLUE_CAN_N_NBAUD_TSEG2            "CAN%d_NBAUD_TSEG2"				// ��λ��2
#define NAME_CANFDBLUE_CAN_N_NBAUD_SJW              "CAN%d_NBAUD_SJW"				// ͬ����ת��� 
#define NAME_CANFDBLUE_CAN_N_NBAUD_BRP              "CAN%d_NBAUD_BRP"				// ʱ�ӷ�Ƶֵ
#define NAME_CANFDBLUE_CAN_N_DBAUD_TSEG1            "CAN%d_DBAUD_TSEG1"				// CANFD������������λ��1         
#define NAME_CANFDBLUE_CAN_N_DBAUD_TSEG2            "CAN%d_DBAUD_TSEG2"				// ��λ��2   
#define NAME_CANFDBLUE_CAN_N_DBAUD_SJW              "CAN%d_DBAUD_SJW"				// ͬ����ת��� 
#define NAME_CANFDBLUE_CAN_N_DBAUD_BRP              "CAN%d_DBAUD_BRP"				// ʱ�ӷ�Ƶֵ     
#define NAME_CANFDBLUE_CAN_N_USE_RESI               "CAN%d_USE_RESI"				// �ն˵��迪��
#define NAME_CANFDBLUE_CAN_N_NBAUD                  "CAN%d_NBAUD"					// �ٲ�������(�� 1000000)
#define NAME_CANFDBLUE_CAN_N_DBAUD                  "CAN%d_DBAUD"					// ����������(�� 5000000)
#define NAME_CANFDBLUE_CAN_N_BAUD_CUSTOM            "CAN%d_BAUD_CUSTOM"				// �Զ��岨����(�� "500Kbps(75%),4.0Mbps(80%),(2,1,1,20,3,1,1,2)")
#define NAME_CANFDBLUE_CAN_N_FILTER_MODE            "CAN%d_FILTER_MODE"				// �˲���ģʽ
#define NAME_CANFDBLUE_CAN_N_FILTER_N_ENABLE        "CAN%d_FILTER%d_ENABLE"			// �˲�����ʹ��, ���6���˲�����Ŵ�1��ʼ
#define NAME_CANFDBLUE_CAN_N_FILTER_N_TYPE          "CAN%d_FILTER%d_TYPE"			// �˲�֡����
#define NAME_CANFDBLUE_CAN_N_FILTER_N_START         "CAN%d_FILTER%d_START"			// �˲���ʼID
#define NAME_CANFDBLUE_CAN_N_FILTER_N_END           "CAN%d_FILTER%d_END"			// �˲�����ID
#define NAME_CANFDBLUE_CAN_N_SEND_INTERVAL			"CAN%d_SEND_PERIOD"				// ���ķ��ͼ����ms��
#define NAME_CANFDBLUE_CAN_N_SEND_BUFSIZE			"CAN%d_SEND_BUF_SIZE"			// ���ͻ�������֡����
#define NAME_CANFDBLUE_CAN_N_SEND_BUFMODE			"CAN%d_SEND_BUF_MODE"			// ���ͻ��������ԣ����������ݡ�����������

#define NAME_CANFDBLUE_BLUE_SCAN_ENABLE				"BLUE_SCAN_ENABLE"				// ����ɨ��ʹ��
#define NAME_CANFDBLUE_BLUE_BROADCAST_ENABLE		"BLUE_BROADCAST_ENABLE"			// �����㲥ʹ��
#define NAME_CANFDBLUE_BLUE_PASSWORD				"BLUE_PASSWORD"					// ������̬�����
#define NAME_CANFDBLUE_BLUE_BRT_INTERVAL			"BLUE_BRT_INTERVAL"				// �����㲥���ʱ��(ms)
#define NAME_CANFDBLUE_BLUE_TX_PWR					"BLUE_TX_PWR"					// �������书��(dbm)
#define NAME_CANFDBLUE_BLUE_SCAN_INTERVAL			"BLUE_SCAN_INTERVAL"			// ����ɨ����ʱ��(s)
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_MODE			"BLUE_SCAN_DEVS_MODE"			// ɨ���豸���˷�ʽ
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_NUM			"BLUE_SCAN_DEVS_NUM"			// ɨ�赽�Ĵӻ��豸����
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_RSST			"BLUE_SCAN_DEVS_RSSI"			// �ź�ǿ��ɨ��
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_KEY			"BLUE_SCAN_DEVS_KEY"			// �ؼ�������ɨ��
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_NAME	"BLUE_SCAN_DEVS_DEV%d_NAME"		// �豸���ƣ�ɨ�赽�������豸��Ϣ�����10���豸����Ŵ�1��ʼ
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_MAC		"BLUE_SCAN_DEVS_DEV%d_MAC"		// �豸MAC��ַ
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_STATUS	"BLUE_SCAN_DEVS_DEV%d_STATUS"	// �豸����״̬

#define NAME_CANFDBLUE_BLUE_MASTER_NUM				"BLUE_MASTER_NUM"				// ��ǰ�������ϵ���������
#define NAME_CANFDBLUE_BLUE_MASTER_N_NAME			"BLUE_MASTER_DEV%d_NAME"		// �豸���ƣ����10�������豸����Ŵ�1��ʼ
#define NAME_CANFDBLUE_BLUE_MASTER_N_MAC			"BLUE_MASTER_DEV%d_MAC"			// �豸MAC��ַ

#define NAME_CANFDBLUE_BLUE_WHITE_LIST_MAC_N		"BLUE_WHITE_LIST_MAC%d"		    // ������MAC�б����5������Ŵ�1��ʼ

#define NAME_CANFDBLUE_USB_COM_BAUDRATE				"USB_COM_BAUDRATE"				// ���ڲ�����, USB���⴮��
#define NAME_CANFDBLUE_USB_COM_STOPBIT				"USB_COM_STOPBIT"				// ֹͣλ
#define NAME_CANFDBLUE_USB_COM_DATABIT				"USB_COM_DATABIT"				// ����λ
#define NAME_CANFDBLUE_USB_COM_PARITY				"USB_COM_PARITY"				// У��λ

#define NAME_CANFDBLUE_CONVERT_MODE				    "CONVERT_MODE"				    // ����ģʽ, ���2��ת��, ��Ŵ�1��ʼ
// #define NAME_CANFDBLUE_CONVERT_PACKET_CNT           "CONVERT_PACKET_CNT"			// CAN���ķ��֡��
// #define NAME_CANFDBLUE_CONVERT_PACKET_TMO           "CONVERT_PACKET_TMO"			// ��ʱ������
#define NAME_CANFDBLUE_CONVERT_RECV_BUF_MODE        "CONVERT_RECV_BUF_MODE"		    // ���ջ���������ʽ
// #define NAME_CANFDBLUE_CONVERT_RETRY_NUM			"CONVERT_RETRY_NUM"			    // ���ݷ���ʧ���ط�����
#define NAME_CANFDBLUE_CONVERT_DIRECT_CTRL0			"CONVERT_DIRECT_CTRL0"			// ����ת������(��һ·)
#define NAME_CANFDBLUE_CONVERT_DIRECT_CTRL1			"CONVERT_DIRECT_CTRL1"			// ����ת������(�ڶ�·)



#endif
