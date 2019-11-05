#include "ball.h"
#include "Graphics.h"
BallData balldata;

void InitBall()
{
	balldata.pos_x = 500.0f;
	balldata.pos_y = 700.0f;
		   
	balldata.radius = 40.0f;
	balldata.center_x = balldata.pos_x + balldata.radius;
	balldata.center_y = balldata.pos_y + balldata.radius;
	balldata.speed = 5.0f;
	balldata.speedflg_x = false;
	balldata.speedflg_y = false;
}

void DrawBall()
{
	DrawTexture(balldata.pos_x,balldata.pos_y, &Ball);
}

void UpDateBall()
{
	if (balldata.speedflg_x == false)
	{
		balldata.pos_x += balldata.speed;
	}		   
	else	   
		balldata.pos_x -= balldata.speed;
			   
	if (balldata.speedflg_y == false)
	{		   
		balldata.pos_y += balldata.speed;
	}		   
	else	   
		balldata.pos_y -= balldata.speed;

	balldata.center_x = balldata.pos_x + balldata.radius;
	balldata.center_y = balldata.pos_y + balldata.radius;

	
	//è„îΩéÀ
	if (balldata.center_y - balldata.radius <= 0.0f)
	{		   
		balldata.speedflg_y = false;
	}	
	//â∫îΩéÀ
	if (balldata.center_y + balldata.radius >= 1080.0f)
	{
		balldata.speedflg_y = true;
	}
	//âEîΩéÀ
	if (balldata.center_x + balldata.radius >= 1920.0f)
	{
		balldata.speedflg_x = true;
	}
	//ç∂îΩéÀ
	if (balldata.center_x - balldata.radius <= 0.0f)
	{		   
		balldata.speedflg_x = false;
	}	
	
}