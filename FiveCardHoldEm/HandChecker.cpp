#include "HandChecker.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player* HandChecker::currentPlayerPtr;
vector<Card> HandChecker::cards;
vector<vector<Card>> HandChecker::suits;

bool HandChecker::compareCards(Card card1, Card card2)
{
	return card1.getRank() > card2.getRank();
}

void HandChecker::splitSuits()
{
	suits = { vector<Card>(), vector<Card>() , vector<Card>() , vector<Card>() }; // [0]=spade, [1]=diamond, [2]=club, [3]=heart

	for (int i = 0; i < 7; i++)
	{
		Card card = cards.at(i);
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

void HandChecker::checkHand(Player *player, vector<Card> communityCards)
{
	currentPlayerPtr = player;
	vector<Card> holeCards = (*currentPlayerPtr).getHoleCards();
	vector<Card> commCards = communityCards;
	cards.clear();
	cards.insert(cards.begin(), commCards.begin(), commCards.end());
	cards.insert(cards.end(), holeCards.begin(), holeCards.end());

	sort(cards.begin(), cards.end(), compareCards);
	splitSuits();
	if (royalFlushCheck()) return;
	if (straightFlushCheck()) return;
	if (fourOfAKindCheck()) return;
	if (fullHouseCheck()) return;
	if (flushCheck()) return;
	if (straightCheck()) return;
	if (threeOfAKindCheck()) return;
	if (twoPairCheck()) return;
	if (pairCheck()) return;
	highCards();
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
				(*currentPlayerPtr).setHandRating(9);
				(*currentPlayerPtr).setHand({suit.at(4), suit.at(3), suit.at(2), suit.at(1), suit.at(0)});
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
					(*currentPlayerPtr).setHandRating(8);
					(*currentPlayerPtr).setHand({suit.at(j + 4), suit.at(j + 3), suit.at(j + 2), suit.at(j + 1), suit.at(j)});
					return true;
				}
				//low ace case
				if (suit.at(0).getRank() == 14 
					&& suit.at(suit.size() - 1).getRank() == 2
					&& suit.at(suit.size() - 2).getRank() == 3 
					&& suit.at(suit.size() - 3).getRank() == 4
					&& suit.at(suit.size() - 4).getRank() == 5)
				{
					(*currentPlayerPtr).setHandRating(8);
					(*currentPlayerPtr).setHand({suit.at(0), suit.at(suit.size() - 1), suit.at(suit.size() - 2), suit.at(suit.size() - 3), suit.at(suit.size() - 4)});
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
		if (cards.at(i).getRank() < rank)
		{
			rank = cards.at(i).getRank();
			occurences = 1;
		}
		else
		{
			occurences++;
		}
		if (occurences == 4)
		{
			vector<Card> playerHand = {cards.at(i - 3), cards.at(i - 2), cards.at(i - 1), cards.at(i)};
			// find the kicker
			for (int j = 0; j < cards.size(); j++)
			{
				if (cards.at(j).getRank() != rank) {
					playerHand.push_back(cards.at(j));
					break;
				}
			}
			(*currentPlayerPtr).setHandRating(7);
			(*currentPlayerPtr).setHand(playerHand);
			return true;
		}
	}
	return false;
}

bool HandChecker::fullHouseCheck()
{
	vector<vector<Card>> cardsInRanks;
	vector<int> ranks;
	vector<int> occurences;

	for (int i = 0; i < 7; i++) 
	{
		int rank = cards.at(i).getRank();
		bool found = false;
		
		for (int j = 0; j < ranks.size(); j++)
		{
			if (rank == ranks.at(j))
			{
				cardsInRanks.at(j).push_back(cards.at(i));
				occurences.at(j)++;
				found = true;
			}
		}
		if (!found)
		{
			ranks.push_back(rank);
			cardsInRanks.push_back({ cards.at(i) });
			occurences.push_back(1);
		}
	}

	bool triple = false;
	bool pair = false;
	vector<Card> tripleCards;
	vector<Card> pairCards;

	for (int i = 0; i < occurences.size(); i++)
	{
		if (occurences.at(i) == 3 && !triple)
		{
			triple = true;
			tripleCards = { cardsInRanks.at(i).at(0), cardsInRanks.at(i).at(1), cardsInRanks.at(i).at(2) };
		}
		else if (occurences.at(i) >= 2 && !pair)
		{
			pair = true;
			pairCards = { cardsInRanks.at(i).at(0), cardsInRanks.at(i).at(1) };
		}
		if (pair && triple)
		{
			vector<Card> playerHand;
			playerHand.insert(playerHand.begin(), tripleCards.begin(), tripleCards.end());
			playerHand.insert(playerHand.end(), pairCards.begin(), pairCards.end());
			(*currentPlayerPtr).setHandRating(6);
			(*currentPlayerPtr).setHand(playerHand);
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
			(*currentPlayerPtr).setHandRating(5);
			(*currentPlayerPtr).setHand({ suits.at(i).at(0), suits.at(i).at(1), suits.at(i).at(2), suits.at(i).at(3), suits.at(i).at(4) });
			return true;
		}
	}
	return false;
}

bool HandChecker::straightCheck() {
	vector<int> ranks;
	vector<Card> uniqueCards;
	for (int i = 0; i < cards.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < ranks.size(); j++)
		{
			if (cards.at(i).getRank() == ranks.at(j)) {
				found = true;
				break;
			}
		}
		if (!found)
		{
			ranks.push_back(cards.at(i).getRank());
			uniqueCards.push_back(cards.at(i));
		}
	}

	if (ranks.size() >= 5)
	{
		for (int i = 0; i < ranks.size() - 4; i++) {
			int highRank = ranks.at(i);
			if (ranks.at(i + 1) == highRank - 1
				&& ranks.at(i + 2) == highRank - 2
				&& ranks.at(i + 3) == highRank - 3
				&& ranks.at(i + 4) == highRank - 4)
			{
				(*currentPlayerPtr).setHandRating(4);
				(*currentPlayerPtr).setHand({ uniqueCards.at(i + 4), uniqueCards.at(i + 3), uniqueCards.at(i + 2), uniqueCards.at(i + 1), uniqueCards.at(i) });
				return true;
			}
			//low ace case
			if (ranks.at(0) == 14
				&& ranks.at(ranks.size() - 1) == 2
				&& ranks.at(ranks.size() - 2) == 3
				&& ranks.at(ranks.size() - 3) == 4
				&& ranks.at(ranks.size() - 4) == 5)
			{
				(*currentPlayerPtr).setHandRating(4);
				(*currentPlayerPtr).setHand({ uniqueCards.at(0),
					uniqueCards.at(uniqueCards.size() - 1), 
					uniqueCards.at(uniqueCards.size() - 2), 
					uniqueCards.at(uniqueCards.size() - 3), 
					uniqueCards.at(uniqueCards.size() - 4) });
				return true;
			}
		}
	}
	return false;
}

