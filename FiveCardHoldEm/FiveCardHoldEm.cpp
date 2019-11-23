// FiveCardHoldEm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "HandChecker.h"
#include "Card.h"

using namespace std;

int main()
{
	int value = 0;
	vector<Card> test = { Card(8, 's'), Card(9,'s'), Card(10,'s'), Card(11,'s'), Card(12,'s'), Card(13,'s'), Card(14,'s') };
	HandChecker hc(test, &value);
	hc.checkHand();
}


