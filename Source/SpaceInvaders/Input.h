#pragma once

class InputClass
{
private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	unsigned char m_old_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
public:
	InputClass();
	~InputClass();
	InputClass(const InputClass&);

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsPausePressed();
	bool IsEscapePressed();
	bool IsKeyPressed(int key);
	void GetMouseLocation(int&, int&);
};