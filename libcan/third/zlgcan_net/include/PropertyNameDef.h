#ifndef PROPERTY_NAME_DEF_H_
#define PROPERTY_NAME_DEF_H_

///< 搜索出来的属性
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
#define NAME_CANFDNET_DEV_NAME                      NAME_DEVNAME                // 设备名称
#define NAME_CANFDNET_DEV_PWD                       NAME_DEVPWD                 // 设备密码
#define NAME_CANFDNET_CAN_N_ENABLE                  NAME_CAN_N_CAN_ENABLE       // 通道使能
#define NAME_CANFDNET_CAN_N_TYPE                    "CAN%d_CAN_TYPE"            // 控制器类型,CAN序号从1开始
#define NAME_CANFDNET_CAN_N_MODE                    NAME_CAN_N_LISTTENMD        // 工作模式
#define NAME_CANFDNET_CAN_N_CLOCK                   "CAN%d_CLOCK"               // 控制器时钟
#define NAME_CANFDNET_CAN_N_TX_ATTEMPTS             "CAN%d_TX_ATTEMPTS"         // 发送失败重传：0-不重传, 1-重传直到超时
#define NAME_CANFDNET_CAN_N_NBAUD_TSEG1             "CAN%d_NBAUD_TSEG1"         // CAN波特率或CANFD仲裁域波特率相位段1
#define NAME_CANFDNET_CAN_N_NBAUD_TSEG2             "CAN%d_NBAUD_TSEG2"         // 相位段2
#define NAME_CANFDNET_CAN_N_NBAUD_SJW               "CAN%d_NBAUD_SJW"           // 同步跳转宽度 
#define NAME_CANFDNET_CAN_N_NBAUD_BRP               "CAN%d_NBAUD_BRP"           // 时钟分频值
#define NAME_CANFDNET_CAN_N_DBAUD_TSEG1             "CAN%d_DBAUD_TSEG1"         // CANFD数据域波特率相位段1         
#define NAME_CANFDNET_CAN_N_DBAUD_TSEG2             "CAN%d_DBAUD_TSEG2"         // 相位段2   
#define NAME_CANFDNET_CAN_N_DBAUD_SJW               "CAN%d_DBAUD_SJW"           // 同步跳转宽度 
#define NAME_CANFDNET_CAN_N_DBAUD_BRP               "CAN%d_DBAUD_BRP"           // 时钟分频值     
#define NAME_CANFDNET_CAN_N_USE_RESI                "CAN%d_USE_RESI"            // 终端电阻开关
#define NAME_CANFDNET_CAN_N_NBAUD                   "CAN%d_NBAUD"               // 仲裁域波特率
#define NAME_CANFDNET_CAN_N_DBAUD                   "CAN%d_DBAUD"               // 数据域波特率
#define NAME_CANFDNET_CAN_N_BAUD_CUSTOM             "CAN%d_BAUD_CUSTOM"         // 自定义波特率
#define NAME_CANFDNET_CAN_N_FILTER_MODE             "CAN%d_FILTER_MODE"         // 滤波器模式, 最多16个滤波
#define NAME_CANFDNET_CAN_N_FILTER_N_ENABLE         "CAN%d_FILTER%d_ENABLE"     // 滤波条件使能, FILTER1~16
#define NAME_CANFDNET_CAN_N_FILTER_N_TYPE           "CAN%d_FILTER%d_TYPE"       // 滤波帧类型
#define NAME_CANFDNET_CAN_N_FILTER_N_START          "CAN%d_FILTER%d_START"      // 滤波起始ID
#define NAME_CANFDNET_CAN_N_FILTER_N_END            "CAN%d_FILTER%d_END"        // 滤波结束ID
#define NAME_CANFDNET_CAN_N_PSEND_ENABLE            "CAN%d_PSEND_ENABLE"        // 定时发送使能, 最多32个定时发送，序号1开始
#define NAME_CANFDNET_CAN_N_PSEND_N_ENABLE          "CAN%d_PSEND%d_ENABLE"      // 消息使能
#define NAME_CANFDNET_CAN_N_PSEND_N_PERIOD          "CAN%d_PSEND%d_PERIOD"      // 报文发送周期
#define NAME_CANFDNET_CAN_N_PSEND_N_COUNT           "CAN%d_PSEND%d_COUNT"       // 报文发送次数
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGID           "CAN%d_PSEND%d_MSGID"       // 帧ID
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGFLAG         "CAN%d_PSEND%d_MSGFLAG"     // 帧标志
#define NAME_CANFDNET_CAN_N_PSEND_N_MSGDATA         "CAN%d_PSEND%d_MSGDATA"     // 帧数据, 十进制整型数组, 如 "1,2,3,4"
#define NAME_CANFDNET_CAN_N_SEND_INTERVAL           NAME_CAN_N_MININTERVAL      // 报文发送间隔
#define NAME_CANFDNET_CAN_N_SEND_BUFSIZE            NAME_CAN_N_SENDBUFF         // 发送缓冲区大小
#define NAME_CANFDNET_CAN_N_SEND_BUFMODE            NAME_CAN_N_BUFFSTRATEGY     // 发送缓冲区策略
#define NAME_CANFDNET_CAN_N_BUSRATIO_ENABLE         "CAN%d_BUSRATIO_ENABLE"     // 总线利用率使能
#define NAME_CANFDNET_CAN_N_BUSRATIO_PERIOD         "CAN%d_BUSRATIO_PERIOD"     // 总线利用率采集周期(ms)
#define NAME_CANFDNET_NIC_GENNIC_MAC                "GENNIC_MAC"                // 通用网卡MAC地址
#define NAME_CANFDNET_NIC_GENNIC_DHCP               "GENNIC_DHCP"               // 是否自动分配IP
#define NAME_CANFDNET_NIC_GENNIC_IP                 "GENNIC_IP"                 // IP地址
#define NAME_CANFDNET_NIC_GENNIC_MASK               "GENNIC_MASK"               // 子网掩码
#define NAME_CANFDNET_NIC_GENNIC_GATEWAY            "GENNIC_GATEWAY"            // 网关IP
#define NAME_CANFDNET_NIC_CARNIC_MAC                "CARNIC_MAC"                // 车载网卡MAC地址
#define NAME_CANFDNET_NIC_CARNIC_DHCP               "CARNIC_DHCP"               // 是否自动分配IP
#define NAME_CANFDNET_NIC_CARNIC_IP                 "CARNIC_IP"                 // IP地址
#define NAME_CANFDNET_NIC_CARNIC_MASK               "CARNIC_MASK"               // 子网掩码
#define NAME_CANFDNET_NIC_CARNIC_GATEWAY            "CARNIC_GATEWAY"            // 网关IP
#define NAME_CANFDNET_NIC_CARNIC_ISMASTER           "CARNIC_ISMASTER"           // 主从机设置
#define NAME_CANFDNET_NIC_CARNIC_SPEED              "CARNIC_SPEED"              // 速率， 0是百兆，1是千兆
#define NAME_CANFDNET_NIC_DNS1                      "NIC_DNS1"                  // DNS1地址
#define NAME_CANFDNET_NIC_DNS2                      "NIC_DNS2"                  // DNS2地址
#define NAME_CANFDNET_CONVERT_N_ENABLE              "CONVERT%d_ENABLE"          // 数据转发配置使能, 最多18个数据转发，序号1开始
#define NAME_CANFDNET_CONVERT_N_MODE                "CONVERT%d_MODE"            // 工作模式
#define NAME_CANFDNET_CONVERT_N_NIC_SEL             "CONVERT%d_NIC_SEL"         // 网卡选择
#define NAME_CANFDNET_CONVERT_N_LOCAL_PORT          "CONVERT%d_LOCAL_PORT"      // 本地端口号
#define NAME_CANFDNET_CONVERT_N_REMOTE_IP           "CONVERT%d_REMOTE_IP"       // 远程目标IP
#define NAME_CANFDNET_CONVERT_N_REMOTE_PORT         "CONVERT%d_REMOTE_PORT"     // 远程目标端口
#define NAME_CANFDNET_CONVERT_N_DC_TMO              "CONVERT%d_DC_TMO"          // 超时断开连接时间
#define NAME_CANFDNET_CONVERT_N_CHN_FLAG            "CONVERT%d_CHN_FLAG"        // CAN通道报文上送标识
#define NAME_CANFDNET_CONVERT_N_ERR_FLAG            "CONVERT%d_ERR_FLAG"        // CAN通标错误报文上送标识
#define NAME_CANFDNET_CONVERT_N_PACKET_CNT          "CONVERT%d_PACKET_CNT"      // CAN报文封包帧数
#define NAME_CANFDNET_CONVERT_N_PACKET_TMO          "CONVERT%d_PACKET_TMO"      // 超时封包间隔
#define NAME_CANFDNET_CONVERT_N_RECV_BUF_MODE       "CONVERT%d_RECV_BUF_MODE"   // 接收缓存区处理方式
#define NAME_CANFDNET_CONVERT_N_MULTICAST_ENABLE    "CONVERT%d_MULTICAST_ENABLE"// UDP组播使能
#define NAME_CANFDNET_CONVERT_N_MULTICAST_ADDR      "CONVERT%d_MULTICAST_ADDR"  // UDP组播地址

