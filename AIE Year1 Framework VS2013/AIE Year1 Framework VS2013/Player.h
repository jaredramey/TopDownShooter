#pragma once
#include "Entity.h"
#include "Bullet.h"

const int Max_Bullets = 20;

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

	//Everything for Bullets handled by Player
	Bullet bullets[Max_Bullets];
	float currentRealodBulletTime = 0.0f;
	float maxBulletReloadTime = 1.0f;
	bool setTextures = false;

	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jump);
	void SetMoveExtreeme(float a_leftExtreeme, float a_rightExtreeme);
	void SetVelocity(float a_velocity);
	float GetMovementKeyRight();
	float GetMovementKeyLeft();
	float GetMovementKeyFire();
	void Move(float a_speed, float a_timeStep);

	void Shoot(unsigned int a_texturePath, float a_delta);
	Bullet& GetInactiveBullet();

	static const char* PLAYER_SPRITE_PATH;
	static const float PLAYER_X;
	static const float PLAYER_Y;
	static const float PLAYER_WIDTH;
	static const float PLAYER_HEIGTH;

	Player();
	~Player();
};

