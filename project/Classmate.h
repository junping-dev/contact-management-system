#ifndef CLASSMATE_H
#define CLASSMATE_H
#include"Contact.h"
#include<QString>
#include<QSqlDatabase>
#include <QSqlQuery>
class Classmate:public Contact
{
private:
    QString school;
public:
    Classmate(QString n,int y,int m,int d,QString t,QString e,QString s,int id=-1);
    Classmate(){};
    QString getExtra();
    QString show();
    QString getClassName();
};


#endif // CLASSMATE_H
