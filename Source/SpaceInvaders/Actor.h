#pragma once
class Weapon;

class Actor : public GameObject
{
protected:
	short int _hp; //���� ����� ����������
	float _xStep; //����������� ��������� �� ��� X
	float _yStep; //����������� ��������� �� ��� Y
	DWORD lLogicUpdTime; //���������� ��� ����������� �� ��������
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
