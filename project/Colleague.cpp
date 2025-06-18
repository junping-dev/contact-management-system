#include"Colleague.h"
Colleague::Colleague(QString n,int y,int m,int d,QString t,QString e,QString en,int id):Contact(n,y,m,d,t,e,id),enterprise(en){}
QString Colleague::getExtra()
{
    return enterprise;
}

QString Colleague::show()
{
    QString show=QString("姓名：%1，电话：%2，邮件地址：%3，出生日期：%4，共事的单位：%5").arg(name,tel,email,birth.show(),enterprise);
    return show;
}
QString Colleague::getClassName()
{
    return QString("colleagues");
}
