#include "AIE.h"
#pragma once

class GameState
{
public:
	unsigned int PlayerLifeToken = CreateSprite("./images/spaceArt/png/life.png", 35, 27, true);


	void SplashScreen();
	void MainMenu();
	void GamePlay();
	void HighScores();

	GameState();
	~GameState();
};

