#include <Windows.h>
#include "Window.h"
#include "Graphics.h"
#include "Input.h"
#include "Player.h"
#include "ball.h"
#include "Block.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	HWND window_handle = MakeWindow(hinstance, 1920, 1080);

	if (InitDirectInput(hinstance, window_handle) == false)
	{
		return 0;
	}

	InitDirectGrahpics(window_handle);

	LoadTexture((char*)"Bg2.jpg", &Bg);
	LoadTexture((char*)"Player.png", &Player);
	LoadTexture((char*)"Ball.png", &Ball);
	LoadTexture((char*)"ÉuÉçÉbÉN.png", &Block);

	InitPlayer();
	InitBlock();
	InitBall();

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (msg.message == WM_CLOSE)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			KeyUpDate();
			UpDateBall();
			HitBall();

			/*PlayerControl(&player);*/
			PlayerControl(&block);

			DrawStart();

			DrawBgTexture(&Bg);

			DrawPlayer();

			DrawBlock();

			DrawBall();
			

			DrawEnd();

		}
	}

	ReleaseTexture(&Bg);
	
	ReleaseDirectInput();
	ReleaseDirectGrahpics();
}