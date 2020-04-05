// James Armstrong
// todo.cpp
// Due: April 5, 2020;

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

// Class prototypes
class Date
{
private:
    friend ostream &operator<<(ostream &, Date);
    friend istream &operator>>(istream &, Date &);
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

class TodoItem
{
private:
    string todo;
    Date dateAdded;
    int id;

    static int ID; // Used to give sequential enumerataion of future TodoItems

public:
    TodoItem();
    TodoItem(Date, string, int);

    static void componentTest();

    void operator=(string);
    bool operator==(string);
    bool operator==(TodoItem &t);
    bool operator==(int);
    friend ostream &operator<<(ostream &, TodoItem &);

    int getId();
    void setId(int);

    string getTodo();
    void setTodo(string);

    Date getDate();
    void setDate(Date);

    static void setStaticId(int);
    static int getStaticId();
};

class TodoList
{
private:
    bool dummyItem; // Used for Spec A4, where if true, then override the dummy with true data
    int todosSize;
    TodoItem *todos; // Specification C4 - TODO array
    void removeIndex(int);
    string logFile;

public:
    TodoList(string = "");
    TodoList(TodoList &);

    void addItem();
    void addItem(string);
    void addItem(TodoItem);
    void removeItem(int);
    void increment();
    void decrement();
    void logTodo(TodoItem);

    // Program Greeting
    void programGreeting();
    bool promptUser();

    static void componentTest();

