#pragma once
#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define NUMBER_OF_CLIPS 16

enum{ ENEMY_ZOMBIE, ENEMY_SKELETON };

class Enemy
{
public:
	
	void Set_Clips( int WhichTypeOfEnemy );
	SDL_Point Position;
	//int xPos, yPos;
	SDL_Point Size;
	//int Enemy_Width, Enemy_Height;
	
	int Surface;
	int PrevFrameSkel, Frame, radius, WalkFrame, AttackFrame, DieFrame, AnimCounter;

	bool Walk, Attack, Die;

	void SetFrame();
	
	SDL_Rect SkeletonClips[ 2 ][ 14 ];
	SDL_Rect EnemyClips[10];
};

class MovingThings
{
public:
	SDL_Point Position;
	//int xPos, yPos;
	int Frame;
	int radius;
	SDL_Point Size;
	//int Width, Height;
	
	int surface;
	SDL_Rect Clips[ NUMBER_OF_CLIPS ];
};

class Heads : public MovingThings
{
public:
	Heads();
	int GetFrame();
	void SetFrame( int WhichFrame );
	void UpdateFrame();

	SDL_Rect GetClips( int WhichClip );

	int length;
	int HowFar;
	int state;
	int HeadTimer;
};

class Boss : public MovingThings
{
public:
	Boss();
	int GetTimerAttack();
	int GetFrame();
	int GetState();

	void ResetAttackTimer();
	void UpdateAttackTimer();
	void SetFrame( int WhichFrame );
	void UpdateFrame();
	void SetState( int WhichState );
	void UpdateBoss();
	void UpdateHeads();

	Heads * CreateBossHeads( SDL_Point iPosition, int surface, int lengthOfTravel );
	//Heads * CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel );

	SDL_Rect GetClips( int WhichClip );
	SDL_Rect ReturnDestRect();

	bool HeadsComing;
	bool HeadAnimation;
	int AnimPaceBoss;
	int HeadTimer;
	int SizeHeads;

	std::list< Heads* > My_BossHead;
	
private:
	int AttackTimer, State;
};

class Animal : public MovingThings
{
public:
	Animal();
	void Setframe();
	int PrevFrameCrow;
};

