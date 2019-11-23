#include "Card.h"

Card::Card(int rank, char suit) 
{
	this->rank = rank;
	this->suit = suit;
}

int Card::getRank()
{
	return this->rank;
}

char Card::getSuit()
{
	return this->suit;
}

string Card::toString()
{
	string str = to_string(rank);
	return str;
}
