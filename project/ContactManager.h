#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H
#include<QVector>
#include<fstream>
#include<string>
#include<QFile>
#include<QTextStream>
#include"connection.h"
#include"Contact.h"
#include"Classmate.h"
#include"Colleague.h"
#include"Friend.h"
#include"Relative.h"

class ContactManager
{
private:
    QVector<Contact*> contacts;

public:
    ~ContactManager();

    static bool addContact(Contact* contact);
    static bool deleteContact(QString category,int id);
    static  bool updateContact(int id, const QString& className, const QString& tel, const QString& email, const QString& extra);
    template<class T>
    bool loadFromDB();
    bool loadAll();
    template<class T>
    static QVector<Contact*> searchInCategory(const QString& name);
    static QVector<Contact*> searchByName(const QString& name);

    QVector<Contact*> findBirthdayInDays(int days);
    void sortByName();
    void sortByBirth();
    QVector<Contact*> countBirthMonth(int month);
    QVector<Contact*>getContacts();
    static bool generateEmail(const QString& fileName, const QString& recipientName, const QString& senderName);
};

#endif // CONTACTMANAGER_H
