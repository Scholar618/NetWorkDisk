#include "protocol.h"

// 动态申请空间
PDU *mkPDU(uint uiMsgLen)
{
    uint uiPDULen = sizeof(PDU) + uiMsgLen; // 要申请的大小
    PDU *pdu = (PDU*)malloc(uiPDULen);
    if(NULL == pdu) // 申请空间失败
    {
        exit(EXIT_FAILURE); // 结束程序
    }
    memset(pdu, 0, uiPDULen);
    pdu->uiPDULen = uiPDULen;
    pdu->uiMsgLen = uiMsgLen;
    return pdu;
}
