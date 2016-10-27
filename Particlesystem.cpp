#include "ParticleSystem.h"
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "time.h"
#include "Game.h"
#include <cmath>

Texture texture;

Container_pSystem::Container_pSystem()
{
	for( int i = 0; i < MAX_CONTAINERS_WEATHER; i++ )
	{
		My_pSystem[ i ] = NULL;
	}

	for( int i = 0; i < MAX_CONTAINERS; i++ )
	{
		Single_particles[ i ] = NULL;
	}

	CreateOwn = NULL;

}

void Container_pSystem::CreateSingleParticle( int xPos, int yPos, float x_Vel, float y_Vel )
{
	int Free;
	if( ( Free = CreateOwn->GetFreeParticle() ) != -1 )
	{
		CreateOwn->Single( Free, xPos, yPos, x_Vel, y_Vel, 35 );
	}

	return;
}



void Container_pSystem::ClearAllContainers()
{
	for( int i = 0; i < MAX_CONTAINERS_WEATHER; i++ )
	{
		if( My_pSystem[ i ] != NULL )
		{
			delete My_pSystem[ i ];
			My_pSystem[ i ] = NULL;
		}
	}

	for( int i = 0; i < MAX_CONTAINERS; i++ )
	{
		if( Single_particles[ i ] != NULL )
		{
			delete Single_particles[ i ];
			Single_particles[ i ] = NULL;
		}
	}

	if( CreateOwn != NULL )
	{
		delete CreateOwn;
		CreateOwn = NULL;
	}
}

void Container_pSystem::Update_pSystem()
{
	for( int i = 0; i < MAX_CONTAINERS_WEATHER; i++ )
	{
		int Empty = 1;
		if( My_pSystem[ i ] != NULL )
		{
			switch( My_pSystem[ i ]->Type_Of_System )
			{
			case PSYSTEM_SNOW:
				if( ( Empty = My_pSystem[ i ]->UpdateSnow() ) == 0 )
				{
					My_pSystem[ i ] = NULL;
				}
				break;

			case PSYSTEM_BLIZZARD:
				if( ( Empty = My_pSystem[ i ]->UpdateBlizzard() ) == 0 )
				{
					My_pSystem[ i ] = NULL;
				}
				break;

			case PSYSTEM_WIND:
				if( ( Empty = My_pSystem[ i ]->UpdateWind() ) == 0 )
				{
					My_pSystem[ i ] = NULL;
				}
				break;
				
			case PSYSTEM_RAIN:
				if( ( Empty = My_pSystem[ i ]->UpdateRain() ) == 0)
				{
					My_pSystem[ i ] = NULL;
				}
				break;
	
			}

			
		}
	}
	if( CreateOwn != NULL )
	{
		
		CreateOwn->Update_SingleParticles();
	}

	for( int i = 0; i < MAX_CONTAINERS; i++ )
	{
		int Empty = 1;
		if( Single_particles[ i ] != NULL )
		{
			switch( Single_particles[ i ]->Type_Of_System )
			{
			case PSYSTEM_PUFF:
				if( ( Empty = Single_particles[ i ]->Update_Effects( PSYSTEM_PUFF, Single_particles[ i ]->EffectStart ) ) == 0 )
				{
					Single_particles[ i ] = NULL;
				}
				break;
			case PSYSTEM_RAINHITS:
				if( ( Empty = Single_particles[ i ]->Update_Effects( PSYSTEM_RAINHITS, Single_particles[ i ]->EffectStart ) ) == 0 )
				{
					Single_particles[ i ] = NULL;
				}
				break;
			}
		}
	}
}

int Container_pSystem::getFreeContainer( int Type )
{
	if( Type == WEATHER )
	{
		for( int i = 0; i < MAX_CONTAINERS_WEATHER; i++ )
		{
			if( !My_pSystem[ i ] )
			{
				return i;
			}
		}
		return -1;
	}
	else if( Type == EFFECT )
	{
		for( int i = 0; i < MAX_CONTAINERS; i++ )
		{
			if( !Single_particles[ i ] )
			{
				return i;
			}
		}
		return -1;
	}
}

