#include"Date.h"
//
Date::Date(int y,int m,int d):year(y),mon(m),day(d){}
//读取数据
int Date::getYear() const { return year; }
int Date::getMonth() const { return mon; }
int Date::getDay() const { return day; }
//写数据，并进行数据和法性检查
bool Date::setYear(int y)
{
    if(y>=1900&&y<=2100){year=y;return 1;}
    else{return 0;}
}
bool Date::setMonth(int m)
{
    if(m>=1&&m<=12){mon=m;return 1;}
    else{return 0;}
}
bool Date::setDay(int d)
{
    if(isValid(year,mon,d))
    {
        day=d;
        return 1;
    }
    else
    {
        return 0;
    }
}

QString Date::show()
{
    QString date=QString("%1年%2月%3日").arg(year).arg(mon).arg(day);
    return date;
}
bool Date::isLeapYear(int y)
{
    if((y%4==0&&y%100!=0)||y%400==0)
    {
        return 1;
    }
    return 0;
}
int Date::getDayInMonth(int y,int m)
{
    const int month[]={ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if(m==2&&isLeapYear(y))
    {
        return 29;
    }
    return month[m];
}
bool Date::isValid(int y,int m,int d)
{
    if(y<1900||y>2100)return 0;
    if(m<1||m>12)return 0;
    if(d<1||d>getDayInMonth(y,m))return 0;
    return 1;
}
bool Date::operator<(const Date&other)const
{
    if(year!=other.year)return year<other.year;
    if(mon!=other.mon)return mon<other.mon;
    return day<other.day;
}
int Date::toDays()const
{
    //
    int days=0;
    for(int y=1900;y<year;y++)
    {
        days+=(Date::isLeapYear(y)?366:365);
    }
    for(int m=1;m<mon;m++)
    {
        days+=Date::getDayInMonth(year,m);
    }
    days+=day;
    return days;
}
int Date::operator-(const Date&other)const
{
    return this->toDays()-other.toDays();
}
QString Date::getWhatDay()
{
    int day=-1;
    day+=this->toDays();
    day%=7;
    QString days[7]={"星期一", "星期二", "星期三", "星期四", "星期五","星期六", "星期日"};
    return days[day];
}
Date Date::getToday()
{
    QDate today = QDate::currentDate();
    return Date(today.year(), today.month(), today.day());
}
