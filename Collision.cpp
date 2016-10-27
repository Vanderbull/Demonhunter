#include "Collision.h"
#include <cmath>

// Fredik Zaar SP6 Demon Hunter

Control_Collision Contr_Coll;

// checks collision
bool Control_Collision::CollisionCircle( Demon *MyDemon, Enemy *MyEnemy, bool Show )
{
	// Cache
	double	dx = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );

	double	dx1 = 0,
			dy1 = 0;

	double	dx2 = 0,
			dy2 = 0;

	if( demon.DemonHunter )
	{
		if( demon.Triangle == true || demon.TriangleAttack == true )
		{
			if( demon.Right == true )
			{
				// Cache
				dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 98 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
				dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 )+ 60 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
				int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
				if( dist3 < MyDemon->Radius + MyEnemy->radius )
				{
				return true;	// Yep, collision
				}

			}
			else
			{
				// Cache
				dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 ) ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
				dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 ) + 65 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
				int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
				if( dist3 < MyDemon->Radius + MyEnemy->radius )
				{
					return true;	// Yep, collision
				}
			}
		}
			
			// Cache
			dx1 = ( ( ( MyDemon->xPos + demon.Feet_W / 2 )+ 15 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy1 = ( ( ( MyDemon->yPos + demon.Feet_H / 2 ) + 80 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );

		if( Show )
		{
			if( demon.Triangle == true || demon.TriangleAttack == true )
			{
				if( demon.Right == true )
				{
					Circle( MyDemon->xPos + demon.Fist_W / 2 + 98, MyDemon->yPos + demon.Fist_H / 2 + 60, MyDemon->RadiusFeet );
				}
				else
				{
					Circle( MyDemon->xPos + demon.Fist_W / 2, MyDemon->yPos + demon.Fist_H / 2 + 65, MyDemon->RadiusFeet );
				}
			}
		}
	}
	else
	{
		if( demon.isKicking )
		{
			if( demon.Right )
			{
				// Cache
				dx1 = ( ( ( MyDemon->xPos + demon.Feet_W / 2 ) + 60 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
				dy1 = ( ( ( MyDemon->yPos + demon.Feet_H / 2 ) + 75 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
			}
			else
			{
				// Cache
				dx1 = ( ( MyDemon->xPos + demon.Feet_W / 2 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
				dy1 = ( ( ( MyDemon->yPos + demon.Feet_H / 2 ) + 75 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
			}
		}
		else
		{
			// Cache
			dx1 = ( ( ( MyDemon->xPos + demon.Feet_W / 2 )+ 15 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy1 = ( ( ( MyDemon->yPos + demon.Feet_H / 2 ) + 80 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
		}

		if( demon.isPunching )
		{
			// Cache
			dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 55 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 ) + 40 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
			int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
			if( dist3 < MyDemon->Radius + MyEnemy->radius )
			{
				return true;	// Yep, collision
			}
		}
		else
		{
			// Cache
			dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 20 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 ) + 40 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
			int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
			if( dist3 < MyDemon->Radius + MyEnemy->radius )
			{
				return true;	// Yep, collision
			}
		}

		if( Show )
		{
			if( demon.isKicking )
			{
				if( demon.Right )
				{
					Circle( MyDemon->xPos + demon.Feet_W / 2 + 60, MyDemon->yPos + demon.Feet_H / 2 + 75, MyDemon->RadiusFeet );
				}
				else
				{
					Circle( MyDemon->xPos + demon.Feet_W / 2, MyDemon->yPos + demon.Feet_H / 2 + 75, MyDemon->RadiusFeet );
				}

			}
			else
			{
				Circle( MyDemon->xPos + demon.Feet_W / 2 + 15, MyDemon->yPos + demon.Feet_H / 2 + 80, MyDemon->RadiusFeet );
			}
			Circle( MyDemon->xPos + DEMONWIDTHREAL / 2, MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45, MyDemon->Radius );
			
			if( demon.isPunching )
			{
				Circle( MyDemon->xPos + demon.Fist_W / 2 + 55, MyDemon->yPos + demon.Fist_H / 2 + 40, MyDemon->RadiusFist );
			}
			else
			{
				Circle( MyDemon->xPos + demon.Fist_W / 2 + 20, MyDemon->yPos + demon.Fist_H / 2 + 40, MyDemon->RadiusFist );
			}
		}
	}

	int dist = ( int )sqrt( dx * dx + dy * dy );
	int dist2 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );
	

	// Do circles overlap?
	if(	dist < MyDemon->Radius + MyEnemy->radius || dist2 < MyDemon->Radius + MyEnemy->radius )
	{
		return true;	// Yep, collision
	}
 
	// No collision
	return false;
}

// checks collision
bool Control_Collision::CollisionCircle( Demon *MyDemon, Heads *EnemyHead, bool Show )
{

	if( demon.Triangle == true || demon.TriangleAttack == true && demon.isMovingLeft == true )
	{
		// Cache
		double	dx = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 + 70) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18) ),
				dy = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 +35) );

		double	dx1 = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 + 25) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18) ),
				dy1 = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 +35) );

		int dist = ( int )sqrt( dx * dx + dy * dy );
		int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );

		// Do circles overlap?
		if(	dist < MyDemon->Radius + EnemyHead->radius || dist1 < MyDemon->Radius + EnemyHead->radius )	
		{
			return true;	// Yep, collision
		}
	}
	else
	{
		// Cache
		double	dx = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 + 20) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18) ),
				dy = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 +35) );

		double	dx1 = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 + 5) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18) ),
				dy1 = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 +35) );

		int dist = ( int )sqrt( dx * dx + dy * dy );
		int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );

		// Do circles overlap?
		if(	dist < MyDemon->Radius + EnemyHead->radius || dist1 < MyDemon->Radius + EnemyHead->radius )	
		{
			return true;	// Yep, collision
		}
	}
	// test boss against the triangle attack and the demon itself.
	if( demon.DemonHunter )
	{
		double	dx2 = 0,
				dy2 = 0;

		if( demon.Triangle == true || demon.TriangleAttack == true )
		{
			if( demon.Right )
			{
				// Cache
				dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 88 ) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18 ) ),
				dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 )+ 60 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 + 35 ) );
			}
			else
			{
				// Cache
				dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 ) ) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 + 18 ) ),
				dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 ) + 65 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 + 35 ) );
			}

			int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
			// Do circles overlap?
			if( dist3 < MyDemon->Radius + EnemyHead->radius )	
			{
				return true;	// Yep, collision
			}
		}

		if( Show )
		{
			if( demon.Triangle == true || demon.TriangleAttack == true && demon.isMovingLeft == true )
			{
				Circle( MyDemon->xPos + DEMONWIDTHREAL / 2 + 70, 
						MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45,
						MyDemon->Radius );

				Circle( MyDemon->xPos + DEMONWIDTHREAL / 2 + 25, 
						MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45,
						MyDemon->Radius );
			}
			else
			{
				Circle( MyDemon->xPos + DEMONWIDTHREAL / 2 + 20, 
						MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45,
						MyDemon->Radius );

				Circle( MyDemon->xPos + DEMONWIDTHREAL / 2 + 5, 
						MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45,
						MyDemon->Radius );
			}

			if( demon.Triangle == true || demon.TriangleAttack == true )
			{
				if( demon.Right )
				{
					Circle( MyDemon->xPos + demon.Fist_W / 2 + 98, 
							MyDemon->yPos + demon.Fist_H / 2 + 60, 
							MyDemon->RadiusFeet );
				}
				else
				{
					Circle( MyDemon->xPos + demon.Fist_W / 2 , 
							MyDemon->yPos + demon.Fist_H / 2 + 65, 
							MyDemon->RadiusFeet );
				}
			}
		}
	}
 
	// No collision
	return false;

}

