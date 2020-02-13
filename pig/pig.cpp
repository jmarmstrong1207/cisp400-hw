// pig.cpp
// James Armstrong, CISP 400
// 1-30-20

#include <iostream>
#include <cstdlib>
#include <limits>
#include <unistd.h>

using namespace std;


void programGreeting();
int randomNumber();
int d6();
int showMenu();

int main()
{
    bool gameQuit = false;
    int grandComputerPoints = 0;
    int grandUserPoints = 0;

    int* highScore = new int(0); // Specification B3 - Hi Score on Heap

    // Specification C1 - Fixed Seed
    srand(2020);

	programGreeting();

    // The entire game is held within this while loop
    while (!gameQuit && grandComputerPoints < 100 && grandUserPoints < 100)
    {
        int userTurnPoints = 0;
        int computerTurnPoints = 0;
        bool usersTurn = true;

        // loop for the user's turn
        while (usersTurn)
        {
            int userChoice = 0;
            int userRolled = 0;

            // Specification B1 - Display Turn Stats
            cout << endl;
            cout << "----------------------" << endl;
            cout << "YOUR TURN" << endl;
            cout << "Current score" << endl;
            cout << "Grand Points for Computer: " << grandComputerPoints << endl;
            cout << "Grand Points for You: " << grandUserPoints << endl;
            cout << "Turn points for You: " << userTurnPoints << endl << endl;

            userChoice = showMenu();

            // User's menu choice if statements
            if (userChoice == 1) userRolled = d6();
            else if (userChoice == 2)
            {
                usersTurn = false;
                grandUserPoints += userTurnPoints;
            }
            else if (userChoice == 3)
            {
                cout << "Game has quit" << endl;
                gameQuit = true;
                break;
            }

            // User's rolled number if statements
            if (userRolled == 1)
            {
                cout << "You rolled a 1! It's now the AI's turn." << endl;
                usersTurn = false;
            }
            if (userRolled >= 2)
            {
                cout << userRolled << " points added to turn points" << endl;
                userTurnPoints += userRolled;
            }
        }

        // loop for the computer's turn
        while (!usersTurn)
        {
            int computerChoice = 0;
            int computerRolled = 0;

            // Specification B1 - Display Turn Stats
            cout << endl;
            cout << "----------------------" << endl;
            cout << "COMPUTER'S TURN" << endl;
            cout << "Current score" << endl;
            cout << "Grand Points for You: " << grandUserPoints << endl;
            cout << "Grand Points for Computer: " << grandComputerPoints << endl;
            cout << "Turn points for Computer: " << computerTurnPoints << endl << endl;

            computerChoice = d6(); // computer's choice is randomized

            // Computer's choice if statements
            if (computerChoice >= 4 && computerChoice <= 6) computerRolled = d6();
            else if (computerChoice >= 1 && computerChoice <= 3)
            {
                cout << "Computer holds." << endl;
                usersTurn = true;
                grandComputerPoints += computerTurnPoints;
            }

            // Computer's rolled number if statements
            if (computerRolled == 1)
            {
                cout << "Computer rolled a 1! It's now the user's turn." << endl;
                usersTurn = true;
            }
            if (computerRolled >= 2)
            {
                cout << computerRolled << " points added to turn points" << endl;
                computerTurnPoints += computerRolled;
            }
        }
    }

    if (grandComputerPoints > grandUserPoints)
    {
        cout << "Computer wins!" << endl;
        *highScore = grandComputerPoints;
    }
    else if (grandComputerPoints < grandUserPoints)
    {
        cout << "You win!" << endl;
        *highScore = grandUserPoints;
    }

    // Specification B4 - Display High Score
    cout << "High score: " << *highScore << endl;

    delete highScore;
    return 0;
}

void programGreeting()
{
    // Specification C2 - Student Name
    cout << "James Armstrong" << endl;

    // Title and description
    cout << "Pig - A game of chance and a 6-sided dice" << endl;

    // Specification B2 - Display Due Date
    cout << "Due: 2-2-20" << endl;
}

// Specification A2 - RandomNumber() function
int randomNumber(int low, int high)
{
    int random = rand() % (high - low + 1) + low;

    // Specification A3 - Protect RandomNumber() input
    if (high < low || low < 1 || high > 100) return -1;

    // Specification A4 - Protect RandomNumber() output
    if (random > 100) return -2;

    else return random;
}

// Specification A1 - D6() function
int d6()
{
    return randomNumber(1, 6);
}

// Specification C3 - Numeric Menu
int showMenu()
{
    int choice = 0;

    cout << "Type the number for the choice you want to make:" << endl;
    cout << "1. Roll" << endl;
    cout << "2. Hold" << endl;
    cout << "3. Quit" << endl;
    cin >> choice;

    // Specification C4 - Bulletproof Menu
    while (choice < 1 || choice > 3)
    {
        cout << endl << "That is an invalid input. Choose again:" << endl;
        cout << "1. Roll" << endl;
        cout << "2. Hold" << endl;
        cout << "3. Quit" << endl;

        // clear the error, and ignore the invalid input
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n');

        cin >> choice;
    }
    return choice;
}
