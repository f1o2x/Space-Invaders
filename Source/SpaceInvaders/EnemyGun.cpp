#include "stdafx.h"

EnemyGun::EnemyGun(Game* g) :Weapon(g)
{
	SetTexture(L"Textures/2.png");
}
EnemyGun::EnemyGun(Game* g, float x, float y) : Weapon(g, x, y, 7.0f, 15.0f)
{
	_speed = -_speed / 2;
	SetTexture(L"Textures/2.png");
}
void EnemyGun::Update(DWORD time)
{
	Weapon::Update(time);

	Actor* act = game->GetPlayer();

	if (act->GetIsAlive())
	{
		if (_x >= act->GetX() &&
			_x <= act->GetX() + act->GetSizeX() &&
			_y >= act->GetY() &&
			_y <= act->GetY() + act->GetSizeY())
		{
			act->SetHP(act->GetHP() - 1);
			SetIsAlive(false);
		}
	}
}