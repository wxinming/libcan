# libcan
CAN卡类库
```
#include <libcan/libcan.h>
#ifdef _DEBUG
#pragma comment(lib, "libcand.lib")
#else
#pragma comment(lib, "libcan.lib")
#endif

int main()
{
    // 返回智能指针std::shared_ptr<can::Base>, 此处为使用周立功USBCANFD200U为例做演示
    auto cansp = can::autoReleaseNew(can::ZLG_USBCANFD200U);

    // 打开CAN日志文件
    FILE* fp = fopen("canlog.txt", "w");
    
    do {
        // 设置过滤的ID
        cansp->setFilterId({ 0x727, 0x7a7 });
        
        // 调试控制台输出日志
        cansp->setOutputLog(true);

        // 注册报文回调并且将日志写入到文件中
        cansp->setMsgProc([cansp, fp](const char* direction, const can::Msg& msg) {
	        std::cout << direction << "->" << msg << std::endl;
            if (fp) {
                fprintf(fp, "%s", cansp->fmtMsg(direction, msg).c_str());
                fflush(fp);
            }
        });

        // 创建摩托罗拉LSB的CAN矩阵算法类
        can::Matrix matrix(can::Matrix::MOTOROLA_LSB);

        // 设置CAN矩阵算法
        cansp->setMatrix(&matrix);

        can::Device dev;

        // 打开索引0的设备
        dev.deviceIndex = 0;

        // 启用第0个通道
        dev.enableChannel[0] = true;

        // 启用第1个通道
        dev.enableChannel[1] = true;

        // 设置通道0仲裁域500kbps
        dev.arbiBaud[0] = 500;

        // 设置通道1仲裁域500kbps
        dev.arbiBaud[1] = 500;

        // 设置通道0数据域2Mbps
        dev.dataBaud[0] = 2000;

        // 设置通道1数据域2Mbps
        dev.dataBaud[1] = 2000;

        // 打开CAN卡
        if (!cansp->open(dev)) {
            std::cout << cansp->getLastError() << std::endl;
            break;
        }

        can::Msg msg[2];
        msg[0].id = 0x100;
        msg[1].id = 0x200;

        // 添加起始位从5开始,长度为10个比特位,数据为128的报文
        cansp->addMsg(msg[0], 5, 10, 128, 0); 

        // 添加起始位从8开始,长度为12个比特位,数据为256的报文
        cansp->addMsg(msg[1], 8, 12, 256, 1);

        // 启动异步发送报文
        cansp->startAsyncSendMsg();
        
        // 等待用户输入q退出
        while (getchar() != 'q'); 

        // 停止异步发送报文
        cansp->stopAsyncSendMsg();

        // 关闭CAN卡
        cansp->close(); 

    } while(false);

    // 关闭CAN日志文件
    if (fp) {
        fclose(fp);
    }
    return 0;
}
```