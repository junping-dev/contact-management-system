#ifndef COLLEAGUE_H
#define COLLEAGUE_H
#include<QString>
#include"Contact.h"
class Colleague:public Contact
{
private:
    QString enterprise;
public:
    Colleague(QString n,int y,int m,int d,QString t,QString e,QString en,int id=-1);
    Colleague(){};
    QString getExtra();
    QString show();
    QString getClassName();
};

#endif // COLLEAGUE_H
