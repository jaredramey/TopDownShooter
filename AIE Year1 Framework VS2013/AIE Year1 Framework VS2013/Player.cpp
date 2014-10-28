#include "Player.h"
#include "AIE.h"


const char* Player::PLAYER_SPRITE_PATH = "./images/spaceArt/png/player.png";
const float Player::PLAYER_X = 400;
const float Player::PLAYER_Y = 200;
const float Player::PLAYER_WIDTH = 99;
const float Player::PLAYER_HEIGTH = 75;

Player::Player() : Entity(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGTH, PLAYER_SPRITE_PATH)
{
	for (int i = 0; i < Max_Bullets; i++)
	{
		playerBullets.push_back(new Bullet());
	}
}

void Player::UpdateBulletPos(float a_bulletX, float a_bulletY)
{
	for (int i = 0; i < Max_Bullets; i++)
	{
		bulletX = (*playerBullets[i]).x;
		bulletY = (*playerBullets[i]).y;
	}
}

float Player::GetBulletX()
{
	return bulletX;
}

float Player::GetBulletY()
{
	return bulletY;
}

void Player::CheckBulletCollision(float a_corner1, float a_corner2, float a_corner3, float a_corner4, int bulletNum)
{
	//Corner1 = lower left, Corner2 = lower Right, Corner3 = upper Left, corner4 = upper Right
	if ((*playerBullets[bulletNum]).x >= a_corner1 && (*playerBullets[bulletNum]).x <= a_corner3)
	{
		bulletCollision = true;
	}

	else
	{
		bulletCollision = false;
	}
}

void Player::SetVelocity(float a_velocity)
{
	velocity = a_velocity;
}

void Player::SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_fire)
{
	moveLeft = a_moveLeft;
	moveRight = a_moveRight;
	fire = a_fire;
}

void Player::SetMoveExtreeme(float a_leftExtreeme, float a_rightExtreeme)
{
	leftMoveExtreeme = a_leftExtreeme;
	rightMoveExtreeme = a_rightExtreeme;
}

float Player::GetMovementKeyRight()
{
	return moveRight;
}

float Player::GetMovementKeyLeft()
{
	return moveLeft;
}

void Player::Shoot(unsigned int a_textureID, float delta)
{
	if (IsKeyDown(32) /*&& currentRealodBulletTime >= maxBulletReloadTime*/)
	{
		GetInactiveBullet().InitializeBullet(GetX(), GetY(), 0.0f, 0.5f, a_textureID);
		for (int i = 0; i < Max_Bullets; i++)
		{
			(*playerBullets[i]).Update(GetDeltaTime());
		}
	}

	currentRealodBulletTime += delta;
}

Bullet& Player::GetInactiveBullet()
{
	if (setTextures == false)
	{
		for (int i = 0; i < Max_Bullets; i++)
		{
			(*playerBullets[i]).bulletTextureID = CreateSprite("./images/spaceArt/png/laserRed.png", 15, 60, true);
		}

		/*for (int i = 0; i < Max_Bullets; i++)
		{
			bullets[i].bulletTextureID = CreateSprite("./images/spaceArt/png/laserRed.png", 15, 60, true);
		}*/
		setTextures = true;
	}

	for (int i = 0; i < Max_Bullets; i++)
	{
		return (*playerBullets[i]);
	}
}

void Player::Move(float a_speed, float a_timeStep)
{

	if (IsKeyDown(moveLeft))
	{
		ChangeX((a_timeStep * a_speed), 2);
		if (GetX() < (leftMoveExtreeme + GetWidth()*.5f))
		{
			ChangeX((leftMoveExtreeme + GetWidth()*.5f), 3);
		}
	}

	//Moving Right
	if (IsKeyDown(moveRight))
	{
		ChangeX((a_timeStep * a_speed), 1);
		if (GetX() >= (rightMoveExtreeme - GetWidth()*.5f))
		{
			ChangeX((rightMoveExtreeme - GetWidth()*.5f), 3);
		}
	}

	//Shooting
	if (IsKeyDown(fire))
	{
		for (int i = 0; i < Max_Bullets; i++)
		{
			(*playerBullets[i]).isActive = true;
			Shoot((*playerBullets[i]).bulletTextureID, GetDeltaTime());
		}
	}

	//Move the player sprite and it's corners
	SetCorners();
	MoveSprite(GetSprite(), GetX(), GetY());
	for (int i = 0; i < Max_Bullets; i++ )
	{
		if (currentRealodBulletTime >= maxBulletReloadTime)
		{
			(*playerBullets[i]).Update(100.f);
			(*playerBullets[i]).Draw();
		}
	}
	
}

Player::~Player()
{
}
