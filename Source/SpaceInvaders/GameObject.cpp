#include "stdafx.h"
GameObject::GameObject(Game* g)
{
	Init(g, defCoord, defCoord, defSize, defSize);
}
GameObject::GameObject(Game* g, float x, float y, float xSize, float ySize)
{
	Init(g, x, y, xSize, ySize);
}
void GameObject::Init(Game* g, float x, float y, float xSize, float ySize)
{
	if (g != 0)
	{
		_x = x;
		_y = y;
		game = g;
		_xSize = xSize;
		_ySize = ySize;
		_VB = game->CreateVertBuff(_xSize, _ySize, _VB);
		_IB = game->CreateIndBuff(_IB);
		D3DXMatrixTranslation(&_TransObject, _x, _y, 0);
	}
}
void GameObject::SetX(float x)
{
	_x = x;
	D3DXMatrixTranslation(&_TransObject, _x, _y, 0);
}
void GameObject::SetY(float y)
{
	_y = y;
	D3DXMatrixTranslation(&_TransObject, _x, _y, 0);
}
void GameObject::SetXY(float x, float y)
{
	_x = x;
	_y = y;
	D3DXMatrixTranslation(&_TransObject, _x, _y, 0);
}
void GameObject::SetSizeX(float x)
{
	_xSize = x;
}
void GameObject::SetSizeY(float y)
{
	_ySize = y;
}
void GameObject::SetIsAlive(bool value)
{
	_isAlive = value;
}
void GameObject::SetTexture(LPWSTR path)
{
	D3DXCreateTextureFromFileEx(game->GetDevice(), path, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Texture);
}
void GameObject::SetGame(Game *g)
{
	game = g;
}
float GameObject::GetX()
{
	return _x;
}
float GameObject::GetY()
{
	return _y;
}
float GameObject::GetSizeX()
{
	return _xSize;
}
float GameObject::GetSizeY()
{
	return _ySize;
}
bool GameObject::GetIsAlive()
{
	return _isAlive;
}
IDirect3DTexture9* GameObject::GetTexture()
{
	return Texture;
}
Game* GameObject::GetGame()
{
	return game;
}
void GameObject::Draw()
{
	game->GetDevice()->SetTransform(D3DTS_WORLD, &_TransObject);
	game->DrawIndex(Texture, _VB, _IB);
}
void GameObject::Move(float x, float y)
{
	_x += x;
	_y += y;
	D3DXMatrixTranslation(&_TransObject, _x, _y, 0);
}
void GameObject::Update(DWORD time){}
GameObject::~GameObject()
{
	game->Release<IDirect3DVertexBuffer9*>(_VB);
	game->Release<IDirect3DIndexBuffer9*>(_IB);
	game->Release<IDirect3DTexture9*>(Texture);
}