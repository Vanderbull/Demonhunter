#pragma once

#include "SDL.h"
#include "SDL_image.h"

class Demon
{
public:

	Demon();
	void InitiateDemon( int surface, int Xpos, int Ypos, int height, int width ); 

	void Set_clips();
	void UpdateEndPosition();
	int  UpdatePlayer();

	void UpdateXPos();

	bool SmallHunter, MediumHunter, LargeHunter, DemonHunter;

	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping;
	bool isCrouching;
	bool isKicking;
	bool isPunching;
	bool CrouchFireBall;
	bool TriangleAttack;
	bool IsInStateAttack();
	bool GetUp;

	bool CheckBoundaries();

	bool LifeFull_Small;
	bool LifeMedium_Small;
	bool LifeLittle_Small;

	bool Crouch, Kick, Jump, Punch, FireBall, CrouchFire, Triangle;

	bool isHit, DieOneLife, Demon_Dead;
	
	int Demon_Height;
	int Demon_Width;
	int DemonSurface;
	int Demon_Health;
	int Demon_Life;
	int Last_Xpos;
	int LastEnd_Pos;
	int xPosHotSpot;

	int AlphaImmortal;
	int LengthOfTriangle;

	bool Immortal;

	int Feet_W, Feet_H, Fist_W, Fist_H;

	int WhichFrame;
	int WhereAnimation;
	int WhereIsEnd;
	int DieState, TriangleState;

	int WhereWalkRight, WhereWalkLeft;
	int WhereJumpLeft, WhereJumpRight;
	int KickRight, KickLeft;
	int CrouchRight, CrouchLeft;
	int PunchRight, PunchLeft;
	int TriangleFireLeft, TriangleFireRight;
	int DieRightDemon, DieLeftDemon;

	int WalkLeft_Demon, WalkRight_Demon;
	int FireBallRight_Demon, FireBallLeft_Demon;
	int JumpRight_Demon, JumpLeft_Demon;
	int CrouchRightFire, CrouchLeftFire;
	int FireBallRight, FireBallLeft;
	
	int Radius, RadiusFist, RadiusFeet;

	bool Right, Left;

	float xPos, yPos;
	float xVel, yVel;

	SDL_Rect AnimationArrays[ 4 ][ 48 ];

private:

};

extern Demon demon;



