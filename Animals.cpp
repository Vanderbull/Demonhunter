#include <SDL.h>

#include "Animals.h"
#include "game.h"

Control_Animals Control_Anim;

#define NUMBER_OF_CLIPS 16

void Animal::Setframe()
{	
	if( Frame < NUMBER_OF_CLIPS )
	{
		Frame = 0;
	}
	else
	{
		Frame++;
	}
}

Animal::Animal()
{
	Frame = 0;
	PrevFrameCrow = 0;
	
	Size.x = 64;
	Size.y = 64;
	// Replaced by SDL_Point
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

void Control_Animals::Draw_Animals()
{
	// Draws the Crow and sets the frame
	float Speed = 200.0f * ( gamestate.dt / 1000.0f );
	if( My_Animals.size() != 0 )
	{
		list< Animal* >::iterator i = My_Animals.begin();
		for( ; i != My_Animals.end(); ++i )
		{
			Animal * animal = (*i);
			
			animal->Position.y -= Speed;
			//animal->xPos -= Speed;

			SDL_Rect CrowDest = {	
				animal->Position.x, animal->Position.y, 	
				animal->Size.x, 
				animal->Size.y 
			};

			/*
			SDL_Rect CrowDest = {	
				animal->xPos, animal->yPos, 	
				animal->Width, 
				animal->Height 
			};
			*/
														
			if( gamestate.OK_PaceEnemy() )
			{
				SDL_BlitSurface( gamestate.GetSurface( animal->surface ),&animal->Clips[ animal->Frame ], 
				gamestate.BackBuffer, &CrowDest );
				
				animal->Setframe();
				animal->PrevFrameCrow = animal->Frame;
			}
			else
			{	
				SDL_BlitSurface( gamestate.GetSurface( animal->surface ),&animal->Clips[ animal->PrevFrameCrow ], 
				gamestate.BackBuffer, &CrowDest );
			}
		}
	}
}

Animal * Control_Animals::CreateAnimal( SDL_Point iPosition, int surface )
{
	Animal * temp = new Animal;
	temp->surface = surface;
	temp->Position.x = iPosition.x;
	temp->Position.y = iPosition.y;

	temp->radius = ( temp->Size.x > temp->Size.y ) ? temp->Size.x / 2 : temp->Size.y / 2;

	return temp;
}

Animal * Control_Animals::CreateAnimal( int xPos, int yPos, int surface )
{
	Animal * temp = new Animal;
	temp->surface = surface;
	temp->xPos = xPos;
	temp->yPos = yPos;

	temp->radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height / 2;

	return temp;
}

void Control_Animals::Create_Animals()
{
	if( rand() % 100 == 5 )
	{
		My_Animals.push_back( CreateAnimal( gamestate.SCREEN_WIDTH, 75 + ( rand() % CrowTurf ) , gamestate.m_srfCrow ) );
	}
}

Control_Animals::Control_Animals()
{
	CrowTurf = 200;
}
