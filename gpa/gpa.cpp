// gpa.cpp
// James Armstrong
// 2-16-20

#include <iostream>
#include <limits>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// "double*&" is a reference to a pointer
// Function prototypes
void processAnswer(double *&, int &, int);
char getLetterGrade(double);
void processGrades(double *&, int);
void displayGrades(double *&, int);
double getGrade();
void incrementArray(double *&, int &);
void addGrade(double *&, int &);
void programGreeting();
int displayMenu();
void unitTest();

int main()
{
    programGreeting();
    unitTest();

    int size = 0;

    // Specification B1 - Dynamic Array
    double* grades = new double[size];

    int answer = displayMenu();
    while (answer != 4)
    {
        processAnswer(grades, size, answer);
        answer = displayMenu();
    }
    return 0;
}

// Process the answer given from the menu
void processAnswer(double *&grades, int &size, int answer)
{
    if (answer == 1)
        addGrade(grades, size);
    else if (answer == 2)
        displayGrades(grades, size);
    else if (answer == 3)
        processGrades(grades, size);
}

// -------------------------------------------------------------------------
// Functions related to displaying grades and GPA

// Specification C3 - Letter Grades
char getLetterGrade(double grade)
{
    if (grade >= 90.0)
        return 'A';
    else if (grade >= 80.0)
        return 'B';
    else if (grade >= 70.0)
        return 'C';
    else if (grade >= 60.0)
        return 'D';
    else
        return 'F';
}

// Get letter grade from the gpa score
char getLetterGradeGPA(double gpa)
{
    if (gpa >= 4.0)
        return 'A';
    else if (gpa >= 3.0)
        return 'B';
    else if (gpa >= 2.0)
        return 'C';
    else if (gpa >= 1.0)
        return 'D';
    else
        return 'F';
}

// Print out the GPA
// Specification C4 - Compute GPA
void processGrades(double *&grades, int size)
{
    if (size == 0)
    {
        cout << "You didn't input any grades\n";
        return;
    }

    double gpa = 0;
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        char letterGrade = getLetterGrade(grades[i]);

        if (letterGrade == 'A')
            sum += 4;
        else if (letterGrade == 'B')
            sum += 3;
        else if (letterGrade == 'C')
            sum += 2;
        else if (letterGrade == 'D')
            sum += 1;
    }

    gpa = sum / size;

    // Specification B4 - Print Letter Grade
    cout << "GPA: " << gpa << " (" << getLetterGradeGPA(gpa) << ")\n\n";
}

// Specification C2 - Print Scores
void displayGrades(double *&grades, int size)
{
    if (size == 0)
    {
        cout << "You didn't input any grades\n";
        return;
    }

    cout << "----------------------------------------\n";
    for (int i = 0; i < size; i++)
        cout << "Grade " << i + 1 << ": " << getLetterGrade(grades[i])
             << " - " << grades[i] << "/100\n";
    cout << "----------------------------------------\n\n";
}

// -------------------------------------------------------------------------
// Functions related to adding grades

// Gets grade from user. Helper function for addGrade()
double getGrade()
{
    double grade = 0;

    cout << "Enter Grade (in points): ";
    cin >> grade;

    // cin has a bool operator oveload that returns false if there is an error
    while (!cin || grade < 0)
    {
        cout << "Invalid input. Please try again: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> grade;
    }
    cout << '\n';

    return grade;
}

// Increment array size by one. Helper function for addGrade()
// Specification B2 - Add Elements
void incrementArray(double*& array, int& size)
{
    double *temp = new double[size + 1];
    for (int i = 0; i < size; i++)
        temp[i] = array[i];

    delete[] array;
    array = temp;
    temp = nullptr;
    size++;
}


// Add a grade to the end of the array
void addGrade(double *&grades, int &size)
{
    double grade = getGrade();

    incrementArray(grades, size);
    grades[size - 1] = grade;
}

// -------------------------------------------------------------------------
int displayMenu()
{
    int answer = 0;
    cout << "Choose a number:\n";
    cout << "1.) Add Grade\n";
    cout << "2.) Display All Grades\n";
    cout << "3.) Process All Grades\n";
    cout << "4.) Quit\n";
    cin >> answer;

    // cin has a bool operator overload that returns false if there is an error
    // Specification B3 - Menu Input Validation
    while (!cin || !(answer >= 1 && answer <= 4))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }

    cout << "\n";
    return answer;
}
// -------------------------------------------------------------------------

// Specification A1 - Date class
class Date
{
private:
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;

public:

    // Specification A2 - External date initialization
    Date(int month, int day, int year, int hour, int minute, int second);
    Date();

    // Specification A3 - Component Test Method in Date
    static void dateTest();

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

void Date::dateTest()
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
    string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year)
        + " " + to_string(hour) + ":";

    if (minute < 10) date += "0" + to_string(minute) + ":";
    else date += to_string(minute) + ":";

    if (second < 10) date += "0" + to_string(second);
    else date += to_string(second);

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

// -------------------------------------------------------------------------
// Specification A4 - Component Test Grade Conversion
void unitTest()
{
    cout << "--------------------------\n";
    cout << "UNIT TEST\n";
    
    Date::dateTest();

    int a = 90;
    int b = 80;
    int c = 70;
    int d = 60;
    int f = 50;

    // getLetterGrade(int) is a helper function to getGrade(). getGrade() finds any errors
    // in the input, so another input validation is not needed in getLetterGrade(int)
    bool working = true;
    if (getLetterGrade(a) != 'A' ||
        getLetterGrade(b) != 'B' || 
        getLetterGrade(c) != 'C' || 
        getLetterGrade(d) != 'D' || 
        getLetterGrade(f) != 'F'
        ) working = false;

    if (working) cout << "getLetterGrade(int) is working\n";
    else cout << "getLetterGrade(int) is not working\n";
    
    cout << "--------------------------\n" << endl;
}

// Specification C1 - Program Greeting Function
void programGreeting()
{
    Date dueDate(2, 16, 2020, 23, 59, 59);
    cout << "James Armstrong - GPA program\n";
    cout << "Due date: " << dueDate.getDate() << '\n';
    cout << endl;
}