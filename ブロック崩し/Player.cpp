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

////プレイヤー操作
//void PlayerControl(PlayerDate* player)
//{
//	float speed = 10.0f;
//	float vec_x = 0.0f;
//	float vec_y = 0.0f;
//	float length = 0.0f;
//
//	//左キー
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
//		// ベクトルの距離を出す
//		length = sqrt(vec_x * vec_x + vec_y * vec_y);
//
//		// 単位ベクトルの成分を計算で出す
//		float normal_x = vec_x / length;
//		float normal_y = vec_y / length;
//
//		// 単位ベクトルに移動量を反映する
//		normal_x *= speed;
//		normal_y *= speed;
//
//		// 移動量を座標に加算
//		player->x += normal_x;
//		player->y += normal_y;
//	}
//}