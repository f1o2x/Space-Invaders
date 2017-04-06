#include "stdafx.h"
void Enemy::SetData()
{
	_xStep = EnemyStepX;
	_yStep = EnemyStepY;
	_dirChangeCount = 0;
	_moveDirection = 1;
	_hp = 2;
}
Enemy::Enemy(Game* g) : Actor(g)
{
	SetData();
}
Enemy::Enemy(Game* g, float x, float y) : Actor(g, x, y, 25.0f, 25.0f)
{
	SetData();
}
Enemy::Enemy(Game* g, float x, float y, float w, float h) : Actor(g, x, y, w, h)
{
	SetData();
}
void Enemy::SetMoveDir(bool Dir)
{
	_dirChangeCount++;
	if (!(_dirChangeCount % 3))
	{
		Move(0.0f, -_yStep);
		_xStep++;
	}
	_moveDirection = Dir;
}
bool Enemy::GetMoveDir()
{
	return _moveDirection;
}
void Enemy::Update(DWORD time)
{
	if (_moveDirection)
	{
		if (_x + _xSize + _xStep< game->GetWidth() / 2)
			Move(_xStep, 0.0f);
		else
		{
			Move(-_xStep, 0.0f);
			SetMoveDir(0);
		}
	}
	else
	{
		if (_x - _xStep > -game->GetWidth() / 2)
			Move(-_xStep, 0.0f);
		else
		{
			Move(_xStep, 0.0f);
			SetMoveDir(1);
		}
	}
	if (_y < -game->GetHeight() / 2.0f + 100.0f)
		game->GetPlayer()->SetIsAlive(false);
}
void Enemy::Shoot(DWORD time)
{
	game->shot_enemy.Update(0);
	Weapon* wpn = new EnemyGun(game, _x + _xSize / 2, _y);
	game->AddWeapon(wpn);
}
Enemy::~Enemy(){}