#define NAME_CANFDNET_CARNET_N_ENABLE				"CARNET%d_ENABLE"			// 车载以太网转发配置使能，序号1开始
#define NAME_CANFDNET_CARNET_N_CARETH_MODE			"CARNET%d_CARETH_MODE"		// 车载以太网工作模式
#define NAME_CANFDNET_CARNET_N_CARETH_PORT			"CARNET%d_CARETH_PORT"		// 本地端口号
#define NAME_CANFDNET_CARNET_N_CARETH_RMT_IP		"CARNET%d_CARETH_RMT_IP"	// 远程目标IP
#define NAME_CANFDNET_CARNET_N_CARETH_RMT_PORT		"CARNET%d_CARETH_RMT_PORT"	// 远程目标端口号
#define NAME_CANFDNET_CARNET_N_GENETH_MODE			"CARNET%d_GENETH_MODE"		// 通用以太网工作模式
#define NAME_CANFDNET_CARNET_N_GENETH_PORT			"CARNET%d_GENETH_PORT"		// 本地端口号
#define NAME_CANFDNET_CARNET_N_GENETH_RMT_IP		"CARNET%d_GENETH_RMT_IP"	// 远程目标IP
#define NAME_CANFDNET_CARNET_N_GENETH_RMT_PORT		"CARNET%d_GENETH_RMT_PORT"	// 远程目标端口号

