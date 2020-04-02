#include "Player.h"

Player::Player(int chips) 
	:chips(chips), handRating(0)
{
}

void Player::clearCards() {
	holeCards.clear();
}

void Player::addCard(Card card) {
	holeCards.push_back(card);
}

vector<Card> Player::getHoleCards() {
	return holeCards;
}

int Player::getChips() {
	return chips;
}

bool Player::removeChips(int amount) {
	if (chips - amount < 0)
	{
		return false;
	}
	chips -= amount;
	return true;
}

void Player::addChips(int amount) {
	chips += amount;
}

void Player::setHandRating(int rating) {
	handRating = rating;
}

int Player::getHandRating()
{
	return handRating;
}

void Player::setHand(vector<Card> hand) {
	this->hand.clear();
	this->hand.insert(this->hand.begin(), hand.begin(), hand.end());
}

vector<Card> Player::getHand()
{
	return hand;
}

string Player::getHandString()
{
	switch (handRating)
	{
	case 9:
		return "Royal Flush Of " + Card::getSuitString(hand.at(0).getSuit());
		break;
	case 8:
		if (hand.at(0).getRank() == 14 && hand.at(1).getRank() == 5)
		{
			return "5 High Straight Flush Of " + Card::getSuitString(hand.at(0).getSuit());
		}
		else
		{
			return Card::getRankString(hand.at(0).getRank()) + " High Straight Flush Of " + Card::getSuitString(hand.at(0).getSuit());
		}
		break;
	case 7:
		return "Four Of A Kind Of " + Card::getRankString(hand.at(0).getRank()) + "s With A " + Card::getRankString(hand.at(4).getRank()) + " Kicker";
		break;
	case 6:
		return "Full House of " + Card::getRankString(hand.at(0).getRank()) + "s and " + Card::getRankString(hand.at(4).getRank()) + "s";
		break;
	case 5:
		return Card::getRankString(hand.at(0).getRank()) + " High Flush Of " + Card::getSuitString(hand.at(0).getSuit());
		break;
	case 4:
		if (hand.at(0).getRank() == 14 && hand.at(1).getRank() == 5)
		{
			return "5 High Straight";
		}
		else
		{
			return Card::getRankString(hand.at(0).getRank()) + " High Straight";
		}
		break;
	case 3:
		return "Three Of A Kind Of " + Card::getRankString(hand.at(0).getRank()) + "s With " + Card::getRankString(hand.at(3).getRank()) + " And " + Card::getRankString(hand.at(4).getRank()) + " As Kickers";
		break;
	case 2:
		return "Two Pair Of " + Card::getRankString(hand.at(0).getRank()) + "s and " + Card::getRankString(hand.at(2).getRank()) + "s With A " + Card::getRankString(hand.at(4).getRank()) + " Kicker";
		break;
	case 1:
		return "Pair Of " + Card::getRankString(hand.at(0).getRank()) + "s With " + Card::getRankString(hand.at(2).getRank()) + ", " + Card::getRankString(hand.at(3).getRank()) + " And " + Card::getRankString(hand.at(4).getRank()) + " As Kickers";
		break;
	default:
		return "High Card Of" + Card::getRankString(hand.at(0).getRank()) + " With " + Card::getRankString(hand.at(1).getRank()) + ", " + Card::getRankString(hand.at(2).getRank()) + ", " + Card::getRankString(hand.at(3).getRank()) + " And " + Card::getRankString(hand.at(3).getRank()) + " As Kickers";
		break;
	}
	return string();
}
