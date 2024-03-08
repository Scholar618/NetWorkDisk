#include "dboperate.h"
#include <QMessageBox>
#include <QDebug>

DBOperate::DBOperate(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QODBC"); // 使用ODBC连接数据库
}

DBOperate &DBOperate::getInstance()
{
    static DBOperate instance;
    return instance;
}

void DBOperate::init()
{
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("networkdiskdb");
    m_db.setUserName("root");              // 数据库用户名
    m_db.setPassword("my-root-123");              // 数据库密码

    if(m_db.open())
    {
        QSqlQuery query;
        query.exec("select * from userInfo");
        while(query.next())
        {
            QString data = QString("%1, %2, %3, %4").arg(query.value(0).toString()).arg(query.value(1).toString())
               .arg(query.value(2).toString()).arg(query.value(3).toString());
            qDebug() << data;
        }
    }
    else
    {
        QMessageBox::critical(NULL, "打开数据库", "打开数据库失败");
    }
}

DBOperate::~DBOperate()
{
    m_db.close();
}