#define NAME_CANFDNET_CLOUD_ENABLE					"CLOUD_ENABLE"				// 接入云使能
#define NAME_CANFDNET_CLOUD_URL						"CLOUD_URL"					// 云服务器地址
#define NAME_CANFDNET_CLOUD_PORT					"CLOUD_PORT"				// 云服务器端口
#define NAME_CANFDNET_CLOUD_DOWN_ENABLE				"CLOUD_DOWN_ENABLE"			// 报文下发使能，位图标识
#define NAME_CANFDNET_CLOUD_UP_ENABLE				"CLOUD_UP_ENABLE"			// 报文上传使能，位图标识
#define NAME_CANFDNET_CLOUD_UP_MODE					"CLOUD_UP_MODE"				// 报文上传模式
#define NAME_CANFDNET_CLOUD_COMPRESS_SIZE			"CLOUD_COMPRESS_SIZE"		// 缓存数据达到该值压缩上传
#define NAME_CANFDNET_CLOUD_COMPRESS_TMO			"CLOUD_COMPRESS_TMO"		// 接收数据超时压缩上报（ms）

///< CANFDNET-400U
#define NAME_CANFDNET_FILTER_ENABLE					"FILTER_ENABLE"				// 滤波使能
#define NAME_CANFDNET_FILTER_IS_WHITELIST			"FILTER_WHITE_LIST"			// 黑白名单， 0-黑名单， 1-白名单
#define NAME_CANFDNET_FILTER_N_BEGIN_ID             "RULE%d_START"				// 滤波起始ID（最多32组过滤规则, 序号1开始）
#define NAME_CANFDNET_FILTER_N_END_ID				"RULE%d_END"				// 滤波结束ID
#define NAME_CANFDNET_FILTER_N_CHANNEL				"RULE%d_CHN"				// 报文通道
#define NAME_CANFDNET_FILTER_N_CANFD				"RULE%d_CANFD"				// 是否CANFD
#define NAME_CANFDNET_FILTER_N_EXT_FRM				"RULE%d_EXT"				// 扩展帧
#define NAME_CANFDNET_FILTER_N_ERR_FRM				"RULE%d_ERR"				// 错误帧
#define NAME_CANFDNET_FILTER_N_RTR_FRM				"RULE%d_RTR"				// 远程帧
#define NAME_CANFDNET_FILTER_N_DATA_LEN				"RULE%d_LEN"				// 报文长度 
#define NAME_CANFDNET_FILTER_N_BEGIN_TIME			"RULE%d_BEGIN_TIME"			// 过滤起始时间，单位s
#define NAME_CANFDNET_FILTER_N_END_TIME				"RULE%d_END_TIME"			// 过滤结束时间，单位s
#define NAME_CANFDNET_FILTER_N_FILTER_DATA			"RULE%d_FILTER_DATA"		// 报文过滤数据，十进制整型数组, 如 "1,255,3,4"
#define NAME_CANFDNET_FILTER_N_MASK_DATA			"RULE%d_MASK_DATA"			// 报文屏蔽数据，十进制整型数组, 如 "1,255,3,4"
#define NAME_CANFDNET_CONVERT_N_PROTOCOL            "CONVERT%d_PROTOCOL"        // 协议, 0-CANFDNET, 1-CANET
#define NAME_CANFDNET_CONVERT_N_COMPRESS_ENABLE     "CONVERT%d_COMPRESS_ENABLE" // 压缩使能, 0-禁能, 1-使能
#define NAME_CANFDNET_CONVERT_N_COMPRESS_SIZE       "CONVERT%d_COMPRESS_SIZE"   // 压缩大小(帧), 范围10~600
#define NAME_CANFDNET_CONVERT_N_COMPRESS_TMO        "CONVERT%d_COMPRESS_TIMEOUT"// 压缩数据超时(ms), 范围500-60000
#define NAME_CANFDNET_CAN_N_TX_ECHO                 "CAN%d_TX_ECHO"             // 发送回显: 0-关闭, 1-开启
#define NAME_CANFDNET_CAN_N_TX_TIMEOUT              "CAN%d_TX_TIMEOUT"          // 发送失败重传超时: 1~1000ms
///< CANFDNET-400U base information
#define NAME_CANFDNET_DEVTYPE                       NAME_DEVTYPE                // 设备型号代号 
#define NAME_CANFDNET_DEV_MODEL                     "DEV_MODEL"                 // 设备型号名称
#define NAME_CANFDNET_FIRMWARE_VER                  NAME_FIRMWARE_VER           // 固件版本号
#define NAME_CANFDNET_HARDWARE_VER                  NAME_HARDWARE_VER           // 硬件版本号
#define NAME_CANFDNET_SN                            NAME_SERIES_NUM             // 设备序列号
#define NAME_CANFDNET_CLOUD_SN                      NAME_CLOUD_SN				// 设备云序列号
#define NAME_CANFDNET_UBOOT_VER                     "UBOOT_VER"                 // Uboot版本号
#define NAME_CANFDNET_KERNEL_VER                    "KERNEL_VER"                // 内核版本号
#define NAME_CANFDNET_ROOTFS_VER                    "ROOTFS_VER"                // 文件系统版本号
#define NAME_CANFDNET_FPGA_VER                      "FPGA_VER"                  // FPGA版本号 

