#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <thread>
#include <algorithm>
#include <stack>
#include "Card/Card.h"
#include "Player/Player.h"
#include "Table/Table.h"
#include "State/State.h"
#include <atomic>

using namespace std;

// cancellation flag so that once one thread “stays,” all threads can stop
static atomic<bool> any_stayed{false};
// shared “best” score (optional)
static atomic<double> best_score{0.0};
std::vector<std::vector<Card>> combinations(const std::vector<Card> &cards, int c)
{
    std::vector<std::vector<Card>> result;
    int r = cards.size();
    if (c < 0 || c > r)
        return result;

    // 1) Setup an index array: [0,1,2,...,c-1]
    std::vector<int> idx(c);
    for (int i = 0; i < c; ++i)
        idx[i] = i;

    // 2) Repeatedly build each combination from idx[], then advance idx[].
    while (true)
    {
        // build current combination
        std::vector<Card> comb;
        comb.reserve(c);
        for (int i = 0; i < c; ++i)
            comb.push_back(cards[idx[i]]);
        result.push_back(comb);

        // 3) Find rightmost position we can increment
        int i = c - 1;
        // max value for idx[j] is r - c + j
        while (i >= 0 && idx[i] == r - c + i)
            --i;
        if (i < 0)
            break; // we have generated everything

        // 4) Increment idx[i], then reset subsequent indices
        ++idx[i];
        for (int j = i + 1; j < c; ++j)
            idx[j] = idx[j - 1] + 1;
    }

    return result;
}
void createGameWorld()
{

    while (!any_stayed)
    {
        // cout << "----------------------------Thread " << thread_id << "----------------------------" << endl;
        Table table1(2);
        // Initialize the game world
        printf("\n\n\n\n------------------------");
        printf("Welcome to the Game World!");
        cout << "------------------------" << endl;
        printf("\n\n\n\n------------------------");
        printf("Initializing game world...\n");
        printf("------------------------");
        // Create a simple game world with a grid of characters

        cout << "Deck before shuffling: " << endl;
        table1.printDeck();
        table1.shuffleDeck();
        cout << "Deck after shuffling: " << endl;
        table1.printDeck();

        //--------------STARTING GAME----------------
        cout << "Dealing cards to players..." << endl;
        table1.dealCard();
        table1.showCardsAllPlayer();
        cout << "-----------------------" << endl;
        //-----------------Pre-Flop----------------

        vector<vector<Card>> comb_pre_flop = combinations(table1.getDeck(), 5 - table1.getCommunityCard().size());
        double score_pre_flop = 0;
        for (const auto &combination : comb_pre_flop)
        {
            score_pre_flop += State::evaluateHand(combination);
        }
        cout << "Pre-flop winning probability: " << score_pre_flop / comb_pre_flop.size() << endl;
        cout << "-----------------------" << endl;
        if (score_pre_flop / comb_pre_flop.size() < 0.5)
        {
            cout << "------------FOLD----------" << endl;
            continue;
        }

        // -----------------------FLOP----------------
        for (int i = 0; i < 3; i++)
        {
            table1.dealCommunityCard();
        }
        table1.printCommunityCard();

        vector<vector<Card>> comb_flop = combinations(table1.getDeck(), 5 - table1.getCommunityCard().size());
        double score_flop = 0;
        for (const auto &combination : comb_flop)
        {
            score_flop += State::evaluateHand(combination);
        }
        cout << " Flop winning probability: " << score_flop / comb_flop.size() << endl;
        cout << "-----------------------" << endl;
        if (score_flop / comb_flop.size() < 0.5)
        {
            cout << "------------FOLD----------" << endl;
            continue;
        }
        // -----------------------TURN----------------
        table1.dealCommunityCard();
        table1.printCommunityCard();

        vector<vector<Card>> comb_turn = combinations(table1.getDeck(), 5 - table1.getCommunityCard().size());
        /*for (const auto &combination : comb)
        {
            for (const auto &card : combination)
            {
                cout << card.get_card() << " ";
            }
            cout << endl;
        }*/
        double score_turn = 0;
        for (const auto &combination : comb_turn)
        {
            score_turn += State::evaluateHand(combination);
        }
        cout << "Turn winning probability: " << score_turn / comb_turn.size() << endl;
        cout << "-----------------------" << endl;
        if (score_turn / comb_turn.size() < 0.5)
        {
            cout << "------------FOLD----------" << endl;
            continue;
        }

        // -----------------------RIVER----------------
        table1.dealCommunityCard();
        table1.printCommunityCard();
        double score_river = 0;
        vector<vector<Card>> comb_river = combinations(table1.getDeck(), 5 - table1.getCommunityCard().size());
        /*for (const auto &combination : comb)
        {
            for (const auto &card : combination)
            {
                cout << card.get_card() << " ";
            }
            cout << endl;
        }*/

        for (const auto &combination : comb_river)
        {
            score_river += State::evaluateHand(combination);
        }
        cout << "River winning probability: " << score_river / comb_river.size() << endl;
        cout << "-----------------------" << endl;
        cout << "PLayer 1 Hand: " << table1.getPlayerOneCard().first.get_card() << ", " << table1.getPlayerOneCard().second.get_card() << endl;
        if (score_river / comb_river.size() < 0.5)
        {
            cout << "------------FOLD----------" << endl;
            continue;
        }
        else
        {
            cout << "------------STAY----------" << endl;
            best_score = score_river / comb_river.size();
            any_stayed = true; // signal everyone else to stop
            break;             // exit your loop & function
        }
    }
    return;
}
int main()
{
    createGameWorld();
}