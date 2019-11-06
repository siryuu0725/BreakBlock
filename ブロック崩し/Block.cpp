#include "Block.h"
#include "Graphics.h"
#include "ball.h"
#include "Input.h"
#include "Hit.h"
#include <math.h>
Blockdata block;

void InitBlock()
{
	block.pos_x = 900.0f;
	block.pos_y = 500.0f;
	block.height = 80.0f;
	block.width = 240.0f;
	block.next_hitcount = 0;
	block.next_hit = false;
}

void DrawBlock()
{
	DrawTexture(block.pos_x, block.pos_y, &Block);
}

void HitBall()
{
	if (block.next_hit == true)
	{
		block.next_hitcount++;
	}
	if (block.next_hitcount == 60)
	{
		block.next_hitcount = 0;
		block.next_hit = false;
	}
	//上反射
	if (balldata.center_x >= block.pos_x && balldata.center_x <= block.pos_x + block.width
		&& balldata.center_y >= block.pos_y - balldata.radius && balldata.center_y <= block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = true;
		block.next_hit = true;

	}
	//下反射
	if (balldata.center_x >= block.pos_x && balldata.center_x <= block.pos_x + block.width
		&& balldata.center_y >= block.pos_y + block.height && balldata.center_y <= block.pos_y + block.height + balldata.radius && block.next_hit == false)
	{
		balldata.speedflg_y = false;
		block.next_hit = true;

	}
	//右反射
	if (balldata.center_x >= block.pos_x - balldata.radius && balldata.center_x <= block.pos_x
		&& balldata.center_y >= block.pos_y && balldata.center_y <= block.pos_y + block.height && block.next_hit == false)
	{
		balldata.speedflg_x = true;
		block.next_hit = true;

	}
	//左反射
	if (balldata.center_x >= block.pos_x + block.width && balldata.center_x <= block.pos_x + block.width + balldata.radius
		&& balldata.center_y >= block.pos_y && balldata.center_y <= block.pos_y + block.height && block.next_hit == false)
	{
		balldata.speedflg_x = false;
		block.next_hit = true;

	}	

	//左頂点
	if (Hit(0, 0) == true && balldata.center_x < block.pos_x && balldata.center_y < block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
		block.next_hit = true;
	}
	else if (Hit(0, 0) == true && balldata.center_x < block.pos_x && balldata.center_y > block.pos_y&& block.next_hit == false)
	{
		balldata.speedflg_x = true;
		block.next_hit = true;

	}
	else if (Hit(0, 0) == true && balldata.center_x > block.pos_x&& balldata.center_y < block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = false;
		block.next_hit = true;

	}
	

	//右頂点
	else if (Hit(block.width, 0) == true && balldata.center_x > block.pos_x&& balldata.pos_y < block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = false;
		block.next_hit = true;

	}
	else if (Hit(block.width, 0) == true && balldata.center_x > block.pos_x&& balldata.pos_y > block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_x = false;
		block.next_hit = true;

	}
	else if (Hit(block.width, 0) == true && balldata.center_x < block.pos_x&& balldata.pos_y < block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = false;
		block.next_hit = true;

	}

	//右下頂点
	else if (Hit(block.width, block.height) == true && balldata.center_x > block.pos_x&& balldata.pos_y > block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = false;
		balldata.speedflg_x = false;
		block.next_hit = true;

	}
	else if (Hit(block.width, block.height) == true && balldata.center_x > block.pos_x&& balldata.pos_y < block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_x = false;
		block.next_hit = true;

	}
	else if (Hit(block.width, block.height) == true && balldata.center_x < block.pos_x&& balldata.pos_y > block.pos_y && block.next_hit == false)
	{
		balldata.speedflg_y = true;
		block.next_hit = true;

	}

	//左下頂点
	else if (Hit(0, block.height) == true && balldata.center_x < block.pos_x&& balldata.pos_y > block.pos_y&& block.next_hit == false)
	{
		balldata.speedflg_y = false;
		balldata.speedflg_x = true;
		block.next_hit = true;

	}
	else if (Hit(0, block.height) == true && balldata.center_x < block.pos_x&& balldata.pos_y < block.pos_y&& block.next_hit == false)
	{
		balldata.speedflg_x = true;
		block.next_hit = true;

	}
	else if (Hit(0, block.height) == true && balldata.center_x > block.pos_x&& balldata.pos_y > block.pos_y&& block.next_hit == false)
	{
		balldata.speedflg_y = true;
		block.next_hit = true;

	}
}

//プレイヤー操作
void PlayerControl(Blockdata* player)
{
	float speed = 10.0f;
	float vec_x = 0.0f;
	float vec_y = 0.0f;
	float length = 0.0f;

	//左キー
	if (GetKey(LEFT_KEY) == true)
	{
		if (player->pos_x > 0.0f)
		{
			vec_x -= speed;
		}
	}
	if (GetKey(RIGHT_KEY) == true)
	{
		if (player->pos_x < 1920.f - 240.0f)
		{
			vec_x += speed;
		}
	}

	if (vec_x != 0.0f || vec_y != 0.0f)
	{
		// ベクトルの距離を出す
		length = sqrt(vec_x * vec_x + vec_y * vec_y);

		// 単位ベクトルの成分を計算で出す
		float normal_x = vec_x / length;
		float normal_y = vec_y / length;

		// 単位ベクトルに移動量を反映する
		normal_x *= speed;
		normal_y *= speed;

		// 移動量を座標に加算
		player->pos_x += normal_x;
		player->pos_y += normal_y;
	}
}