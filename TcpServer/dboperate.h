#ifndef DBOPERATE_H
#define DBOPERATE_H
// 数据库操作
#include <QObject>
#include <QSqlDatabase> // 连接数据库
#include <QSqlQuery>    // 查询数据库

class DBOperate : public QObject
{
    Q_OBJECT
public:
    explicit DBOperate(QObject *parent = nullptr);
    static DBOperate& getInstance();
    void init();
    ~DBOperate();
signals:

public slots:
private:
    QSqlDatabase m_db;  // 连接数据库
};

#endif // DBOPERATE_H
