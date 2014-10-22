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

EnemyShips::EnemyShips(float a_x, float a_y) : Entity(a_x, a_y, ENEMY_WIDTH, ENEMY_HEIGTH, ENEMY_SPRITE_PATH)
{
	speed = (((rand() % 4) + 2) *.1);
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
		/*if (right == true && GetX() < 800)
		{
		//x += .04f;
		ChangeX(a_speed, 1);
		if (GetX() > 800) {
		thisDirection = true;
		}

		//change the direction from right to left
		if (right = true && GetX() >= 900)
		{
		right = false;
		left = true;
		}
		}*/

		//if (thisDirection == true)
		//{


	/*if (left == true && GetX() > 0)
	{
		//x -= .04f;
		ChangeX(a_speed, 2);
		if (GetX() < 0) {
			thisDirection = true;
		}

		//Change direction from left to right
		if (left == true && GetX() <= 0) //Continue Here
		{
			left = false;
			right = true;
		}
	}*/


	if (GetY() > 0)
		{
			ChangeY(a_speed, 2);
		}
	SetCorners();
}

void EnemyShips::Direction()
{
	srand(time(NULL));
	//direction = rand() % 2 + 1;
	newLocation = rand() % 750 + 49;
	
		if (direction == 1)
		{
			left = true;
		}

		else if (direction == 2)
		{
			right = true;
		}

		if (newLocation > 0)
		{
			this->ChangeX(newLocation, 3);
		}

		newLocation = 0;
		direction = 0;
}

EnemyShips::~EnemyShips()
{
}
