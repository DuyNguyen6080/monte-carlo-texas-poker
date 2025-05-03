#ifndef PLAYER_H
#define PLAYER_H
#include "../Card/Card.h"
class Player
{
private:
    Card hand[2];
    int chips;
    int bet;

public:
    Player() : chips(100), bet(0) {} // Initialize player with 100 chips and no bet
    void setHand(Card c1, Card c2)
    {
        hand[0] = c1;
        hand[1] = c2;
    }
    void setfirstCard(Card c1) { hand[0] = c1; }  // Set first card in hand
    void setsecondCard(Card c2) { hand[1] = c2; } // Set second card in hand
    void setCard(int i, Card c) { hand[i] = c; }  // Set card at index i in hand
    Card *getHand() { return hand; }              // Return pointer to hand array
    int getChips() { return chips; }              // Return number of chips
    void addChips(int c);                         // Add chips to player
    void subtractChips(int c);                    // Subtract chips from player
    void resetBet();                              // Reset bet to 0
    void setChips(int c);
    int getBet();
    void setBet(int b);
};
#endif