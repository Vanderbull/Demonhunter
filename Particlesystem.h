#pragma once
#include "SDL.h"
#include "string"
#include <fstream>

enum{	PSYSTEM_SNOW, PSYSTEM_BLIZZARD, PSYSTEM_WIND, 
		PSYSTEM_PUFF, PSYSTEM_SINGLE, WEATHER, EFFECT, 
		PSYSTEM_RAIN, PSYSTEM_RAINHITS };

const int MAX_SURFACES = 128;
const int MAX_CONTAINERS = 10;
const int MAX_CONTAINERS_WEATHER = 4;

class Texture
{
public:
	Texture();
	SDL_Surface * Snow;
	SDL_Surface * Rain;
	void Load_Files();
};

extern Texture texture;

class Particle
{
public:
	Particle( int Type );
	float x, y;
	float xVel, yVel;
	int xStart, yStart;
	bool Alive;
	void UpdateRight( int Type );
	int UpdateLeft( int Type, bool Up = false, int Start = 0 );

	int WhichFlakeToUse;
	int Life_Length, Life;
	int DirUp;


private:
};

class Particle_System
{
public:
	Particle_System( int WhichTypeOfEffect, int Number_Of_particles );
	Particle_System( int Number_Of_Particles );

	Particle *MyParticles[ 305 ];

	

	void NewParticles( int Type );
	void ResetParticle( Particle * p, int Type );

	void Single(	int index, int xPos, int yPos, 
					float x_Vel, float y_Vel, int LiveSpan );

	void StartUpSnowPuff( 	int index, int xPos, int yPos, 
							float x_Vel,float y_Vel, int LifeSpan );

	void Circle( long centerx, long centery, long radius );
										
	int GetFreeParticle();
	int GetFreeIndex();
	 
	void Load_Files();
	void Set_Rects();

	float Speed[ 10 ];

	int Width, Height;
	int EffectStart;
	
	SDL_Rect src;

	float Timer_Particles_Snow;
	float Timer_Particles_Change_Dir;
	float Timer_Particles_Rain;

	bool Right, Left, Up, Down;

	SDL_Surface * Load_imageAlpha( std::string filename, int r, int g, int b );
	SDL_Surface * Snow;
	SDL_Surface * Rain;

	friend class Container_pSystem;
	friend class Particle;

	
	int Type_Of_System;
private:
	int _Number_Of_Particles;

	SDL_Rect SnowFlakes[ 3 ];
	SDL_Rect Raindrops[ 4 ];

	int UpdateSnow();
	int UpdateBlizzard();
	int UpdateWind();
	int UpdateRain();
	int Update_SingleParticles();
	int Update_Effects( int Type, int XstartEffect = 0 );
};

class Container_pSystem
{
public:
	Container_pSystem();
	void CreateParticleSystem( int Type, int WhichTypeOfEffect );
	void CreateSingleParticle( int xPos, int yPos, float x_Vel, float y_Vel );
	void CreateSnowPuff( int xStart, int yStart );
	void CreateRainHit( int xHotSpot, int yHotSpot );
	void Update_pSystem();
	void ClearAllContainers();

	int FreeIndex;
	int getFreeContainer( int Type );

	Texture * Holder;
	
private:
	
	Particle_System *My_pSystem[ MAX_CONTAINERS_WEATHER ];
	Particle_System *Single_particles[ MAX_CONTAINERS ];
	Particle_System *CreateOwn;

};
