#pragma once
#include <list>

#include "EnemiesAndObjects.h"
#include "game.h"

#define NUMBER_OF_CLIPS 16

void Enemy::Set_Clips( int WhichTypeOfEnemy )
{ 
	// enemy type zombie
	if( WhichTypeOfEnemy == 0 )
	{
		for( int i = 0; i < 10; i++ )
		{
			EnemyClips[ i ].x = i * Enemy_Width;
			EnemyClips[ i ].y = 0;
			EnemyClips[ i ].h = Enemy_Height;
			EnemyClips[ i ].w = Enemy_Width;
		}
	}
	// enemy type 1 Skelton
	else if( WhichTypeOfEnemy == 1 )
	{
		Frame = 0;
		for( int i = 0; i < 2; i++ )
		{
			for( int j = 0; j < 14; j++ )
			{
				SkeletonClips[ i ][ j ].x = j * Enemy_Width;
				SkeletonClips[ i ][ j ].y = i * Enemy_Height;
				SkeletonClips[ i ][ j ].h = Enemy_Height;
				SkeletonClips[ i ][ j ].w = Enemy_Width;
			}
		}
	}
}

void Enemy::SetFrame()
{
	if( Walk )
	{
		if( WalkFrame == 8 )
		{
			WalkFrame = 0;
		}
		else
		{
			WalkFrame++;
		}
		Frame = WalkFrame;
	}
	else if( Attack )
	{
		Walk = false;
		if( AttackFrame == 18 )
		{
			AttackFrame = 9;
			Walk = true;
			Attack = false;
		}
		else
		{
			AttackFrame++;
		}

		Frame = AttackFrame;
	}
	else if( Die )
	{
		Walk = false;
		if( DieFrame == 27 ) 
		{
			DieFrame = 27;

		}
		else
		{
			DieFrame++;
		}
		Frame = DieFrame;
	}
}

int Heads::GetFrame()
{
	return Frame;
}

void Heads::SetFrame( int WhichFrame )
{
	Frame = WhichFrame;
}

void Heads::UpdateFrame()
{
	Frame++;
}

int Boss::GetTimerAttack()
{
	AttackTimer++;
	return AttackTimer;
}

int Boss::GetState()
{
	return State;
}

void Boss::ResetAttackTimer()
{
	AttackTimer = 0;
}

void Boss::UpdateAttackTimer()
{
	AttackTimer++;
}

void Boss::SetState( int WhichState )
{
	State = WhichState;
}

void Boss::SetFrame( int WhichFrame )
{
	Frame = WhichFrame;
}
int Boss::GetFrame()
{
	return Frame;
}

void Boss::UpdateFrame()
{
	Frame++;
}

void Boss::UpdateBoss()
{
	int x = GetTimerAttack();
	if( x >= BOSS_ATTACK_START || HeadsComing == true )
	{
		HeadsComing = true;
		AnimPaceBoss++;
		HeadTimer++;
		SetState( BOSS_ATTACK );
		if( AnimPaceBoss >= ANIMPACEBOSSHEAD )
		{
			UpdateFrame();
			AnimPaceBoss = 0;
		}
		ResetAttackTimer();
		if( HeadTimer >= 20 )
		{
			if( HeadAnimation == true )
			{
				HeadTimer = 0;
				My_BossHead.push_back(	CreateBossHeads( xPos, yPos + 10, surface, 20 * SizeHeads ));
				SizeHeads++;
			}
			
			if( GetFrame() >= 4 )
			{
				HeadAnimation = true;
				SetFrame( BOSS_IDLE );
			}
		}

		if( SizeHeads == 6 )
		{
			HeadsComing = false;
			SetFrame( BOSS_IDLE );
			SizeHeads = 1;
		}
	}
	else
	{
		SetFrame( BOSS_IDLE );
		UpdateAttackTimer();
	}
		//sanity check
	switch( GetState() )
	{
		case BOSS_IDLE:
			{
				SDL_BlitSurface( gamestate.GetSurface( surface ), &GetClips( GetFrame() ), 
						gamestate.screen, &ReturnDestRect() );
			}
		case BOSS_ATTACK:
			{
				SDL_BlitSurface( gamestate.GetSurface( surface ), &GetClips( GetFrame() ), 
						gamestate.screen, &ReturnDestRect() );
			}
		case BOSS_DIE:
			{
				SDL_BlitSurface( gamestate.GetSurface( surface ), &GetClips( GetFrame() ), 
						gamestate.screen, &ReturnDestRect() );
			}
	}
	UpdateHeads();
}

