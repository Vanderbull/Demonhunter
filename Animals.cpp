#include "Animals.h"
#include <SDL.h>
#include "game.h"

Control_Animals Control_Anim;

void Animal::Setframe()
{	
	if( Frame == 15 )
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
	Height =	64;
	Width =		64;

	for( int i = 0; i < 16; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].h = Height;
		Clips[ i ].w = Width;
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
			
			animal->xPos -= Speed;

			SDL_Rect CrowDest = {	animal->xPos, animal->yPos, 	
									animal->Width, 
									animal->Height };  

														
			if( gamestate.OK_PaceEnemy() )
			{
				SDL_BlitSurface(	gamestate.GetSurface( animal->surface ),&animal->Clips[ animal->Frame ], 
									gamestate.BackBuffer, &CrowDest );
				animal->Setframe();
				animal->PrevFrameCrow = animal->Frame;
			}
			else
			{
							
				SDL_BlitSurface(	gamestate.GetSurface( animal->surface ),&animal->Clips[ animal->PrevFrameCrow ], 
									gamestate.BackBuffer, &CrowDest );
			}
		}
	}

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
