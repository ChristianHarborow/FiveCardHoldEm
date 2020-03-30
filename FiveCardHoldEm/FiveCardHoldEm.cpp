// FiveCardHoldEm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "HandChecker.h"

using namespace std;

int main()
{
	Player player1 = Player(2000);
	player1.addCard(Card(4, 's'));
	player1.addCard(Card(2, 'c'));
	vector<Card> communityCards = { Card(2, 'd'), Card(4, 'd'), Card(11,'s'), Card(3, 'd'), Card(8, 'h') };
	HandChecker::checkHand(&player1, communityCards);
	
	for (Card card : player1.getHand())
	{
		cout << card.toString() << "\n";
	}
}



