

#include "Player.h"

void Player::addChips(int c) { chips += c; }      // Add chips to player
void Player::subtractChips(int c) { chips -= c; } // Subtract chips from player
void Player::resetBet() { bet = 0; }              // Reset bet to 0
void Player::setChips(int c) { chips = c; }
int Player::getBet() { return bet; }
void Player::setBet(int b) { bet = b; }
