#pragma once

#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines

#include "random.h"
#include "D3D.h"
#include "SpriteFont.h"
#include "singleton.h"
#include "player.h"

using namespace std;


class Dice
{
public:
	void init();
	int getFace() const;
	void roll();
private:
	int face_;		//the number on the dice
	RandomNumberGenerator rng_; 	//the private random number generator
};

class Game : public Singleton<Game> {
private:
	MyD3D& mD3D;
	DirectX::SpriteBatch* mpSB = nullptr;
	DirectX::SpriteFont* mpF = nullptr;
	Dice dice1_;
	Dice dice2_;
	string resultOutput;
	
	bool isPressed = false;

	Player mPlayer;

public:
	Game(MyD3D& d3d);

	void init();

	void Update(float dTime);
	void Render(float dTime);
	void Release();

	void renderText(DirectX::SpriteBatch& batch, DirectX::SpriteFont& font);

	int play(int rolls);
	string getRollResult();
	bool enterPressed = false;
	int rolls;
	string playerInput = "";
	string input;
	string gameInfo;
	

	enum gameStates { SETUP, INPUT, RUNNING, FINISHED };
	gameStates state = SETUP;

	string score;
};

