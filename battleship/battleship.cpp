// battleship.cpp
// James Armstrong
// Due: 5-14-20

#include <ctime>
#include <string>
#include <limits>
#include <iostream>
#include <fstream>
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
    Ship(string name = "", int size = 0, char mapChar = '0');
    int getSize();
    string getName();
    char getMapChar();
};

// Specification A3 - Child Classes
class Carrier : public Ship
{

public:
    Carrier(string name = "", int size = 0, char mapChar = '0')
        : Ship(name, size, mapChar)
        {}
};
class Battleship : public Ship
{
public:
    Battleship(string name = "", int size = 0, char mapChar = '0')
        : Ship(name, size, mapChar)
        {}
};
class Cruiser : public Ship
{
public:
    Cruiser(string name = "", int size = 0, char mapChar = '0')
        : Ship(name, size, mapChar)
        {}
};
class Submarine : public Ship
{
public:
    Submarine(string name = "", int size = 0, char mapChar = '0')
        : Ship(name, size, mapChar)
        {}
};
class Destroyer : public Ship
{
public:
    Destroyer(string name = "", int size = 0, char mapChar = '0')
        : Ship(name, size, mapChar)
    {}
};


// Keeps track of every move made
class Move
{
private:
    friend ostream& operator<<(ostream&, Move);
    int mapSize;
    bool hit;
    bool player;
    
    char playerMap[10][10];
    char enemyMap[10][10];

    // Coords of the move
    char row;
    char col;
    

public:

    Move(char row, char col, bool hit, bool player, char playerMap[10][10], char enemyMap[10][10]);
    Move();

    void displayEnemyMap();
    void displayPlayerMap();

    bool isHit();
    bool isPlayer();
    char getRow();
    char getCol();
};


class BattleshipGame
{

private:
    friend void operator>>(BattleshipGame&, string&);
    friend Move;
    bool mapCheats;
    bool multiFire;
    int mapSize;
    char playerMap[10][10];
    char enemyMap[10][10];
    int gameShipsSize;

    Ship gameShips[5]; // List of ships available for the game

    int movesSize;
    Move *moves; // Used to replay the game


    void placeShips();
    void displayPlayerMap();
    void displayEnemyMap();
    void displayEnemyMapHidden();
    void toggleCheats();

public:
    BattleshipGame();
    ~BattleshipGame();
    
    string getUserInput();
    void displayMaps();

    char** getPlayerMap();
    char** getEnemyMap();

    void shootEnemy(int row, int col);
    void shootPlayer(int row, int col);

    bool isPlayerWinner();
    bool isEnemyWinner();

    bool isPlayerShipSunk(char x);
    bool isEnemyShipSunk(char x);

    int getPlayerShipCount();
    int getEnemyShipCount();

    bool isMultiFire();

	void clearScreen();

    void incrementMovesArray();
    void addMove(Move m);
    void replayGame();
};

// Function prototypes
void programGreeting();

int main()
{
    srand(time(0));

    programGreeting();

    BattleshipGame x;

    bool gameQuit = false;
    bool playersTurn = true;
    string answer = "";

    int playerShipCount = 5;
    int enemyShipCount = 5;

    int playerTurns = playerShipCount;
    int enemyTurns = enemyShipCount;

    // Game is looped within here
    while (!gameQuit)
    {
        // Refresh the player turns if both sides have no more turns w/ multifire mode on
        if (playerTurns <= 0)
            playerTurns = x.getPlayerShipCount();
        if (enemyTurns <= 0)
            enemyTurns = x.getEnemyShipCount();

        if (playersTurn)
        {
            playerTurns--;
            x.displayMaps();
            x >> answer;

            // Specification A1 - Resign Game
            if (answer == "q")
            {
                gameQuit = true;
                break;
            }

            // Converts the character to the coords by first converting it to ASCII, then subtracting
            // 65 (A in ascii) for row, and 49 (1) for col
            int row = static_cast<int>(answer[0]) - 65;
            int col = (answer.size() == 3) ? 9 : static_cast<int>(answer[1]) - 49;

            // Clear the console to refresh the new map, which will be displayed the next time
            // it's the player's turn. Unnecessary to display it for the AI.
			x.clearScreen();

            x.shootEnemy(row, col);
            playerShipCount = x.getPlayerShipCount();

            cout << "------------------------------\n";

            if (x.isPlayerWinner())
            {
                cout << "Player wins!\n";
                gameQuit = true;
                x.displayMaps();
            }

            // This prevents winning to redundantly do the actions within this else statement
            else
            {
                if (!x.isMultiFire() || playerTurns == 0)
                    playersTurn = false;
            }
        }

        else
        {
            enemyTurns--;
            int row = rand() % 9;
            int col = rand() % 9;

            x.shootPlayer(row, col);
            enemyShipCount = x.getEnemyShipCount();

            cout << "------------------------------\n";

            if (x.isEnemyWinner())
            {
                cout << "AI wins!\n";
                gameQuit = true;
                x.displayMaps();
            }

            // This prevents this bool redundantly to turn false when the AI wins.
            else
            {
                if (!x.isMultiFire() || enemyTurns == 0)
                    playersTurn = true;
            }
        }
    }

    string ans = "";
    cout << "Do you want to watch a replay of your game? (y/n): ";
    cin.ignore();
    getline(cin, ans);

    while (ans !=  "y" && ans != "n")
    {
        cout << "Invalid answer. Type y or n to watch a replay of your game: ";
        getline(cin, ans);
    }

    // Specification A4 - Replay Finished Game
    if (ans == "y") x.replayGame();

    return 0;
}

