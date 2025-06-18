#include"Friend.h"
Friend::Friend(QString n,int y,int m,int d,QString t,QString e,QString l,int id):Contact(n,y,m,d,t,e,id),location(l){}
QString Friend::getExtra()
{
    return location;
}
QString Friend::show()
{
    QString show=QString("姓名：%1，电话：%2，邮件地址：%3，出生日期：%4，认识的地点：%5").arg(name,tel,email,birth.show(),location);
    return show;
}
QString Friend::getClassName()
{
    return QString("friends");
}

