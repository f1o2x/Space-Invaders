#pragma once
#include "stdafx.h"
class StdGun : public Weapon
{
private:
	StdGun();
public:
	StdGun(Game* g);
	StdGun(Game* g, float x, float y);
	void Update(DWORD time);
};