void programGreeting()
{
    cout << "Welcome. This is is the game Battleship.\n";
    cout << "Author: James Armstrong\n";

    Date now;
    cout << "Today's date: " << now.getDate() << '\n';

    Date x(5, 3, 2020, 23, 59, 59);
    cout << "Due date: " << x.getDate() << '\n'
         << endl;
        
    cout << "In the map, 'M' means missed shot and 'X' means ship has been hit. Good luck!" << endl;
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
//--------------------------------------------------------------------------------------------------
// Ship class methods


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

// Specification B3 - Random Start
// Randomizes both sides
void BattleshipGame::placeShips()
{

    Carrier carrier("carrier", 5, 'C');
    Battleship battleship("battleship", 4, 'B');
    Cruiser cruiser("cruiser", 3, 'A');
    Submarine submarine("submarine", 3, 'S');
    Destroyer destroyer("destroyer", 2, 'D');
    gameShips[0] = carrier;
    gameShips[1] = battleship;
    gameShips[2] = cruiser;
    gameShips[3] = submarine;
    gameShips[4] = destroyer;

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

    // Place AI ships
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
                if (enemyMap[randRow + i][randCol] != ' ')
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
                    if (enemyMap[randRow + i][randCol] != ' ')
                        shipInTheWay = true;
                }
            }

            // Actually place the ship char onto the map
            for (int i = 0; i < x.getSize(); i++)
            {
                enemyMap[randRow + i][randCol] = x.getMapChar();
            }
        }
        else
        {

            // Check if ship is in the way
            bool shipInTheWay = false;
            for (int i = 0; i < x.getSize(); i++)
            {
                if (enemyMap[randRow][randCol + i] != ' ')
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
                    if (enemyMap[randRow][randCol + i] != ' ')
                        shipInTheWay = true;
                }
            }

            // Actually place the ship char onto the map
            for (int i = 0; i < x.getSize(); i++)
            {
                enemyMap[randRow][randCol + i] = x.getMapChar();
            }
        }
    }
}

