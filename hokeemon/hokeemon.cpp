// hokeemon.cpp
// James Armstrong
// Due April 19, 2020

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Specification C2 - Creature Class
// Specification B2 - Virtual Class Creature
class Creature
{
private:
    string name;
    int boredom;
    int hunger;
    bool dead;
public:
    Creature();

    virtual void play() = 0;
    virtual void feed() = 0;
    virtual void listen() = 0;


    int getBoredom();
    void setBoredom(int);
    
    int getHunger();
    void setHunger(int);

    string getName();
    void setName(string);

    bool isDead();
    void setDeath(bool);
};

// Specification B1 - Child Class
class HokeemonCreature : public Creature
{
public:
    HokeemonCreature();
    HokeemonCreature(HokeemonCreature&);
    
    friend ostream& operator <<(ostream&, HokeemonCreature&);
    void operator +(HokeemonCreature&);
    
    void operator =(HokeemonCreature&);
    void play();
    void feed();
    void listen();

    static void unitTest(void (*lambda)());
};

// Specification A3 - Second Child Class
// I don't know what to do with this, so I just made it an "easy" mode creature where
// feeding and playing with it reduces its hunger and boredom by around 1000
class HokeemonCreature2 : public Creature
{
public:
    friend ostream& operator <<(ostream&, HokeemonCreature2&);
    void operator =(HokeemonCreature2&);
    void play();
    void feed();
    void listen();
    
    static void unitTest();
};

class HokeemonGame
{
private:
    HokeemonCreature creature;

public:
    void nameCreature();
    void passTime();
    bool promptUser();

    static void unitTest();
};

int main()
{
    srand(time(0));

    cout << "UNIT TESTS:\n";
    cout << "----------------------------------\n";
    HokeemonGame::unitTest();

    // Specification A4 - Write a Lambda
    auto lambda = []() { cout << "This is a functional lambda. It works.\n"; };
    HokeemonCreature::unitTest(lambda);

    HokeemonCreature2::unitTest();
    cout << "----------------------------------" << endl;
    
    HokeemonGame h;

    while (h.promptUser()) {};

    return 0;
}

void HokeemonCreature::unitTest(void (*lambda)())
{
    lambda();

    HokeemonCreature x;
    x.setBoredom(1);
    x.setHunger(2);
    x.setName("test123");
    
    cout << "HokeemonCreature: setting and getting variables ";
    (x.getBoredom() == 1 && x.getHunger() == 2 && x.getName() == "test123") ?
        cout << "works" : cout << "doesn't work";
    cout << "\n\n";

    x.feed();
    x.play();
    cout << "HokeemonCreature: Feeding and playing ";
    (x.getBoredom() < 1 && x.getHunger() > 2) ?
        cout << "works" : cout << "doesn't work";
    cout << "\n\n";
    
    HokeemonCreature y;
    x.setBoredom(10);
    y.setBoredom(20);
    y.setHunger(30);
    y.setName("Alex");

    //Specification B4 - Overload + Operator
    x + y;
    
    cout << "HokeemonCreature: operator + ";
    (x.getHunger() == 30 && x.getBoredom() == 10 && x.getName() == "tesAl") ?
        cout << "works" : cout << "doesn't work";
    cout << endl;

    cout << "HokeemonCreature: copy constructor ";
    x.setBoredom(1);
    x.setHunger(2);
    x.setName("test123");
    HokeemonCreature copy = x; 
    (copy.getBoredom() == 1 && copy.getHunger() == 2 && copy.getName() == "test123") ?
        cout << "works" : cout << "doesn't work";
    cout << endl;
}

void HokeemonCreature2::unitTest()
{
    HokeemonCreature2 x;
    x.setBoredom(1);
    x.setHunger(2);
    x.setName("test123");
    
    cout << "HokeemonCreature2: setting and getting variables ";
    (x.getBoredom() == 1 && x.getHunger() == 2 && x.getName() == "test123") ?
        cout << "works" : cout << "doesn't work";
    cout << "\n\n";

    x.feed();
    x.play();
    cout << "HokeemonCreature2: Feeding and playing ";
    (x.getBoredom() < 1 && x.getHunger() > 2) ?
        cout << "works" : cout << "doesn't work";
    cout << endl;
}

void HokeemonGame::unitTest()
{
    HokeemonGame g;
    g.creature.setBoredom(1);
    g.creature.setHunger(2);
    g.creature.setName("test123");
    
    cout << "HokeemonGame: setting and getting variables ";
    (g.creature.getBoredom() == 1 && g.creature.getHunger() == 2 && g.creature.getName() == "test123") ?
        cout << "works" : cout << "doesn't work";
    cout << "\n\n";

    g.creature.feed();
    g.creature.play();
    cout << "HokeemonGame: Feeding and playing: ";
    (g.creature.getBoredom() < 1 && g.creature.getHunger() > 2) ?
        cout << "works" : cout << "doesn't work";
    cout << "\n\n";

    g.creature.setBoredom(1);
    g.creature.setHunger(2);
    g.passTime();
    cout << "HokeemonGame: passTime() ";
    (g.creature.getBoredom() > 1 && g.creature.getHunger() < 2) ?
        cout << "works" : cout << "doesn't work";
    cout << endl;

}

Creature::Creature()
{
    name = "";
    boredom = rand() % 6;
    hunger = rand() % 6;
    dead = false;

    if (boredom == 19 && hunger == 1)
        cout << "Your creature is about to die from boredom and starvation!" <<
        "Play and feed with it as the next action!\n";

    else if (boredom == 19)
        cout << "Your creature is about to die from boredom! Play with it as the next action!\n";

    else if (hunger == 0)
        cout << "Your creature is about to die from starvation! Feed it as the next action!\n";

}


