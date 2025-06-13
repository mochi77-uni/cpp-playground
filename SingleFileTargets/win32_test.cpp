
#define UNICODE

#include <windows.h>
#include <tchar.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szStr, int iCmdShow) {
	// L"Hello" use wide string literal (wchar_t[])
	// "Hello" use narrow string literal (char[])
	MessageBox(nullptr, L"処理は成功しました。", L"情報", MB_OK | MB_ICONINFORMATION);
	return 0;
}