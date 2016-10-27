#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"

// Fredik Zaar SP6 Demon Hunter

// holds all the info on the collisions
class Control_Collision
{
public:
	bool CollisionCircle( Demon *MyDemon, PowerUp *TransForm, bool Show );
	bool CollisionCircle( Demon *MyDemon, Enemy *MyEnemy, bool Show );
	bool CollisionCircle( Demon *MyDemon, Boss *Myboss, bool Show );
	bool CollisionCircle( Demon *MyDemon, Heads *EnemyHead, bool Show );

	bool CollisionCircle( FireBall *MyFire, Enemy *MyEnemy, bool Show );
	bool CollisionCircle( FireBall *MyFire, Heads *EnemyHead, bool Show );
	bool CollisionCircle( FireBall *MyFire, Boss *My_boss, bool Show );
	

	bool CollisionBox( Demon *MyDemon, Enemy *MyEnemy, bool Show );
	bool CollisionPixel( Demon *MyDemon, Enemy *MyEnemy );

	bool CheckCollisionWithPlayer( Enemy *MyEnemy, int WhichCollisionToUse );
	bool CheckCollisionWithPlayer( PowerUp *TransForm, int WhichCollisionToUse );

	void Circle( long centerx, long centery, long radius );
	void SetPixelMine( int xPos, int yPos );
};

extern Control_Collision Contr_Coll;
