#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy
{
public:
	EnemyBoss(Game* game);
	EnemyBoss(Game* game, float x, float y);
	void Update(DWORD time);
};