///< ZNE-100TA
#define NAME_ZNE_DEV_NAME                           NAME_DEVNAME                // 设备名称
#define NAME_ZNE_DEV_PWD                            NAME_DEVPWD                 // 设备密码
#define NAME_ZNE_IP_MODE                            NAME_IP_MODE                // IP模式，静态设置或动态获取
#define NAME_ZNE_NET_CFG_SWITCH                     "NET_CFG_SWITCH"            // 网络配置使能
#define NAME_ZNE_CMDPORT                            NAME_CMDPORT                // 配置端口（命令端口）
#define NAME_ZNE_WEBPORT                            NAME_WEBPORT                // 网页端口
#define NAME_ZNE_IO_STASETTOE                       "IOSTASETTOE"               // IO功能
#define NAME_ZNE_DEV_IP                             NAME_DEVIP                  // 设备IP地址
#define NAME_ZNE_DEV_MASK                           NAME_DEVMASK                // 子网掩码
#define NAME_ZNE_GATEWAY                            NAME_GATE                   // 网关地址
#define NAME_ZNE_DNS                                NAME_DNSSERVER              // 域名服务器
#define NAME_ZNE_DEV_MAC                            NAME_DEVMAC                 // MAC地址
#define NAME_ZNE_SPEED_MODE                         NAME_SPEED_MODE             // 速度模式
#define NAME_ZNE_FILTER_ENABLE			            "FILTER_ENABLE"             // 过滤使能
#define NAME_ZNE_FILTER_N_IP			            "FILTER%d_IP"               // 过滤IP（白名单），FILTER1~FILTER8
#define NAME_ZNE_FILTER_N_MASK			            "FILTER%d_MASK"             // 过滤IP子网掩码
#define NAME_ZNE_COM_N_WORKPORT			            "C%d_PORT"                  // 本地端口（工作端口)
#define NAME_ZNE_COM_N_DST_PORT_N			        "C%d_DST_PORT%d"            // 目标端口
#define NAME_ZNE_COM_N_DST_IP_N			            "C%d_DST_IP%d"              // 目标IP
#define NAME_ZNE_COM_N_WORKTYPE			            "C%d_OP"                    // 工作模式
#define NAME_ZNE_COM_N_TCPCONPWD			        "C%d_LINK_P"                // 是否验证连接密码
#define NAME_ZNE_COM_N_MAXTCPCT			            "C%d_LINK_NUM"              // 连接数量
#define NAME_ZNE_COM_N_TCPTURBO			            "C%d_TCP_TURBO"             // TCP_TUBO
#define NAME_ZNE_COM_N_CLEARBUF			            "C%d_BUF_CLS"               // 清空串口
#define NAME_ZNE_COM_N_TCPCONSEND			        "C%d_LINK_S"                // 连接发送信息
#define NAME_ZNE_COM_N_DISCONNECT			        "C%d_TCP_CLS"               // TCP断开控制
#define NAME_ZNE_COM_N_DB_SWITCH			        "C%d_DB_SWITCH"             // 多播使能
#define NAME_ZNE_COM_N_DB_IP   			            "C%d_DB_IP"                 // 多播IP
#define NAME_ZNE_COM_N_DB_PORT 			            "C%d_DB_PORT"               // 多播端口
#define NAME_ZNE_COM_N_TCPTMOUT			            "C%d_TCPAT"                 // TCP心跳时间
#define NAME_ZNE_COM_N_TIMEOUT			            "C%d_IT"                    // 超时时间
#define NAME_ZNE_COM_N_CNN_SEND			            "C%d_CNN_SEND"              // 连接提示
#define NAME_ZNE_COM_N_BAUD				            "C%d_BAUD"                  // 波特率
#define NAME_ZNE_COM_N_DATABITS			            "C%d_DATAB"                 // 数据位
#define NAME_ZNE_COM_N_STOPBITS			            "C%d_STOPB"                 // 停止位
#define NAME_ZNE_COM_N_CHECKBITS			        "C%d_PARITY"                // 校验位
#define NAME_ZNE_COM_N_PACKGAPTM			        "C%d_SER_T"                 // 分包时间
#define NAME_ZNE_COM_N_PACKLEN			            "C%d_SER_LEN"               // 分包长度
#define NAME_ZNE_COM_N_TCPCONSEND_C		            "C%d_LINK_C"                // TCP连接控制
#define NAME_ZNE_COM_N_MODBUS_SWITCH			    "C%d_MODBUS_SWITCH"         // Modbus转换
#define NAME_ZNE_COM_N_MODBUS_POLL			        "C%d_MODBUS_POLL"           // Modbus轮询
#define NAME_ZNE_COM_N_MODBUS_POLL_TIMEOUT	        "C%d_MODBUS_POLL_TIMEOUT"   // Modbus轮询超时
#define NAME_ZNE_COM_N_HTTPD_OPTION			        "C%d_HTTPD_OPTION"          // Httpd方法
#define NAME_ZNE_COM_N_TRIP_HEADER			        "C%d_TRIP_HEADER"           // Httpd数据去包头
#define NAME_ZNE_COM_N_HTTPD_URL				    "C%d_HTTPD_URL"             // Httpd URL
#define NAME_ZNE_COM_N_HTTPD_CLIENT_HEADER	        "C%d_HTTPD_CLIENT_HEADER"   // Httpd 自定义包

///< ZNE-100TL
#define NAME_ZNE_COM_ENABLEST			            "C%d_ENABLEST"              // 帧控使能
#define NAME_ZNE_COM_START				            "C%d_D1"                    // 帧起始字节
#define NAME_ZNE_COM_END				            "C%d_D2"                    // 帧结束字节
#define NAME_ZNE_COM_FLOWCTRL			            "C%d_SER_C"                 // 流控
#define NAME_ZNE_PPPOE_USERNAME		                "PPPOE_USERNAME"            // PPPOE用户名
#define NAME_ZNE_PPPOE_PWD			                "PPPOE_PWD"                 // PPPOE密码
#define NAME_ZNE_PPPOE_ENABLE		                "PPPOE_ENABLE"              // PPPOE使能
#define NAME_ZNE_PPPOE_IP			                "PPPOE_IP"                  // PPPOE IP


