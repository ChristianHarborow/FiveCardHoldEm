#pragma once

#include <string>

using namespace std;

class Card
{
private:
	int rank; //2,3,4,5,6,7,8,9,10,J=11,Q=12,K=13,A=14
	char suit; //s = Spades, d = Diamonds, c = Clubs, h = Hearts
public:
	Card(int rank, char suit);
	int getRank();
	static string getRankString(int rank);
	char getSuit();
	static string getSuitString(char suit);
	string toString();
};

