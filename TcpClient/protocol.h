#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdlib.h>
#include <string>
#include <unistd.h>


typedef unsigned int uint;

struct PDU
{
    uint uiPDULen;      // 总的协议数据单元大小
    uint uiMsgType;     // 消息类型
    char caData[64];    // 数组
    uint uiMsgLen;      // 实际消息长度
    int caMsg[];        // 实际信息
};

// 产生结构体PDU
PDU *mkPDU(uint uiMsgLen);


#endif // PROTOCOL_H
