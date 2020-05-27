#define _HAS_STD_BYTE 0

#include <ctime>	//for time used in random number routines
#include <iostream>	//for cin >> & cout <<
#include <string>	//for string routines
#include <vector>

#include "game.h"
#include "player.h"
#include "SpriteFont.h"
#include "SpriteBatch.h"
#include "WindowUtils.h"
#include "CommonStates.h"
#include "Windows.h"
#include "D3DUtil.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Game::Game(MyD3D& d3d)
	:mD3D(d3d), mpSB(nullptr)
{
	mpSB = new SpriteBatch(&mD3D.GetDeviceCtx());
	mpF = new SpriteFont(&mD3D.GetDevice(), L"data/fonts/comicSansMS.spritefont");
	Game::init();
}

void Game::Release()
{
	delete mpSB;
	mpSB = nullptr;
	delete mpF;
	mpF = nullptr;
}

void Game::Update(float dTime) {
	switch (state) {
	case SETUP:
		gameInfo += input;
		input = "";

		if (enterPressed) {
			mPlayer.init(playerInput);
			enterPressed = false;
			playerInput = "";
			gameInfo = "How many rolls would you like?: ";
			state = INPUT;
		}
		break;

	case INPUT:
		if (input != "") {
			if (isdigit(input[0])) {
				gameInfo += input;
			}
			else {
				playerInput.erase(playerInput.size() - 1, 1);
			}
		}

		if (enterPressed) {
			rolls = stoi(playerInput);
			mPlayer.updateScoreAmount(rolls);

			state = RUNNING;
		}

		input = "";
		break;

	case RUNNING:
		score = to_string(play(rolls));
		gameInfo = resultOutput + "\n" + mPlayer.getName() + "'s final score is " + score;
		state = FINISHED;
		break;

	case FINISHED:

		break;
	}
}

void Game::Render(float dTime) {
	mD3D.BeginRender(Colours::Black);


	CommonStates dxstate(&mD3D.GetDevice());
	mpSB->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mD3D.GetWrapSampler());
	
	renderText(*mpSB, *mpF);

	mpSB->End();

	mD3D.EndRender();
}

void Game::init() {
	dice1_.init();
	dice2_.init();
	resultOutput = "";
	gameInfo = "What is your name?: ";
	
}

int Game::play(int rolls) {
	Score score;
	score.init();
	for (int i = 1; i <= rolls; i++)
	{
		dice1_.roll();
		dice2_.roll();
		resultOutput += "In try no: " + to_string(i) + "    Dice values are: " + to_string(dice1_.getFace()) + " and " + to_string(dice2_.getFace());
		/*cout << "\nIn try no: " << i << " \tdice values are: "
		  << dice1_.getFace() << " & "
		  << dice2_.getFace();*/
		if (dice1_.getFace() == dice2_.getFace())
		{
			score.updateAmount(dice1_.getFace());
			if (dice1_.getFace() == 6)
			{
				resultOutput += "    JackPot!!!";
				/*cout << "JackPot!!!";*/
				score.updateAmount(score.getAmount());
			}
		}
		else
			if ((dice1_.getFace() == 6) || (dice2_.getFace() == 6))
				score.updateAmount(1);
		//cout << "\tThe current score is: "
		//  << score.getAmount();	//check current score
		resultOutput += "    The current score is: " + to_string(score.getAmount()) + "\n";
	}
	return score.getAmount();
}

string Game::getRollResult()
{
	return resultOutput;
}

void Game::renderText(DirectX::SpriteBatch& batch, DirectX::SpriteFont& font) {

	RECT r = font.MeasureDrawBounds(gameInfo.c_str(), Vector2(0, 0));
	Vector2 pos{ 25.f, 10.f };
 	font.DrawString(&batch, gameInfo.c_str(), pos, Colours::Magenta, 0.f, Vector2(0, 0), 1.15f);
}

void Dice::init()
//reset the random number generator from current system time
{
	rng_.seed();
}
int Dice::getFace() const
//get the value of the dice face
{
	return face_;
}
void Dice::roll()
//roll the dice
{
	face_ = rng_.getRandomValue(6) + 1;
}