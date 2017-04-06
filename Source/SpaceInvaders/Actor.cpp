#include "stdafx.h"
Actor::Actor(Game* g) : GameObject(g){ _isAlive = true; }
Actor::Actor(Game* g, float x, float y, float xSize, float ySize) : GameObject(g, x, y, xSize, ySize){ _isAlive = true; }
void Actor::SetHP(short int hp)
{
	_hp = hp;
	if (_hp <= 0)
		_isAlive = false;
}
void Actor::SetStepX(float step)
{
	_xStep = step;
}
void Actor::SetStepY(float step)
{
	_yStep = step;
}
short int Actor::GetHP()
{
	return _hp;
}
float Actor::GetStepX()
{
	return _xStep;
}
float Actor::GetStepY()
{
	return _yStep;
}
void Actor::Shoot(DWORD time){}
Actor::~Actor(){}

