#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <vector>

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
	std::vector<Bullet*> playerBullets;
	float currentRealodBulletTime = 0.0f;
	float maxBulletReloadTime = 1.0f;
	bool setTextures = false;
	float bulletX;
	float bulletY;
	bool bulletCollision = false;

	void UpdateBulletPos(float a_bulletX, float a_bulletY);
	float GetBulletX();
	float GetBulletY();
	void CheckBulletCollision(float a_corner1, float a_corner2, float a_corner3, float a_corner4, int bulletNum);
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

