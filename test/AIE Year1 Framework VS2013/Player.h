#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int health;

	float speed;
	float velocity;
	float leftMoveExtreeme;
	float rightMoveExtreeme;
	float bottomExtreeme;

	unsigned int moveLeft;
	unsigned int moveRight;
	unsigned int fire;

public:
	bool hasShot = false;
	float shotChargeTime = 150;
	float jumpRecharge;

	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jump);
	void SetMoveExtreeme(float a_leftExtreeme, float a_rightExtreeme, float a_bottomeExtreeme);
	void SetVelocity(float a_velocity);
	float GetMovementKeyRight();
	float GetMovementKeyLeft();
	float GetMovementKeyFire();

	void Move(float a_speed, float a_timeStep);

	static const char* PLAYER_SPRITE_PATH;
	static const float PLAYER_X;
	static const float PLAYER_Y;
	static const float PLAYER_WIDTH;
	static const float PLAYER_HEIGTH;

	Player();
	~Player();
};

