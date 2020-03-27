#include "Card.h"

Card::Card(int rank, char suit) 
{
	this->rank = rank;
	this->suit = suit;
}

int Card::getRank()
{
	return rank;
}

string Card::getRankString(int rank) {
	string rankString;

	switch (rank)
	{
	case 11:
		rankString = "Jack";
		break;
	case 12:
		rankString = "Queen";
		break;
	case 13:
		rankString = "King";
		break;
	case 14:
		rankString = "Ace";
		break;
	default:
		rankString = to_string(rank);
		break;
	}

	return rankString;
}

char Card::getSuit()
{
	return suit;
}

string Card::getSuitString(char suit) {
	string suitString;
	
	switch (suit)
	{
	case 's':
		suitString = "Spades";
		break;
	case 'd':
		suitString = "Diamonds";
		break;
	case 'c':
		suitString = "Clubs";
		break;
	default:
		suitString = "Hearts";
		break;
	}

	return suitString;
}

string Card::toString()
{		
	return getRankString(rank) + " Of " + getSuitString(suit);
}
