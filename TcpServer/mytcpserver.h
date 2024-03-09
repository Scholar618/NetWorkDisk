#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <mytcpsocket.h>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer();

    // 单例编程
    static MyTcpServer &getInstance();

    void incomingConnection(qintptr handle) override;

private:
    QList<MyTcpSocket*> m_tcpSocketList; // 存储服务器所有已经建立的Socket连接
};

#endif // MYTCPSERVER_H