///< CANFDWIFI     
#define NAME_CANFDWIFI_DEV_NAME                     NAME_DEVNAME					// 设备名称
#define NAME_CANFDWIFI_DEV_PWD                      NAME_CANFDNET_DEV_PWD			// 设备密码
#define NAME_CANFDWIFI_CAN_N_MODE                   "CAN%d_LISTEN_MD"				// 工作模式, 正常模式、只听模式、自发自收, CAN序号从1开始
#define NAME_CANFDWIFI_CAN_N_ENABLE                 "CAN%d_CAN_ENABLE"              // 通道使能, CAN序号从1开始
#define NAME_CANFDWIFI_CAN_N_TYPE                   "CAN%d_CAN_TYPE"				// 控制器类型
#define NAME_CANFDWIFI_CAN_N_CLOCK                  "CAN%d_CLOCK"					// 控制器时钟
#define NAME_CANFDWIFI_CAN_N_NBAUD_TSEG1            "CAN%d_NBAUD_TSEG1"				// CAN波特率或CANFD仲裁域波特率相位段1
#define NAME_CANFDWIFI_CAN_N_NBAUD_TSEG2            "CAN%d_NBAUD_TSEG2"				// 相位段2
#define NAME_CANFDWIFI_CAN_N_NBAUD_SJW              "CAN%d_NBAUD_SJW"				// 同步跳转宽度 
#define NAME_CANFDWIFI_CAN_N_NBAUD_BRP              "CAN%d_NBAUD_BRP"				// 时钟分频值
#define NAME_CANFDWIFI_CAN_N_DBAUD_TSEG1            "CAN%d_DBAUD_TSEG1"				// CANFD数据域波特率相位段1         
#define NAME_CANFDWIFI_CAN_N_DBAUD_TSEG2            "CAN%d_DBAUD_TSEG2"				// 相位段2   
#define NAME_CANFDWIFI_CAN_N_DBAUD_SJW              "CAN%d_DBAUD_SJW"				// 同步跳转宽度 
#define NAME_CANFDWIFI_CAN_N_DBAUD_BRP              "CAN%d_DBAUD_BRP"				// 时钟分频值     
#define NAME_CANFDWIFI_CAN_N_USE_RESI               "CAN%d_USE_RESI"				// 终端电阻开关
#define NAME_CANFDWIFI_CAN_N_NBAUD                  "CAN%d_NBAUD"					// 仲裁域波特率(如 1000000)
#define NAME_CANFDWIFI_CAN_N_DBAUD                  "CAN%d_DBAUD"					// 数据域波特率(如 5000000)
#define NAME_CANFDWIFI_CAN_N_BAUD_CUSTOM            "CAN%d_BAUD_CUSTOM"				// 自定义波特率(如 "500Kbps(75%),4.0Mbps(80%),(2,1,1,20,3,1,1,2)")
#define NAME_CANFDWIFI_CAN_N_FILTER_MODE            "CAN%d_FILTER_MODE"				// 滤波器模式, 最多6个滤波
#define NAME_CANFDWIFI_CAN_N_FILTER_N_ENABLE        "CAN%d_FILTER%d_ENABLE"			// 滤波条件使能
#define NAME_CANFDWIFI_CAN_N_FILTER_N_TYPE          "CAN%d_FILTER%d_TYPE"			// 滤波帧类型
#define NAME_CANFDWIFI_CAN_N_FILTER_N_START         "CAN%d_FILTER%d_START"			// 滤波起始ID
#define NAME_CANFDWIFI_CAN_N_FILTER_N_END           "CAN%d_FILTER%d_END"			// 滤波结束ID
#define NAME_CANFDWIFI_CAN_N_SEND_INTERVAL			"CAN%d_SEND_PERIOD"				// 报文发送间隔（ms）
#define NAME_CANFDWIFI_CAN_N_SEND_BUFSIZE			"CAN%d_SEND_BUF_SIZE"			// 发送缓冲区（帧数）
#define NAME_CANFDWIFI_CAN_N_SEND_BUFMODE			"CAN%d_SEND_BUF_MODE"			// 发送缓冲区策略，满丢新数据、满丢旧数据

#define NAME_CANFDWIFI_CAN_N_PSEND_ENABLE           "CAN%d_PSEND_ENABLE"            // 定时发送使能, 最多32个定时发送，序号1开始
#define NAME_CANFDWIFI_CAN_N_PSEND_N_ENABLE         "CAN%d_PSEND%d_ENABLE"          // 消息使能
#define NAME_CANFDWIFI_CAN_N_PSEND_N_PERIOD         "CAN%d_PSEND%d_PERIOD"          // 报文发送周期
#define NAME_CANFDWIFI_CAN_N_PSEND_N_PERIOD_UNIT    "CAN%d_PSEND%d_PERIOD_UNIT"     // 报文发送周期单位（无该参数时为ms）
#define NAME_CANFDWIFI_CAN_N_PSEND_N_COUNT          "CAN%d_PSEND%d_COUNT"           // 报文发送次数
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGID          "CAN%d_PSEND%d_MSGID"           // 帧ID
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGFLAG        "CAN%d_PSEND%d_MSGFLAG"         // 帧标志
#define NAME_CANFDWIFI_CAN_N_PSEND_N_MSGDATA        "CAN%d_PSEND%d_MSGDATA"         // 帧数据, 十进制整型数组, 如 "1,2,3,4"
 
#define NAME_CANFDWIFI_CAN_N_BUSRATIO_ENABLE        "CAN%d_BUSRATIO_ENABLE"         // 总线利用率使能
#define NAME_CANFDWIFI_CAN_N_BUSRATIO_PERIOD        "CAN%d_BUSRATIO_PERIOD"         // 总线利用率采集周期(ms)
 
