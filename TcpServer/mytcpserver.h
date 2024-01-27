#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer();

    // 单例编程
    static MyTcpServer &getInstance();

    void incomingConnection(qintptr handle) override;
};

#endif // MYTCPSERVER_H