void BattleshipGame::displayPlayerMap()
{
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < mapSize; i++)
    {
        cout << static_cast<char>(65 + i) << " ";

        for (int j = 0; j < mapSize; j++)
        {
            cout << playerMap[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

void BattleshipGame::displayEnemyMap()
{
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < mapSize; i++)
    {
        cout << static_cast<char>(65 + i) << " ";

        for (int j = 0; j < mapSize; j++)
        {
            cout << enemyMap[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

void BattleshipGame::displayEnemyMapHidden()
{
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < mapSize; i++)
    {
        cout << static_cast<char>(65 + i) << " ";

        for (int j = 0; j < mapSize; j++)
        {
            if (enemyMap[i][j] == 'X' || enemyMap[i][j] == 'M')
            {
                cout << enemyMap[i][j];
                cout << " ";
            }
            else
                cout << "  ";
        }
        cout << endl;
    }
}

BattleshipGame::BattleshipGame()
{
    movesSize = 0;
    moves = new Move[movesSize];

    multiFire = false;
    mapCheats = false;
    mapSize = 10;
    gameShipsSize = 5;

    // Set up map with spaces to make it empty
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            playerMap[i][j] = ' ';
            enemyMap[i][j] = ' ';
        }
    }

    placeShips();
}

BattleshipGame::~BattleshipGame()
{
    delete[] moves;
}

string BattleshipGame::getUserInput()
{
    string answer = "";
    cout << "Type in a coordinate to fire (e.g. \"A1\"). Type \"/multifire\" for multifire mode, "
        << "\"q\" to quit:\n";

    // MAP CHEATS COMMAND: "/cheat";
    cin >> answer;

    // Specification C3 - Validate Input
    while (

        // This needs to be absolutely true for anything else to be checked.
        (answer != "/cheat" && answer != "q" && answer != "/multifire") &&

        ((answer.size() > 3 || answer.size() < 2) ||

         // If the column letter isn't valid
         static_cast<int>(answer[0]) > 74 || static_cast<int>(answer[0] < 41) ||

         // If the row number isn't valid
         static_cast<int>(answer[1]) > 58 || static_cast<int>(answer[1] < 49) ||

         // If the user didn't put a 10 in the end. Needs to be size 3, because inputs like A100
         // or AA10 isn't valid
         (answer.size() == 3 && answer.substr(1, 2) != "10")))
    {
        cout << "Invalid input. Please try again\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> answer;
    }

    // Specification B1 - Secret Option
    if (answer == "/cheat")
    {
        toggleCheats();
        answer = getUserInput();
    }

    // Specification A2 - MultiFire Game
    if (answer == "/multifire")
    {
        multiFire = true;
        answer = getUserInput();
    }

    return answer;
}

void BattleshipGame::toggleCheats()
{
    if (mapCheats)
        mapCheats = false;
    else
        mapCheats = true;

    clearScreen();
    displayMaps();
}

void BattleshipGame::shootEnemy(int row, int col)
{
    bool hit = false;

    if (enemyMap[row][col] != ' ' && enemyMap[row][col] != 'X' && enemyMap[row][col] != 'M')
    {
        cout << "PLAYER HAS HIT A SHIP" << endl;
        enemyMap[row][col] = 'X';
        hit = true;

    }

    // Specification B2 - Adv Input Validation
    else if (enemyMap[row][col] == 'X' || enemyMap[row][col] == 'M')
    {
		clearScreen();
        cout << "You cannot shoot where you already shot. Please try again.\n";
        cout << "------------------------------\n";
        displayMaps();

        string answer = getUserInput();

        int row = static_cast<int>(answer[0]) - 65;
        int col = (answer.size() == 3) ? 9 : static_cast<int>(answer[1]) - 49;
		clearScreen();
        shootEnemy(row, col);
    }
    else
    {
        cout << "PLAYER MISSED!" << endl;
        enemyMap[row][col] = 'M';
    }


    // Convert to original answer so that moves array knows the coordinate
    char r = static_cast<char>(row + 65);
    char c = static_cast<char>(col + 49);

    Move m(r, c, hit, true, playerMap, enemyMap);
    addMove(m);
}
void BattleshipGame::shootPlayer(int row, int col)
{
    bool hit = false;
    if (playerMap[row][col] != ' ' && playerMap[row][col] != 'X' && playerMap[row][col] != 'M')
    {
        cout << "AI HAS HIT A SHIP" << endl;
        playerMap[row][col] = 'X';
        hit = true;
    }

    // Specification C2 - Prohibit AI wasted shots
    // Coordinates previously hit are marked with 'X'.
    else if (playerMap[row][col] == 'X' || playerMap[row][col] == 'M')
        shootPlayer(rand() % 9, rand() % 9);
    else
    {
        cout << "AI MISSED" << endl;
        playerMap[row][col] = 'M';
    }

    // Convert to original answer so that moves array knows the coordinate
    char r = static_cast<char>(row + 65);
    char c = static_cast<char>(col + 49);
    Move m(r, c, hit, false, playerMap, enemyMap);
    addMove(m);
}

void BattleshipGame::displayMaps()
{
    cout << "Your map:\n";
    displayPlayerMap();
    cout << endl;

    cout << "Enemy map:\n";
    (mapCheats) ? displayEnemyMap() : displayEnemyMapHidden();
    cout << endl;
}

bool BattleshipGame::isPlayerWinner()
{
    const int NUM_X_NEEDED = 5 + 4 + 3 + 3 + 2; // Numbers from size of each ship

    // Counts the number of X's in the enemy's map 
    int xNum = 0;
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            if (enemyMap[i][j] == 'X')
                xNum++;
        }
    }
    return xNum == NUM_X_NEEDED;
}

bool BattleshipGame::isEnemyWinner()
{
    const int NUM_X_NEEDED = 5 + 4 + 3 + 3 + 2; // Numbers from size of each ship

    // Count the number of X's in the player's map
    int xNum = 0;
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            if (playerMap[i][j] == 'X')
                xNum++;
        }
    }
    return xNum == NUM_X_NEEDED;
}

