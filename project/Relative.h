#ifndef RELATIVE_H
#define RELATIVE_H
#include<QString>
#include"Contact.h"
class Relative:public Contact
{
private:
    QString call;
public:
    Relative(QString n,int y,int m,int d,QString t,QString e,QString c,int id=-1);
    Relative(){};
    QString getExtra();
    QString show();
    QString getClassName();
};

#endif // RELATIVE_H
