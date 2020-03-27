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

char HandChecker::suitNumToChar(int num) {
	switch (num)
	{
	case 0:
		return 's';
		break;
	case 1:
		return 'd';
		break;
	case 2:
		return 'c';
		break;
	default:
		return 'h';
		break;
	}
}

void HandChecker::checkHand() 
{
	sort(hand.begin(), hand.end(), compareCards);
	splitSuits();
	royalFlushCheck();
	straightFlushCheck();
	fourOfAKindCheck();
	fullHouseCheck();
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
				cout << "Royal Flush of " + Card::getSuitString(suitNumToChar(i));
				return true;
			}
		}
	}
	return false;
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
					cout << Card::getRankString(highRank) + " High straight flush of " + Card::getSuitString(suitNumToChar(i));
					return true;
				}
				//low ace case
				if (suit.at(0) == 2 && suit.at(1) == 3 
					&& suit.at(2) == 4 && suit.at(3) == 5 
					&& suit.at(suit.size() - 1) == 14)
				{
					cout << "5 High Straight Flush";
					return true;
				}
			}
		}
	}
	return false;
}

bool HandChecker::fourOfAKindCheck()
{
	int rank = 15;
	int occurences = 0;

	for (int i = 6; i >= 0; i--)
	{
		if (hand.at(i).getRank() < rank)
		{
			rank = hand.at(i).getRank();
			occurences = 1;
		}
		else
		{
			occurences++;
		}
		if (occurences == 4)
		{
			cout << "4 of a Kind of " + Card::getRankString(rank) + "s";
			return true;
		}
	}
	return false;
}

bool HandChecker::fullHouseCheck()
{
	vector<int> ranks = {};
	vector<int> occurences = {};

	for (int i = 6; i >= 0; i--) 
	{
		int rank = hand.at(i).getRank();
		bool found = false;
		
		for (int j = 0; j < ranks.size(); j++)
		{
			if (rank == ranks.at(j))
			{
				occurences.at(j)++;
				found = true;
			}
		}
		if (!found)
		{
			ranks.push_back(rank);
			occurences.push_back(1);
		}
	}

	int triple = 0;
	int pair = 0;

	for (int i = 0; i < occurences.size(); i++)
	{
		if (occurences.at(i) == 3)
		{
			triple = ranks.at(i);
		}
		else if (occurences.at(i) == 2)
		{
			pair = ranks.at(i);
		}
		if (pair != 0 && triple != 0)
		{
			cout << "FULL HOUSE OF " << triple << "s AND " << pair << "s";
			return true;
		}
	}
	return false;
}

bool HandChecker::flushCheck()
{
	for (int i = 0; i < 4; i++)
	{
		if (suits.at(i).size() >= 5) {

		}
	}
	return NULL;
}