void Container_pSystem::CreateSnowPuff( int xStart, int yStart )
{
	float SpeedPart = 0.1f;
	int Index = getFreeContainer( EFFECT );
	Single_particles[ Index ] = new Particle_System( PSYSTEM_PUFF, 299 );
	Single_particles[ Index ]->Type_Of_System = PSYSTEM_PUFF;
	Single_particles[ Index ]->EffectStart = yStart;
	Single_particles[ Index ]->Up = true;
	Single_particles[ Index ]->Down = false;
	for( int i = 3; i < 22; i += 3 )
	{
		Single_particles[ Index ]->Circle( xStart, yStart, i );
	}
}

void Container_pSystem::CreateRainHit( int xHotSpot, int yHotSpot )
{
	int Index = getFreeContainer( EFFECT );
	Single_particles[ Index ] = new Particle_System( PSYSTEM_RAINHITS, 9 );
	Single_particles[ Index ]->Type_Of_System = PSYSTEM_RAINHITS;
	Single_particles[ Index ]->EffectStart = yHotSpot;
	Single_particles[ Index ]->Up = true;
	Single_particles[ Index ]->Down = false;
	
	int Free[ 8 ];
	int index = 0;
	float SetVel[ 8 ];
	for( float i = 0.3f; i < 1.0f; i += 0.1f )
	{	
		SetVel[ index ] = i;
		index++;
	}

	for( int i = 0; i < 4; i++ )
	{
		if( i == 0 )
		{
			Free[ i ] = Single_particles[ Index ]->GetFreeParticle();
			Single_particles[ Index ]->Single(	Free[ i ], xHotSpot, yHotSpot, 
												2.0f, 5.0f, 10 );
		}
		else if( i == 1 )
		{
			Free[ i ] = Single_particles[ Index ]->GetFreeParticle();
			Single_particles[ Index ]->Single(	Free[ i ], xHotSpot - 5, yHotSpot, 
												2.0f, 5.5f, 10 );
		}
		else
		{
			Free[ i ] = Single_particles[ Index ]->GetFreeParticle();
			Single_particles[ Index ]->Single(	Free[ i ], xHotSpot + 5, yHotSpot, 
												2.0f, 4.5f, 10 );
		}
	}
}

void Container_pSystem::CreateParticleSystem( int Type, int WhichTypeOfEffect )
{
	int index = getFreeContainer( WEATHER );
	int indexEffect = getFreeContainer( EFFECT );



	if( Type == WEATHER )
	{
		switch( WhichTypeOfEffect )
		{
		case PSYSTEM_SNOW:
			{
				My_pSystem[ index ] = new Particle_System( PSYSTEM_SNOW, 300 );
				My_pSystem[ index ]->Type_Of_System = PSYSTEM_SNOW;
				My_pSystem[ index ]->Timer_Particles_Snow = 600;
				
				break;
			}
		case PSYSTEM_BLIZZARD:
			{
				My_pSystem[ index ] = new Particle_System( PSYSTEM_BLIZZARD, 300 );
				My_pSystem[ index ]->Type_Of_System = PSYSTEM_BLIZZARD;
				My_pSystem[ index ]->Timer_Particles_Snow = 600;
				break;
			}
		case PSYSTEM_WIND:
			{
				My_pSystem[ index ] = new Particle_System( PSYSTEM_WIND, 300 );
				My_pSystem[ index ]->Type_Of_System = PSYSTEM_WIND;
				My_pSystem[ index ]->Timer_Particles_Snow = 600;
				break;
			}
		case PSYSTEM_RAIN:
			{
				My_pSystem[ index ] = new Particle_System( PSYSTEM_RAIN, 200 );
				My_pSystem[ index ]->Type_Of_System = PSYSTEM_RAIN;
				My_pSystem[ index ]->Timer_Particles_Rain = 600;
				break;
			}
		case PSYSTEM_SINGLE:
			{
				if( CreateOwn == NULL )
				{
					CreateOwn = new Particle_System( 300 );
					CreateOwn->Type_Of_System = PSYSTEM_SINGLE;
					My_pSystem[ index ]->Timer_Particles_Snow = 600;
				}
				break;
			}
		}
	}
	else if( Type == EFFECT )
	{
		switch( WhichTypeOfEffect )
		{
			case PSYSTEM_PUFF:
				Single_particles[ indexEffect ] = new Particle_System( PSYSTEM_PUFF, 100 );
				Single_particles[ indexEffect ]->Type_Of_System = PSYSTEM_PUFF;	
				My_pSystem[ index ]->Timer_Particles_Snow = 600;
				break;
		}

	}
}

