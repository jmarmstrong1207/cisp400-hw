#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Date
{
private:
    friend ostream& operator<<(ostream&, Date);
    friend istream& operator>>(istream&, Date&);
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;

public:
    Date(int month, int day, int year, int hour, int minute, int second);
    Date();

    static void componentTest();
    static void componentTestOperator();

    int getMonth();
    int getDay();
    int getYear();
    int getHour();
    int getMinute();
    int getSecond();
    string getDate();
};

Date::Date(int month, int day, int year, int hour, int minute, int second)
{
    this->month = month;
    this->day = day;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}
Date::Date()
{
    time_t unixNow = time(NULL);
    tm *now = localtime(&unixNow);

    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;
    this->year = now->tm_year + 1900;
    this->hour = now->tm_hour;
    this->minute = now->tm_min;
    this->second = now->tm_sec;
}


int main()
{
    Date::componentTestOperator();
    Date::componentTest();
    return 0;
}

void Date::componentTest()
{
    int month = 12;
    int day = 7;
    int year = 2000;
    int hour = 12;
    int minute = 0;
    int second = 30;

    Date d(month, day, year, hour, minute, second);
    Date dd;

    time_t unixNow = time(NULL);
    tm *now = localtime(&unixNow);

    if (month == d.getMonth() && now->tm_mon + 1 == dd.getMonth())
        cout << "getMonth() is working\n";
    else cout << "getMonth() is not working\n";

    if (day == d.getDay() && now->tm_mday == dd.getDay())
        cout << "getDay() is working\n";
    else cout << "getDay() is not working\n";

    if (year == d.getYear() && now->tm_year + 1900 == dd.getYear())
        cout << "getYear() is working\n";
    else cout << "getYear() is not working\n";

    if (hour == d.getHour() && now->tm_hour == dd.getHour())
        cout << "getHour() is working\n";
    else cout << "getHour() is not working\n";

    if (minute == d.getMinute() && now->tm_min == dd.getMinute())
        cout << "getMinute() is working\n";
    else cout << "getMinute() is not working\n";

    if (second == d.getSecond() && now->tm_sec == dd.getSecond())
        cout << "getSecond() is working\n";
    else cout << "getSecond() is not working\n";

    cout << endl;
}

void Date::componentTestOperator()
{
    Date d(0,0,0,0,0,0);
    cout << "Input the day, month, year, hour, min, second for the date:\n";
    cin >> d;
    cout << d << endl;
}

int Date::getMonth()
{
    return month;
}
int Date::getDay()
{
    return day;
}
int Date::getYear()
{
    return year;
}

string Date::getDate()
{
    string date = "";

    if (month < 10)
        date += "0" + to_string(month) + "/";
    else
        date += to_string(month) + "/";
        
    if (day < 10)
        date += "0" + to_string(day) + "/";
    else
        date += to_string(day) + "/";

    date += to_string(year) + " ";
    
    if (hour < 10)
        date += "0" + to_string(hour) + ":";
    else
        date += to_string(hour) + ":";

    if (minute < 10)
        date += "0" + to_string(minute) + ":";
    else
        date += to_string(minute) + ":";

    if (second < 10)
        date += "0" + to_string(second);
    else
        date += to_string(second);

    return date;
}

int Date::getHour()
{
    return hour;
}
int Date::getMinute()
{
    return minute;
}
int Date::getSecond()
{
    return second;
}

ostream& operator<<(ostream& o, Date d)
{
    o << d.getDate();
    return o;
}

istream& operator>>(istream& i, Date& d)
{
    i >> d.month >> d.day >> d.year >> d.hour >> d.minute >> d.second;
    return i;
}