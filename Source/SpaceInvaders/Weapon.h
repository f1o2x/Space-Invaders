#pragma once

class Weapon : public GameObject
{
private:
	Weapon();
protected:
	float _speed;
	const float _defSpeed = 4.0f;
public:
	Weapon(Game* g);
	Weapon(Game* g, float x, float y, float xSize, float ySize);
	void Draw();
	virtual void Update(DWORD time);
};



