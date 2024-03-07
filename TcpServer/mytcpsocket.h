#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include "protocol.h"

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket();

public slots:
    void recvMsg(); // 槽函数，按照协议形式处理传输过来的数据
};

#endif // MYTCPSOCKET_H
