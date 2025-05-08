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

    for (int hand = 0; hand <= 1; hand++)
    {
        int indexplayer = 1;
        for (Player *player : players)
        {

            if (player == nullptr)
            {
                cout << "Player is null!" << endl;
                return;
            }
            cout << "dealing " << hand + 1
                 << " card to player " << indexplayer << endl;
            // Check if the player has a hand of 2 cards already

            if (player->getHand().find("-1e") == std::string::npos)
            {
                cout << "Player already has 2 cards!" << endl;
                continue;
                ;
            }
            else
            {

                Card dealtCard = deck.at(0);
                player->setCard(hand, dealtCard); // Set the dealt card in the player's hand
                cout << "Player " << indexplayer << " received card: " << player->getHand() << endl;
                indexplayer++;
                deck.erase(deck.begin()); // Remove the dealt card from the deck
            }
            cout << "--------------------------" << endl;
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
    cout << endl
         << "-------------------------" << endl;
}

void Table::showCardsAllPlayer()
{
    int indexplayer = 1;
    for (Player *player : players)
    {
        cout << "Player " << indexplayer << " Hand: " << player->getHand() << endl;
        indexplayer++;
    }
}