bool HandChecker::threeOfAKindCheck() {
	int rank = 15;
	int occurences = 0;

	for (int i = 0; i < 7; i++)
	{
		if (cards.at(i).getRank() < rank)
		{
			rank = cards.at(i).getRank();
			occurences = 1;
		}
		else
		{
			occurences++;
		}
		if (occurences == 3)
		{
			vector<Card> playerHand = { cards.at(i - 2), cards.at(i - 1), cards.at(i) };
			// find the kickers
			for (int j = 0; j < cards.size(); j++)
			{
				if (cards.at(j).getRank() != rank) {
					playerHand.push_back(cards.at(j));
					if (playerHand.size() == 5)
					{
						break;
					}
				}
			}
			(*currentPlayerPtr).setHandRating(3);
			(*currentPlayerPtr).setHand(playerHand);
			return true;
		}
	}
	return false;
}

bool HandChecker::twoPairCheck() {
	vector<vector<Card>> cardsInRanks;
	vector<int> ranks;
	vector<int> occurences;

	for (int i = 0; i < 7; i++)
	{
		int rank = cards.at(i).getRank();
		bool found = false;

		for (int j = 0; j < ranks.size(); j++)
		{
			if (rank == ranks.at(j))
			{
				cardsInRanks.at(j).push_back(cards.at(i));
				occurences.at(j)++;
				found = true;
			}
		}
		if (!found)
		{
			ranks.push_back(rank);
			cardsInRanks.push_back({ cards.at(i) });
			occurences.push_back(1);
		}
	}

	vector<Card> pairCards;
	Card kicker = Card(0,'x');

	for (int i = 0; i < occurences.size(); i++)
	{
		if (occurences.at(i) == 2)
		{
			pairCards.insert(pairCards.end(), cardsInRanks.at(i).begin(), cardsInRanks.at(i).end());
		}
		else if (kicker.getRank() == 0) {
			kicker = cardsInRanks.at(i).at(0);
		}
		if (pairCards.size() == 4 && kicker.getRank() != 0)
		{
			(*currentPlayerPtr).setHandRating(2);
			pairCards.push_back(kicker);
			(*currentPlayerPtr).setHand(pairCards);
			return true;
		}
	}
	return false;
}

bool HandChecker::pairCheck() {
	int rank = 15;
	int occurences = 0;

	for (int i = 0; i < 7; i++)
	{
		if (cards.at(i).getRank() < rank)
		{
			rank = cards.at(i).getRank();
			occurences = 1;
		}
		else
		{
			occurences++;
		}
		if (occurences == 2)
		{
			vector<Card> playerHand = { cards.at(i - 1), cards.at(i) };
			// find the kickers
			for (int j = 0; j < cards.size(); j++)
			{
				if (cards.at(j).getRank() != rank) {
					playerHand.push_back(cards.at(j));
					if (playerHand.size() == 5)
					{
						break;
					}
				}
			}
			(*currentPlayerPtr).setHandRating(1);
			(*currentPlayerPtr).setHand(playerHand);
			return true;
		}
	}
	return false;
}

void HandChecker::highCards() {
	vector<Card> playerHand;
	for (int j = 0; j < 5; j++)
	{
		playerHand.push_back(cards.at(j));
		
	}
	(*currentPlayerPtr).setHandRating(0);
	(*currentPlayerPtr).setHand(playerHand);
}