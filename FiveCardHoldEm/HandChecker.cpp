#include "HandChecker.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool HandChecker::compareCards(Card card1, Card card2)
{
	return card1.getRank() > card2.getRank();
}

void HandChecker::splitSuits()
{
	suits = { vector<Card>(), vector<Card>() , vector<Card>() , vector<Card>() }; // [0]=spade, [1]=diamond, [2]=club, [3]=heart

	for (int i = 0; i < 7; i++)
	{
		Card card = hand.at(i);
		switch (card.getSuit())
		{
		case 's':
			suits.at(0).push_back(card);
			break;
		case 'c':
			suits.at(1).push_back(card);
			break;
		case 'd':
			suits.at(2).push_back(card);
			break;
		default:
			suits.at(3).push_back(card);
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

void HandChecker::checkHand(Player player, vector<Card> communityCards) 
{
	hand.clear();
	hand.insert(hand.begin(), communityCards.begin(), communityCards.end());
	hand.insert(hand.end(), player.getHoleCards.begin(), player.getHoleCards.end());

	sort(hand.begin(), hand.end(), compareCards);
	splitSuits();
	if (royalFlushCheck()) return;
	if (straightFlushCheck()) return;
	if (fourOfAKindCheck()) return;
	if (fullHouseCheck()) return;
}

bool HandChecker::royalFlushCheck() 
{
	for (int i = 0; i < 4; i++)
	{
		vector<Card> suit = suits.at(i);
		if (suit.size() >= 5)
		{
			if (suit.at(0).getRank() == 14
				&& suit.at(1).getRank() == 13
				&& suit.at(2).getRank() == 12
				&& suit.at(3).getRank() == 11
				&& suit.at(4).getRank() == 10)
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
		vector<Card> suit = suits.at(i);
		if (suit.size() >= 5)
		{
			for (int j = 0; j < suit.size() - 4; j++)
			{
				int highRank = suit.at(j).getRank();
				if (suit.at(j + 1).getRank() == highRank - 1
					&& suit.at(j + 2).getRank() == highRank - 2
					&& suit.at(j + 3).getRank() == highRank - 3
					&& suit.at(j + 4).getRank() == highRank - 4)
				{
					cout << Card::getRankString(highRank) + " High straight flush of " + Card::getSuitString(suitNumToChar(i));
					return true;
				}
				//low ace case
				if (suit.at(0).getRank() == 14 
					&& suit.at(suit.size() - 1).getRank() == 2
					&& suit.at(suit.size() - 2).getRank() == 3 
					&& suit.at(suit.size() - 3).getRank() == 4
					&& suit.at(suit.size() - 4).getRank() == 5)
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

	for (int i = 0; i < 7; i++)
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

	for (int i = 0; i < 7; i++) 
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
		if (occurences.at(i) == 3 && triple != 0)
		{
			triple = ranks.at(i);
		}
		else if (occurences.at(i) == 2 && pair != 0)
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