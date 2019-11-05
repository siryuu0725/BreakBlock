#include "Player.h"
#include "Input.h"
#include "Graphics.h"
#include <math.h>

PlayerDate player;

void InitPlayer()
{
	player.x = 500.0f;
	player.y = 800.0f;
}

void DrawPlayer()
{
	DrawTexture(player.x, player.y, &Player);
}

////�v���C���[����
//void PlayerControl(PlayerDate* player)
//{
//	float speed = 10.0f;
//	float vec_x = 0.0f;
//	float vec_y = 0.0f;
//	float length = 0.0f;
//
//	//���L�[
//	if (GetKey(LEFT_KEY) == true)
//	{
//		if (player->x > 0.0f)
//		{
//			vec_x -= speed;
//		}
//	}
//	if (GetKey(RIGHT_KEY) == true)
//	{
//		if (player->x < 1000.f - 150.0f)
//		{
//			vec_x += speed;
//		}
//	}
//	
//	if (vec_x != 0.0f || vec_y != 0.0f)
//	{
//		// �x�N�g���̋������o��
//		length = sqrt(vec_x * vec_x + vec_y * vec_y);
//
//		// �P�ʃx�N�g���̐������v�Z�ŏo��
//		float normal_x = vec_x / length;
//		float normal_y = vec_y / length;
//
//		// �P�ʃx�N�g���Ɉړ��ʂ𔽉f����
//		normal_x *= speed;
//		normal_y *= speed;
//
//		// �ړ��ʂ����W�ɉ��Z
//		player->x += normal_x;
//		player->y += normal_y;
//	}
//}