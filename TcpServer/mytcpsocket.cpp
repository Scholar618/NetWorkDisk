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
    switch(pdu->uiMsgType)
    {
    case ENUM_MSG_TYPE_REGISTER_REQUEST:
    {
        char caName[32] = {'\0'};
        char caPwd[32] = {'\0'};
        strncpy(caName, pdu->caData, 32);
        strncpy(caPwd, pdu->caData + 32, 32);
        bool ret = DBOperate::getInstance().handleRegister(caName, caPwd);
        PDU *respdu = mkPDU(0);
        respdu->uiMsgType = ENUM_MSG_TYPE_REGISTER_RESPOND;
        if(ret)
        {
            strcpy(respdu->caData, REGISTER_OK);
        }
        else
        {
            strcpy(respdu->caData, REGISTER_Name_FAILED);
        }
        write((char*)respdu, respdu->uiPDULen);   // 发送数据给Server
        free(respdu);
        respdu = NULL;
        break;
    }
    default:
        break;
    }
    free(pdu);
    pdu = NULL;
    // qDebug() << caName << "\n" << caPwd << pdu->uiMsgType; // 输出
}
