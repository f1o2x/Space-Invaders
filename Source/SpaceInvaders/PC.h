#pragma once
#include "Actor.h"
class PC : public Actor
{
private:
	PC();
protected:
	const int defHP = 3;
	const float PCStepX = 10.0f;
public:
	PC(Game* g);
	PC(Game* g, float x, float y, short int hp);
	void Shoot(DWORD time);
};
