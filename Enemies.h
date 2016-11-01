#pragma once
#include <list>

#include "SDL.h"
#include "SDL_image.h"

#include "Objects.h"

enum{ ENEMY_ZOMBIE, ENEMY_SKELETON, ENEMY_SKULL };

// holds info for all the enemies
class Enemy
{
public:
	void Set_Clips( int WhichTypeOfEnemy );
	float xPos, yPos;
	int Enemy_Width, Enemy_Height;
	int Surface;
	int PrevFrameSkel, Frame, radius,
		WalkFrameLeft, WalkFrameRight, AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, AnimCounter;

	bool Walk, Attack, Die, LeftOf_Demon, RightOf_Demon;

	void SetFrame();
	void SetFrameSkull();
	
	SDL_Rect SkeletonClips[ 4 ][ 14 ];
	SDL_Rect EnemyClips[ 10 ];
	SDL_Rect Skulls[ 21 ];
};

class MovingThings
{
public:
	float xPos, yPos;
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

	float length;
	float HowFarSpeed;
	float HowFar;
	int state;
	float HeadTimer;

	int HeadHeight, HeadWidth;
};

class Boss : public MovingThings
{
public:
	Boss();
	float GetTimerAttack();
	int GetFrame();
	int GetState();

	int radius_Second;

	int BossWidth, BossHeight;
	int BossLife;
	bool BossDead;

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

	float AnimPaceBoss;
	float HeadTimer;
	float SizeHeads;

	std::list< Heads* > My_BossHead;

private:
	int State; 
};

// controls the enemies and creates the enemies
class Control_Enemies
{
public:
	Control_Enemies();
	void Draw_Enemies();
	void Create_Enemies();
	std::list< Enemy* > My_Enemies;
	Enemy * CreateEnemy( int xPos, int yPos, int surface );	
private:
	std::list< Enemy* > My_Enemies_dead;
	
	int Zombie, Skeleton, Skull;

	bool Collide;
	bool CollideFire;
	bool Attack;
};

extern Control_Enemies Control_ENEMY;
