#pragma once
#include "Actor.h"
class Enemy : public Actor
{
private:
	const float EnemyStepX = 5.0f;
	const float EnemyStepY = 25.0f;
	int _dirChangeCount; //Переменная хранит кол-во смен направлений врагов для увеличения скорости их движения
	bool _moveDirection; //Направление движения
	Enemy();
	void SetData();
public:
	Enemy(Game* g);
	Enemy(Game* g, float x, float y);
	Enemy(Game* g, float x, float y, float w, float h);
	void SetMoveDir(bool Dir);
	bool GetMoveDir();
	void Update(DWORD time); 
	void Shoot(DWORD time);
	~Enemy();
};
