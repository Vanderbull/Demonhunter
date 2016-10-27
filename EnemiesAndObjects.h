#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <list>

enum{ ENEMY_ZOMBIE, ENEMY_SKELETON };



class Enemy
{
public:
	
	void Set_Clips( int WhichTypeOfEnemy );
	int xPos, yPos;
	int Enemy_Width, Enemy_Height;
	int Surface;
	int PrevFrameSkel, Frame, radius,
		WalkFrame, AttackFrame, DieFrame, AnimCounter;

	bool Walk, Attack, Die;

	void SetFrame();
	
	SDL_Rect SkeletonClips[ 2 ][ 14 ];
	SDL_Rect EnemyClips[10];


	
private:
};

class MovingThings
{
public:
	int xPos, yPos;
	int Frame;
	int radius;
	int Width, Height;
	
	int surface;
	SDL_Rect Clips[ 16 ];
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

	Heads * CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel );

	SDL_Rect GetClips( int WhichClip );
	SDL_Rect ReturnDestRect();

	bool HeadsComing;
	bool HeadAnimation;
	int AnimPaceBoss;
	int HeadTimer;
	int SizeHeads;

	std::list< Heads* > My_BossHead;

	
	
private:
	int AttackTimer, State;; 

};

class Animal : public MovingThings
{
public:
	Animal();
	void Setframe();
	int PrevFrameCrow;

private:
};

