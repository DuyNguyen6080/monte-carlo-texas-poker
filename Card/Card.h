
#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
class Card
{
private:
    int rank;
    char suit;

public:
    Card() : rank(-1), suit('e') {} // Default constructor
    Card(int r, char s) : rank(r), suit(s) {}
    std::string get_card();
    int getRank();
    char getSuit();
    void setCard(int r, char s)
    {
        rank = r;
        suit = s;
    } // Set card rank and suit
    void setRank(int r) { rank = r; }  // Set card rank only
    void setSuit(char s) { suit = s; } // Set card suit only
    std::string getCard()
    {
        std::string card = std::to_string(rank) + suit;
        return card;
    } // Get card as string
};
#endif // CARD_H