#define NAME_CANFDWIFI_NIC_GENNIC_MAC               "GENNIC_MAC"                    // 通用网卡MAC地址
#define NAME_CANFDWIFI_NIC_GENNIC_DHCP              "GENNIC_DHCP"                   // 是否自动分配IP
#define NAME_CANFDWIFI_NIC_GENNIC_IP                "GENNIC_IP"                     // IP地址
#define NAME_CANFDWIFI_NIC_GENNIC_MASK              "GENNIC_MASK"                   // 子网掩码
#define NAME_CANFDWIFI_NIC_GENNIC_GATEWAY           "GENNIC_GATEWAY"                // 网关IP
#define NAME_CANFDWIFI_NIC_WIFI_MAC                 "NIC_WIFI_MAC"                  // WIFI网卡MAC地址
#define NAME_CANFDWIFI_NIC_WIFI_DHCP                "NIC_WIFI_DHCP"                 // 是否自动分配IP
#define NAME_CANFDWIFI_NIC_WIFI_IP                  "NIC_WIFI_IP"                   // IP地址
#define NAME_CANFDWIFI_NIC_WIFI_MASK                "NIC_WIFI_MASK"                 // 子网掩码
#define NAME_CANFDWIFI_NIC_WIFI_GATEWAY             "NIC_WIFI_GATEWAY"              // 网关IP
#define NAME_CANFDWIFI_NIC_DNS1                     "NIC_DNS1"                      // DNS1地址
#define NAME_CANFDWIFI_NIC_DNS2                     "NIC_DNS2"                      // DNS2地址

#define NAME_CANFDWIFI_WIFI_EN_WLAN					"WIFI_EN_WLAN"					// 无线网络使能
#define NAME_CANFDWIFI_WIFI_SSID					"WIFI_SSID"						// 无线设备名称
#define NAME_CANFDWIFI_WIFI_WPA_PWD					"WIFI_WPA_PWD"					// 无线设备密码
#define NAME_CANFDWIFI_WIFI_FREQ					"WIFI_FREQ"						// 无线频率
#define NAME_CANFDWIFI_WIFI_CHANNEL					"WIFI_CHANNEL"					// 工作信道
#define NAME_CANFDWIFI_WIFI_WLAN_MODE				"WIFI_WLAN_MODE"				// 无线模式，AP做热点或者Station做设备
#define NAME_CANFDWIFI_WIFI_WPA_MODE				"WIFI_WPA_MODE"					// 加密方式

#define NAME_CANFDWIFI_CONVERT_N_ENABLE             "CONVERT%d_ENABLE"              // 数据转发配置使能, 最多18个数据转发，序号1开始
#define NAME_CANFDWIFI_CONVERT_N_MODE               "CONVERT%d_MODE"                // 工作模式
#define NAME_CANFDWIFI_CONVERT_N_NIC_SEL            "CONVERT%d_NIC_SEL"             // 网卡选择
#define NAME_CANFDWIFI_CONVERT_N_LOCAL_PORT         "CONVERT%d_LOCAL_PORT"          // 本地端口号
#define NAME_CANFDWIFI_CONVERT_N_REMOTE_IP          "CONVERT%d_REMOTE_IP"           // 远程目标IP
#define NAME_CANFDWIFI_CONVERT_N_REMOTE_PORT        "CONVERT%d_REMOTE_PORT"         // 远程目标端口
#define NAME_CANFDWIFI_CONVERT_N_DC_TMO             "CONVERT%d_DC_TMO"              // 超时断开连接时间
#define NAME_CANFDWIFI_CONVERT_N_CHN_FLAG           "CONVERT%d_CHN_FLAG"            // CAN通道报文上送标识
#define NAME_CANFDWIFI_CONVERT_N_ERR_FLAG           "CONVERT%d_ERR_FLAG"            // CAN通标错误报文上送标识
#define NAME_CANFDWIFI_CONVERT_N_PACKET_CNT         "CONVERT%d_PACKET_CNT"          // CAN报文封包帧数
#define NAME_CANFDWIFI_CONVERT_N_PACKET_TMO         "CONVERT%d_PACKET_TMO"          // 超时封包间隔
#define NAME_CANFDWIFI_CONVERT_N_RECV_BUF_MODE      "CONVERT%d_RECV_BUF_MODE"       // 接收缓存区处理方式
#define NAME_CANFDWIFI_CONVERT_N_MULTICAST_ENABLE   "CONVERT%d_MULTICAST_ENABLE"    // UDP组播使能
#define NAME_CANFDWIFI_CONVERT_N_MULTICAST_ADDR     "CONVERT%d_MULTICAST_ADDR"      // UDP组播地址
#define NAME_CANFDWIFI_CONVERT_N_HEARTBEAT_TIME     "CONVERT%d_HEARTBEAT_TIME"      // TCP心跳时间(单位10ms)
#define NAME_CANFDWIFI_CONVERT_N_CLASSIC_PROTO      "CONVERT%d_CLASSIC_PROTO"       // 经典CANWIFI协议使能

#define NAME_CANFDWIFI_CLOUD_ENABLE                 "CLOUD_ENABLE"                  // 接入云使能
#define NAME_CANFDWIFI_CLOUD_URL                    "CLOUD_URL"                     // 云服务器地址
#define NAME_CANFDWIFI_CLOUD_PORT                   "CLOUD_PORT"                    // 云服务器端口
#define NAME_CANFDWIFI_CLOUD_DOWN_ENABLE            "CLOUD_DOWN_ENABLE"             // 报文下发使能，位图标识
#define NAME_CANFDWIFI_CLOUD_UP_ENABLE              "CLOUD_UP_ENABLE"               // 报文上传使能，位图标识
#define NAME_CANFDWIFI_CLOUD_UP_MODE                "CLOUD_UP_MODE"                 // 报文上传模式
#define NAME_CANFDWIFI_CLOUD_COMPRESS_SIZE          "CLOUD_COMPRESS_SIZE"           // 缓存数据达到该值压缩上传
#define NAME_CANFDWIFI_CLOUD_COMPRESS_TMO           "CLOUD_COMPRESS_TMO"            // 接收数据超时压缩上报（ms）