// checks collision
bool Control_Collision::CollisionCircle( Demon *MyDemon, Boss *Myboss, bool Show )
{
	// Cache
	double	dx =	( ( MyDemon->xPos + DEMONWIDTHREAL / 2 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 100 ) ),
			dy =	( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( Myboss->yPos + Myboss->BossHeight / 2 - 30 ) );

	double  dx1 =	( ( MyDemon->xPos + DEMONWIDTHREAL / 2 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 95 ) ),
			dy1 =	( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 45 ) - ( Myboss->yPos + Myboss->BossHeight / 2 + 220 ) );

	// test boss against the triangle attack and the demon itself.
	if( demon.DemonHunter )
	{
		double	dx2 = 0,
				dy2 = 0,
				dx3 = 0,
				dy3 = 0;

		if( demon.Triangle == true || demon.TriangleAttack == true && demon.Right == true )
		{
			// Cache
			dx2 =	( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 98 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 100 ) ),
			dy2 =	( ( ( MyDemon->yPos + demon.Fist_H / 2 )+ 60 ) - ( Myboss->yPos + Myboss->BossHeight / 2 - 30) );
			dx3 =	( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 98 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 95 ) ),
			dy3 =	( ( ( MyDemon->yPos + demon.Fist_H / 2 )+ 60 ) - ( Myboss->yPos + Myboss->BossHeight / 2 + 220 ) );
		}
		else
		{
			// Cache
			dx2 = ( ( ( MyDemon->xPos + demon.Fist_W / 2 ) - 35) - ( Myboss->xPos + Myboss->BossWidth / 2 ) + 100 ),
			dy2 = ( ( ( MyDemon->yPos + demon.Fist_H / 2 ) + 65 ) - ( Myboss->yPos + Myboss->BossHeight / 2 ) - 30 );
			dx3 =	( ( ( MyDemon->xPos + demon.Fist_W / 2 )+ 35 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 95 ) ),
			dy3 =	( ( ( MyDemon->yPos + demon.Fist_H / 2 )+ 65 ) - ( Myboss->yPos + Myboss->BossHeight / 2 + 220 ) );
		}
			
		if( Show )
		{
			if( demon.Triangle == true || demon.TriangleAttack == true && demon.Right == true )
			{
				Circle( MyDemon->xPos + demon.Fist_W / 2 + 98, MyDemon->yPos + demon.Fist_H / 2 + 60, MyDemon->RadiusFeet );
			}
			else
			{
				Circle( MyDemon->xPos + demon.Fist_W / 2 - 35, MyDemon->yPos + demon.Fist_H / 2 + 65, MyDemon->RadiusFeet );
			}
		}

		int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
		int dist4 = ( int )sqrt( dx3 * dx3 + dy3 * dy3 );
			// Do circles overlap?
		if( dist3 < MyDemon->Radius + Myboss->radius || dist4 < MyDemon->Radius + Myboss->radius )	
		{
			return true;	// Yep, collision
		}

	}

	int dist = ( int )sqrt( dx * dx + dy * dy );
	int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );
	

	// Do circles overlap?
	if(	dist < MyDemon->Radius + Myboss->radius || dist1 < MyDemon->Radius + Myboss->radius )	
	{
		return true;	// Yep, collision
	}
 
	// No collision
	return false;
}

