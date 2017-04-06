#pragma once

class GameObject
{
private:
	GameObject();
protected:
	//Размер и координаты по-умолчанию
	const float defSize = 1.0f;
	const float defCoord = 0.0f;
	//Координата левого верхнего угла объекта
	float _x;
	float _y;
	//Размер объекта
	float _xSize;
	float _ySize;
	//
	bool _isAlive; //Переменная состояния объекта(жив/убит)
	Game* game;
	D3DXMATRIX _TransObject; //Матрица преобразований
	IDirect3DVertexBuffer9* _VB;
	IDirect3DIndexBuffer9* _IB;
	IDirect3DTexture9* Texture;
public:
	GameObject(Game* g);
	GameObject(Game* g, float x, float y, float xSize, float ySize);
	void Init(Game* g, float _x, float _y, float _xSize, float _ySize); //Инициализация объекта
	void SetX(float x);
	void SetY(float y);
	void SetXY(float x, float y);
	void SetSizeX(float x);
	void SetSizeY(float y);
	void SetIsAlive(bool value);
	void SetTexture(LPWSTR path);
	void SetGame(Game *g);
	float GetX();
	float GetY();
	float GetSizeX();
	float GetSizeY();
	bool GetIsAlive();
	IDirect3DTexture9* GetTexture();
	Game* GetGame();
	virtual void Draw();
	virtual void Move(float x, float y);
	virtual void Update(DWORD time);
	virtual ~GameObject();
};

