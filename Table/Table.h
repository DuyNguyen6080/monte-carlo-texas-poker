#ifndef Table_cpp
#define Table_cpp

#include <iostream>
#include <vector>
#include <stack>
#include "../Player/Player.h"
#include "../Card/Card.h"

using namespace std;
class Table
{
private:
    vector<Player *> players;
    vector<Card> deck;
    int numPlayers;

public:
    Table(int numPlayers) : numPlayers(numPlayers)
    {
        for (int i = 0; i < numPlayers; i++)
        {

            players.push_back(new Player());
        }
        // Initialize deck with cards (for simplicity, using only ranks 1-13 and suits 'H', 'D', 'C', 'S')
        for (int rank = 2; rank <= 14; rank++)
        {
            for (char suit : {'H', 'D', 'C', 'S'})
            {
                deck.push_back(Card(rank, suit));
            }
        }
    }
    void shuffleDeck();
    void dealCard();
    void printDeck();
    void showCardsAllPlayer();
};

#endif