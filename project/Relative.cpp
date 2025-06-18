#include"Relative.h"
Relative::Relative(QString n,int y,int m,int d,QString t,QString e,QString c,int id):Contact(n,y,m,d,t,e,id),call(c){}
QString Relative::getExtra()
{
    return call;
}
QString Relative::show()
{
    QString show=QString("姓名：%1，电话：%2，邮件地址：%3，出生日期：%4，称呼：%5").arg(name,tel,email,birth.show(),call);
    return show;
}
QString Relative::getClassName()
{
    return QString("relatives");
}
