

#include "../Table/Table.h"
#include "../Card/Card.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class State
{
private:
    pair<Card, Card> player_hand;
    vector<Card> community_cards;
    vector<Card> combine_cards; // Combine player hand and community cards
    static int checkStraightFlush(const std::vector<Card> &cards);
    static int checkStraight(const std::vector<Card> &cards);
    static int checkFourOfAKind(const std::vector<Card> &cards);
    static int checkFullHouse(const std::vector<Card> &cards);
    static int checkFlush(const std::vector<Card> &cards);
    static int checkThreeOfAKind(const std::vector<Card> &cards);
    static int checkTwoPair(const std::vector<Card> &cards);
    static int checkOnePair(const std::vector<Card> &cards);
    static int checkHighCard(const std::vector<Card> &cards);
    static bool isConsecutive(const std::vector<Card> &cards, int start, int end);

public:
    State(Table table)
    {
        player_hand = table.getPlayerOneCard();
        community_cards = table.getCommunityCard();
        combine_cards.push_back(player_hand.first);
        combine_cards.push_back(player_hand.second);
        combine_cards.insert(combine_cards.end(), community_cards.begin(), community_cards.end());
        sort(combine_cards.begin(), combine_cards.end(), [](Card a, Card b)
             { return a.getRank() < b.getRank(); });
    }
    int evaluateHand();
    static int evaluateHand(vector<Card> hand);
    void printPlayerHand()
    {
        cout << "State Player Hand: " << player_hand.first.get_card() << ", " << player_hand.second.get_card() << endl;
    }
};