bool BattleshipGame::isPlayerShipSunk(char x)
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            // If the character still exists in the map, then the ship isn't sunk yet
            if (playerMap[i][j] == x)
                return false;
        }
    }
    return true;
}

bool BattleshipGame::isEnemyShipSunk(char x)
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            // If the character still exists in the map, then the ship isn't sunk yet
            if (enemyMap[i][j] == x)
                return false;
        }
    }
    return true;
}

int BattleshipGame::getPlayerShipCount()
{
    int sum = 5;
    if (isPlayerShipSunk('C'))
        sum--;
    if (isPlayerShipSunk('B'))
        sum--;
    if (isPlayerShipSunk('A'))
        sum--;
    if (isPlayerShipSunk('S'))
        sum--;
    if (isPlayerShipSunk('D'))
        sum--;

    return sum;
}
int BattleshipGame::getEnemyShipCount()
{
    int sum = 5;
    if (isEnemyShipSunk('C'))
        sum--;
    if (isEnemyShipSunk('B'))
        sum--;
    if (isEnemyShipSunk('A'))
        sum--;
    if (isEnemyShipSunk('S'))
        sum--;
    if (isEnemyShipSunk('D'))
        sum--;

    return sum;
}

bool BattleshipGame::isMultiFire()
{
    return multiFire;
}

void BattleshipGame::clearScreen()
{
	for (int i = 0; i < 20; i++)
	{
		cout << '\n';
	}
	cout << endl;
}

// Increment array size by one.
void BattleshipGame::incrementMovesArray()
{
    Move *temp = new Move[movesSize + 1];
    for (int i = 0; i < movesSize; i++)
        temp[i] = moves[i];

    delete[] moves;
    moves = temp;
    temp = nullptr;
    movesSize++;
}

void BattleshipGame::addMove(Move m)
{
    incrementMovesArray();
    moves[movesSize - 1] = m;
}

void BattleshipGame::replayGame()
{
    cout << "-------------------------------------\n";
    for (int i = 0; i < movesSize; i++)
    {
        // A primitive delayer
        for (int j = 0; j < 999999999; j++)
        {
            if (j == 999999998)
                cout << moves[i];
        }
        cout << "-------------------------------------" << endl;
    }
    
}

//--------------------------------------------------------------------------------------------------
// Move methods

// Requires a copy of the map
Move::Move(char row, char col, bool hit, bool player, char playerMap[10][10], char enemyMap[10][10])
{
    this->hit = hit;
    this->player = player;
    this->row = row;
    this->col = col;
    mapSize = 10;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            this->playerMap[i][j] = playerMap[i][j];
            this->enemyMap[i][j] = enemyMap[i][j];
        }
    }
}

Move::Move()
{
    hit = false;
    player = false;
    row = '0';
    col = '0';
    mapSize = 0;
}

void Move::displayPlayerMap()
{
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < mapSize; i++)
    {
        cout << static_cast<char>(65 + i) << " ";

        for (int j = 0; j < mapSize; j++)
        {
            cout << playerMap[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

void Move::displayEnemyMap()
{
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < mapSize; i++)
    {
        cout << static_cast<char>(65 + i) << " ";

        for (int j = 0; j < mapSize; j++)
        {
            cout << enemyMap[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

bool Move::isHit()
{
    return hit;
}

bool Move::isPlayer()
{
    return player;
}

char Move::getRow()
{
    return row;
}
char Move::getCol()
{
    return col;
}

// Specification C4 - Overload «
ostream& operator<<(ostream &x, Move m)
{
    if (m.isPlayer())
        x << " - PLAYER'S TURN: \n";
    else
        x << " - AI'S TURN: \n";

    x << "Your map: \n";
    m.displayPlayerMap();
        
    x << "AI map: \n";
    m.displayEnemyMap();


    if (m.isHit())
        x << "HIT - ";
    else
        x << "MISS - ";
    x << m.getRow() << m.getCol() << '\n'; 
    x << endl;

    return x;
}

//Specification B4 - Overload »
void operator>>(BattleshipGame& b, string &s)
{
    s = b.getUserInput();
}