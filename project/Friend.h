#ifndef FRIEND_H
#define FRIEND_H
#include<QString>
#include"Contact.h"
class Friend:public Contact
{
private:
    QString location;
public:
    Friend(QString n,int y,int m,int d,QString t,QString e,QString l,int id=-1);
    Friend(){};
    QString getExtra();
     QString show();
    QString getClassName();
};

#endif // FRIEND_H
