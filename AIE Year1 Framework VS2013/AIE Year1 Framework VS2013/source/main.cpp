#include "AIE.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyShips.h"
#include "GlobalInfo.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//Setting up file for HighScore
fstream HighScore;
char highScoreOne[10];

//Function Prototypes
void SplashScreen();
void MainMenu();
void HowTo();
void GetHighScore();
void DisplayHighScore();

enum Gamestates
{
	eSPLASHSCREEN,
	eMAINEMENU,
	eGAMPLAY,
	eHOWTO,
	eHIGHSCORE
};

struct Score
{
	int score = 0;
	char theScore[10];
};
Score scoreOne;


int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeigth, false, "Top Down Shooter");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	bool gameLoop = true;
	int loadUp = 0;

	//Initiate Player and set ect. values
	unsigned int cornerCheck1 = CreateSprite("./images/spaceArt/png/laserGreenShot.png", 28, 26, true);
	unsigned int cornerCheck2 = CreateSprite("./images/spaceArt/png/laserGreen.png", 28, 26, true);
	unsigned int cornerCheck3 = CreateSprite("./images/spaceArt/png/laserRedShot.png", 28, 26, true);
	unsigned int cornerCheck4 = CreateSprite("./images/spaceArt/png/laserRed.png", 28, 26, true);

	Player player = Player();
	player.SetVelocity(300.f);
	player.SetMovementKeys(65, 68, 32);
	player.SetMoveExtreeme(0, 800);
	EnemyShips enemy = EnemyShips();
	GlobalInfo globalInfo = GlobalInfo();

	

	std::vector<EnemyShips*> ships;
	for (int i = 0; i < 20; i++)
	{
		ships.push_back(new EnemyShips(rand() % 800, 1500));
		(*ships[i]).isActive = true;
	}

	Gamestates eCurrentState = eSPLASHSCREEN;

    //Game Loop
    do
    {
        ClearScreen();


		switch (eCurrentState)
		{
		case eSPLASHSCREEN:
			SplashScreen();
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;

		case eMAINEMENU:
			MainMenu();
			//if enter is pressed change state to gameplay
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMPLAY;
			}

			//if Space is pressed then go to the How To menu
			if (IsKeyDown(32))
			{
				eCurrentState = eHOWTO;
			}

			//if ESC is pressed then exit the program
			if (IsKeyDown(256))
			{
				gameLoop = false;
			}
			break;

		case eHIGHSCORE:
			GetHighScore();
			DisplayHighScore();
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;

		case eHOWTO:
			HowTo();
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;



		case eGAMPLAY:
		
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}


			player.Move(500.f, GetDeltaTime());
			DrawSprite(player.GetSprite());

			//for loop to move the ships
			for (int i = 0; i < 20; i++)
			{
				(*ships[i]).ShipMovements((*ships[i]).speed);
				MoveSprite((*ships[i]).GetSprite(), (*ships[i]).GetX(), (*ships[i]).GetY());
				if ((*ships[i]).isActive = true)
				{
					DrawSprite((*ships[i]).GetSprite());
				}
			}

			for (int i = 0; i < 20; i++)
			{
				player.CheckBulletCollision((*ships[i]).GetY(), (*ships[i]).GetWidth(), (*ships[i]).GetX(), (*ships[i]).GetHeigth(), i);
				if (player.bulletCollision == true)
				{
					//(*ships[i]).isActive = false;
					scoreOne.score += 10;
				}
			}


			MoveSprite(cornerCheck1, (*ships[10]).GetUpLeftCornerX(), (*ships[10]).GetUpLeftCornerY());
			MoveSprite(cornerCheck2, (*ships[10]).GetUpRightCornerX(), (*ships[10]).GetUpRightCornerY());
			MoveSprite(cornerCheck3, (*ships[10]).GetLowLeftCornerX(), (*ships[10]).GetLowLeftCornerY());
			MoveSprite(cornerCheck4, (*ships[10]).GetLowRightCornerX(), (*ships[10]).GetLowRightCornerY());
			DrawSprite(cornerCheck1);
			DrawSprite(cornerCheck2);
			DrawSprite(cornerCheck3);
			DrawSprite(cornerCheck4);

			DrawString(itoa(scoreOne.score, scoreOne.theScore, 10), screenWidth* 0.15f, screenHeigth *0.05f);
			break;
		}

    } while(!FrameworkUpdate() && gameLoop == true);

    Shutdown();

    return 0;
}

void SplashScreen()
{
	int waiting = 0;
	bool loop = true;
	do{
		DrawString("Loading...", 400, 500);
		waiting++;
		if (waiting > 1000)
		{
			DrawString("Press BackSpace", 400, 450);
		}
	} while (loop = true);
}

void MainMenu()
{
	DrawString("TOP DOWN SHOOTER", screenWidth - 675, screenHeigth - 100);
	DrawString("Main Menu", screenWidth - 590, screenHeigth - 200);
	DrawString("Press Enter to start", screenWidth - 630, screenHeigth - 250);
	DrawString("Press Space to read the How To", screenWidth - 700, screenHeigth - 300);
	DrawString("Press Escape to quit", screenWidth - 630, screenHeigth - 350);
}

void HowTo()
{
	DrawString("How to Play", screenWidth - 615, screenHeigth - 200);
	DrawString("Shoot: Space", screenWidth - 810, screenHeigth - 250);
	DrawString("Move Left: A", screenWidth - 810, screenHeigth - 280);
	DrawString("Move Right: D", screenWidth - 810, screenHeigth - 310);
	DrawString("Press Backspace to return to Main Menu", screenWidth - 740, screenHeigth - 450);
}


void GetHighScore()
{
	HighScore.open("HighScore.txt", ios_base::in);

	//Read and get scoreOne
	float scoreOne;
	HighScore >> scoreOne;

	//Flush stream buffer and close file
	HighScore.sync();
	HighScore.close();
	HighScore.clear();

	//Set the scores to a char so it can be displayed later
	itoa(scoreOne, highScoreOne, 10);
}

void DisplayHighScore()
{
	DrawString("Old High Score", screenWidth - 600, screenHeigth - 600);
	DrawString("Player 1: ", screenWidth - 660, screenHeigth - 650);
	DrawString(highScoreOne, screenWidth - 530, screenHeigth - 650);
	DrawString("Press Backspace to return to Main Menu", screenWidth - 740, screenHeigth - 450);
}