#include "AIE.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>

int main( int argc, char* argv[] )
{	
    Initialise(800, 1000, false, "Top Down Shooter");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	bool gameLoop = true;

	//Initiate Bullet
	Bullet bullet = Bullet();
	bullet.bulletTextureID = CreateSprite("./images/spaceArt/png/laserRed.png", 0, 0,true);
	//Initiate Player and set ect. values
	Player player = Player();
	player.SetVelocity(300.f);
	player.SetMovementKeys(65, 68, 32);
	player.SetMoveExtreeme(0, 800);

    //Game Loop
    do
    {
        ClearScreen();

		if(IsKeyDown(/*value for Esc, placehold with Q for now*/ 'Q'))
		{
			gameLoop = false;
		}

		player.Move(500.f, GetDeltaTime());
		DrawSprite(player.GetSprite());
		if (IsKeyDown(32))
		{
			player.Shoot(bullet.bulletTextureID, GetDeltaTime());
			for (int i = 0; i < Max_Bullets; i++)
			{
				player.bullets[i].Update(GetDeltaTime());
				player.bullets[i].Draw();
			}
		}

    } while(!FrameworkUpdate() && gameLoop == true);

    Shutdown();

    return 0;
}
