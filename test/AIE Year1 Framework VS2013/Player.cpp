#include "Player.h"
#include "AIE.h"


const  char* Player::PLAYER_SPRITE_PATH = "./images/spaceArt/png/player.png";
const float Player::PLAYER_X = 400;
const float Player::PLAYER_Y = 200;
const float Player::PLAYER_WIDTH = 99;
const float Player::PLAYER_HEIGTH = 75;

Player::Player() : Entity(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGTH, PLAYER_SPRITE_PATH)
{

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

void Player::SetMoveExtreeme(float a_leftExtreeme, float a_rightExtreeme, float a_bottomeExtreeme)
{
	leftMoveExtreeme = a_leftExtreeme;
	rightMoveExtreeme = a_rightExtreeme;
	bottomExtreeme = a_bottomeExtreeme;
}

float Player::GetMovementKeyRight()
{
	return moveRight;
}

float Player::GetMovementKeyLeft()
{
	return moveLeft;
}

void Player::Move(float a_speed, float a_timeStep)
{

	if (IsKeyDown(moveLeft) /*&& hasJumped == false*/)
	{
		ChangeX((a_timeStep * a_speed), 2);
		if (GetX() < (leftMoveExtreeme + GetWidth()*.1f))
		{
			ChangeX((leftMoveExtreeme + GetWidth()*.1f), 3);
		}
	}

	//Moving Right
	if (IsKeyDown(moveRight) /*&& hasJumped == false*/)
	{
		ChangeX((a_timeStep * a_speed), 1);
		if (GetX() >(rightMoveExtreeme - GetWidth()) && velocity > 0)
		{
			ChangeX((rightMoveExtreeme - GetWidth()), 3);
		}
	}

	//Shooting
	if (IsKeyDown(fire))
	{
		
	}

	//Move the player sprite and it's corners
	SetCorners();
	MoveSprite(GetSprite(), GetX(), GetY());
}

Player::~Player()
{
}
