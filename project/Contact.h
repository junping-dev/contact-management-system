#ifndef CONTACT_H
#define CONTACT_H
#include<QString>
#include<QSqlDatabase>
#include <QSqlQuery>
#include"Date.h"
class Contact
{
protected:
    int id;
    QString name,tel,email;
    Date birth;
public:
    Contact(QString n,int y,int m,int d,QString t,QString e,int id=-1);
    Contact(){};
    virtual ~Contact(){}
    //公共的添加操作
    virtual bool saveToDB(QSqlDatabase& db);
    //显示
    virtual QString show()=0;
    //id
    void setId(int i);
    int getId()const;
    //获取元素
    QString getName() const;
    QString getTel() const;
    QString getEmail() const;
    Date getBirth() const;
    virtual QString getExtra()=0;
    virtual QString getClassName()=0;
    // //没有使用update函数
    // // 公共的 update 实现
    // virtual bool updateInDB(QSqlDatabase& db,QString category,int id);

};
#endif // CONTACT_H
