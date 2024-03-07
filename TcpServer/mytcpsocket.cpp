#include "mytcpsocket.h"


MyTcpSocket::MyTcpSocket()
{
    connect(this, SIGNAL(readyRead())
            , this, SLOT(recvMsg()));
}

// 处理各自socket收到的数据
void MyTcpSocket::recvMsg()
{
    qDebug() << this -> bytesAvailable(); // 获取接收到的数据大小
    uint uiPDULen = 0;
    this->read((char*)&uiPDULen, sizeof(uint)); // 先读取uint大小的数据，首个uint正是总数据大小
    uint uiMsgLen = uiPDULen - sizeof(PDU); // 实际消息大小，sizeof(PDU)只会计算结构体大小，不包括实际信息长度
    PDU *pdu = mkPDU(uiMsgLen);
    this -> read((char*)pdu + sizeof(uint), uiPDULen - sizeof(uint)); // 接收剩余部分数据（第一个uint已读取）
    qDebug() << pdu -> uiMsgType << ' ' << (char*)pdu -> caMsg; // 输出
}
