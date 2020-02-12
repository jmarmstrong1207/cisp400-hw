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

//----------------------------------------------
// Class prototypes
// Specification B1 - OOP
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

    static void dateTest();

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

    string getDescription();
    void setDescription(string x);
    unsigned int getQuantity();
    void setQuantity(unsigned int x);
    double getCost();
    void setCost(double x);
    Date getDateAdded();
    void setDate();
};

class Inventory
{
private:
    int itemsSize;
    Item *items; // Specification C1 - Dynamic Array

    void incrementItemsArray();
    void decrementItemsArray();
    void removeIndex(int index);
    void logChange(Item x);

public:
    void addItem();
    void editItem();
    void removeItem();
    void displayInventory();
    Inventory();
    static int displayMenu();

    ~Inventory()
    {
        delete[] items;
    }
};
//----------------------------------------------

int main()
{
    programGreeting();
    Inventory x;

    bool quit = false;
    while (!quit)
    {
        int answer = Inventory::displayMenu();

        if (answer == 1)
            x.addItem();
        else if (answer == 2)
            x.removeItem();
        else if (answer == 3)
            x.editItem();
        else if (answer == 4)
            x.displayInventory();
        else if (answer == 5)
            quit = true;
    }

    return 0;
}

// Specification C4 - Main Menu
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

    // Specification C5 - Validate Menu
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
//----------------------------------------------
// Inventory class methods

Inventory::Inventory()
{
    itemsSize = 0;
    items = new Item[itemsSize];
}

// Specification C2 - Add Option
void Inventory::addItem()
{
    Item x;
    string description;
    unsigned int quantity;
    double cost;

    //----------------------------------------------
    // Add description

    cout << "Give description (22 char max): ";
    cin >> description;

    // Specification A2 - Validate Inventory
    while (!cin || description.size() > 22)
    {
        cout << "That is an invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> description;
    }
    x.setDescription(description);

    //----------------------------------------------
    // Add quantity

    cout << "Give quantity (must be >0): ";
    cin >> quantity;

    // Specification A2 - Validate Inventory
    while (!cin)
    {
        cout << "That is an invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> quantity;
    }
    x.setQuantity(quantity);

    //----------------------------------------------
    // Add cost

    cout << "Give cost: ";
    cin >> cost;

    // Specification A2 - Validate Inventory
    while (!cin || cost < 0)
    {
        cout << "That is an invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cost;
    }
    x.setCost(cost);
    //----------------------------------------------

    x.setDate();

    // Add one more slot in the array and append new item
    incrementItemsArray();
    items[itemsSize - 1] = x;
    logChange(x);
}

// Specification A1 - Edit Inventory
void Inventory::editItem()
{
    // Don't edit an item if inventory is empty
    if (itemsSize == 0)
    {
        cout << "Inventory is empty. Add items." << endl;
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

    // Specification A2 - Validate Inventory
    if (!cin || !(answer <= itemsSize && answer > 0))
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

    // Specification A2 - Validate Inventory
    if (!cin || !(propertyToEdit <= 3 && propertyToEdit > 0))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> propertyToEdit;
    }

    //----------------------------------------------

    // If user chose to edit description
    if (propertyToEdit == 1)
    {
        string description = "";

        cout << "Give new description (22 char max): ";
        cin >> description;

        // Specification A2 - Validate Inventory
        while (!cin || description.size() > 22)
        {
            cout << "That is an invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> description;
        }
        items[answer - 1].setDescription(description);
    }

    // If user chose to edit quantity
    else if (propertyToEdit == 2)
    {
        unsigned int quantity = 0;

        cout << "Give new quantity (must be >0): ";
        cin >> quantity;

        // Specification A2 - Validate Inventory
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
    }

    // If user chose to edit cost
    else
    {
        double cost;
        cout << "Give cost: ";
        cin >> cost;

        // Specification A2 - Validate Inventory
        while (!cin || cost < 0)
        {
            cout << "That is an invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> cost;
        }
        items[answer - 1].setCost(cost);
    }
    cout << endl;
}

//Specification B2 - Delete Inventory Item
void Inventory::removeItem()
{
    // Don't edit an item if inventory is empty
    if (itemsSize == 0)
    {
        cout << "Inventory is empty. Add items." << endl;
        return;
    }

    int answer = 0;
    cout << "Select item to remove:\n";
    for (int i = 0; i < itemsSize; i++)
        cout << i + 1 << ".) " << items[i].getDescription() << '\n';
    cin >> answer;

    // Specification A2 - Validate Inventory
    if (!cin || !(answer <= itemsSize && answer > 0))
    {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }
    removeIndex(answer - 1);
    decrementItemsArray();
}

// Specification C3 - Display Option
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
        cout << "Description: " << items[i].getDescription() << '\n';
        cout << "Quantity: " << items[i].getQuantity() << '\n';
        cout << "Cost: $" << items[i].getCost() << '\n';
        cout << "Date added: ";
        cout << items[i].getDateAdded().getDate() << '\n'
             << endl;
    }
    cout << endl;
}

// Increment array size by one.
// Specification B2 - Add Elements
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
// Specification B3 - Shrink Dynamic Array
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

// Given an i, push every item from the right to left once starting at i
void Inventory::removeIndex(int index)
{
    for (int i = index; i < itemsSize - 1; i++)
        items[i] = items[i + 1];
}

// Specification A3 - Logfile
void Inventory::logChange(Item x)
{
    ofstream output("log.txt", ofstream::app);
    output << x.getDateAdded().getDate() << " - " << x.getDescription() << " Added\n";
    output.close();
}
