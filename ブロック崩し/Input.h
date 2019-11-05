#ifndef DIRECT_INPUT_H_
#define DIRECT_INPUT_H_

#include <Windows.h>
#include <dinput.h>

#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")


// キーコード
#define CLEAR_KEY	0x0000		// クリア用
#define UP_KEY		0x0001		// 上キー
#define DOWN_KEY	0x0002		// 下キー
#define LEFT_KEY	0x0004		// 左キー
#define RIGHT_KEY	0x0008		// 右キー
#define RETURN_KEY	0x0010	// リターンキー
#define SPACE_KEY   0x0020  // スペースキー


bool InitDirectInput(HINSTANCE instance_handle, HWND window_handle);

void KeyUpDate();

bool GetKey(DWORD key_code);

bool GetKeyDown(DWORD key_code);

bool GetKeyUp(DWORD key_code);

void ReleaseDirectInput();


#endif