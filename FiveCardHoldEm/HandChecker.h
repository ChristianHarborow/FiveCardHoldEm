#pragma once
#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

class HandChecker
{
private:
	static Player player;
	static vector<Card> cards;
	static vector<vector<Card>> suits;

	static bool compareCards(Card card1, Card card2);
	static void splitSuits();

	static bool royalFlushCheck();
	static bool straightFlushCheck();
	static bool fourOfAKindCheck();
	static bool fullHouseCheck();
	static bool flushCheck();
	static bool straightCheck();
	static bool threeOfAKindCheck();
	static bool twoPairCheck();
	static bool pairCheck();
	static void highCards();
public:
	static void checkHand(Player player, vector<Card> communityCards);
};

