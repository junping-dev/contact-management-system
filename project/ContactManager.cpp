#include"ContactManager.h"
//正确析构释放内存
ContactManager::~ContactManager()
{
    int n=contacts.size();
    for(int i=0;i<n;i++)
    {
        delete contacts[i];
    }
    contacts.clear();
}
//添加联系人
bool ContactManager::addContact(Contact*contact)
{
    QSqlDatabase db=createConnection();
    return contact->saveToDB(db);
}
//删除联系人
bool ContactManager::deleteContact(QString category,int id)
{
    QSqlDatabase db=createConnection();
    QSqlQuery query(db);
    QString sql="DELETE FROM "+category+" WHERE id = ?";
    query.prepare(sql);
    query.addBindValue(id);
    if(query.exec())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//更新联系人
bool ContactManager::updateContact(int id, const QString& className, const QString& tel, const QString& email, const QString& extra)
{
    QSqlDatabase db = createConnection();
    QSqlQuery query(db);
    QString sql = QString("UPDATE %1 SET tel=?, email=?, extra=? WHERE id=?").arg(className);
    query.prepare(sql);
    query.addBindValue(tel);
    query.addBindValue(email);
    query.addBindValue(extra);
    query.addBindValue(id);
    return query.exec();
}

//决定用模板做，分别从不同的表里面载入联系人
template<class T>
bool ContactManager::loadFromDB()
{
    QSqlDatabase db=createConnection();
    QSqlQuery query(db);
    T a;
    QString sql="SELECT*FROM "+a.getClassName();
    if (!query.exec(sql))
    {
        qDebug() << "Load failed:" << query.lastError().text();
        return 0;
    }
    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int year = query.value("year").toInt();
        int mon = query.value("mon").toInt();
        int day = query.value("day").toInt();
        QString tel = query.value("tel").toString();
        QString email = query.value("email").toString();
        QString extra = query.value("extra").toString();
        Contact*c= new T(name, year, mon, day, tel, email, extra,id);
        contacts.append(c);
    }
    return 1;
}
//载入全部的联系人
bool ContactManager::loadAll()
{
    return loadFromDB<Classmate>()
           &&loadFromDB<Colleague>()
            &&loadFromDB<Friend>()
           &&loadFromDB<Relative>();


}
//分别从不同的表里面查询
template<class T>
QVector<Contact*> ContactManager::searchInCategory(const QString& name)
{
    QVector<Contact*> results;
    QSqlDatabase db = createConnection();
    QSqlQuery query(db);
    T a;
    QString table = a.getClassName();  // 表名

    QString sql = QString("SELECT id, name, year, mon, day, tel, email, extra FROM %1 WHERE name = ?")
                      .arg(table);
    query.prepare(sql);
    query.addBindValue(name);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return results;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int y = query.value("year").toInt();
        int m = query.value("mon").toInt();
        int d = query.value("day").toInt();
        QString tel = query.value("tel").toString();
        QString email = query.value("email").toString();
        QString extra = query.value("extra").toString();

        Contact* c = new T(name, y, m, d, tel, email, extra, id);
        results.append(c);
    }

    return results;
}
//所有联系人的查询
QVector<Contact*> ContactManager::searchByName(const QString& name)
{
    QVector<Contact*>res;
    res+=ContactManager::searchInCategory<Classmate>(name);
    res+=ContactManager::searchInCategory<Colleague>(name);
    res+=ContactManager::searchInCategory<Friend>(name);
    res+=ContactManager::searchInCategory<Relative>(name);
    return res;
}
//找几天后的生日
QVector<Contact*> ContactManager::findBirthdayInDays(int days)
{
    QVector<Contact*>people;
    for(Contact*c:contacts)
    {
        Date today=Date::getToday();
        Date a=c->getBirth();
        int year=today.getYear();
        a.setYear(year);
        //考虑到生日可能在下一年，进行判断
        if(a-today<0)
        {
            a.setYear(year+1);
        }
        //判断是否合法，排除闰年2月29日四年才一次生日
        if(a.isValid(a.getYear(),a.getMonth(),a.getDay()))
        {
            int time=a-today;
            if(time<=days&&time>=0)
            {
                people.append(c);
            }
        }

    }
    //按生日排好序
    std::sort(people.begin(),people.end(),[](Contact* a, Contact* b) {
        return a->getBirth() < b->getBirth();
    });
    return people;
}
void ContactManager::sortByName()
{
    //按照姓名排序
    std::sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
        return a->getName() < b->getName();
    });
}
void ContactManager::sortByBirth()
{
    //按照生日排序
    std::sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
        return a->getBirth() < b->getBirth();
    });
}
//在某个月内过生日的人数
QVector<Contact*> ContactManager::countBirthMonth(int month)
{
    QVector<Contact*>sameMonth;
    loadAll();
    for(Contact*c:contacts)
    {
        if( c->getBirth().getMonth()==month)
        {
            sameMonth.append(c);
        }
    }
    return sameMonth;
}
//获取联系人
QVector<Contact*>ContactManager::getContacts()
{
    return contacts;
}
//生成邮件
bool ContactManager::generateEmail(const QString& fileName, const QString& recipientName, const QString& senderName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        out << recipientName << ":\n\n";
        out << "    祝生日快乐，健康幸福。\n\n";
        out << "                            " << senderName << "\n";
        file.close();
        return true;
    }
    return false;
}

