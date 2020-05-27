#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines

#include "player.h"

using namespace std;

void Player::init(const string& playerInput) {
	score_.init();
	name_ = playerInput;
}
void Player::updateScoreAmount(int a) {
	score_.updateAmount(a);
}
string Player::getName() const {
	return name_;
}
int Player::getScoreAmount() const {
	return score_.getAmount();
}
string Player::readInName() const {
	//ask the user for their name
	string name;
	cout << "\nYour name? ";
	cin >> name;
	return name;
}
int Player::readInNumberOfThrows() const {
	//ask the user for the number of dice throws
	int num;
	cout << "\nHow many go do you want? ";
	cin >> num;
	return num;
}

void Score::init()
{
	amount_ = 0;
}
int Score::getAmount() const
{
	return amount_;
}
void Score::updateAmount(int value)
//increment when value>0, decrement otherwise
{
	amount_ += value;
}