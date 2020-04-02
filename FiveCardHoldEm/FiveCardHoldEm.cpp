#include <iostream>
#include <algorithm>
#include "HandChecker.h"

using namespace std;

int main()
{
	/*TESTING*/

	vector<Player> players = { Player(2000), Player(2000) };
	players.at(0).addCard(Card(10, 'd')); 
	players.at(0).addCard(Card(3, 'c'));
	players.at(1).addCard(Card(2, 'h'));
	players.at(1).addCard(Card(10, 'c'));

	vector<Card> communityCards = { Card(12, 'd'), Card(3, 'd'), Card(11,'h'), Card(9, 'c'), Card(9, 'h') };
	HandChecker::checkHand(&(players.at(0)), communityCards);
	HandChecker::checkHand(&(players.at(1)), communityCards);
	
	if (players.at(0).getHandRating() > players.at(1).getHandRating())
	{
		cout << "Player 1 Wins With A " + players.at(0).getHandString();
	}
	else if (players.at(0).getHandRating() < players.at(1).getHandRating()) 
	{
		cout << "Player 2 Wins With A " + players.at(1).getHandString();
	}
	else
	{
		int winner = -1;
		for ( int i = 0; i < 5; i++)
		{
			if (players.at(0).getHand().at(i).getRank() > players.at(1).getHand().at(i).getRank())
			{
				winner = 0;
				break;
			}
			else if (players.at(0).getHand().at(i).getRank() < players.at(1).getHand().at(i).getRank())
			{
				winner = 1;
				break;
			}
		}
		if (winner == -1)
		{
			cout << "Players Hands Are Equal";
		}
		else
		{
			cout << "Player " << (winner + 1) << " Wins With A " << players.at(0).getHandString();
		}
	}
}