void Boss::UpdateHeads()
{
	if( My_BossHead.size() != 0 )
	{
		list< Heads* > vRemoveHead;
		list< Heads* >::iterator vRemoveIterHead;

		list< Heads* >::iterator i = My_BossHead.begin();
		for( ; i != My_BossHead.end(); ++i )
		{
			Heads * temp = (*i);
			if( temp->HowFar == temp->length )
			{
				temp->state = HEAD_DOWN;

				if( temp->yPos > 500 )
				{
					temp->state = HEAD_CRASH;
					if( temp->state == HEAD_CRASH )
					{
						temp->HeadTimer++;
						if( temp->HeadTimer > 5 )
						{
							if( temp->GetFrame() <= 4 )
							{
								temp->UpdateFrame();	
							}
							else
							{
								vRemoveHead.push_back( (*i) );
								temp->SetFrame( 4 );
							}
							temp->HeadTimer = 0;
						}
					}
				}

				if( temp->state == HEAD_DOWN ) 
				{
					temp->HeadTimer++;
					if( temp->HeadTimer > 5 )
					{
						if( temp->GetFrame() <= 2 )
						{
							temp->UpdateFrame();
							temp->HeadTimer = 0;
						}
					}
					temp->yPos += 10;
				}
			}
			else
			{
				temp->xPos -= 5;
				temp->HowFar++;
			}
			SDL_Rect HeadDest = { temp->xPos, temp->yPos, temp->Width, temp->Height };
			
			SDL_BlitSurface( gamestate.GetSurface( temp->surface ), &temp->GetClips( temp->GetFrame() ), 
					gamestate.screen, &HeadDest );
	
		}

		vRemoveIterHead = vRemoveHead.begin();
		for( ; vRemoveIterHead != vRemoveHead.end() ; ++vRemoveIterHead )
		{
			My_BossHead.remove( *vRemoveIterHead );
		}
	}
	return;
}

Heads * Boss::CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel )
{
	Heads * temp = new Heads;
	temp->xPos = xPos;
	temp->yPos = yPos;
	temp->surface = surface;
	temp->length = lengthOfTravel;

	temp->radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height;

	return temp;
}

SDL_Rect Boss::ReturnDestRect()
{
	SDL_Rect destRect = { xPos, yPos, Width, Height };
	return destRect;
}

SDL_Rect Boss::GetClips( int WhichClip )
{
	return Clips[ WhichClip ];
}

SDL_Rect Heads::GetClips( int WhichClip )
{
	return Clips[ WhichClip ];
}

Boss::Boss()
{
	Size.x = 150;
	Size.y = 300;
	
	//Height = 300;
	//Width = 150;

	HeadsComing = false;
	HeadAnimation = false;
	HeadTimer = 0;
	SizeHeads = 1;
	
	AttackTimer = 0;
	AnimPaceBoss = 0;
	State = 0;
	Frame = 0;

	for( int i = 0; i < 8; i++ )
	{
		Clips[ i ].x = i * Size.x;
		Clips[ i ].y = 0;
		Clips[ i ].h = Size.y;
		Clips[ i ].w = Size.x;
	}
}

Animal::Animal()
{
	Frame = 0;
	PrevFrameCrow = 0;
	Size.x = 64;
	Size.y = 64;
	
	//Height = 64;
	//Width = 64;

	for( int i = 0; i < NUMBER_OF_CLIPS; i++ )
	{
		Clips[ i ].x = i * Size.x;
		Clips[ i ].y = 0;
		Clips[ i ].h = Size.y;
		Clips[ i ].w = Size.x;
	}
}

Heads::Heads()
{
	Size.x = 54;
	Size.y = 54;
	
	//Width = 54;
	//Height = 54;
	Frame = 0;
	HowFar = 0;
	HeadTimer = 0;

	state = 0;
	
	Clips[0].x = 1050;
	Clips[0].y = 0;
	Clips[0].h = 77;
	Clips[0].w = 55;

	Clips[1].x = 1125;
	Clips[1].y = 0;
	Clips[1].h = 74;
	Clips[1].w = 65;

	Clips[2].x = 1190;
	Clips[2].y = 0;
	Clips[2].h = 74;
	Clips[2].w = 75;

	Clips[3].x = 1060;
	Clips[3].y = 87;
	Clips[3].h = 50;
	Clips[3].w = 55;

	Clips[4].x = 1125;
	Clips[4].y = 85;
	Clips[4].h = 55;
	Clips[4].w = 60;

	Clips[5].x = 1195;
	Clips[5].y = 80;
	Clips[5].h = 54;
	Clips[5].w = 70;
}

void Animal::Setframe()
{	
	if( Frame == NUMBER_OF_CLIPS )
	{
		Frame = 0;
	}
	else
	{
		Frame++;
	}
}
