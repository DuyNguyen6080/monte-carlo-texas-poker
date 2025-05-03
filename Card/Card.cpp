
#include <string>
#include "Card.h"

std::string Card::get_card()
{
    std::string card = std::to_string(rank) + suit;
    return card;
}
int Card::getRank() { return rank; }
char Card::getSuit() { return suit; }
