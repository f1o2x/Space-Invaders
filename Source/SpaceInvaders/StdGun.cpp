#include "stdafx.h"

StdGun::StdGun(Game* g) :Weapon(g)
{
	SetTexture(L"Textures/1.png");
}
StdGun::StdGun(Game* g, float x, float y) : Weapon(g, x, y, 7.0f, 15.0f)
{
	SetTexture(L"Textures/1.png");
}
void StdGun::Update(DWORD time)
{
	Weapon::Update(time);

	std::list < Actor* >*enemyL = game->GetEnemyList();

	for each (Actor* enemy in *enemyL)
	{
		if (enemy->GetIsAlive())
		{
			if (_x >= enemy->GetX() &&
				_x <= enemy->GetX() + enemy->GetSizeX() &&
				_y >= enemy->GetY() &&
				_y <= enemy->GetY() + enemy->GetSizeY())
			{
				enemy->SetHP(enemy->GetHP() - 1);
				SetIsAlive(false);
				break;
			}
		}
	}
}