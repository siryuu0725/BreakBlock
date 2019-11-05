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

}

void DrawBlock()
{
	DrawTexture(block.pos_x, block.pos_y, &Block);
}

void HitBall()
{
	
	//�㔽��
	if (balldata.center_x >= block.pos_x && balldata.center_x <= block.pos_x + block.width
		&& balldata.center_y >= block.pos_y - balldata.radius && balldata.center_y <= block.pos_y)
	{
		balldata.speedflg_y = true;
	}
	//������
	if (balldata.center_x >= block.pos_x && balldata.center_x <= block.pos_x + block.width
		&& balldata.center_y >= block.pos_y + block.height && balldata.center_y <= block.pos_y + block.height + balldata.radius)
	{
		balldata.speedflg_y = false;
	}
	//�E����
	if (balldata.center_x >= block.pos_x - balldata.radius && balldata.center_x <= block.pos_x
		&& balldata.center_y >= block.pos_y && balldata.center_y <= block.pos_y + block.height)
	{
		balldata.speedflg_x = true;
	}
	//������
	if (balldata.center_x >= block.pos_x + block.width && balldata.center_x <= block.pos_x + block.width + balldata.radius
		&& balldata.center_y >= block.pos_y && balldata.center_y <= block.pos_y + block.height)
	{
		balldata.speedflg_x = false;
	}	

	if (Hit(0, 0) == true)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
	}

	if (Hit(block.width, 0) == true)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
	}
	if (Hit(block.width, block.height) == true)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
	}
	/*if (Hit(0, block.height) == true)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
	}*/
}

//�v���C���[����
void PlayerControl(Blockdata* player)
{
	float speed = 10.0f;
	float vec_x = 0.0f;
	float vec_y = 0.0f;
	float length = 0.0f;

	//���L�[
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
		// �x�N�g���̋������o��
		length = sqrt(vec_x * vec_x + vec_y * vec_y);

		// �P�ʃx�N�g���̐������v�Z�ŏo��
		float normal_x = vec_x / length;
		float normal_y = vec_y / length;

		// �P�ʃx�N�g���Ɉړ��ʂ𔽉f����
		normal_x *= speed;
		normal_y *= speed;

		// �ړ��ʂ����W�ɉ��Z
		player->pos_x += normal_x;
		player->pos_y += normal_y;
	}
}