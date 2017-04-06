#pragma once
class Weapon;

class Actor : public GameObject
{
protected:
	short int _hp; //Очки жизни персонажей
	float _xStep; //Перемещение персонажа по оси X
	float _yStep; //Перемещение персонажа по оси Y
	DWORD lLogicUpdTime; //Переменная для манипуляций со временем
public:
	Actor():GameObject(0){};
	Actor(Game* g);
	Actor(Game* g, float x, float y, float xSize, float ySize);
	void SetHP(short int hp); 
	void SetStepX(float step);
	void SetStepY(float step);

	short int GetHP();
	float GetStepX();
	float GetStepY();
	virtual void Shoot(DWORD time);
	~Actor();
};
