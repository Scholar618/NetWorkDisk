#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdlib.h>
#include <string>
#include <unistd.h>


typedef unsigned int uint;

#define REGISTER_OK "register ok!"
#define REGISTER_Name_FAILED "register failed,Name has existed!"

// 消息类型
enum ENUM_MSG_TYPE
{
    ENUM_MSG_TYPE_Min = 0,
    ENUM_MSG_TYPE_REGISTER_REQUEST, // 请求
    ENUM_MSG_TYPE_REGISTER_RESPOND, // 回复
    ENUM_MSG_TYPE_Max = 0x00ffffff, // 32位
};

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
