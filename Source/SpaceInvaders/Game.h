#pragma once
#include "stdafx.h"
class Actor;
class GameObject;
class Weapon;

struct Vertex
{
	float _x, _y, _z;
	float _u, _v;
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z;
		_u = u; _v = v;
	}
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};

class Game
{
private:
	enum States //��������� ����
	{
		StartScreen,
		Playing,
		BossFight,
		EndScreen,
		Exiting
	};
	IDirect3DDevice9* Device; //������, �������������� ���������� ����������, ������������ ��� ������ �������
	InputClass* Input; //������ ����� (Direct input)
	DWORD lLogicUpdTime; //����� ���������� ����������
	DWORD cLogicUpdTime; //�����, ��������� � ���������� ����������
	int width; //������ ���� ����
	int height; //������ ���� ����
	int state; //��������� ����
	HWND window; //������������� ����
	Actor* player; //�����
	GameObject* BackGround; //���
	GameObject* ForeGround; //��������� �����
	GameObject* PauseScreen; //�����
	GameObject* HUD_life_player; //���������� ����� ������
	GameObject* HUD_life_boss; //���������� ����� �����
	const int enemyCntX = 11; //���������� ������ �� �����������
	const int enemyCntY = 5; //���������� ������ �� ���������
	std::list <Actor* > EnemyList; //������ ������
	std::list < Weapon* > WeaponList; //������ ���������� ��������
public:
	void LoadEnemies();
	XAudioSound sound, shot_player, shot_enemy;
	Game();
	bool Pause;
	IDirect3DVertexBuffer9* CreateVertBuff(float width, float height, IDirect3DVertexBuffer9* VB);
	IDirect3DIndexBuffer9* CreateIndBuff(IDirect3DIndexBuffer9* IB);
	IDirect3DDevice9** GetDeviceAddr();	
	IDirect3DDevice9* GetDevice();
	InputClass* GetInput();
	Actor* GetPlayer();
	HWND GetWindow();
	std::list < Weapon* >* GetWeaponList();
	std::list < Actor* >* GetEnemyList();
	int GetWidth();
	int GetHeight();
	void SetInput(InputClass* input);
	void SetWindow(HWND window);
	void CheckInput(DWORD time);
	void AddWeapon(Weapon* w);
	void SetMatrices();
	bool Setup();
	void Win();
	void Loose();
	void DrawIndex(IDirect3DTexture9* Tex, IDirect3DVertexBuffer9* VB, IDirect3DIndexBuffer9* IB);
	void DrawHUD();
	bool Display(float timeDelta);
	void Update();
	void Exit();
	template<class T> void Release(T t)
	{
		if (t)
		{
			t->Release();
			t = 0;
		}
	}
	template<class T> void Delete(T t)
	{
		if (t)
		{
			delete t;
			t = 0;
		}
	}
	void Cleanup();
	~Game();
};