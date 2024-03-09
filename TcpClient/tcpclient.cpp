#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include "protocol.h"
#include <unistd.h>

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();

    connect(&m_tcpSocket, SIGNAL(connected())
            , this, SLOT(showConnect()));
    connect(&m_tcpSocket, SIGNAL(readyRead())
            , this, SLOT(recvMsg()));

    // 连接服务器
    m_tcpSocket.connectToHost(QHostAddress(m_strIP), m_usPort);

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    QFile file(":/client.config");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray byData = file.readAll();
        QString strData = byData.toStdString().c_str();
        // IP\r\n\Port\r\n
        file.close();
        strData.replace("\r\n", " ");
        QStringList strList = strData.split(" ");
        m_strIP = strList.at(0);
        m_usPort = strList.at(1).toUShort();
        qDebug() << "ip :" << m_strIP << "port :" << m_usPort;
    }
    else
    {
        QMessageBox::critical(this, "open config", "open config failed");
    }
}

void TcpClient::showConnect()
{
    QMessageBox::information(this, "连接服务器", "连接服务器成功!");
}

#if 0
// 客户端发送数据测试
void TcpClient::on_send_pb_clicked()
{
    QString strMsg = ui->lineEdit->text();
    if(!strMsg.isEmpty())
    {
        PDU *pdu = mkPDU(strMsg.size());
        pdu->uiMsgType = 8888;
        memcpy(pdu->caMsg, strMsg.toStdString().c_str(), strMsg.size());
        m_tcpSocket.write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else
    {
        QMessageBox::warning(this, "信息发送", "发送的信息不能为空！");
    }

}
#endif

// 登录按钮
void TcpClient::on_Login_pb_clicked()
{

}

// 注册按钮
void TcpClient::on_reg_pb_clicked()
{
    QString strName = ui->name_line->text();
    QString strPwd = ui->pwd_line->text();
    if(!strName.isEmpty() || !strPwd.isEmpty())
    {
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_REGISTER_REQUEST;
        strncpy(pdu->caData, strName.toStdString().c_str(), 32);    // 前32位放用户名
        strncpy(pdu->caData+32, strPwd.toStdString().c_str(), 32);  // 后32位放密码
        m_tcpSocket.write((char*)pdu, pdu->uiPDULen);   // 发送数据给Server
        free(pdu);
        pdu = NULL;
    }
    else
    {
        QMessageBox::critical(this, "注册", "用户名或密码为空，注册失败");
    }
}

// 注销按钮
void TcpClient::on_cancel_pb_clicked()
{

}

void TcpClient::recvMsg()
{
    qDebug() << m_tcpSocket.bytesAvailable(); // 获取接收到的数据大小
    uint uiPDULen = 0;
    m_tcpSocket.read((char*)&uiPDULen, sizeof(uint)); // 先读取uint大小的数据，首个uint正是总数据大小
    uint uiMsgLen = uiPDULen - sizeof(PDU); // 实际消息大小，sizeof(PDU)只会计算结构体大小，不包括实际信息长度
    PDU *pdu = mkPDU(uiMsgLen);
    m_tcpSocket.read((char*)pdu + sizeof(uint), uiPDULen - sizeof(uint)); // 接收剩余部分数据（第一个uint已读取）
    switch(pdu->uiMsgType)
    {
    case ENUM_MSG_TYPE_REGISTER_RESPOND:
    {
        if(0 == strcmp(pdu->caData, REGISTER_OK))
        {
            QMessageBox::information(this, "注册", REGISTER_OK);
        }
        else if(0 == strcmp(pdu->caData, REGISTER_Name_FAILED))
        {
            QMessageBox::warning(this, "注册", REGISTER_Name_FAILED);
        }
        break;
    }
    default:
        break;
    }
    free(pdu);
    pdu = NULL;
}
