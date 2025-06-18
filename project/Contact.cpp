#include "Contact.h"
Contact::Contact(QString n, int y, int m, int d, QString t, QString e, int id):id(id),name(n),tel(t),email(e),birth(y,m,d){}
void Contact::setId(int i)
{
    id=i;
}
int Contact::getId()const
{
    return id;
}

QString Contact::getName() const
{
    return name;
}

QString Contact::getTel() const
{
    return tel;
}

QString Contact::getEmail() const
{
    return email;
}

Date Contact::getBirth() const
{
    return birth;
}
bool Contact::saveToDB(QSqlDatabase& db)
{
    QSqlQuery query(db);
    QString sql = QString("INSERT INTO %1 (name, year, mon, day, tel, email, extra) VALUES (?, ?, ?, ?, ?, ?, ?)").arg(getClassName());
    query.prepare(sql);
    query.addBindValue(name);
    query.addBindValue(birth.getYear());
    query.addBindValue(birth.getMonth());
    query.addBindValue(birth.getDay());
    query.addBindValue(tel);
    query.addBindValue(email);
    query.addBindValue(getExtra());
    return query.exec();
}
// //注意，由于这个接口无法实现我的UI界面的操作逻辑，并没有用到这个函数
// bool Contact::updateInDB(QSqlDatabase& db,QString category,int id)
// {
//     QSqlQuery query(db);
//     QString sql = QString("UPDATE %1 SET tel=?, email=?, extra=? WHERE id=?").arg(category);
//     query.prepare(sql);
//     query.addBindValue(tel);
//     query.addBindValue(email);
//     query.addBindValue(getExtra());
//     query.addBindValue(id);
//     return query.exec();
// }