// checks collision
bool Control_Collision::CollisionCircle( FireBall *MyFire, Boss *My_boss, bool Show )
{
	// Cache
	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( My_boss->xPos + My_boss->BossWidth / 2 + 100 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( My_boss->yPos + My_boss->BossHeight/ 2 - 30) );
	
	double	dx1 = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( My_boss->xPos + My_boss->BossWidth / 2 + 95 ) ),
			dy1 = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( My_boss->yPos + My_boss->BossHeight  / 2 + 220 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->radius ) ;
	}

	int dist = (int)sqrt( dx * dx + dy * dy );
	int dist1 = (int)sqrt( dx1 * dx1 + dy1 * dy1 );

	// Do circles overlap?
	if( dist < MyFire->radius + My_boss->radius || dist1 < MyFire->radius + My_boss->radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}


// checks collision
bool Control_Collision::CollisionCircle( FireBall *MyFire, Heads *EnemyHead, bool Show )
{
	// Cache
	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( EnemyHead->xPos + EnemyHead->HeadWidth / 2 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( EnemyHead->yPos + EnemyHead->HeadHeight / 2 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->radius ) ;
	}

	int dist = (int)sqrt( dx*dx + dy*dy );

	// Do circles overlap?
	if( dist < MyFire->radius + EnemyHead->radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool Control_Collision::CollisionCircle( FireBall *MyFire, Enemy * MyEnemy, bool Show )
{
	// Cache
	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->radius ) ;
	}

	int dist = (int)sqrt( dx*dx + dy*dy );

	// Do circles overlap?
	if( dist < MyFire->radius + MyEnemy->radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool Control_Collision::CollisionCircle( Demon *MyDemon, PowerUp *TransForm, bool Show )
{

	// Cache
	double	dx = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 - 10 ) - ( TransForm->xPos + TransForm->Width / 2 ) ),
			dy = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 - 10 ) - ( TransForm->yPos + TransForm->Height / 2 ) );

		// Cache
	double	dx1 = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 + 20 ) - ( TransForm->xPos + TransForm->Width / 2 ) ),
			dy1 = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 + 40 ) - ( TransForm->yPos + TransForm->Height / 2 ) );
	
	if( Show )
	{
		Circle( TransForm->xPos + TransForm->Width / 2, TransForm->yPos + TransForm->Height / 2, TransForm->radius ) ;
		Circle( MyDemon->xPos + DEMONWIDTHREAL - 10 / 2, MyDemon->yPos + DEMONHEIGHTREAL / 2 - 10, MyDemon->Radius );
		Circle( MyDemon->xPos + DEMONWIDTHREAL + 20 / 2, MyDemon->yPos + DEMONHEIGHTREAL / 2 + 40, MyDemon->Radius );
	}

	int dist = (int)sqrt( dx * dx + dy * dy );
	int dist2 = (int)sqrt( dx1 * dx1 + dy1 * dy1 );

	// Do circles overlap?
	if( dist < MyDemon->Radius + TransForm->radius || 
		dist2 < MyDemon->Radius + TransForm->radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool Control_Collision::CheckCollisionWithPlayer( PowerUp *TransForm, int WhichCollisionToUse )
{
	
	bool temp = false;

	if( WhichCollisionToUse == 1 )
	{
		temp = CollisionCircle( &demon, TransForm, false );
	}

	return temp;
}

// checks collision
void Control_Collision::Circle( long centerx, long centery, long radius )
{
         long d, y, x;

		 // setup
         d = 3 - (2 * radius);
         x = 0;
         y = radius;

         // draw the thing
         while (y > x) {
                 SetPixelMine( centerx + x,centery + y );
                 SetPixelMine( centerx + y,centery + x );
                 SetPixelMine( centerx - x,centery + y );
                 SetPixelMine( centerx - y,centery + x );
                 SetPixelMine( centerx + x,centery - y );
                 SetPixelMine( centerx + y,centery - x );
                 SetPixelMine( centerx - x,centery - y );
                 SetPixelMine( centerx - y,centery - x );

                 if (d < 0) {
                         d = d + ( 4 * x ) + 6;
                 } else {
                         d = d + 4 * ( x - y ) + 10;
                         y--;
                 }
                 x++;
         }
}

// checks collision
void Control_Collision::SetPixelMine( int xPos, int yPos  )
{
	SDL_LockSurface( gamestate.BackBuffer );

	COLORREF color( RGB( 255, 0, 0 ) );

	int dstPitch = gamestate.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;
	
	dst[ ( yPos * dstPitch / 4 ) + ( xPos ) ] = color;

	SDL_UnlockSurface( gamestate.BackBuffer );

}


// ----------------------------------------------------------------------------
// ChecksCollision - test if any collision occurs
// ----------------------------------------------------------------------------
bool Control_Collision::CheckCollisionWithPlayer( Enemy *MyEnemy, int WhichCollisionToUse )
{
	
	bool temp = false;

	if( MyEnemy->xPos - demon.xPos >= 150 )
	{
		return temp;
	}
	
	if( MyEnemy->Die == true )
	{
		return false;
	}

	if( WhichCollisionToUse == 1 )
	{
		temp = CollisionCircle( &demon, MyEnemy, false );
	}
	if( temp )
	{
		temp = CollisionBox( &demon, MyEnemy, false );
	}

	return temp;
}

// ----------------------------------------------------------------------------
// CheckBoxCollision - test if box collision occurs
// ----------------------------------------------------------------------------
bool Control_Collision::CollisionBox( Demon *MyDemon, Enemy *MyEnemy, bool Show )
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

	left1 = MyDemon->xPos - 10;
	left2 = MyEnemy->xPos;
	right1 = MyDemon->xPos + MyDemon->Demon_Width - 10;
	right2 = MyEnemy->xPos + MyEnemy->Enemy_Width;
	top1 = MyDemon->yPos;
    top2 = MyEnemy->yPos;
	bottom1 = MyDemon->yPos + MyDemon->Demon_Height;
	bottom2 = MyEnemy->yPos + MyEnemy->Enemy_Height;

    if ( bottom1 < top2 ) return false;
    if ( top1 > bottom2 ) return false;

    if ( right1 < left2 ) return false;
    if ( left1 > right2 ) return false;

    return true;

};

bool Control_Collision::CollisionPixel( Demon *MyDemon, Enemy *MyEnemy )
{
	return false;
}