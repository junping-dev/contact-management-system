#include<connection.h>
QSqlDatabase createConnection()
{
    QString connectionName = "my_connection";

    if (QSqlDatabase::contains(connectionName)) {
        return QSqlDatabase::database(connectionName);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("addressbook");
    db.setUserName("root");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << "数据库连接失败" << db.lastError().text();
    } else {
        qDebug() << "数据库连接成功";
    }

    return db;
}

