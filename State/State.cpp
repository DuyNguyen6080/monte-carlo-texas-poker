#include "State.h"

int straightFlushValue = 1;
int straightValue = 1;
int flushValue = 1;
int fourOfAKindValue = 1;
int fullHouseValue = 1;
int threeOfAKindValue = 1;
int twoPairValue = 1;
int onePairValue = 1;
int highCardValue = 0;
int State::checkStraightFlush(const std::vector<Card> &cards)
{
    // Check each suit
    for (int suit = 0; suit < 4; ++suit)
    {
        std::vector<Card> suitedCards;
        for (const Card &card : cards)
        {
            if (card.getSuit() == suit)
            {
                suitedCards.push_back(card);
            }
        }
        if (suitedCards.size() >= 5)
        {
            int straightValue = checkStraight(suitedCards);
            if (straightValue)
            {
                return straightFlushValue;
            }
        }
    }
    return 0;
}
int State::checkStraight(const std::vector<Card> &cards)
{

    // Check regular straights
    for (int i = 0; i <= 2; ++i)
    {
        if (isConsecutive(cards, i, i + 4))
        {
            return straightValue;
        }
    }
    return 0;
}

int State::checkFourOfAKind(const std::vector<Card> &cards)
{
    for (int i = 0; i <= 3; ++i)
    {
        if (cards[i].getRank() == cards[i + 1].getRank() &&
            cards[i + 1].getRank() == cards[i + 2].getRank() &&
            cards[i + 2].getRank() == cards[i + 3].getRank())
        {
            return fourOfAKindValue;
        }
    }
    return 0;
}

int State::checkFullHouse(const std::vector<Card> &cards)
{
    bool hasThree = false;
    int threeRank = 0;
    int pairRank = 0;

    // Check for three of a kind
    for (int i = 0; i <= 4; ++i)
    {
        if (cards[i].getRank() == cards[i + 1].getRank() &&
            cards[i + 1].getRank() == cards[i + 2].getRank())
        {
            hasThree = true;
            threeRank = cards[i].getRank();
            break;
        }
    }

    if (hasThree)
    {
        // Look for pair
        for (int i = 0; i <= 5; ++i)
        {
            if (cards[i].getRank() != threeRank &&
                cards[i].getRank() == cards[i + 1].getRank())
            {
                pairRank = cards[i].getRank();
                return fullHouseValue;
            }
        }
    }
    return 0;
}
int State::checkFlush(const std::vector<Card> &cards)
{
    // Check each suit
    for (int suit = 0; suit < 4; ++suit)
    {
        std::vector<Card> suitedCards;
        for (const Card &card : cards)
        {
            if (card.getSuit() == suit)
            {
                suitedCards.push_back(card);
            }
        }
        if (suitedCards.size() >= 5)
        {
            return flushValue;
        }
    }
    return 0;
}
int State::checkThreeOfAKind(const std::vector<Card> &cards)
{
    for (int i = 0; i <= 4; ++i)
    {
        if (cards[i].getRank() == cards[i + 1].getRank() &&
            cards[i + 1].getRank() == cards[i + 2].getRank())
        {
            return threeOfAKindValue;
        }
    }
    return 0;
}
int State::checkTwoPair(const std::vector<Card> &cards)
{
    int firstPairRank = 0;
    int secondPairRank = 0;

    for (int i = 0; i <= 5; ++i)
    {
        if (cards[i].getRank() == cards[i + 1].getRank())
        {
            if (firstPairRank == 0)
            {
                firstPairRank = cards[i].getRank();
                i++; // Skip the next card
            }
            else if (secondPairRank == 0 && cards[i].getRank() != firstPairRank)
            {
                secondPairRank = cards[i].getRank();
                return twoPairValue;
            }
        }
    }
    return 0;
}
int State::checkOnePair(const std::vector<Card> &cards)
{
    for (int i = 0; i <= 5; ++i)
    {
        if (cards[i].getRank() == cards[i + 1].getRank())
        {
            return onePairValue;
        }
    }
    return 0;
}

int State::checkHighCard(const std::vector<Card> &cards)
{
    return highCardValue;
}
bool State::isConsecutive(const std::vector<Card> &cards, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        if (cards[i].getRank() != cards[i + 1].getRank() + 1)
        {
            return false;
        }
    }
    return true;
}

int State::evaluateHand()
{
    const std::vector<Card> &cards = community_cards; // Use 'this->' to reference the member

    // Sort cards by rank (descending)
    std::vector<Card> sortedCards = cards;
    std::sort(sortedCards.begin(), sortedCards.end(),
              [](const Card &a, const Card &b)
              { return a.getRank() > b.getRank(); });

    // Check for straight flush
    if (int value = checkStraightFlush(sortedCards))
    {
        // cout << "Straight Flush" << endl;
        return value;
    }

    // Check for four of a kind
    if (int value = checkFourOfAKind(sortedCards))
    {
        // cout << "Four of a Kind" << endl;
        return value;
    }

    // Check for full house
    if (int value = checkFullHouse(sortedCards))
    {
        // cout << "Full House" << endl;
        return value;
    }

    // Check for flush
    if (int value = checkFlush(sortedCards))
    {
        // cout << "Flush" << endl;
        return value;
    }

    // Check for straight
    if (int value = checkStraight(sortedCards))
    {
        // cout << "Straight" << endl;
        return value;
    }

    // Check for three of a kind
    if (int value = checkThreeOfAKind(sortedCards))
    {
        // cout << "Three of a Kind" << endl;
        return value;
    }

    // Check for two pair
    if (int value = checkTwoPair(sortedCards))
    {
        // cout << "Two Pair" << endl;
        return value;
    }

    // Check for one pair
    if (int value = checkOnePair(sortedCards))
    {
        // cout << "One Pair" << endl;
        return value;
    }

    // High card
    return checkHighCard(sortedCards);
}

int State::evaluateHand(vector<Card> hand)
{
    const std::vector<Card> &cards = hand;

    // Sort cards by rank (descending)
    std::vector<Card> sortedCards = cards;
    std::sort(sortedCards.begin(), sortedCards.end(),
              [](const Card &a, const Card &b)
              { return a.getRank() > b.getRank(); });

    // Check for straight flush
    if (int value = checkStraightFlush(sortedCards))
    {
        // cout << "Straight Flush" << endl;
        return value;
    }

    // Check for four of a kind
    if (int value = checkFourOfAKind(sortedCards))
    {
        // cout << "Four of a Kind" << endl;
        return value;
    }

    // Check for full house
    if (int value = checkFullHouse(sortedCards))
    {
        // cout << "Full House" << endl;
        return value;
    }

    // Check for flush
    if (int value = checkFlush(sortedCards))
    {
        // cout << "Flush" << endl;
        return value;
    }

    // Check for straight
    if (int value = checkStraight(sortedCards))
    {
        // cout << "Straight" << endl;
        return value;
    }

    // Check for three of a kind
    if (int value = checkThreeOfAKind(sortedCards))
    {
        // cout << "Three of a Kind" << endl;
        return value;
    }

    // Check for two pair
    if (int value = checkTwoPair(sortedCards))
    {
        // cout << "Two Pair" << endl;
        return value;
    }

    // Check for one pair
    if (int value = checkOnePair(sortedCards))
    {
        // cout << "One Pair" << endl;
        return value;
    }

    // High card
    return checkHighCard(sortedCards);
}