// loads image with chosen value to not show
SDL_Surface * Particle_System::Load_imageAlpha( std::string filename, int r, int g, int b )
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}

	return optimizedImage;
}

// checks collision
void Particle_System::Circle( long centerx, long centery, long radius )
{
     long d, y, x;

	// setup
	d = 3 - (2 * radius);
	x = 0;
	y = radius;

	int Free[ 8 ];
	
	int timer = 0;
	int index = 0;
	float SetVel[ 8 ];
	for( float i = 0.1f; i < 0.8f; i += 0.1f )
	{	
		SetVel[ index ] = i;
		index++;
	}

     // draw the thing
	while (y > x) 
	{
		
		if( timer > 4 )
		{
			for( int i = 0; i < 8; i++ )
			{
				Free[ i ] = GetFreeParticle();
			}
			Single( Free[ 0 ], centerx + x, centery + y, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 1 ], centerx + y, centery + x, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 2 ], centerx - x, centery + y, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 3 ], centerx - y, centery + x, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 4 ], centerx + x, centery - y, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 5 ], centerx + y, centery - x, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 6 ], centerx - x, centery - y, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			Single( Free[ 7 ], centerx - y, centery - x, SetVel[ rand() % 8 ], 
					SetVel[ rand() % 8 ] + 1.0f, 10 );
			timer = 0;
		}

		timer++;
			
		

		if (d < 0) 
		{
		d = d + ( 4 * x ) + 6;
		} 
		else 
		{
		d = d + 4 * ( x - y ) + 10;
		y--;
		}
		x++;
	}
	 
}

int Particle_System::Update_Effects( int Type, int XstartEffect )
{
	int AnyoneAlive = 0;

	if( Type == PSYSTEM_PUFF )
	{
		
		for( int i = 0; i < _Number_Of_Particles; i++ )
		{
			if( MyParticles[ i ]->Life_Length == MyParticles[ i ]->Life )
			{
				MyParticles[ i ]->Alive = false;
			}
			MyParticles[ i ]->Life++;

			if( MyParticles[ i ]->Alive == true )
			{
				int check = MyParticles[ i ]->UpdateLeft( PSYSTEM_PUFF, Up, XstartEffect );
				if( check == 1 )
				{
					Up = false;
				}
				
				SDL_Rect dest = {	(int)MyParticles[ i ]->x,
									(int)MyParticles[ i ]->y,
									Width, 
									Height };

				SDL_BlitSurface( gamestate.texture->Snow, &src, gamestate.BackBuffer, &dest );

				AnyoneAlive++;

				if( check == 2 )
				{
					MyParticles[ i ]->Alive = false;
				}
										
			}
		}
		return AnyoneAlive;
	}
	else if( Type == PSYSTEM_RAINHITS )
	{		
		for( int i = 0; i < _Number_Of_Particles; i++ )
		{
			if( MyParticles[ i ]->Alive == true )
			{
				if( MyParticles[ i ]->Life_Length == MyParticles[ i ]->Life )
				{
					MyParticles[ i ]->Alive = false;
				}

				MyParticles[ i ]->Life++;

				int check = MyParticles[ i ]->UpdateLeft( PSYSTEM_RAINHITS, Up, XstartEffect );
				if( check == 1 )
				{
					Up = false;
				}

				SDL_Rect dest = {	(int)MyParticles[ i ]->x,
									(int)MyParticles[ i ]->y,
									Width, 
									Height };

				SDL_BlitSurface( gamestate.texture->Rain, &src, gamestate.BackBuffer, &dest );

				AnyoneAlive++;

				if( check == 2 )
				{
					MyParticles[ i ]->Alive = false;
				}
										
			}
		}
		return AnyoneAlive;
	}

	
}
void Particle_System::StartUpSnowPuff( 	int index, int xPos, int yPos, float x_Vel, 
										float y_Vel, int LifeSpan )
{
	MyParticles[ index ]->Alive = false;
	MyParticles[ index ]->x = xPos;
	MyParticles[ index ]->y = yPos;
	MyParticles[ index ]->xVel = x_Vel;
	MyParticles[ index ]->yVel = y_Vel;
	MyParticles[ index ]->Life_Length = LifeSpan;
	MyParticles[ index ]->Life = 0;
}

