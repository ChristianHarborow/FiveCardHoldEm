#pragma once
#include <vector>
#include "Card.h"


class Player
{
private:
	static const int DEFAULT_CHIPS = 1000;
	int chips;
	vector<Card> holeCards;
	int handRating; 
	vector<Card> hand;
public:
	Player(int chips = DEFAULT_CHIPS);
	void clearCards();
	void addCard(Card card);
	vector<Card> getHoleCards();
	int getChips();
	bool removeChips(int amount);
	void addChips(int amount);
	void setHandRating(int rating);
	void setHand(vector<Card> hand);
};
