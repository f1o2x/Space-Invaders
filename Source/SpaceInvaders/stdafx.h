#pragma once
#pragma comment(lib, "winmm.lib")
#include "targetver.h"

#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Lib/x86/d3dx9.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Mmsystem.h>
#include <commdlg.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <xaudio2.h>
#include "Include\d3dx9.h"
#include "Include\dinput.h"
#include <list>
#include "Wave.h"
#include "XAudioSound.h"
#include "Input.h"
#include "Game.h"
#include "GameObject.h"
#include "Actor.h"
#include "PC.h"
#include "Enemy.h"
#include "EnemyBoss.h"
#include "Weapon.h"
#include "StdGun.h"
#include "EnemyGun.h"
#include "Main.h"