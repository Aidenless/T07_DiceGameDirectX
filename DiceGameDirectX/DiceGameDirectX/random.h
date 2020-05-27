#pragma once

#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines

using namespace std;

class RandomNumberGenerator
{
public:
	void seed() const;
	int getRandomValue(int) const;
};