#define NAME_CANFDWIFI_LOG_LEVEL                    "LOG_LEVEL"                     // 日志级别

#define NAME_CANFDWIFI_CANCFGWIFI_ENABLE            "CANCFGWIFI_ENABLE"             // CAN配置WIFI参数使能
#define NAME_CANFDWIFI_CANCFGWIFI_CHN               "CANCFGWIFI_CHN"                // 配置CAN通道
#define NAME_CANFDWIFI_CANCFGWIFI_EXT               "CANCFGWIFI_EXT"                // 报文ID是否为扩展帧
#define NAME_CANFDWIFI_CANCFGWIFI_CFG_ID            "CANCFGWIFI_CFG_ID"             // 进入或退出配置ID
#define NAME_CANFDWIFI_CANCFGWIFI_ACK_ID            "CANCFGWIFI_ACK_ID"             // 命令应答对应报文ID
#define NAME_CANFDWIFI_CANCFGWIFI_SSID_ID           "CANCFGWIFI_SSID_ID"            // 设置 WIFI SSID 命令对应报文 ID
#define NAME_CANFDWIFI_CANCFGWIFI_PWD_ID            "CANCFGWIFI_PWD_ID"             // 设置 WIFI 密码命令对应报文 ID
#define NAME_CANFDWIFI_CANCFGWIFI_CHN_ID            "CANCFGWIFI_CHN_ID"             // 设置 WIFI 信道命令对应报文 ID
#define NAME_CANFDWIFI_CANCFGWIFI_MAC_ID            "CANCFGWIFI_MAC_ID"             // 获取 WIFI 的 MAC 地址命令对应报文 ID



///< CANFDBLUE (视为串口设备，无搜索属性)     
#define NAME_CANFDBLUE_DEV_NAME                     NAME_DEVNAME					// 设备名称
#define NAME_CANFDBLUE_DEVTYPE                      "DEV_TYPE"						// 设备类型
#define NAME_CANFDBLUE_DEVMAC                       "MAC"							// MAC地址
#define NAME_CANFDBLUE_FIRMWARE_VER                 "FIRMWARE_VER"					// 固件版本
#define NAME_CANFDBLUE_HARDWARE_VER                 "HARDWARE_VER"					// 硬件版本
#define NAME_CANFDBLUE_SERIES_NUM                   "SERIES_NUM"					// 序列号
#define NAME_CANFDBLUE_DEV_PWD                      NAME_CANFDNET_DEV_PWD			// 设备密码
#define NAME_CANFDBLUE_CAN_N_ENABLE                 "CAN%d_ENABLE"				    // CAN口使能, CAN序号从1开始
#define NAME_CANFDBLUE_CAN_N_CTRL_TYPE              "CAN%d_CONTROLLER_TYPE"			// 控制器类型, 0-CANFD, 1-CAN
#define NAME_CANFDBLUE_CAN_N_CANFD_STD              "CAN%d_CANFD_STANDARD"			// CANFD标准, 0-ISO, 1-Non ISO
#define NAME_CANFDBLUE_CAN_N_MODE                   "CAN%d_LISTEN_MD"				// 工作模式, 正常模式、只听模式、自发自收
#define NAME_CANFDBLUE_CAN_N_CLOCK                  "CAN%d_CLOCK"					// 控制器时钟
#define NAME_CANFDBLUE_CAN_N_NBAUD_TSEG1            "CAN%d_NBAUD_TSEG1"				// CAN波特率或CANFD仲裁域波特率相位段1
#define NAME_CANFDBLUE_CAN_N_NBAUD_TSEG2            "CAN%d_NBAUD_TSEG2"				// 相位段2
#define NAME_CANFDBLUE_CAN_N_NBAUD_SJW              "CAN%d_NBAUD_SJW"				// 同步跳转宽度 
#define NAME_CANFDBLUE_CAN_N_NBAUD_BRP              "CAN%d_NBAUD_BRP"				// 时钟分频值
#define NAME_CANFDBLUE_CAN_N_DBAUD_TSEG1            "CAN%d_DBAUD_TSEG1"				// CANFD数据域波特率相位段1         
#define NAME_CANFDBLUE_CAN_N_DBAUD_TSEG2            "CAN%d_DBAUD_TSEG2"				// 相位段2   
#define NAME_CANFDBLUE_CAN_N_DBAUD_SJW              "CAN%d_DBAUD_SJW"				// 同步跳转宽度 
#define NAME_CANFDBLUE_CAN_N_DBAUD_BRP              "CAN%d_DBAUD_BRP"				// 时钟分频值     
#define NAME_CANFDBLUE_CAN_N_USE_RESI               "CAN%d_USE_RESI"				// 终端电阻开关
#define NAME_CANFDBLUE_CAN_N_NBAUD                  "CAN%d_NBAUD"					// 仲裁域波特率(如 1000000)
#define NAME_CANFDBLUE_CAN_N_DBAUD                  "CAN%d_DBAUD"					// 数据域波特率(如 5000000)
#define NAME_CANFDBLUE_CAN_N_BAUD_CUSTOM            "CAN%d_BAUD_CUSTOM"				// 自定义波特率(如 "500Kbps(75%),4.0Mbps(80%),(2,1,1,20,3,1,1,2)")
#define NAME_CANFDBLUE_CAN_N_FILTER_MODE            "CAN%d_FILTER_MODE"				// 滤波器模式
#define NAME_CANFDBLUE_CAN_N_FILTER_N_ENABLE        "CAN%d_FILTER%d_ENABLE"			// 滤波条件使能, 最多6个滤波，序号从1开始
#define NAME_CANFDBLUE_CAN_N_FILTER_N_TYPE          "CAN%d_FILTER%d_TYPE"			// 滤波帧类型
#define NAME_CANFDBLUE_CAN_N_FILTER_N_START         "CAN%d_FILTER%d_START"			// 滤波起始ID
#define NAME_CANFDBLUE_CAN_N_FILTER_N_END           "CAN%d_FILTER%d_END"			// 滤波结束ID
#define NAME_CANFDBLUE_CAN_N_SEND_INTERVAL			"CAN%d_SEND_PERIOD"				// 报文发送间隔（ms）
#define NAME_CANFDBLUE_CAN_N_SEND_BUFSIZE			"CAN%d_SEND_BUF_SIZE"			// 发送缓冲区（帧数）
#define NAME_CANFDBLUE_CAN_N_SEND_BUFMODE			"CAN%d_SEND_BUF_MODE"			// 发送缓冲区策略，满丢新数据、满丢旧数据

