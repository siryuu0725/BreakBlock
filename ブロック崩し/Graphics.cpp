#include "Graphics.h"


static LPDIRECT3D9 g_Interface;
static LPDIRECT3DDEVICE9 g_Device;

TEXTURE_DATE Bg;
TEXTURE_DATE Player;
TEXTURE_DATE Ball;
TEXTURE_DATE Block;


//DirectXの初期化
bool  InitDirectGrahpics(HWND window_handle)
{
	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_Interface == NULL)
	{
		return false;
	}

	D3DPRESENT_PARAMETERS present_param;

	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	present_param.BackBufferCount = 1;
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;
	present_param.Windowed = true;
	present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if (FAILED(g_Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&present_param,
		&g_Device)))
	{
		return false;
	}

	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param.BackBufferWidth;
	view_port.Height = present_param.BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(g_Device->SetViewport(&view_port)))
	{
		return false;
	}
	return true;
}

void ReleaseDirectGrahpics()
{
	g_Device->Release();
	g_Interface->Release();
}

bool DrawStart()
{
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (D3D_OK == g_Device->BeginScene())
	{
		return true;
	}
	return false;
}

void DrawEnd()
{
	g_Device->EndScene();
	g_Device->Present(NULL, NULL, NULL, NULL);
}



bool LoadTexture(const char* file_name, TEXTURE_DATE* texture)
{
	Size size;
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_Device,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture->Texture)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture->Texture->GetLevelDesc(0, &desc)))
		{
			texture->Texture->Release();
			texture->Texture = NULL;
			return false;
		}
		texture->Width = (float)desc.Width;
		texture->Height = (float)desc.Height;
	}
}


//背景用
void DrawBgTexture(TEXTURE_DATE* texture)
{

	CUSTOM_VERTEX bg[4] =
	{
		// 左上頂点
		{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },//右から2番目と1番目が座標
		// 右上頂点
		{ texture->Width, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		// 右下頂点
		{ texture->Width, texture->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		// 左下頂点
		{ 0.0f, texture->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_Device->SetTexture(0, texture->Texture);

	g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bg, sizeof(CUSTOM_VERTEX));
}

//自キャラ敵キャラ用
void DrawTexture(float x, float y, TEXTURE_DATE* texture)
{
	CUSTOM_VERTEX obj[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + texture->Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
		{ x + texture->Width, y + texture->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		{ x, y + texture->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	// 頂点構造の指定
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_Device->SetTexture(0, texture->Texture);

	g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, obj, sizeof(CUSTOM_VERTEX));

}

//アニメーション用
void DrawUVTexture(float x, float y, TEXTURE_DATE* texture, float sprite_width, float sprite_height, float tu, float tv)
{
	float Ttu = sprite_width / texture->Width;
	float Ttv = sprite_height / texture->Height;

	CUSTOM_VERTEX effect[4] =
	{
		{ x, y, 0.0f, 1.0f, tu, tv },
		{ x + sprite_width, y, 0.0f, 1.0f, tu + Ttu , tv },
		{ x + sprite_width, y + sprite_height, 0.0f, 1.0f, tu + Ttu, tv + Ttv},
		{ x, y + sprite_height, 0.0f, 1.0f, tu, tv + Ttv },
	};

	// 頂点構造の指定
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_Device->SetTexture(0, texture->Texture);

	g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, effect, sizeof(CUSTOM_VERTEX));

}

void ReleaseTexture(TEXTURE_DATE* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}