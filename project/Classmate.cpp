#include"Classmate.h"
Classmate::Classmate(QString n,int y,int m,int d,QString t,QString e,QString s,int id):Contact(n,y,m,d,t,e,id),school(s){}
QString Classmate::getExtra()
{
    return school;
}
 QString Classmate::show()
{
     QString show=QString("姓名：%1，电话：%2，邮件地址：%3，出生日期：%4，一起上学的学校：%5").arg(name,tel,email,birth.show(),school);
    return show;
}
QString Classmate::getClassName()
{
    return QString("classmates");
}
