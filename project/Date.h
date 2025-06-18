#ifndef DATE_H
#define DATE_H
#include<QString>
#include<QDate>
class Date
{
private:
    int year,mon,day;
public:
    Date(int y,int m,int d);
    Date(){}
    //
    static Date getToday();
    //读取数据
    int getYear() const ;
    int getMonth() const ;
    int getDay() const ;
    //写数据，并进行数据和法性检查
    bool setYear(int y);
    bool setMonth(int m);
    bool setDay(int d);
    //展示数据
    QString show();
    //判断闰年
    static bool isLeapYear(int y);

    static int getDayInMonth(int y,int m);

    static bool isValid(int y,int m,int d);
    //
    bool operator<(const Date&other)const;
    //
    int toDays()const;
    //
    int operator-(const Date&other)const;
    //
    QString getWhatDay();

};
#endif // DATE_H
