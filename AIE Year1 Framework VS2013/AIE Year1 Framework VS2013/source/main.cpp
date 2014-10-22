#include "AIE.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyShips.h"
#include "GlobalInfo.h"
#include <iostream>
#include <ctime>

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeigth, false, "Top Down Shooter");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	bool gameLoop = true;

	unsigned int cornerCheck1 = CreateSprite("./images/spaceArt/png/laserGreenShot.png", 28, 26, true);
	unsigned int cornerCheck2 = CreateSprite("./images/spaceArt/png/laserGreen.png", 28, 26, true);
	unsigned int cornerCheck3 = CreateSprite("./images/spaceArt/png/laserRedShot.png", 28, 26, true);
	unsigned int cornerCheck4 = CreateSprite("./images/spaceArt/png/laserRed.png", 28, 26, true);

	//Initiate Bullet
	Bullet bullet = Bullet();
	//bullet.bulletTextureID = CreateSprite("./images/spaceArt/png/laserRed.png", 0, 0,true);
	//Initiate Player and set ect. values
	Player player = Player();
	player.SetVelocity(300.f);
	player.SetMovementKeys(65, 68, 32);
	player.SetMoveExtreeme(0, 800);
	EnemyShips enemy = EnemyShips();

	std::vector<EnemyShips*> ships;
	for (int i = 0; i < 20; i++)
	{
		ships.push_back(new EnemyShips(rand() % 800, 1500));
	}

    //Game Loop
    do
    {
        ClearScreen();

		if(IsKeyDown(256))
		{
			gameLoop = false;
		}

		player.Move(500.f, GetDeltaTime());
		DrawSprite(player.GetSprite());
		for (int i = 0; i < 20; i++)
		{
			(*ships[i]).ShipMovements((*ships[i]).speed);
			MoveSprite((*ships[i]).GetSprite(), (*ships[i]).GetX(), (*ships[i]).GetY());
			DrawSprite((*ships[i]).GetSprite());
		}
		MoveSprite(cornerCheck1, (*ships[10]).GetUpLeftCornerX(), (*ships[10]).GetUpLeftCornerY());
		MoveSprite(cornerCheck2, (*ships[10]).GetUpRightCornerX(), (*ships[10]).GetUpRightCornerY());
		MoveSprite(cornerCheck3, (*ships[10]).GetLowLeftCornerX(), (*ships[10]).GetLowLeftCornerY());
		MoveSprite(cornerCheck4, (*ships[10]).GetLowRightCornerX(), (*ships[10]).GetLowRightCornerY());
		DrawSprite(cornerCheck1);
		DrawSprite(cornerCheck2);
		DrawSprite(cornerCheck3);
		DrawSprite(cornerCheck4);

    } while(!FrameworkUpdate() && gameLoop == true);

    Shutdown();

    return 0;
}
