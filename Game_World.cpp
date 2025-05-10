#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include "Card/Card.h"
#include "Player/Player.h"
#include "Table/Table.h"

using namespace std;

class State {
    private:
        pair<Card, Card> player_hand;
        vector<Card> community_cards;
        double USBC1;
        int time_visit;
    public:
        State(Table table) {
            player_hand = table.getPlayerOneCard();
            community_cards = table.getCommunityCard();
            USBC1 = 0;
            time_visit;
        }
        void setUSBC(double score) {USBC1 = score;}
        void set_timevisit(int numTime) {time_visit = numTime;}
        double getUSBC(){return USBC1;}
        int get_timevisit(){return time_visit;}
    
};

int main()
{
    // Initialize the game world
    printf("Welcome to the Game World!\n");
    printf("Initializing game world...\n");

    // Create a simple game world with a grid of characters
    Table table1(2);
    cout << "Deck before shuffling: " << endl;
    table1.printDeck();
    table1.shuffleDeck();
    cout << "Deck after shuffling: " << endl;
    table1.printDeck();

    table1.dealCard();
    table1.showCardsAllPlayer();
    table1.printDeck();
}