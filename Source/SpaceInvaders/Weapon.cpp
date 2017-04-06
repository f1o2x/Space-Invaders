#include "stdafx.h"
Weapon::Weapon(Game* g) : GameObject(g)
{
	_speed = _defSpeed;
}
Weapon::Weapon(Game* g, float x, float y, float xSize, float ySize) : GameObject(g, x, y, xSize, ySize)
{
	_isAlive = true;
	_speed = _defSpeed;
}
void Weapon::Draw()
{
	GameObject::Draw();
}
void Weapon::Update(DWORD time)
{
	GameObject::Move(0.0f, _speed);
	float y = GetY();

	if (y < -game->GetHeight() /2 || y > game->GetHeight() /2)
	{
		_isAlive = false;
		return;
	}
}