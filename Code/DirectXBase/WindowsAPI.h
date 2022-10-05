#pragma once
#include<Windows.h>

class WindowsAPI
{
#pragma region �֐�
public:
	static HINSTANCE GetIns();
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static bool WindowCreate();
	static bool WindowClassRelease();
	static bool WindowMassage();
#pragma endregion

#pragma region �ϐ�
public:
	static WNDCLASSEX w;
	static HWND hwnd;
	static const int win_width; //����
	static const int win_height; //�c��

private:
	static MSG msg;
#pragma endregion

};