void Particle_System::Single(	int index, int xPos, int yPos, float x_Vel, 
								float y_Vel, int LifeSpan )
{
	MyParticles[ index ]->Alive = true;
	MyParticles[ index ]->x = xPos;
	MyParticles[ index ]->y = yPos;
	MyParticles[ index ]->xVel = x_Vel;
	MyParticles[ index ]->yVel = y_Vel;
	MyParticles[ index ]->Life_Length = LifeSpan;
	MyParticles[ index ]->Life = 0;
}

int Particle_System::Update_SingleParticles()
{
	int AnyoneAlive = 0;
	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == true )
		{
			if( MyParticles[ i ]->Life_Length == MyParticles[ i ]->Life )
			{
				MyParticles[ i ]->Alive = false;
				ResetParticle( MyParticles[ i ], PSYSTEM_PUFF );
			}

			MyParticles[ i ]->Life++;

			MyParticles[ i ]->x += MyParticles[ i ]->xVel;
			MyParticles[ i ]->y += MyParticles[ i ]->yVel;

			SDL_Rect src = {	SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].x,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].y,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].w, 
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].h };
			

			SDL_Rect dest = {	(int)MyParticles[ i ]->x,
								(int)MyParticles[ i ]->y,
								Width, 
								Height };

			SDL_BlitSurface( gamestate.texture->Snow, &src, gamestate.BackBuffer, &dest );

			AnyoneAlive++;
		}
	}
	return AnyoneAlive;
}

int Particle_System::GetFreeParticle()
{
	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == false )
		{
			MyParticles[ i ]->Alive = true;
			return i;
		}
	}
	return -1;
}

void Particle_System::Load_Files()
{
	/*Snow = NULL, Rain = NULL;
	Snow = Load_imageAlpha( "Snow.png", 0, 0, 0 );
	Rain = Load_imageAlpha( "Raindrops.png", 255, 255, 0 );
	int Alpha = 150;
	int AlphaRain = 150;
	if( Snow != NULL )
	{
		SDL_SetAlpha( Snow, SDL_SRCALPHA | SDL_RLEACCEL, Alpha );
	}
	if( Rain != NULL )
	{
		SDL_SetAlpha( Rain, SDL_SRCALPHA | SDL_RLEACCEL, AlphaRain );
	}*/
	Set_Rects();

	Timer_Particles_Rain = 0;
}

void Particle_System::Set_Rects()
{

	Width = 16;
	Height = 20;
	for( int i = 0; i < 3; i++ )
	{
		(*this).SnowFlakes[ i ].x = Width * i;
		(*this).SnowFlakes[ i ].y = 0;
		(*this).SnowFlakes[ i ].w = Width;
		(*this).SnowFlakes[ i ].h = Height;
	}
	
	Width = 7;
	Height = 29;
	for( int i = 0; i < 4; i++ )
	{
		(*this).Raindrops[ i ].x = Width * i;
		(*this).Raindrops[ i ].y = 0;
		(*this).Raindrops[ i ].w = Width;
		(*this).Raindrops[ i ].h = Height;
	}
}

