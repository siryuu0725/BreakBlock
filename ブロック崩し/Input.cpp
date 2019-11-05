#define DIRECTINPUT_VERSION 0x0800
#include "Input.h"
#include <Windows.h>
#include "Window.h"

// �L�[���\����
struct INPUTSTATE
{
	DWORD now;
	DWORD trg;
	DWORD ntrg;
};

// DIRECTINPUT8�̃|�C���^
static LPDIRECTINPUT8 g_pInputInterface;

// DIRECTINPUTDEVICE8�̃|�C���^
static LPDIRECTINPUTDEVICE8 g_pInputDevice;

// �L�[���
static INPUTSTATE g_InputState;

bool InitDirectInput(HINSTANCE instance_handle, HWND window_handle)
{
	// IDirectInput8�C���^�[�t�F�C�X�̎擾
	HRESULT hr = DirectInput8Create(instance_handle,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInputInterface,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}

	// IDirectInputDevice8�C���^�[�t�F�C�X�̎擾
	hr = g_pInputInterface->CreateDevice(GUID_SysKeyboard, &g_pInputDevice, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
	hr = g_pInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}


	// �������[�h�̐ݒ�
	hr = g_pInputDevice->SetCooperativeLevel(window_handle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		return false;
	}

	//�f�o�C�X�̎擾�J�n
	g_pInputDevice->Acquire();

	return true;
}

void ReleaseDirectInput()
{
	g_pInputDevice->Unacquire();
	g_pInputDevice->Release();
	g_pInputInterface->Release();
}


void KeyUpDate()
{
	// �L�[����i�[�p
	BYTE KeyState[256];
	HRESULT hr;

	// �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
	hr = g_pInputDevice->GetDeviceState(sizeof(BYTE) * 256, KeyState);
	if (SUCCEEDED(hr))
	{
		// 1�t���[���O�̃L�[���̊m��
		DWORD old = g_InputState.now;

		g_InputState.now = 0;

		// ��L�[
		if (KeyState[DIK_UP] & 0x80)
		{
			g_InputState.now |= UP_KEY;
		}

		// ���L�[
		if (KeyState[DIK_DOWN] & 0x80)
		{
			g_InputState.now |= DOWN_KEY;
		}

		// ���L�[
		if (KeyState[DIK_LEFT] & 0x80)
		{
			g_InputState.now |= LEFT_KEY;
		}

		//�E�L�[
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			g_InputState.now |= RIGHT_KEY;
		}

		//Enter�L�[
		if (KeyState[DIK_SPACE] & 0x80)
		{
			g_InputState.now |= SPACE_KEY;
		}

		g_InputState.trg = (g_InputState.now & (~old));	// �g���K�[���擾
		g_InputState.ntrg = (~g_InputState.now) & old;	// �t�g���K�[���擾

	}
	else if (hr == DIERR_INPUTLOST) {
		g_pInputDevice->Acquire();
	}
}

bool GetKey(DWORD key_code)
{
	return g_InputState.now & key_code;
}

bool GetKeyDown(DWORD key_code)
{
	return g_InputState.trg & key_code;
}

bool GetKeyUp(DWORD key_code)
{
	return g_InputState.ntrg & key_code;
}