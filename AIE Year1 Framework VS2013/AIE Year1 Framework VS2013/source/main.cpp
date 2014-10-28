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

//enum to handle the current gamestate
enum Gamestates
{
	eSPLASHSCREEN,
	eMAINEMENU,
	eGAMPLAY,
	eHOWTO,
	eHIGHSCORE
};

//quick struct for player score so I can output it onto to screen later
struct Score
{
	int score = 0;
	char theScore[10];
};
Score scoreOne;

//an int I can use and loop on later
int playerLives = PlayerLives;

int main( int argc, char* argv[] )
{	
	//initialize the AIE Framework
    Initialise(screenWidth, screenHeigth, false, "Top Down Shooter");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//ect variables
	bool gameLoop = true;
	bool damage = false;
	int loadUp = 0;
	float damageRecovery = 0;
	

	
	unsigned int cornerCheck1 = CreateSprite("./images/spaceArt/png/life.png", 28, 26, true);
	unsigned int cornerCheck2 = CreateSprite("./images/spaceArt/png/life.png", 28, 26, true);
	unsigned int cornerCheck3 = CreateSprite("./images/spaceArt/png/life.png", 28, 26, true);
	unsigned int cornerCheck4 = CreateSprite("./images/spaceArt/png/laserRed.png", 28, 26, true);
	
	//Initiate Player and set ect. values
	Player player = Player();
	player.SetVelocity(300.f);
	player.SetMovementKeys(65, 68, 32);
	player.SetMoveExtreeme(0, 800);
	EnemyShips enemy = EnemyShips();
	GlobalInfo globalInfo = GlobalInfo();

	//create and fill a vector of ships
	std::vector<EnemyShips*> ships;
	for (int i = 0; i < 20; i++)
	{
		ships.push_back(new EnemyShips(rand() % 800, 1500));
		(*ships[i]).isActive = true;
	}

	//set current state to splash screen
	Gamestates eCurrentState = eSPLASHSCREEN;

    //Game Loop
    do
    {
        ClearScreen();


		switch (eCurrentState)
		{
			//Splash screen
		case eSPLASHSCREEN:
			SplashScreen();
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;

			//Main Menu
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

			//Add one more for leaderboards

			//if ESC is pressed then exit the program
			if (IsKeyDown(256))
			{
				gameLoop = false;
			}
			break;

			//Leaderboard
		case eHIGHSCORE:
			GetHighScore();
			DisplayHighScore();
			//return to main menu
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;

			//How To play section
		case eHOWTO:
			HowTo();
			GetHighScore();
			DisplayHighScore();
			//return to main menu
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}
			break;



		case eGAMPLAY:
		//return to main menu and reset all values
			if (IsKeyDown(259))
			{
				eCurrentState = eMAINEMENU;
			}

			//Move the player
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

			//Check to see if the bullet has hit anything and if it has then up player score
			for (int i = 0; i < 20; i++)
			{
				if (player.CheckBulletCollision((*ships[i]).GetLowLeftCornerX(), (*ships[i]).GetUpRightCornerX(), (*ships[i]).GetUpLeftCornerY(), (*ships[i]).GetLowRightCornerY(), i) == true)
				{
					(*ships[i]).isActive = false;
					scoreOne.score += 10;
				}
			}

			//check to see if the player has run into any ships and if it has then loose a life
			for (int i = 0; i < 20; i++)
			{
				//added if statement so player doesn't loose all their life in one go
				if (damageRecovery == 0)
				{
					for (int i = 0; i < 20; i++)
					{
						if ((player.GetX() >= ((*ships[i]).GetLowLeftCornerX()) && player.GetX() <= ((*ships[i]).GetLowRightCornerX())) && (player.GetY() <= (*ships[i]).GetUpLeftCornerY() && player.GetY() >= (*ships[i]).GetLowRightCornerY()))
						{
							playerLives--;
							damageRecovery += 100;
						}
					}
				}
			}

			//change damage back to false so collision can check again
			if (damageRecovery > 0)
				damageRecovery -= .5f;

			//output player score and player lives
			DrawString(itoa(scoreOne.score, scoreOne.theScore, 10), screenWidth* 0.15f, screenHeigth *0.05f);

			if (playerLives == 3)
			{
				MoveSprite(cornerCheck1, screenWidth* 0.95f, screenHeigth *0.05f);
				DrawSprite(cornerCheck1);
				MoveSprite(cornerCheck2, screenWidth* 0.9f, screenHeigth *0.05f);
				DrawSprite(cornerCheck2);
				MoveSprite(cornerCheck3, screenWidth* 0.85f, screenHeigth *0.05f);
				DrawSprite(cornerCheck3);
			}

			else if (playerLives == 2)
			{
				MoveSprite(cornerCheck1, screenWidth* 0.95f, screenHeigth *0.05f);
				DrawSprite(cornerCheck1);
				MoveSprite(cornerCheck2, screenWidth* 0.9f, screenHeigth *0.05f);
				DrawSprite(cornerCheck2);
			}

			else if (playerLives == 1)
			{
				MoveSprite(cornerCheck1, screenWidth* 0.95f, screenHeigth *0.05f);
				DrawSprite(cornerCheck1);
			}

			else
			{
				//If the game ends then track the score for next game
				HighScore.open("HighScore.txt", ios_base::out);

				if (HighScore.is_open())
				{
					//write score into file
					HighScore << scoreOne.score << endl;

					//Change gamestate to End
					eCurrentState = eMAINEMENU;
				}
				//If something happens then tell the user
				else
				{
					DrawString("Couldn't save Score!", screenWidth - 615, screenHeigth - 200);
				}

				//Close the file
				HighScore.close();

				//reset all values
				player.ChangeX(screenWidth*.5f, 3);
				for (int i = 0; i < 20; i++)
				{
					(*ships[i]).ChangeY(1100, 3);
				}
				scoreOne.score = 0;
				playerLives = 3;
			}

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
		DrawString("Press BackSpace", 380, 450);

	} while (waiting < 1000);
}

//everything in main menu
void MainMenu()
{
	DrawString("TOP DOWN SHOOTER", screenWidth - 675, screenHeigth - 100);
	DrawString("Main Menu", screenWidth - 590, screenHeigth - 200);
	DrawString("Press Enter to start", screenWidth - 630, screenHeigth - 250);
	DrawString("Press Space to read the How To", screenWidth - 700, screenHeigth - 300);
	DrawString("Press Escape to quit", screenWidth - 630, screenHeigth - 350);
}

//everything in how to
void HowTo()
{
	DrawString("How to Play", screenWidth - 615, screenHeigth - 200);
	DrawString("Shoot: Space", screenWidth - 810, screenHeigth - 250);
	DrawString("Move Left: A", screenWidth - 810, screenHeigth - 280);
	DrawString("Move Right: D", screenWidth - 810, screenHeigth - 310);
	DrawString("Press Backspace to return to Main Menu", screenWidth - 740, screenHeigth - 450);
}

//Get highscores and Display them
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