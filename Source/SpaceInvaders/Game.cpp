#include "stdafx.h"
bool IsGOAlive(GameObject* value) //”чавствует в удалении снар€да или врага из списка
{
	bool res = !value->GetIsAlive();
	if (res)
		delete value;
	return res;
}
Game::Game()
{
	Device = 0;
	width = 1024;
	height = 768;
}
IDirect3DVertexBuffer9* Game::CreateVertBuff(float width, float height, IDirect3DVertexBuffer9* VB)
{
	Device->CreateVertexBuffer(4 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &VB, 0);
	Vertex* VSquare;
	VB->Lock(0, 0, (void**)&VSquare, 0);
	VSquare[0] = Vertex(0, 0, 1.0f, 0.0f, 1.0f);
	VSquare[1] = Vertex(0, height, 1.0f, 0.0f, 0.0f);
	VSquare[2] = Vertex(width, height, 1.0f, 1.0f, 0.0f);
	VSquare[3] = Vertex(width, 0, 1.0f, 1.0f, 1.0f);
	VB->Unlock();
	return VB;
}
IDirect3DIndexBuffer9* Game::CreateIndBuff(IDirect3DIndexBuffer9* IB)
{
	Device->CreateIndexBuffer(6 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);
	WORD* ISquare = 0;
	IB->Lock(0, 0, (void**)&ISquare, 0);
	ISquare[0] = 0;
	ISquare[1] = 1;
	ISquare[2] = 2;
	ISquare[3] = 0;
	ISquare[4] = 2;
	ISquare[5] = 3;
	IB->Unlock();
	return IB;
}
IDirect3DDevice9** Game::GetDeviceAddr()
{
	return &Device;
}
IDirect3DDevice9* Game::GetDevice()
{
	return Device;
}
InputClass* Game::GetInput()
{
	return Input;
}