int Creature::getBoredom() { return boredom; };
void Creature::setBoredom(int x) {boredom = x; };
    
int Creature::getHunger() { return hunger; };
void Creature::setHunger(int x) { hunger = x; };

string Creature::getName() { return name; };
void Creature::setName(string x) { name = x; };

bool Creature::isDead() { return dead; };
void Creature::setDeath(bool x) { dead = x; };


HokeemonCreature::HokeemonCreature()
{
}

// Specification A2 - Copy Constructor
// My rational is simple: Copy everything from the creature in the parameter to the
// new creature
HokeemonCreature::HokeemonCreature(HokeemonCreature& x)
{
    setBoredom(x.getBoredom());
    setHunger(x.getHunger());
    setName(x.getName());
}
void HokeemonCreature::play()
{
    int x = rand() % 5 + 4;
    cout << "You played with your creature. boredom is now " << getBoredom() - x << "." << endl;
    setBoredom(getBoredom() - x);
}

void HokeemonCreature::feed()
{
    int x = rand() % 4 + 3;
    cout << "You fed your creature. Hunger is now " << getHunger() + x << "." << endl;
    setHunger(getHunger() + x);
}

void HokeemonCreature::listen()
{
    cout << *this;
    if (getBoredom() == 19 && getHunger() == 1)
        cout << "Your creature is about to die from boredom and starvation!" <<
        "Play and feed with it as the next action!\n";

    else if (getBoredom() == 19)
        cout << "Your creature is about to die from boredom! Play with it as the next action!\n";

    else if (getHunger() == 0)
        cout << "Your creature is about to die from starvation! Feed it as the next action!\n";
}

void HokeemonCreature2::play()
{
    int x = rand() % 5 + 1000;
    cout << "You played with your creature. boredom is now " << getBoredom() - x << "." << endl;
    setBoredom(getBoredom() - x);
}

void HokeemonCreature2::feed()
{
    int x = rand() % 4 + 1000;
    cout << "You fed your creature. Hunger is now " << getHunger() + x << "." << endl;
    setHunger(getHunger() + x);
}

void HokeemonCreature2::listen()
{
    cout << *this;
}

void HokeemonCreature2::operator=(HokeemonCreature2& x)
{
    setBoredom(x.getBoredom());
    setHunger(x.getHunger());
}

// Specification B3 - Overload Assignment Operator
void HokeemonCreature::operator=(HokeemonCreature& x)
{
    setBoredom(x.getBoredom());
    setHunger(x.getHunger());
}

// Specification B4 - Overload + Operator
// I cannot make it return a HokeemonCreature without a lot of convolution and warnings. I could not
// make it get it to work the traditional way. It would've been better to require a breed() or
// some other function. Having it return HokeemonCreature or HokeemonCreature& or * does not work at
// all without warnings/errors
void HokeemonCreature::operator +(HokeemonCreature& x)
{
    string l = getName().substr(0, getName().length() / 2);
    string r = x.getName().substr(0, x.getName().length() / 2);

    setName(l + r);
    setHunger(x.getHunger());
}

// Specification A1 - Critter Name
// Prompts user to give a name to the creature
void HokeemonGame::nameCreature()
{
    string input;
    cout << "Name your creature: ";
    getline(cin, input);
    cout << "Creature has been named." << endl;
    creature.setName(input);
}
// Specification C1 - PassTime()
void HokeemonGame::passTime()
{
    creature.setHunger(creature.getHunger() - 1);
    creature.setBoredom(creature.getBoredom() + 1);

    if (creature.getHunger() < 0 && creature.getBoredom() > 20)
    {
        cout << "Your creature died of boredom and starvation. Game over.\n";
        creature.setDeath(true);
    }
    else if (creature.getHunger() < 0)
    {
        cout << "Your creature died of starvation. Game over.\n";
        creature.setDeath(true);
    }
    else if (creature.getBoredom() > 20)
    {
        cout << "Your creature died from a catatonic state from boredom. Game over.\n";
        creature.setDeath(true);
    }
}

// Returns false is user quits game or creature died
bool HokeemonGame::promptUser()
{
    if (creature.isDead()) return false;
    string input;
    cout << "Choose an action by typing the number preceding it:\n";
    cout << "1.) Listen\n";
    cout << "2.) Play\n";
    cout << "3.) Feed\n";
    cout << "4.) Play and feed\n";
    cout << "5.) Quit\n";
    getline(cin, input);
    cout << '\n';

    // Specification C3 - Validate Input
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
    {
        cout << "Invalid input. Choose a number: ";
        getline(cin, input);
    }

    switch (stoi(input))
    {
    case 1:
        passTime();
        creature.listen();
        break;
    
    case 2:
        creature.play();
        passTime();
        break;
    
    case 3:
        creature.feed();
        passTime();
        break;
    case 4:
        creature.play();
        creature.feed();
        passTime();
        break;

    case 5:

        // Notifies main() if the user quit or not to break the loop
        return false;
        break;
    
    default:
        cout << "I have no clue how this was called.\n";
        break;
    }

    return true;
}

// Specification C4 - Overload «
ostream& operator <<(ostream& o, HokeemonCreature& x)
{
    o << "Creature's boredom: " << x.getBoredom() << '\n';
    o << "Creature's hunger: " << x.getHunger() << endl;
    return o;
}

ostream& operator <<(ostream& o, HokeemonCreature2& x)
{
    o << "Creature's boredom: " << x.getBoredom() << '\n';
    o << "Creature's hunger: " << x.getHunger() << endl;
    return o;
}