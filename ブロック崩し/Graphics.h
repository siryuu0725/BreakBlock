#ifndef GRAHPICS
#define GRAHPICS

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include <Windows.h>

typedef struct
{
	LPDIRECT3DTEXTURE9 Texture;
	float Width;
	float Height;
}TEXTURE_DATE;

extern TEXTURE_DATE Bg;
extern TEXTURE_DATE Player;
extern TEXTURE_DATE Ball;
extern TEXTURE_DATE Block;


struct Size
{
	Size()
	{
		Width = 0.0f;
		Height = 0.0f;
	}

	Size(float width, float height)
	{
		Width = width;
		Height = height;
	}

	Size(const Size& size)
	{
		this->Width = size.Width;
		this->Height = size.Height;
	}

	float Width;
	float Height;
};


struct CUSTOM_VERTEX
{
	float x;
	float y;
	float z;
	float rhw;
	float tu;
	float tv;
};

bool InitDirectGrahpics(HWND);

void ReleaseDirectGrahpics();

bool DrawStart();

void DrawEnd();

bool LoadTexture(const char*, TEXTURE_DATE*);

void DrawBgTexture(TEXTURE_DATE*);

void DrawTexture(float x, float y, TEXTURE_DATE* texture_data);

void DrawUVTexture(float x, float y, TEXTURE_DATE* texture, float sprite_width, float sprite_height, float tu, float tv);

void ReleaseTexture(TEXTURE_DATE*);

#endif

