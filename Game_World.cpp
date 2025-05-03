#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include "Card/Card.h"
#include "Player/Player.h"
#include "Table/Table.h"

using namespace std;

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