int Particle_System::UpdateRain()
{
	if( Timer_Particles_Rain > 8 )
	{
		Timer_Particles_Rain = 0;
		NewParticles( PSYSTEM_RAIN );
	}

	Timer_Particles_Rain++;
	int AnyoneAlive = 0;

	for( int i = 0; i < _Number_Of_Particles; i++ )
	{


		if( MyParticles[ i ]->Alive == true )
		{
			
			MyParticles[ i ]->UpdateRight( PSYSTEM_RAIN );

			SDL_Rect src = {	Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].x,
								Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].y,
								Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].w, 
								Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].h };
			

			SDL_Rect dest = {	(int)MyParticles[ i ]->x,
								(int)MyParticles[ i ]->y,
								Width, 
								Height };

			SDL_BlitSurface( gamestate.texture->Rain, &src, gamestate.BackBuffer, &dest );
								
			AnyoneAlive++;
		}

	}
	return AnyoneAlive;
}

int Particle_System::UpdateWind()
{
	if( Timer_Particles_Snow > 60 )
	{
		Timer_Particles_Snow = 0;
		NewParticles( PSYSTEM_WIND );
	}

	Timer_Particles_Snow++;
	int AnyoneAlive = 0;

	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == true )
		{
			MyParticles[ i ]->UpdateLeft( PSYSTEM_WIND );

			SDL_Rect src = {	SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].x,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].y,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].w, 
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].h };
			

			SDL_Rect dest = {	(int)MyParticles[ i ]->x,
								(int)MyParticles[ i ]->y,
								Width, 
								Height };

			SDL_BlitSurface( gamestate.texture->Snow, &src, gamestate.BackBuffer, &dest );
						
			AnyoneAlive++;
		}
	}
	return AnyoneAlive;
}

int Particle_System::UpdateBlizzard()
{
	if( Timer_Particles_Snow > 35 )
	{
		Timer_Particles_Snow = 0;
		NewParticles( PSYSTEM_BLIZZARD );
	}

	Timer_Particles_Snow++;
	if( Timer_Particles_Change_Dir > 100 )
	{
		Timer_Particles_Change_Dir = 0;
		if( Right == true )
		{
			Right = false;
			Left = true;
		}
		else
		{	
			Right = true;
			Left = false;
		}
	}
	Timer_Particles_Change_Dir++;
	int AnyoneAlive = 0;

	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == true )
		{
			if( Right )
				MyParticles[ i ]->UpdateRight( PSYSTEM_BLIZZARD );
			else
				MyParticles[ i ]->UpdateLeft( PSYSTEM_BLIZZARD );

			
			SDL_Rect src = {	SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].x,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].y,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].w, 
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].h };
			

			SDL_Rect dest = {	(int)MyParticles[ i ]->x,
								(int)MyParticles[ i ]->y,
								Width, 
								Height };
			
			SDL_BlitSurface( gamestate.texture->Snow, &src, gamestate.BackBuffer, &dest );

			AnyoneAlive++;
									
		}
	}
	return AnyoneAlive;
}


int Particle_System::UpdateSnow()
{
	if( Timer_Particles_Snow > 150 )
	{
		Timer_Particles_Snow = 0;
		NewParticles( PSYSTEM_SNOW );
	}

	Timer_Particles_Snow++;
	if( Timer_Particles_Change_Dir > 100 )
	{
		Timer_Particles_Change_Dir = 0;
		if( Right == true )
		{
			Right = false;
			Left = true;
		}
		else
		{	
			Right = true;
			Left = false;
		}
	}
	Timer_Particles_Change_Dir++;
	int AnyoneAlive = 0;

	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == true )
		{
			if( Right )
				MyParticles[ i ]->UpdateRight( PSYSTEM_SNOW );
			else
				MyParticles[ i ]->UpdateLeft( PSYSTEM_SNOW );

			
			SDL_Rect src = {	SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].x,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].y,
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].w, 
								SnowFlakes[ MyParticles[ i ]->WhichFlakeToUse ].h };
			

			SDL_Rect dest = {	(int)MyParticles[ i ]->x,
								(int)MyParticles[ i ]->y,
								Width, 
								Height };

			SDL_BlitSurface( gamestate.texture->Snow, &src, gamestate.BackBuffer, &dest );

			AnyoneAlive++;
									
		}
	}
	return AnyoneAlive;
}

