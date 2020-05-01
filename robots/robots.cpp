#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

class Map
{
private:
    char map[10][10];

public:
    static const int mapSize = 10;

    Map()
    {
        // Set up map with spaces to make it empty
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++)
            {
                int random = rand() % 10 + 1;

                // Populate 40% of map with batteries
                if (random <= 4) map[i][j] = 'B';
                else map[i][j] = ' ';
            }
    }

    char getMapElement(int row, int col)
    {
        // Return W for wall
        if (col < 0 || col >= mapSize || row < 0 || row >= mapSize) return '|';
        else return map[row][col];
    }
    void setMapElement(int row, int col, char val) { map[row][col] = val; }
};

class Robot
{
private:
    int power;
    int totalEnergyHarvested;
    
    int stepsSurvived;
    char sensorStates[4];


    // Each gene correspond to possible sensor states. first 4 states are from N,S,E,W and the fifth
    // is the action code
    char genes[16][5];

public:
    static const int numGenes = 16;
    static const int geneLength = 5;

    // Default constructor. This randomizes its genes
    Robot()
    {
        power = 5;
        stepsSurvived = 0;
        totalEnergyHarvested = 0;

        // Randomize sensor states of the genes
        for (int i = 0; i < numGenes; i++)
            for (int j = 0; j < geneLength - 1; j++)
            {
                int random = rand() % 4;
                switch (random)
                {
                case 0:
                    genes[i][j] = ' ';
                    break;

                case 1:
                    genes[i][j] = '|';
                    break;
                
                case 2:
                    genes[i][j] = 'B';
                    break;
                }
            }
        
        // Randomize the actions for each gene
        for (int i = 0; i < numGenes; i++)
        {
            int random = rand() % 5;
            switch (random)
            {
            case 0:
                genes[i][geneLength - 1] = 'N';
                break;

            case 1:
                genes[i][geneLength - 1] = 'S';
                break;
                
            case 2:
                genes[i][geneLength - 1] = 'E';
                break;
                
            case 3:
                genes[i][geneLength - 1] = 'W';
                break;
                
            // This makes it go a random direction at the time it moves
            case 4:
                genes[i][geneLength - 1] = 'R';
                break;
            }
        }

    }


    // Constructor that gets half of the genes from x and y
    Robot(Robot x, Robot y)
    {
        power = 0;
        stepsSurvived = 0;
        totalEnergyHarvested = 0;
        
        // First half
        for (int i = 0; i < numGenes / 2; i++)
        {
            for (int j = 0; j < geneLength; j++)
            {
                genes[i][j] = x.genes[i][j];
            }
        }

        // Second half
        for (int i = numGenes / 2; i < numGenes; i++)
        {
            for (int j = 0; j < geneLength; j++)
            {
                genes[i][j] = y.genes[i][j];
            }
        }

        int randomMutationChance = rand() % 100 + 1;

        if (randomMutationChance <= 5)
        {
            int random = rand() % 3;
            int randomGeneRow = rand() % numGenes;
            int randomGeneCol = rand() % geneLength;

            switch (random)
            {
            case 0:
                genes[randomGeneRow][randomGeneCol] = ' ';
                break;
            case 1:
                genes[randomGeneRow][randomGeneCol] = '|';
                break;
            case 2:
                genes[randomGeneRow][randomGeneCol] = 'B';
                break;
            }
        }
        
    }

    char getGeneElement(int row, int col) { return genes[row][col]; }

    int getStepsSurvived() { return stepsSurvived; }
    void setStepsSurvived(int x) { stepsSurvived = x; }
    int incrementStepsSurvived() { stepsSurvived++; }
    
    void setPower(int x) { power = x; }
    int getPower() { return power; }

    void incrementTotalEnergyHarvested() { totalEnergyHarvested += 5; }
    int getTotalEnergyHarvested() { return totalEnergyHarvested; }
};

// Used in RobotGame to return robot's map coords
struct coords
{
    int row;
    int col;

    coords()
    {
        row = 0;
        col = 0;
    }
    coords(int r, int c)
    {
        row = r;
        col = c;
    }
};

// Each game is a game with one map and one robot
class RobotGame
{
private:
    Map map;
    Robot robot;
    char currentRobotState[4];
    coords currentLocation;

    void getRobotLocation()
    {
        for (int i = 0; i < map.mapSize; i++)
            for (int j = 0; j < map.mapSize; j++)
                if (map.getMapElement(i, j) == 'R') currentLocation = coords(i, j);
        
    }


