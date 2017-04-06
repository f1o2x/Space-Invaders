#pragma once
#include "stdafx.h"
class EnemyGun : public Weapon
{
private:
	EnemyGun();
public:
	EnemyGun(Game* g);
	EnemyGun(Game* g, float x, float y);
	void Update(DWORD time);
};