// invinq.cpp
// James Armstrong
// Due 3-15-20

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

// Function prototypes
void programGreeting();
void unitTest();

//----------------------------------------------
// Class prototypes
// Specification B1 - Date class
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
    Date(int month, int day, int year, int hour, int minute, int second);
    Date();

    static void componentTest();

    int getMonth();
    int getDay();
    int getYear();
    int getHour();
    int getMinute();
    int getSecond();
    string getDate();
};

class Item
{
private:
    string description;
    unsigned int quantity;
    double cost;

    Date dateAdded;

public:
    Item();

    static void componentTest();

    string getDescription();
    void setDescription(string x);
    unsigned int getQuantity();
    void setQuantity(unsigned int x);
    double getCost();
    void setCost(double x);
    Date getDateAdded();
    void setDate();
    void operator>>(ostream &x);
};

class Inventory
{
private:
    int itemsSize;
    Item *items; // Specification C2 - Dynamic Array

    void incrementItemsArray();
    void decrementItemsArray();
    void removeIndex(int index);

public:
    Inventory();
    ~Inventory();

    static void componentTest();

    void addItem();
    void editItem();
    void removeItem();
    void displayInventory();
    static int displayMenu();
    void operator<<(Item x);
};
//----------------------------------------------

int main()
{
    programGreeting();

    // Specification A4 - UnitTest() method in main()
    unitTest();
    Inventory x;

    bool quit = false;
    while (!quit)
    {
        int answer = Inventory::displayMenu();

        switch (answer)
        {
        case 1:
            x.addItem();
        case 2:
            x.removeItem();
        case 3:
            x.editItem();
        case 4:
            x.displayInventory();
        case 5:
            quit = true;
        }
    }
    return 0;
}

void unitTest()
{
    cout << "---------------------------\n";
    cout << "TESTING\n\n";
    Date::componentTest();
    Item::componentTest();
    Inventory::componentTest();
    cout << "---------------------------\n";
}

// Specification C1 - Alpha Menu
int Inventory::displayMenu()
{
    int answer = 0;
    cout << "---------------------------\n";
    cout << "Choose a number:\n";
    cout << "1.) Add item\n";
    cout << "2.) Remove item\n";
    cout << "3.) Edit item\n";
    cout << "4.) Display Inventory\n";
    cout << "5.) Quit\n";
    cin >> answer;

    // Specification B3 - Menu Input Validation
    while (!cin || !(answer <= 5 && answer >= 1))
    {
        cout << "That is an invalid input. Please try again: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }
    cout << "---------------------------\n"
         << endl;
    return answer;
}

void programGreeting()
{
    Date now;
    cout << "James Armstrong - GPA program\n";
    cout << "Current date: ";
    cout << now.getDate() << '\n';
    cout << "Due: 3/15/2020\n";
    cout << endl;
}

//----------------------------------------------
// Date class methods

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

//Specification B2 - ComponentTest method in Date
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

    // Testing the 2 constructors
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
    string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year) + " " + to_string(hour) + ":";

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

//----------------------------------------------
// Item class methods

Item::Item()
{
    description = "";
    quantity = 0;
    cost = 0;

    Date now;
    dateAdded = now;
}

void Item::componentTest()
{
    Item a;
    a.setDescription("desc");
    a.setCost(101);
    a.setQuantity(100);

    (a.getDescription() == "desc") ? cout << "Item description works\n" : cout << "Item description does not work\n";

    (a.getCost() == 101) ? cout << "Item cost works\n" : cout << "Item cost does not work\n";

    (a.getQuantity() == 100) ? cout << "Item quantity works\n" : cout << "Item quantity does not work\n";

    cout << endl;
}
string Item::getDescription()
{
    return description;
}
void Item::setDescription(string x)
{
    description = x;
}

unsigned int Item::getQuantity()
{
    return quantity;
}
void Item::setQuantity(unsigned int x)
{
    quantity = x;
}

double Item::getCost()
{
    return cost;
}
void Item::setCost(double x)
{
    cost = x;
}

Date Item::getDateAdded()
{
    return dateAdded;
}

void Item::setDate()
{
    Date now;
    dateAdded = now;
}

// Display item operator
// Specification A3 - Overload operator»
void Item::operator>>(ostream &x)
{
    x << "Description: " << getDescription() << '\n';
    x << "Quantity: " << getQuantity() << '\n';
    x << "Cost: $" << getCost() << '\n';
    x << "Date added: ";
    x << getDateAdded().getDate() << '\n'
      << endl;
}
//----------------------------------------------
// Inventory class methods

Inventory::Inventory()
{
    itemsSize = 0;
    items = new Item[itemsSize];
}

Inventory::~Inventory()
{
    delete[] items;
}

void Inventory::componentTest()
{
    Inventory x;
    Item a;
    a.setDescription("desc");
    a.setCost(101);
    a.setQuantity(100);

    x << a;
    (x.items[0].getDescription() == "desc") ? cout << "Inventory adding works\n" : cout << "Inventory adding doesn't work\n";

    x.decrementItemsArray();
    (x.itemsSize == 0) ? cout << "Inventory decrementing works\n" : cout << "Inventory decrementing doesn't work\n";

    cout << endl;
}