void Particle_System::NewParticles( int Type )
{
	for( int i = 0; i < 8; i++ )
	{
		int FreeParticle = GetFreeIndex();
		if( FreeParticle == -1 )
		{
			return;
		}

		ResetParticle( MyParticles[ FreeParticle ],  Type );
		MyParticles[ FreeParticle ]->Alive = true;
		
	}	
}

int Particle_System::GetFreeIndex()
{
	for( int i = 0; i < _Number_Of_Particles; i++ )
	{
		if( MyParticles[ i ]->Alive == false )
		return i;
	}

	return -1;
}


Particle_System::Particle_System( int Number_Of_Particles )
{
	(*this).Load_Files();

	for( int i = 0; i < Number_Of_Particles; i++ )
	{
		MyParticles[ i ] = new Particle( PSYSTEM_SINGLE );
	}
	(*this)._Number_Of_Particles = Number_Of_Particles;
}

Particle_System::Particle_System( int WhichTypeOfEffect, int Number_Of_particles )
{
	Load_Files();

	int x = 0;
	if( WhichTypeOfEffect == PSYSTEM_BLIZZARD )
	{
		for( float i = 0.7f; i < 1.5f; i += 0.1f )
		{
			Speed[ x ] = i;
			x++;
		}
	}
	else if( WhichTypeOfEffect == PSYSTEM_RAIN )
	{
		for( float i = 10.0f; i < 20.0f; i += 1.0f )
		{
			Speed[ x ] = i;
			x++;
		}
	}
	else
	{
		for( float i = 0.2f; i < 1.0f; i += 0.1f )
		{
			Speed[ x ] = i;
			x++;
		}
	}

	for( int i = 0; i < Number_Of_particles; i++ )
	{
		MyParticles[ i ] = new Particle( WhichTypeOfEffect );
		MyParticles[ i ]->Alive = false;
		if( WhichTypeOfEffect == PSYSTEM_RAIN )
		{
			MyParticles[ i ]->xVel = 0.0f;
		}
		else 
		{ 
			MyParticles[ i ]->xVel = 0.2f; 
		}
		
		int random = rand() % 8;
		MyParticles[ i ]->yVel = Speed[ random ];	

		src.x = Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].x;
		src.y = Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].y;
		src.w =	Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].w; 
		src.h = Raindrops[ MyParticles[ i ]->WhichFlakeToUse ].h;
	}

	_Number_Of_Particles = Number_Of_particles;

	Timer_Particles_Snow = 0.0f;
	Timer_Particles_Change_Dir = 0.0f;
	Right = false;
	Left = true;




	

}

Particle::Particle( int Type )
{
	if( Type == PSYSTEM_WIND )
	{
		if( rand() % 5 == 1 )
		{
			( *this ).WhichFlakeToUse = rand() % 3;
			y = rand() % 700;
			x = 805;
		}
		else
		{
			( *this ).WhichFlakeToUse = rand() % 3;
			x = (float)(rand() % 600 + rand() % 600 + rand() % 600);
			if( x > gamestate.SCREEN_WIDTH )
			{
				x = (float)(rand() % 600);
			}
			y = -5;
		}
	}
	else if( Type == PSYSTEM_SINGLE )
	{
		Alive = false;
		( *this ).WhichFlakeToUse = rand() % 3;
	}
	else if( Type == PSYSTEM_PUFF )
	{
		Alive = false;
		( *this ).WhichFlakeToUse = rand() % 3;
	}
	else if( Type == PSYSTEM_RAINHITS )
	{
		Alive = false;
		( *this ).WhichFlakeToUse = rand() % 2 + 2;
	}
	else
	{
		( *this ).WhichFlakeToUse = rand() % 3;
		x = (float)(rand() % 600 + rand() % 600 + rand() % 600);
		if( x > gamestate.SCREEN_WIDTH )
		{
			x = (float)( rand() % 600 );
		}
		y = -5;
	}

	DirUp = 0;
}

