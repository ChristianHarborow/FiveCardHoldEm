#include "HandChecker.h"
#include <algorithm>
#include <iostream>

using namespace std;

HandChecker::HandChecker(vector<Card> hand, int* value)
{
	this->hand = hand;
	this->value = value;
}

bool HandChecker::compareCards(Card card1, Card card2)
{
	return card1.getRank() < card2.getRank();
}

void HandChecker::splitSuits()
{
	suits = { vector<int>(), vector<int>() , vector<int>() , vector<int>() }; // [0]=spade, [1]=diamond, [2]=club, [3]=heart

	for (int i = 0; i < 7; i++)
	{
		Card card = hand.at(i);
		switch (card.getSuit())
		{
		case 's':
			suits.at(0).push_back(card.getRank());
			break;
		case 'c':
			suits.at(1).push_back(card.getRank());
			break;
		case 'd':
			suits.at(2).push_back(card.getRank());
			break;
		default:
			suits.at(3).push_back(card.getRank());
			break;
		}
	}
}

void HandChecker::checkHand() 
{
	sort(hand.begin(), hand.end(), compareCards);
	splitSuits();
	royalFlushCheck();
	straightFlushCheck();
}

bool HandChecker::royalFlushCheck() 
{
	for (int i = 0; i < 4; i++)
	{
		vector<int> suit = suits.at(i);
		int size = suit.size();
		if (size >= 5)
		{
			if (suit.at(size - 1) == 14
				&& suit.at(size - 2) == 13
				&& suit.at(size - 3) == 12
				&& suit.at(size - 4) == 11
				&& suit.at(size - 5) == 10)
			{
				cout << "ROYAL_FLUSH";
				return true;
			}
		}
	}
}

bool HandChecker::straightFlushCheck()
{
	for (int i = 0; i < 4; i++)
	{
		vector<int> suit = suits.at(i);
		if (suit.size() >= 5)
		{
			for (int j = suit.size() - 1; j >= 4; j--)
			{
				int highRank = suit.at(j);
				if (suit.at(j - 1) == highRank - 1
					&& suit.at(j - 2) == highRank - 2
					&& suit.at(j - 3) == highRank - 3
					&& suit.at(j - 4) == highRank - 4)
				{
					cout << "STRAIGHT FLUSH " << to_string(highRank) << " HIGH";
					return true;
				}
				//low ace case
				if (suit.at(0) == 2 && suit.at(1) == 3 
					&& suit.at(2) == 4 && suit.at(3) == 5 
					&& suit.at(suit.size() - 1) == 14)
				{
					cout << "STRAIGHT FLUSH 5 HIGH";
					return true;
				}
			}
		}
	}
	return false;
}
