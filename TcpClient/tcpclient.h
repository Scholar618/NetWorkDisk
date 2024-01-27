#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void loadConfig();

public slots:
    void showConnect();

private:
    Ui::TcpClient *ui;
    QString m_strIP;    // IP
    quint16 m_usPort;   // 无符号短整型Port

    // m_tcpSocket用于连接服务器，和服务器的数据进行交互
    QTcpSocket m_tcpSocket;
};
#endif // TCPCLIENT_H