    // Moves robot, consuming batteries and not moving if it's an invalid move
    void moveRobot()
    {
        getRobotLocation();

        int geneIndex = getGeneMatch();

        /*
        if (geneIndex != -1)
        {
            cout << "GENE MATCH. GENE:\n";
            for (int i = 0; i < robot.geneLength; i++)
            {
                cout << robot.getGeneElement(geneIndex, i) << ' ';
            }
            cout << "\n------------------\n";
            cout << endl;
        }
        else cout << "MATCH NOT FOUND\n";
        */

        // Holds value of the action in the gene index geneIndex
        char action;

        // Holds the value of coords the robot is going to move to
        char mapCoordValue;

        // If no matching gene, then do the last gene's action
        if (geneIndex == -1)
            action = robot.getGeneElement(robot.numGenes - 1, robot.geneLength - 1);
        
        // Else, get the gene index's action
        else action = robot.getGeneElement(geneIndex, robot.geneLength - 1);

        // If action is random, override the action variable to a random direction. If it isn't random,
        // the action variable is already a direction
        if (action == 'R')
        {
            int random = rand() % 4;
            switch (random)
            {
            case 0:
                action = 'N';
                break;
            case 1:
                action = 'S';
                break;
            case 2:
                action = 'E';
                break;
            case 3:
                action = 'W';
                break;
            }
        }

        switch (action)
        {
        case 'N':
            mapCoordValue = map.getMapElement(currentLocation.row - 1, currentLocation.col);
            if (mapCoordValue != '|')
            {
                 // Delete robot on current location
                map.setMapElement(currentLocation.row, currentLocation.col, ' ');

                // Set to new location
                map.setMapElement(currentLocation.row - 1, currentLocation.col, 'R');
            }
            
            break;
        case 'S':
            mapCoordValue = map.getMapElement(currentLocation.row + 1, currentLocation.col);
            if (mapCoordValue != '|')
            {
                map.setMapElement(currentLocation.row, currentLocation.col, ' ');
                map.setMapElement(currentLocation.row + 1, currentLocation.col, 'R');
            }
            break;
        case 'E':
            mapCoordValue = map.getMapElement(currentLocation.row, currentLocation.col + 1);
            if (mapCoordValue != '|')
            {
                map.setMapElement(currentLocation.row, currentLocation.col, ' ');
                map.setMapElement(currentLocation.row, currentLocation.col + 1, 'R');
            }
            break;
        case 'W':
            mapCoordValue = map.getMapElement(currentLocation.row, currentLocation.col - 1);
            if (mapCoordValue != '|')
            {
                map.setMapElement(currentLocation.row, currentLocation.col, ' ');
                map.setMapElement(currentLocation.row, currentLocation.col - 1, 'R');
            }
            break;
        }

        // If the robot stepped onto a battery, he gained +5 power. Else, he lost 1 power
        if (mapCoordValue == 'B')
        {
            robot.setPower(robot.getPower() + 5);
            robot.incrementTotalEnergyHarvested();
        }
        else robot.setPower(robot.getPower() - 1);
    }

    // Finds a match of the current state and the genes in the robot
    // Returns -1 if not found
    // Returns index of the gene array if found
    int getGeneMatch()
    {
        for (int i = 0; i < robot.numGenes; i++)
        {
            int count = 0;
            for (int j = 0; j < robot.geneLength; j++)
            {
                // Counts how many times the current gene array elements matches the robot state
                if (robot.getGeneElement(i, j) == currentRobotState[j]) count++;
            }

            // If all 4 gene elements match, then the entire gene matches. Return this gene index
            if (count == 4) return i;
        }

        return -1;
    }

    // Sets the current robot state array from the robot's surroundings
    void setCurrentRobotState()
    {
        getRobotLocation();
        currentRobotState[0] = map.getMapElement(currentLocation.row - 1, currentLocation.col); // North
        currentRobotState[1] = map.getMapElement(currentLocation.row + 1, currentLocation.col); // South
        currentRobotState[2] = map.getMapElement(currentLocation.row, currentLocation.col + 1); // East
        currentRobotState[3] = map.getMapElement(currentLocation.row, currentLocation.col - 1); // West
    }

    // Does one step of the game
    void passTime()
    {
        setCurrentRobotState();
        getRobotLocation();

        //displayMap();
        moveRobot();


    }

public:
    RobotGame()
    {
        // Randomly place robot in map
        map.setMapElement(rand() % map.mapSize, rand() % map.mapSize, 'R');
        getRobotLocation();
    }

    void setRobot(Robot x) { robot = x; }
    Robot getRobot() { return robot; }

    void start()
    {
        while (robot.getPower() > 0)
        {
            passTime();
            robot.incrementStepsSurvived();
        }
        // cout << "HE DED\n";
    }

    void displayMap()
    {
        for (int i = 0; i < map.mapSize; i++)
        {
            for (int j = 0; j < map.mapSize; j++)
            {
                cout << map.getMapElement(i, j) << ' ';
            }
            cout << endl;
        }
        cout << "POWER: " << robot.getPower() << '\n';
        cout << "---------------------------";
        cout <<endl;
    }

