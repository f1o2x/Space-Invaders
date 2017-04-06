#include "stdafx.h"
#include "Resource.h"
Game game;
int EnterMsgLoop()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	static float lastTime = (float)timeGetTime();
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			float currTime = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;
			game.Update();
			game.Display(timeDelta);
			lastTime = currTime;
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: ::PostQuitMessage(0);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType, IDirect3DDevice9** device)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = L"main_window";

	if (!RegisterClass(&wc))
	{
		::MessageBox(0, L"RegisterClass() - FAILED", 0, 0);
		return false;
	}
	HRESULT hr = 0;
	IDirect3D9* d3d9 = 0;
	HWND hwnd = 0;
	
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(0, L"Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if (caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
	{
		::MessageBox(0, L"Hardware Doesn't support PS 2.0 - Using Software Rendering", 0, 0);
		deviceType = D3DDEVTYPE_REF;
		width = width / 2;
		height = height / 2;
	}
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;
	AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, TRUE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
	hwnd = ::CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"main_window", L"Space Invaders",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN/*WS_EX_TOPMOST*/,
		0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

	if (!hwnd)
	{
		::MessageBox(0, L"CreateWindow() - FAILED", 0, 0);
		return false;
	}

	HICON hicon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYSpaceInvaders));
	if (hicon)
	{
		::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
	}
	hicon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (hicon)
	{
		::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
	}
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	game.SetWindow(hwnd);

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);

	if (FAILED(hr))
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);
		if (FAILED(hr))
		{
			d3d9->Release();
			::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}
	d3d9->Release();
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if (!InitD3D(hInstance, game.GetWidth(), game.GetHeight(), true, D3DDEVTYPE_HAL, game.GetDeviceAddr()))
	{
		::MessageBox(0, L"InitD3D FAILED", 0, 0);
		return 0;
	}
	InputClass* m_Input = new InputClass();
	if (!m_Input)
	{
		return 0;
	}
	if (!m_Input->Initialize(hInstance, game.GetWindow(), game.GetWidth(), game.GetHeight()))
	{
		MessageBox(0, L"Could not initialize the input object.", L"Error", MB_OK);
		return 0;
	}
	game.SetInput(m_Input);

	if (!game.Setup())
	{
		::MessageBox(0, L"Setup FAILED", 0, 0);
		return 0;
	}

	EnterMsgLoop();
	game.GetDevice()->Release();
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}
	return 0;
}