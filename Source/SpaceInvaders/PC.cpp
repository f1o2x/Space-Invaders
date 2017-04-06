#include "stdafx.h"
const float PCSize = 40.0f;
PC::PC(Game* g) : Actor(g)
{
	_hp = defHP;
	_xStep = PCStepX;
}
PC::PC(Game* g, float x, float y, short int hp) : Actor(g, x, y, PCSize, PCSize + 20)
{
	_hp = hp;
	_xStep = PCStepX;
}
void PC::Shoot(DWORD time)
{
	if ((time - lLogicUpdTime) * 0.001f >= 0.4f)
	{
		game->shot_player.Update(0);
		Weapon* wpn = new StdGun(game, _x + _xSize / 2 - 3.5f, _y + 25.0f);
		game->AddWeapon(wpn);
		lLogicUpdTime = time;
	}
}