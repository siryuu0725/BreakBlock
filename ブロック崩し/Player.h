#ifndef PLAYER
#define PLAYER
#include"Graphics.h"

struct PlayerDate
{
	float x, y;
	float radius;
};

extern PlayerDate player;

void PlayerControl(PlayerDate* player);

void InitPlayer();

void DrawPlayer();

#endif