// Specification C2 - Resize Array - add to end
void Inventory::addItem()
{
    Item x;
    string description;
    int quantity;
    double cost;

    //----------------------------------------------
    // Add description

    cout << "Give description (22 char max): ";
    cin.ignore();
    getline(cin, description);

    // Specification B4 - Inventory Entry Input Validation
    while (description.size() > 22)
    {
        cout << "The description must be 22 characters max. Please try again: ";
        getline(cin, description);
    }
    x.setDescription(description);

    //----------------------------------------------
    // Add quantity

    cout << "Give quantity (must be >0): ";
    cin >> quantity;

    // Specification B4 - Inventory Entry Input Validation
    while (!cin || quantity < 0)
    {
        cout << "That is an invalid input. Please try again (must be >0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> quantity;
    }
    x.setQuantity(quantity);

    //----------------------------------------------
    // Add cost

    cout << "Give cost (must be >0): ";
    cin >> cost;

    // Specification B4 - Inventory Entry Input Validation
    while (!cin || cost < 0)
    {
        cout << "That is an invalid input. Please try again (must be >0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cost;
    }
    x.setCost(cost);
    //----------------------------------------------

    x.setDate();

    *this << x;
}

// Specification A1 - Edit Inventory
void Inventory::editItem()
{
    // Don't edit an item if inventory is empty
    if (itemsSize == 0)
    {
        cout << "Inventory is empty. Add items.\n"
             << endl;
        return;
    }

    //----------------------------------------------
    // Choose item to edit

    int answer = 0;
    cout << "Select item to edit:\n";
    for (int i = 0; i < itemsSize; i++)
    {
        cout << i + 1 << ".) " << items[i].getDescription() << '\n';
    }
    cin >> answer;

    // Specification B4 - Inventory Entry Input Validation
    while (!cin || !(answer <= itemsSize && answer > 0))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }

    //----------------------------------------------
    // Choose property to edit

    int propertyToEdit = 0;
    cout << "What property to edit (Pick #)?\n";
    cout << "1.) Description\n";
    cout << "2.) Quantity\n";
    cout << "3.) Cost\n";
    cin >> propertyToEdit;

    // Specification B4 - Inventory Entry Input Validation
    while (!cin || !(propertyToEdit <= 3 && propertyToEdit > 0))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> propertyToEdit;
    }

    //----------------------------------------------

    // If user chose to edit description
    switch (propertyToEdit)
    {
    case 1:
    {
        string description = "";

        cout << "Give new description (22 char max): ";
        cin >> description;

        // Specification B4 - Inventory Entry Input Validation
        while (!cin || description.size() > 22)
        {
            cout << "That is an invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> description;
        }
        items[answer - 1].setDescription(description);

        break;
    }

    // If user chose to edit quantity
    case 2:
    {
        unsigned int quantity = 0;

        cout << "Give new quantity (must be >0): ";
        cin >> quantity;

        // Specification B4 - Inventory Entry Input Validation
        while (!cin)
        {
            if (quantity < 0)
                cout << "Quantity has to be >0. Please try again: ";
            else
                cout << "That is an invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> quantity;
        }
        items[answer - 1].setQuantity(quantity);
        break;
    }

    // If user chose to edit cost
    default:
    {
        double cost;
        cout << "Give cost: ";
        cin >> cost;

        // Specification B4 - Inventory Entry Input Validation
        while (!cin || cost < 0)
        {
            cout << "That is an invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> cost;
        }
        items[answer - 1].setCost(cost);
    }
    }
    cout << endl;
}

// Specification C3 - Resize Array - subtract from end
void Inventory::removeItem()
{
    // Don't edit an item if inventory is empty
    if (itemsSize == 0)
    {
        cout << "Inventory is empty. Add items.\n"
             << endl;
        return;
    }

    int answer = 0;
    cout << "Select item to remove:\n";
    for (int i = 0; i < itemsSize; i++)
        cout << i + 1 << ".) " << items[i].getDescription() << '\n';
    cin >> answer;

    while (!cin || !(answer <= itemsSize && answer > 0))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }
    removeIndex(answer - 1);
    decrementItemsArray();
}

void Inventory::displayInventory()
{
    if (itemsSize == 0)
    {
        cout << "Inventory is empty. Add items." << endl;
        return;
    }
    for (int i = 0; i < itemsSize; i++)
    {
        cout << "Item " << i + 1 << ":\n";
        items[i] >> cout;
    }
    cout << endl;
}

// Increment array size by one.
void Inventory::incrementItemsArray()
{
    Item *temp = new Item[itemsSize + 1];
    for (int i = 0; i < itemsSize; i++)
        temp[i] = items[i];

    delete[] items;
    items = temp;
    temp = nullptr;
    itemsSize++;
}

// Decrement array size by one.
void Inventory::decrementItemsArray()
{
    Item *temp = new Item[itemsSize - 1];
    for (int i = 0; i < itemsSize - 1; i++)
        temp[i] = items[i];

    delete[] items;
    items = temp;
    temp = nullptr;
    itemsSize--;
}

// Given an index, push every item from the right to left once starting at index
void Inventory::removeIndex(int index)
{
    for (int i = index; i < itemsSize - 1; i++)
        items[i] = items[i + 1];
}

// Add item operator
// Specification A2 - Overload operator«
void Inventory::operator<<(Item x)
{
    incrementItemsArray();
    items[itemsSize - 1] = x;
}