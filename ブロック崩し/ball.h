#ifndef BALL_
#define BALL_

typedef struct
{
	float pos_x, pos_y;
	float center_x;
	float center_y;
	float radius;
	float speed;
	
	bool speedflg_x;
	bool speedflg_y;
}BallData;
extern BallData balldata;


void InitBall();

void DrawBall();

void UpDateBall();


#endif 
