#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines

#include "random.h"

using namespace std;

void RandomNumberGenerator::seed() const
//seed the random number generator from current system time
//so that the numbers will be different every time
{
	srand(static_cast<unsigned>(time(0)));
}
int RandomNumberGenerator::getRandomValue(int max) const
//produce a random number in range [1..max]
{
	return (rand() % max) + 1;
}