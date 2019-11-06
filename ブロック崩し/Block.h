#ifndef BLOCK
#define BLOCK


typedef struct
{
	float pos_x;
	float pos_y;
	float width;
	float height;
	int next_hitcount;
	bool next_hit;

}Blockdata;

extern Blockdata block;

void InitBlock();

void DrawBlock();

void HitBall();

void PlayerControl(Blockdata* player);

#endif 
