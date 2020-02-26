// battleship.cpp
// James Armstrong
// Due: 5-14-20

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

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

// Specification C1 - OOP
class Ship
{
private:
    string name;
    int size;
    char mapChar; // The character to represent the ship in the map

public:
    Ship();
    Ship(string name, int size, char mapChar);
    int getSize();
    string getName();
    char getMapChar();
};

class BattleshipGame
{
private:
    int mapSize;
    int gameShipsSize;
    Ship gameShips[5]; // List of ships available for the game
    char playerMap[10][10];
    char enemyMap[10][10];

    void placeShips();

public:
    BattleshipGame();
    void displayMaps();
};

int main()
{
    BattleshipGame x;
    x.displayMaps();
    return 0;
}

//--------------------------------------------------------------------------------------------------
// Date methods
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
    string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year) + " " + to_string(hour);

    if (minute < 10)
        date += "0" + to_string(minute);
    else
        date += to_string(minute);

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
//--------------------------------------------------------------------------------------------------
// Ship class methods

Ship::Ship()
{
    this->name = "";
    this->size = 0;
    this->mapChar = '0';
}
Ship::Ship(string name, int size, char mapChar)
{
    this->name = name;
    this->size = size;
    this->mapChar = mapChar;
}

int Ship::getSize()
{
    return size;
}
string Ship::getName()
{
    return name;
}
char Ship::getMapChar()
{
    return mapChar;
}
//--------------------------------------------------------------------------------------------------

void BattleshipGame::placeShips()
{
    srand(time(0));

    // Place user ships
    for (Ship x : gameShips)
    {
        bool placeVertical = rand() % 2;
        int randRow = rand() % 10;
        int randCol = rand() % 10;

        if (placeVertical)
        {

            // Check if ship is in the way
            bool shipInTheWay = false;
            for (int i = 0; i < x.getSize(); i++)
            {
                if (playerMap[randRow + i][randCol] != ' ')
                    shipInTheWay = true;
            }

            // Checks if there's enough space to place the ship in the map
            while (mapSize - randRow <= x.getSize() || shipInTheWay)
            {
                shipInTheWay = false;
                randRow = rand() % 10;
                randCol = rand() % 10;
                for (int i = 0; i < x.getSize(); i++)
                {
                    if (playerMap[randRow + i][randCol] != ' ')
                        shipInTheWay = true;
                }
            }

            // Actually place the ship char onto the map
            for (int i = 0; i < x.getSize(); i++)
            {
                playerMap[randRow + i][randCol] = x.getMapChar();
            }
        }
        else
        {

            // Check if ship is in the way
            bool shipInTheWay = false;
            for (int i = 0; i < x.getSize(); i++)
            {
                if (playerMap[randRow][randCol + i] != ' ')
                    shipInTheWay = true;
            }

            // Checks if there's enough space to place the ship in the map
            while (mapSize - randCol <= x.getSize() || shipInTheWay)
            {
                shipInTheWay = false;
                randRow = rand() % 10;
                randCol = rand() % 10;
                for (int i = 0; i < x.getSize(); i++)
                {
                    if (playerMap[randRow][randCol + i] != ' ')
                        shipInTheWay = true;
                }
            }

            // Actually place the ship char onto the map
            for (int i = 0; i < x.getSize(); i++)
            {
                playerMap[randRow][randCol + i] = x.getMapChar();
            }
        }
    }
}

void BattleshipGame::displayMaps()
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            cout << playerMap[i][j];
        }
        cout << endl;
    }
}

BattleshipGame::BattleshipGame()
{
    mapSize = 10;
    gameShipsSize = 5;

    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            playerMap[i][j] = ' ';
            enemyMap[i][j] = ' ';
        }
    }

    Ship carrier("carrier", 5, 'C');
    Ship battleship("battleship", 4, 'B');
    Ship cruiser("cruiser", 3, 'A');
    Ship submarine("submarine", 3, 'S');
    Ship destroyer("destroyer", 2, 'D');
    gameShips[0] = carrier;
    gameShips[1] = battleship;
    gameShips[2] = cruiser;
    gameShips[3] = submarine;
    gameShips[4] = destroyer;
    placeShips();
}