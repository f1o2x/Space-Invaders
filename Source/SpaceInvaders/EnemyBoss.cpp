#include "stdafx.h"
#include "EnemyBoss.h"
EnemyBoss::EnemyBoss(Game* game) :Enemy(game)
{
	_hp = 75;
}
EnemyBoss::EnemyBoss(Game* game, float x, float y) : Enemy(game, x, y, 150.0f, 100.0f)
{
	_hp = 75; 
}
void EnemyBoss::Update(DWORD time)
{
	Enemy::Update(time);
	if (time % 1000 > 800)
		Shoot(time);
	else if (!(rand() % 10))
		Shoot(time);
}