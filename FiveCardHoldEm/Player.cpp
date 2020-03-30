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

	default:
		break;
	}
	return string();
}
