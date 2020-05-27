#pragma once

#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines

using namespace std;

class Score
{
public:
	void init();
	int getAmount() const;
	void updateAmount(int);
private:
	int amount_;
};

class Player {
private:
	string name_;
	Score score_;
	string readInName() const;
public:
	void init(const string& playerInput);
	void updateScoreAmount(int a);
	string getName() const;
	int getScoreAmount() const;
	int readInNumberOfThrows() const;
};