    int getStepsSurvived() { return robot.getStepsSurvived(); }

    void setStepsSurvived(int x) { robot.setStepsSurvived(x); }

    void setPower(int x) { robot.setPower(x); }
    int getTotalEnergyHarvested() { return robot.getTotalEnergyHarvested(); }

};

// This is the primary class that runs a simulation of a population of robots
class Simulation
{
private:
    vector<RobotGame> robotSimulations;

    int generations; // Number of generations for the simulation to run through
    int population;
    int currentTime; // Used to name the CSV file for the current simulation run

    // Kill the bottom 50% (in terms of steps survived) and reproduce the remaining to fill the gaps
    void killAndReproduce()
    {
        // Sorts in Descending order
        sort(robotSimulations.begin(), robotSimulations.end(), [](RobotGame x, RobotGame y) {return x.getTotalEnergyHarvested() > y.getTotalEnergyHarvested(); });

        int num = 0;
        for (int i = population / 2; i < population; i += 2)
        {
            robotSimulations[i].setRobot(Robot(robotSimulations[num].getRobot(), robotSimulations[num + 1].getRobot()));
            robotSimulations[i + 1].setRobot(Robot(robotSimulations[num + 1].getRobot(), robotSimulations[num].getRobot()));
            num += 2;
        }
    }

public:
    Simulation()
    {
        population = 200;
        generations = 10;
        currentTime = time(0);

        for (int i = 0; i < population; i++)
        {
            robotSimulations.push_back(RobotGame());
        }

    }

    Simulation(int pop, int gen)
    {
        population = pop;
        generations = gen;
        currentTime = time(0);

        for (int i = 0; i < population; i++)
        {
            robotSimulations.push_back(RobotGame());
        }
    }

    void startSimulation()
    {
        // Run for a number of generations
        for (int i = 0; i < generations; i++)
        {
            // Start each robot game
            for (RobotGame& x : robotSimulations)
            {
                x.start();
            }

            printToCSV();

            // Prevents the half of the last generation from getting killed
            if (i != generations - 1)
            {
                killAndReproduce();
            
                // After the generation finishes, the steps survived and powerresets for all robots
                for (RobotGame& x : robotSimulations)
                {
                    x.setStepsSurvived(0);
                    x.setPower(5);

                }
            }
        }
    }

    void getStats(ostream& o = cout)
    {
        int sum = 0;
        for (RobotGame& x : robotSimulations)
        {
            sum += x.getTotalEnergyHarvested();
        }
        int avg = sum / population;

        o << "Total energy harvested: " << sum << '\n';
        o << "Average energy harvested: " << avg << endl;
    }

    // Prints the current generation's total and average energy harvested to a CSV file. Useful
    // for graphing the generations
    void printToCSV()
    {
        int sum = 0;
        for (RobotGame& x : robotSimulations)
        {
            sum += x.getTotalEnergyHarvested();
        }
        int avg = sum / population;

        ifstream i("stats " + to_string(currentTime) + ".csv");
        ofstream f("stats " + to_string(currentTime) + ".csv", std::ios_base::app);

        // If new file...
        if (i.peek() == EOF)
        {
            f << "POPULATION: " << population << ", GENERATIONS: " << generations << endl;
            f << "Total energy harvested, Average energy harvested" << endl;
        }
        
        i.close();

        f << sum << ", " << avg << endl;
        f.close();
    }
};

// Function Prototypes
void programGreeting();
bool stringIsInt(string);

int main()
{
    // In the simulation, '|' is a wall (used to note the bounds of the array),
    // 'B' is a battery, & 'R' is the robot

    srand(time(0));

    programGreeting();

    cout << "Enter a population number: ";

    string pop = "";
    getline(cin, pop);

    while (!stringIsInt(pop))
    {
        cout << "Invalid input. Try again: ";
        getline(cin, pop);
    }

    cout << "Enter how many generations to last: ";

    string gen = "";
    getline(cin, gen);

    while (!stringIsInt(gen))
    {
        cout << "Invalid input. Try again: ";
        getline(cin, gen);
    }

    Simulation x(stoi(pop), stoi(gen));
    x.startSimulation();

    cout << "Last generation stats:\n";
    x.getStats();

    return 0;
}

// Helper function for Inventory::addItem() and editItem()
bool stringIsInt(string x)
{
    for (char c : x)
    {
        // Checks if character is not in btwn 48 and 57 in ASCII. That range is for integers
        if (static_cast<int>(c) < 48 || static_cast<int>(c) > 57) return false;
    }

    return true;
}

void programGreeting()
{
    string dummy;
    cout << "Welcome to James Armstrong's final project! The project will make a CSV file based on "
    << "each generation's total and average energy harvested." << endl;
}