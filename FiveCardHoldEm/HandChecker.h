#pragma once
#include "Card.h"
#include <vector>

using namespace std;

class HandChecker
{
private:
	vector<Card> hand;
	int* value;
	vector<vector<int>> suits;

	static bool compareCards(Card card1, Card card2);
	void splitSuits();

	bool royalFlushCheck();
	bool straightFlushCheck();
	bool fourOfAKindCheck();
	bool fullHouseCheck();
	bool flushCheck();
	bool straightCheck();
	bool threeOfAKindCheck();
	bool twoPairCheck();
	bool pairCheck();
public: 
	HandChecker(vector<Card> hand, int* value);
	void checkHand();
	

	
};