Actor* Game::GetPlayer()
{
	return player;
}
HWND Game::GetWindow()
{
	return window;
}
std::list < Weapon* >* Game::GetWeaponList()
{
	return &WeaponList;
}
std::list < Actor* >* Game::GetEnemyList()
{
	return &EnemyList;
}
int Game::GetWidth()
{
	return width;
}
int Game::GetHeight()
{
	return height;
}
void Game::SetInput(InputClass* input)
{
	Input = input;
}
void Game::SetWindow(HWND window)
{
	this->window = window;
}
void Game::CheckInput(DWORD time)
{
	if (!Input->Frame())
	{
		return;
	}

	if (Input->IsEscapePressed() == true)
	{
		Exit();
		return;
	}
	if (state == States::Playing || state == States::BossFight)
	{
		if (Input->IsPausePressed())
		{
			Pause = !Pause;
		}
		if (!Pause)
		{
			if (Input->IsKeyPressed(DIK_A))
			{
				if (player->GetX() - player->GetStepX() > -width / 2.0f)
					player->Move(-player->GetStepX(), 0.0f);
			}
			if (Input->IsKeyPressed(DIK_D))
			{
				if (player->GetX() + player->GetStepX() + player->GetSizeX() < width / 2.0f)
					player->Move(player->GetStepX(), 0.0f);
			}
		}
	}
	else if (state == States::EndScreen)
	{
		/*if (Input->IsKeyPressed(DIK_RETURN))
		{
			Setup();
		}*/
	}

	if (Input->IsKeyPressed(DIK_SPACE))
	{
		if (state == States::StartScreen)
		{
			sound.Stop();
			sound.LoadSound("Sounds/enemyFight.wav");
			sound.Start();
			state = States::Playing;
			return;
		}
		else if (!Pause)
		{
			if (state == States::Playing || state == States::BossFight)
			{
				player->Shoot(time);
			}
		}
	}
}
void Game::AddWeapon(Weapon* w)
{
	WeaponList.push_back(w);
}
void Game::SetMatrices()
{
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	D3DXVECTOR3 position(0.0f, 0.0f, -height/2.0f + 5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float)width / (float)(height), 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);
	Device->SetRenderState(D3DRS_LIGHTING, false);
	Device->SetRenderState(D3DRS_CULLMODE, false);
}
void Game::LoadEnemies()
{
	float enemyPosX = -150.0f;
	float enemyPosY = height / 2 - 200.0f;//150
	for (int i = 0; i < enemyCntY; i++)
	{
		for (int j = 0; j < enemyCntX; j++)
		{
			Actor* enemy = new Enemy(this, enemyPosX + j * 50, enemyPosY + i * 25);
			EnemyList.push_back(enemy);
		}
	}
	int i = 0;
	for each (Actor* enemy in EnemyList)
	{
		++i;
		if (i <= 2 * enemyCntX)
			enemy->SetTexture(L"Textures/ship2.png");
		else if (i <= 4 * enemyCntX)
			enemy->SetTexture(L"Textures/ship3.png");
		else
			enemy->SetTexture(L"Textures/ship4.png");
	}
}
bool Game::Setup()
{
	Cleanup();
	Pause = 0;
	time_t lastUpdTime = (time_t)timeGetTime();
	state = States::StartScreen;
	sound.Init();
	sound.LoadSound("Sounds/intro.wav");
	sound.Start();
	shot_player.Init();
	shot_player.LoadSound("Sounds/shot.wav");
	shot_player.Start();
	shot_enemy.Init();
	shot_enemy.LoadSound("Sounds/eShot.wav");
	shot_enemy.Start();

	BackGround = new GameObject(this, -width / 2.0f, -height / 2.0f, (float)width, (float)height);
	BackGround->SetTexture(L"Textures/bg.png");
	ForeGround = new GameObject(this, -width / 2.0f, -height / 2.0f, (float)width, (float)height);
	ForeGround->SetTexture(L"Textures/fg.png");

	PauseScreen = new GameObject(this, -width / 2.0f, -height / 2.0f, (float)width, (float)height);
	PauseScreen->SetTexture(L"Textures/pause.png");

	HUD_life_player = new GameObject(this, -width / 2.0f, height / 2.0f, 25.0f, 35.0f);
	HUD_life_player->SetTexture(L"Textures/player1.png");

	HUD_life_boss = new GameObject(this, 0, 0, 25.0f, 25.0f);
	HUD_life_boss->SetTexture(L"Textures/heart-icon.png");

	player = new PC(this, 0.0f, -height / 2 + 50.0f, 3);
	player->SetTexture(L"Textures/player1.png");
	LoadEnemies();
	SetMatrices();
	return true;
}
void Game::Win()
{
	sound.Stop();
	sound.LoadSound("Sounds/win.wav");
	sound.Start();
	sound.Update(0);
	state = States::EndScreen;
	ForeGround->SetTexture(L"Textures/win.png");
}
void Game::Loose()
{
	sound.Stop();
	sound.LoadSound("Sounds/lose.wav");
	sound.Start();
	sound.Update(0);
	state = States::EndScreen;
	ForeGround->SetTexture(L"Textures/lose.png");
}
void Game::DrawIndex(IDirect3DTexture9* Tex, IDirect3DVertexBuffer9* VB, IDirect3DIndexBuffer9* IB)
{
	Device->SetStreamSource(0, VB, 0, sizeof(Vertex));
	Device->SetIndices(IB);
	Device->SetFVF(Vertex::FVF);
	Device->SetTexture(0, Tex);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 4);
}
void Game::DrawHUD()
{
	for (int i = 0; i < player->GetHP(); i++)
	{
		HUD_life_player->SetXY(-width / 2.0f + 50.0f + i * 25.0f, height / 2.0f - 50.0f);
		HUD_life_player->Draw();
	}
	if (state == States::BossFight)
	{
		Actor* boss = EnemyList.front();
		for (int i = 0; i < boss->GetHP(); i++)
		{
			HUD_life_boss->SetXY(width / 2.0f - 50.0f - i * 10.0f, height / 2.0f - 50.0f);
			HUD_life_boss->Draw();
		}
	}
}
bool Game::Display(float timeDelta)
{
	if (Device && state != States::Exiting)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x007777ff, 1.0f, 0);
		Device->BeginScene();

		if (state == States::Playing || state == States::BossFight)
		{		
				Device->SetRenderState(D3DRS_ZWRITEENABLE, 0);
			BackGround->Draw();
				Device->SetRenderState(D3DRS_ZWRITEENABLE, 1);
			player->Draw();
			for each(Actor* enemy in EnemyList)
			{
				enemy->Draw();
			}
			for each(Weapon* w in WeaponList)
			{
				w->Draw();
			}
			DrawHUD();
		}
		if (Pause)
			PauseScreen->Draw();
		else if (state == States::EndScreen || state == States::StartScreen)
		{
				Device->SetRenderState(D3DRS_ZWRITEENABLE, 0);
			ForeGround->Draw();
				Device->SetRenderState(D3DRS_ZWRITEENABLE, 1);
		}
		Device->EndScene();
		Device->Present(0, 0, 0, 0); //secondary buffer
	}
	return true;
}
void Game::Update()
{
	cLogicUpdTime = timeGetTime();
	if ((cLogicUpdTime - lLogicUpdTime) * 0.001f >= 0.02f)
	{
		CheckInput(cLogicUpdTime);
		if (!Pause)
		{
			if (state != States::EndScreen)
				sound.Update(1);
			if (state == States::Playing || state == States::BossFight)
			{
				srand(cLogicUpdTime);
				for each (Actor* enemy in EnemyList)
				{
					if (!(rand() % 1000))
						enemy->Shoot(cLogicUpdTime);
					enemy->Update(cLogicUpdTime);
				}

				for each(Weapon* w in WeaponList)
				{
					w->Update(cLogicUpdTime);
				}

				WeaponList.remove_if(IsGOAlive);
				EnemyList.remove_if(IsGOAlive);

				if (EnemyList.empty())
				{
					if (state == States::BossFight)
					{
						Win();
					}
					else
					{
						sound.Stop();
						sound.LoadSound("Sounds/bossFight.wav");
						sound.Start();
						state = States::BossFight;
						float enemyPosX = -150.0f;
						float enemyPosY = height / 2 - 150.0f;
						Actor* enemy = new EnemyBoss(this, enemyPosX, enemyPosY);
						enemy->SetTexture(L"Textures/boss.png");
						EnemyList.push_back(enemy);
					}
				}
				if (!player->GetIsAlive())
				{
					Loose();
				}
			}

		}
		lLogicUpdTime = cLogicUpdTime;
	}
}
void Game::Exit()
{
	state = States::Exiting;
	::DestroyWindow(window);
}


void Game::Cleanup()
{
	sound.Stop();
	shot_enemy.Stop();
	shot_player.Stop();
	for each(Weapon* w in WeaponList)
	{
		delete w;
	}
	WeaponList.clear();

	for each(Enemy* w in EnemyList)
	{
		delete w;
	}
	EnemyList.clear();

	if (BackGround != nullptr)
	{
		delete BackGround;
		BackGround = nullptr;
	}

	if (ForeGround != nullptr)
	{
		delete ForeGround;
		ForeGround = nullptr;
	}

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	if (HUD_life_player != nullptr)
	{
		delete HUD_life_player;
		HUD_life_player = nullptr;
	}

	if (HUD_life_boss != nullptr)
	{
		delete HUD_life_boss;
		HUD_life_boss = nullptr;
	}

}

Game::~Game()
{
	Cleanup();
}