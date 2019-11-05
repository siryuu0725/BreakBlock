#include "Hit.h"
#include "ball.h"
#include "Block.h"
#include <math.h>

 bool Hit(/*Blockdata* block_width, Blockdata* block_height*/ float width, float height)
{
	/*float a = block_x->pos_x - balldata_x->center_x;
	float b = block_y->pos_y - balldata_y->center_y;
	float c = sqrt(a * a + b * b);

	if (c <= balldata.radius)
	{
		balldata.speedflg_y = true;
		balldata.speedflg_x = true;
	}*/
	float a = (block.pos_x + width) - balldata.center_x;
	float b = (block.pos_y + height) - balldata.center_y;
	float c = sqrt(a * a + b * b);

	if (c <= balldata.radius)
	{
		return true;
	}
	return false;

}