    friend string operator>>(string, TodoList &t);
    friend ostream &operator<<(ostream &, TodoList &);
};

int main()
{
    srand(time(0));
    Date::componentTest();
    TodoItem::componentTest();
    TodoList::componentTest();
    cout << "---------------------------------------" << endl;

    TodoList t("log.txt");
    t.programGreeting();

    bool loop = true;
    while (loop)
        loop = t.promptUser();
    return 0;
}

void TodoItem::componentTest()
{
    Date now;
    TodoItem t(now, "test", 1234);

    // TodoItem initialization test. This is essentially 3 diagnostic tests in just 3 lines
    cout << "TodoItem initialization ";
    (t == 1234 && t == "test" && t.getDate().getDate() == now.getDate()) ?
        cout << "works\n" : cout << "doesn't work\n";
    cout << endl;
}
int TodoItem::ID = 0;

string TodoItem::getTodo() { return todo; }

void TodoItem::setTodo(string x) { todo = x; }

Date TodoItem::getDate() { return dateAdded; }

void TodoItem::setDate(Date x) { dateAdded = x; }

void TodoItem::setStaticId(int x) { ID = x; }

int TodoItem::getStaticId() { return ID; }

// Specification A4 - Overload Constructor
// This is used not only for A4 specifications, but for copying elements from the logfile to the
// array.
TodoItem::TodoItem(Date d, string t, int id)
{
    dateAdded = d;
    todo = t;
    this->id = id;
}

TodoItem::TodoItem()
{
    Date now;
    todo = "";

    // Specification A3 - System Date
    dateAdded = now;
}

int TodoItem::getId() { return id; };

void TodoItem::setId(int x) { id = x; };

// Specification A2 - Overload Assignment Operator
void TodoItem::operator=(string n)
{
    todo = n;
    id = ID++;
}

bool TodoItem::operator==(string n)
{
    return todo == n;
}

bool TodoItem::operator==(TodoItem &t)
{
    return todo == t.todo;
}

bool TodoItem::operator==(int id)
{
    return this->id == id;
}

// Specification C1 - Overload «
ostream &operator<<(ostream &o, TodoList &t)
{
    for (int i = 0; i < t.todosSize; i++)
    {
        o << "Todo #" << i + 1 << ":\n";
        o << t.todos[i];
        o << endl;
    }
    return o;
}

// Specification C2 - Overload »
string operator>>(string s, TodoList &t)
{
    t.addItem(s);
    return s;
}

ostream &operator<<(ostream &o, TodoItem &t)
{
    o << "Date added: " << t.dateAdded << '\n';
    o << "ID #: " << t.id << '\n';
    o << "Todo: " << t.todo << '\n';

    return o;
}

// Specification A1 - Overload Copy Constructor
TodoList::TodoList(TodoList &t)
{
    dummyItem = t.dummyItem;
    todosSize = t.todosSize;

    // Copy all elements in dynamic array to new pointer
    todos = new TodoItem[todosSize];
    for (int i = 0; i < todosSize; i++)
        todos[i] = t.todos[i];

    logFile = t.logFile;
}

// Specification C3 - Test TODO's
void TodoList::componentTest()
{
    TodoList x;
    "One" >> x;
    "Two" >> x;
    "3" >> x;
    "4" >> x;
    "5" >> x;
    cout << "TodoList::addItem() and >> operator ";
    (x.todos[0] == "One" && x.todos[1] == "Two" &&
     x.todos[2] == "3" && x.todos[3] == "4" && x.todos[4] == "5")
        ? cout << "works\n"
        : cout << "doesn't work\n";

    x.removeItem(0);
    x.removeItem(3);

    cout << "TodoList::removeItem() ";
    (x.todos[0] == "Two" && x.todos[2] == "5") ? cout << "works\n" : cout << "doesn't work\n";
    cout << endl;

    // Copy constructor testing
    TodoList y(x);

    cout << "TodoList copy constructor ";
    (x.todos[0] == y.todos[0] && x.todos[2] == y.todos[2]) ? cout << "works\n" : cout << "doesn't work\n";
    cout << endl;
}

// Helper function for prompUser()
bool stringIsInt(string x)
{
    for (char c : x)
    {
        // Checks if character is not in btwn 48 and 57 in ASCII. That range is for integers
        if (static_cast<int>(c) < 48 || static_cast<int>(c) > 57)
            return false;
    }

    return true;
}

// Returns false if person inputted to quit
bool TodoList::promptUser()
{
    char cmd;
    string input;
    cout << "\"+*input*\" to add as a todo, \"-*ID*\" to remove, \"?\" to list the todos. (e.g. +Do the dishes)\n";
    cout << "q to quit\n";
    cout << "Enter your command: ";
    cin >> cmd;

    // Quit statement
    if (cmd == 'q')
        return false;
    else if (cmd != '?')
    {
        getline(cin, input);

        // Trim trailing whitespace
        int i = 0;
        while (input[i] == ' ')
            i++;

        input = input.substr(i);
    }

    while (
        !cin ||
        (cmd != '+' && cmd != '?' && cmd != '-') ||
        (cmd == '-' && !stringIsInt(input)))
    {
        cout << "Invalid input. Please try again.\n";
        cout << "Enter your command: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cmd;

        if (cmd == 'q')
            return false;
        else if (cmd != '?')
            cin >> input;
    }

    switch (cmd)
    {

    // Specification B1  - + Symbol
    case '+':
        if (!dummyItem && input == "")
        {
            dummyItem = true;

            // This makes a dummy item
            addItem();
        }

        else if (!dummyItem)
            input >> *this;

        // This is enacted when real data is inputted when there is a dummy item
        else if (input != "")
        {
            // Using the assignment operator here will unnecessarily increment id again (it's incremented
            // in the assignment operator constructor)
            todos[todosSize - 1].setTodo(input);

            Date now;
            todos[todosSize - 1].setDate(now);

            todos[todosSize - 1].setId(TodoItem::getStaticId());
            TodoItem::setStaticId(TodoItem::getStaticId() + 1);

            logTodo(todos[todosSize - 1]);

            dummyItem = false;
        }
        break;

    // Specification B3  - - Symbol
    case '-':
        removeItem(stoi(input));
        break;

    // Specification B2  - ? Symbol
    case '?':
        cout << "\n---------------------------------------\n";
        cout << *this;
        cout << "---------------------------------------\n";
        break;

    // In 99.99% of cases, the user shouldn't be getting the default case
    default:
        cout << "Somewhere it's broken, and I don't know how you got here.\n";
        break;
    }
    cout << endl;

    return true;
}

void TodoList::logTodo(TodoItem x)
{
    std::ofstream f(logFile, std::ofstream::app);

    f << x;
    f.close();
}

// Dummy item add
void TodoList::addItem()
{
    Date dumm(0, 0, 0, 0, 0, 0);
    TodoItem t(dumm, "dummy", 99999);
    increment();
    todos[todosSize - 1] = t;
}

void TodoList::addItem(string todo)
{
    increment();
    todos[todosSize - 1] = todo;
    logTodo(todos[todosSize - 1]);
}

void TodoList::addItem(TodoItem todo)
{
    increment();
    todos[todosSize - 1] = todo;
    // Don't need to logTodo because this function is only used when copying from a log file
}

void TodoList::removeItem(int id)
{
    bool found = false;
    for (int i = 0; i < todosSize; i++)
    {
        if (todos[i].getId() == id)
        {
            removeIndex(i);
            decrement();
            found = true;
        }
    }

    if (!found)
        cout << "Item not found. Please try again.\n"
             << endl;
    else
    {
        cout << "Item " << id << " deleted.\n"
             << endl;

        // Because an item was deleted, we need to update the logfile. It's easier to delete
        // the entire thing and then put all the elements back in
        ofstream f(logFile);
        for (int i = 0; i < todosSize; i++)
        {
            f << todos[i];
        }
        f.close();
    }
}

// Increment array size by one.
void TodoList::increment()
{
    TodoItem *temp = new TodoItem[todosSize + 1];
    for (int i = 0; i < todosSize; i++)
        temp[i] = todos[i];

    delete[] todos;
    todos = temp;
    temp = nullptr;
    todosSize++;
}

// Decrement array size by one.
void TodoList::decrement()
{
    TodoItem *temp = new TodoItem[todosSize - 1];
    for (int i = 0; i < todosSize - 1; i++)
        temp[i] = todos[i];

    delete[] todos;
    todos = temp;
    temp = nullptr;
    todosSize--;
}

// Given an index, push every item from the right to left once starting at index
void TodoList::removeIndex(int index)
{
    for (int i = index; i < todosSize - 1; i++)
        todos[i] = todos[i + 1];
}

TodoList::TodoList(string file)
{
    dummyItem = false;
    todosSize = 0;
    todos = new TodoItem[0];
    logFile = file;

    // Specification B4 - Persistence
    // If file exists, then copy the previous todo list to the new one
    if (logFile != "")
    {
        ifstream f(logFile);

        // f.eof() by itself doesn't check if the pointer is at the end of file. It only returns true
        // if a previous read has been made and if the read fails because it's at the end of file,
        // it returns true to note that. We need f.peek() to know if we are already at the end of the
        // file WITHOUT reading a line.
        int x = f.peek();

        // Loops to get each logged todo item
        while (x != EOF)
        {
            string dateAdded;
            getline(f, dateAdded);

            // If dateAdded is blank, then we are at the end of the file and there is no more items
            // to add.
            if (dateAdded == "")
                break;
            dateAdded = dateAdded.substr(12); // Remove "Date added:" prefix

            // Get each element of the date from the dateAdded string
            int month = stoi(dateAdded.substr(0, 2));
            int day = stoi(dateAdded.substr(3, 2));
            int year = stoi(dateAdded.substr(6, 4));
            int hour = stoi(dateAdded.substr(11, 2));
            int min = stoi(dateAdded.substr(14, 2));
            int sec = stoi(dateAdded.substr(17, 4));

            Date x(month, day, year, hour, min, sec);

            string id;
            getline(f, id);
            id = id.substr(6); // Remove everything in "ID #: ..." except "..."

            // This will be used to prevent duplicate ids by making the static var LogItem::ID start
            // at this larger Id
            if (stoi(id) > TodoItem::getStaticId())
                TodoItem::setStaticId(stoi(id));

            string todo;
            getline(f, todo);
            todo = todo.substr(6); // Same thing as before. Remove "Todo: ";

            TodoItem i(x, todo, stoi(id));

            addItem(i);

            // This ignores the newline per each item so that the parser can get the next one
            f.ignore(1);
        }
        f.close();

        // Because the static var TodoItem::ID is set to the largest id, we need to increment it
        // up one to prevent a single duplicate.
        TodoItem::setStaticId(TodoItem::getStaticId() + 1);
    }
}

void TodoList::programGreeting()
{
    cout << "Author: James Armstrong\n";
    cout << "File: todo.cpp - Add, delete, and view your todo items\n";
    cout << "Due: April 5, 2020" << endl;

    Date now;
    cout << "Current date: " << now << '\n';
    cout << "---------------------------------------" << endl;
}

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
    else
        cout << "getMonth() is not working\n";

    if (day == d.getDay() && now->tm_mday == dd.getDay())
        cout << "getDay() is working\n";
    else
        cout << "getDay() is not working\n";

    if (year == d.getYear() && now->tm_year + 1900 == dd.getYear())
        cout << "getYear() is working\n";
    else
        cout << "getYear() is not working\n";

    if (hour == d.getHour() && now->tm_hour == dd.getHour())
        cout << "getHour() is working\n";
    else
        cout << "getHour() is not working\n";

    if (minute == d.getMinute() && now->tm_min == dd.getMinute())
        cout << "getMinute() is working\n";
    else
        cout << "getMinute() is not working\n";

    if (second == d.getSecond() && now->tm_sec == dd.getSecond())
        cout << "getSecond() is working\n";
    else
        cout << "getSecond() is not working\n";

    cout << endl;
}

void Date::componentTestOperator()
{
    Date d(0, 0, 0, 0, 0, 0);
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

ostream &operator<<(ostream &o, Date d)
{
    o << d.getDate();
    return o;
}

istream &operator>>(istream &i, Date &d)
{
    i >> d.month >> d.day >> d.year >> d.hour >> d.minute >> d.second;
    return i;
}