#define NAME_CANFDBLUE_BLUE_SCAN_ENABLE				"BLUE_SCAN_ENABLE"				// 蓝牙扫描使能
#define NAME_CANFDBLUE_BLUE_BROADCAST_ENABLE		"BLUE_BROADCAST_ENABLE"			// 蓝牙广播使能
#define NAME_CANFDBLUE_BLUE_PASSWORD				"BLUE_PASSWORD"					// 蓝牙静态配对码
#define NAME_CANFDBLUE_BLUE_BRT_INTERVAL			"BLUE_BRT_INTERVAL"				// 蓝牙广播间隔时间(ms)
#define NAME_CANFDBLUE_BLUE_TX_PWR					"BLUE_TX_PWR"					// 蓝牙发射功率(dbm)
#define NAME_CANFDBLUE_BLUE_SCAN_INTERVAL			"BLUE_SCAN_INTERVAL"			// 蓝牙扫描间隔时间(s)
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_MODE			"BLUE_SCAN_DEVS_MODE"			// 扫描设备过滤方式
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_NUM			"BLUE_SCAN_DEVS_NUM"			// 扫描到的从机设备数量
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_RSST			"BLUE_SCAN_DEVS_RSSI"			// 信号强度扫描
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_KEY			"BLUE_SCAN_DEVS_KEY"			// 关键字名称扫描
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_NAME	"BLUE_SCAN_DEVS_DEV%d_NAME"		// 设备名称，扫描到的蓝牙设备信息，最多10个设备，序号从1开始
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_MAC		"BLUE_SCAN_DEVS_DEV%d_MAC"		// 设备MAC地址
#define NAME_CANFDBLUE_BLUE_SCAN_DEVS_DEV_N_STATUS	"BLUE_SCAN_DEVS_DEV%d_STATUS"	// 设备连接状态

#define NAME_CANFDBLUE_BLUE_MASTER_NUM				"BLUE_MASTER_NUM"				// 当前已连接上的主机数量
#define NAME_CANFDBLUE_BLUE_MASTER_N_NAME			"BLUE_MASTER_DEV%d_NAME"		// 设备名称，最多10个主机设备，序号从1开始
#define NAME_CANFDBLUE_BLUE_MASTER_N_MAC			"BLUE_MASTER_DEV%d_MAC"			// 设备MAC地址

#define NAME_CANFDBLUE_BLUE_WHITE_LIST_MAC_N		"BLUE_WHITE_LIST_MAC%d"		    // 白名单MAC列表，最多5个，序号从1开始

#define NAME_CANFDBLUE_USB_COM_BAUDRATE				"USB_COM_BAUDRATE"				// 串口波特率, USB虚拟串口
#define NAME_CANFDBLUE_USB_COM_STOPBIT				"USB_COM_STOPBIT"				// 停止位
#define NAME_CANFDBLUE_USB_COM_DATABIT				"USB_COM_DATABIT"				// 数据位
#define NAME_CANFDBLUE_USB_COM_PARITY				"USB_COM_PARITY"				// 校验位

#define NAME_CANFDBLUE_CONVERT_MODE				    "CONVERT_MODE"				    // 工作模式, 最多2组转发, 序号从1开始
// #define NAME_CANFDBLUE_CONVERT_PACKET_CNT           "CONVERT_PACKET_CNT"			// CAN报文封包帧数
// #define NAME_CANFDBLUE_CONVERT_PACKET_TMO           "CONVERT_PACKET_TMO"			// 超时封包间隔
#define NAME_CANFDBLUE_CONVERT_RECV_BUF_MODE        "CONVERT_RECV_BUF_MODE"		    // 接收缓存区处理方式
// #define NAME_CANFDBLUE_CONVERT_RETRY_NUM			"CONVERT_RETRY_NUM"			    // 数据发送失败重发次数
#define NAME_CANFDBLUE_CONVERT_DIRECT_CTRL0			"CONVERT_DIRECT_CTRL0"			// 控制转发方向(第一路)
#define NAME_CANFDBLUE_CONVERT_DIRECT_CTRL1			"CONVERT_DIRECT_CTRL1"			// 控制转发方向(第二路)



#endif