void Particle_System::ResetParticle( Particle * p, int Type )
{
	if( Type == PSYSTEM_WIND )
	{
		if( rand() % 5 == 1 )
		{
			p->WhichFlakeToUse = rand() % 3;
			p->y = rand() % 700;
			p->x = gamestate.SCREEN_WIDTH;
		}
		else
		{
			p->WhichFlakeToUse = rand() % 3;
			p->x = (float)(rand() % 600 + rand() % 600 + rand() % 600);
			if( p->x > gamestate.SCREEN_WIDTH )
			{
				p->x = (float)(rand() % 600);
			}
			p->y = 0;
		}
	}
	else if( Type == PSYSTEM_PUFF || Type == PSYSTEM_RAINHITS )
	{
		p->Alive = false;
	}
	else
	{
		p->WhichFlakeToUse = rand() % 3;
		p->x = (float)(rand() % 600 + rand() % 600 + rand() % 600);
		if( p->x > gamestate.SCREEN_WIDTH )
		{
			p->x = (float)(rand() % 600);
		}
		p->y = 0;
	}

}

void Particle::UpdateRight( int Type )
{
	if( x < -10 || x > gamestate.SCREEN_WIDTH || y > gamestate.SCREEN_HEIGHT || y < -10 )
	{
		(*this).Alive = false;
	}
	else
	{
		x += xVel;
		y += yVel;
	}	

	if( Type == PSYSTEM_RAIN )
	{ 
		if( y > gamestate.SCREEN_HEIGHT - 100 )
		{
			gamestate.pSystem->CreateRainHit( (*this).x, (*this).y );
			(*this).Alive = false;
		}
	}

}

int Particle::UpdateLeft( int Type, bool Up, int Start )
{
	if( x < -10 || x > gamestate.SCREEN_WIDTH || y > gamestate.SCREEN_HEIGHT || y < -10 )
	{
		(*this).Alive = false;
	}
	else
	{
		if( Type == PSYSTEM_WIND )
		{
			x -= ( xVel + 1.8f );
			y += ( yVel + 1.8f );
		}
		else if( Type == PSYSTEM_PUFF || Type == PSYSTEM_RAINHITS )
		{
			int RightLeft = rand() % 2;
			if( RightLeft == 0 )
			{
				x -= xVel;
			}
			else
			{
				x += xVel;
			}

			if( ( y - yVel ) < Start - 25 )
			{
				DirUp = 1;
			}

		

			if( Up )
			{
				y -= yVel;
			}
			else
			{
				if( y + yVel > Start + 45 )
				{
					return 2;
				}
				y += yVel;
			}	
		}
		else
		{
			x -= xVel;
			y += yVel;
		}
	}	
	return DirUp;

}

Texture::Texture()
{
	Load_Files();
}

void Texture::Load_Files()
{
	Snow = gamestate.Load_image( "Snow.png", 0, 0, 0 );
	Rain = gamestate.Load_image( "Raindrops.png", 255, 255, 0 );
	int Alpha = 150;
	int AlphaRain = 150;
	if( Snow != NULL )
	{
		SDL_SetAlpha( Snow, SDL_SRCALPHA | SDL_RLEACCEL, Alpha );
	}
	if( Rain != NULL )
	{
		SDL_SetAlpha( Rain, SDL_SRCALPHA | SDL_RLEACCEL, AlphaRain );
	}
}





