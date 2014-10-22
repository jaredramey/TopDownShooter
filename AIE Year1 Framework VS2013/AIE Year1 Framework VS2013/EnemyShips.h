#pragma once
#include "Entity.h"

class EnemyShips : public Entity
{
public:
	bool left = false;
	bool right = false;
	int direction;

	bool isActive;
	bool thisDirection = true;
	int once = 0;

	void ShipMovements(float speed);
	void Direction();

	EnemyShips();
	~EnemyShips();

	static const char* ENEMY_SPRITE_PATH;
	static const float ENEMY_X;
	static const float ENEMY_Y;
	static const float ENEMY_WIDTH;
	static const float ENEMY_HEIGTH;
};

