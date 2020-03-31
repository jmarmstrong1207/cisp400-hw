#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Card
{
private:
    string suit;
    string name;

public:
    Card(string, string);

    string getSuit() { return suit; }
    string getName() { return name; }
};

Card::Card(string s, string n)
{
    suit = s;
    name = n;
}


class Blackjack
{
private:
    const int deckSize = 52;
    Card deck[52] =
    {
        Card("Diamond", "2"),
        Card("Diamond", "3"),
        Card("Diamond", "4"),
        Card("Diamond", "5"),
        Card("Diamond", "6"),
        Card("Diamond", "7"),
        Card("Diamond", "8"),
        Card("Diamond", "9"),
        Card("Diamond", "10"),
        Card("Diamond", "J"),
        Card("Diamond", "Q"),
        Card("Diamond", "K"),
        Card("Diamond", "A"),
        Card("Heart", "2"),
        Card("Heart", "3"),
        Card("Heart", "4"),
        Card("Heart", "5"),
        Card("Heart", "6"),
        Card("Heart", "7"),
        Card("Heart", "8"),
        Card("Heart", "9"),
        Card("Heart", "10"),
        Card("Heart", "J"),
        Card("Heart", "Q"),
        Card("Heart", "K"),
        Card("Heart", "A"),
        Card("Spade", "2"),
        Card("Spade", "3"),
        Card("Spade", "4"),
        Card("Spade", "5"),
        Card("Spade", "6"),
        Card("Spade", "7"),
        Card("Spade", "8"),
        Card("Spade", "9"),
        Card("Spade", "10"),
        Card("Spade", "J"),
        Card("Spade", "Q"),
        Card("Spade", "K"),
        Card("Spade", "A"),
        Card("Clubs", "2"),
        Card("Clubs", "3"),
        Card("Clubs", "4"),
        Card("Clubs", "5"),
        Card("Clubs", "6"),
        Card("Clubs", "7"),
        Card("Clubs", "8"),
        Card("Clubs", "9"),
        Card("Clubs", "10"),
        Card("Clubs", "J"),
        Card("Clubs", "Q"),
        Card("Clubs", "K"),
        Card("Clubs", "A"),
    };
public:
    Blackjack();
    void shuffle();
};

Blackjack::Blackjack()
{
}

void Blackjack::shuffle()
{
    srand(time(0));
    for (int i = 0; i < 52; i++)
    {
        int randIndex = rand() % 52;
        Card temp = deck[i];
        deck[i] = deck[randIndex];
        deck[randIndex] = temp;
    }
}