
#include <string>
#include "Card.h"

std::string Card::get_card() const
{
    char suitChar;
    switch (suit)
    {
    case 0:
        suitChar = 'H';
        break; // Hearts
    case 1:
        suitChar = 'D';
        break; // Diamonds
    case 2:
        suitChar = 'C';
        break; // Clubs
    case 3:
        suitChar = 'S';
        break; // Spades
    default:
        suitChar = 'e';
        break; // Error
    }
    std::string card = std::to_string(rank) + "_" + suitChar;
    return card;
}
int Card::getRank() const { return rank; }
int Card::getSuit() const { return suit; }
