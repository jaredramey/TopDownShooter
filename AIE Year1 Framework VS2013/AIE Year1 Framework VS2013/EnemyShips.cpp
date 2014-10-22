#include "EnemyShips.h"
#include "AIE.h"
#include <stdlib.h>
#include <time.h>

const char* EnemyShips::ENEMY_SPRITE_PATH = "./images/spaceArt/png/enemyShip.png";
const float EnemyShips::ENEMY_X = 400;
const float EnemyShips::ENEMY_Y = 800;
const float EnemyShips::ENEMY_WIDTH = 98;
const float EnemyShips::ENEMY_HEIGTH = 50;

EnemyShips::EnemyShips() : Entity(ENEMY_X, ENEMY_Y, ENEMY_WIDTH, ENEMY_HEIGTH, ENEMY_SPRITE_PATH)
{

}

void EnemyShips::ShipMovements(float a_speed)
{
	/*if (left == false && right == false)
	{
	Direction();
	}

	if (left == true)
	{
	if (GetX() < (0 + GetWidth()*.5))
	{
	left == false;
	right == true;
	ChangeX(a_speed, 1);

	}

	if (GetX() > (0 + GetWidth()*.5) && left == true)
	{
	ChangeX(a_speed, 2);
	}
	}

	if (right == true)
	{
	if (GetX() > (800 - GetWidth()*.5))
	{
	right == false;
	left == true;
	ChangeX(a_speed, 2);
	}

	if (GetX() > (800 - GetWidth()*.5) && right == true)
	{
	ChangeX(a_speed, 1);
	}
	}*/
	if (left == false && right == false || left == true && right == true)
	{
		Direction();
	}

	if (left == true && GetX() > 0)
	{
		//x -= .04f;
		ChangeX(a_speed, 2);
		if (GetX() < 0) {
			thisDirection = true;
		}
	}

	if (right == true && GetX() < 800)
	{
		//x += .04f;
		ChangeX(a_speed, 1);
		if (GetX() > 800) {
			thisDirection = true;
		}
	}

	if (thisDirection == true)
	{
		//Change direction from left to right
		if (left == true && GetX() <= 0) //Continue Here
		{
			left = false;
			right = true;
		}

		//change the direction from right to left
		if (right = true && GetX() >= 900)
		{
			right = false;
			left = true;
		}

		if (GetY() > 0)
		{

			//y -= 4.f;
			//ChangeY(a_speed, 2);

		}
	}
	MoveSprite(GetSprite(), GetX(), GetY());
}

void EnemyShips::Direction()
{
	srand(time(NULL));
	direction = rand() % 2 + 1;
	
		if (direction == 1)
		{
			left = true;
		}

		else if (direction == 2)
		{
			right = true;
		}

		direction = 0;
		once++;
}

EnemyShips::~EnemyShips()
{
}
