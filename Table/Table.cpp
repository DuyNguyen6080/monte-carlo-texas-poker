#include "Table.h"
#include <random>
#include <chrono>
#include <algorithm> // For std::shuffle
void Table::shuffleDeck()
{
    // Shuffle the deck (for simplicity, not implemented here)
    if (!deck.empty())
    {
        std::shuffle(deck.begin(),
                     deck.end(),
                     std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        return;
    }
    else
    {
        cout << "Deck is empty!" << endl;
    }
}

void Table::dealCard()
{
    if (deck.empty())
    {
        cout << "Deck is empty!" << endl;
        return;
    }
    for (int hand = 0; hand < 2; hand++)
    {

        int indexplayer = 1;
        for (Player player : players)
        {
            cout << "dealing " << hand + 1
                 << " card to player " << indexplayer << endl;
            // Check if the player has a hand of 2 cards already
            if (player.getHand()[0].getRank() != -1 && player.getHand()[1].getRank() != -1)
            {
                cout << "Player already has 2 cards!" << endl;
                return;
            }
            else
            {

                Card dealtCard = deck.at(0);
                player.setCard(hand, dealtCard);
                cout << "Player " << indexplayer << " received card: " << player.getHand()->get_card() << endl;
                deck.erase(deck.begin()); // Remove the dealt card from the deck
            }
            indexplayer++;
        }
    }
    return;
}

void Table::printDeck()
{
    cout << "Deck contains: " << endl;

    for (Card card : deck)
    {
        cout << card.get_card() << " ";
    }
    cout << endl;
}

void Table::showCardsAllPlayer()
{
    int indexplayer = 1;
    for (Player player : players)
    {
        cout << "Player " << indexplayer << " Hand: " << player.getHand()->get_card() << endl;
        indexplayer++;
    }
}