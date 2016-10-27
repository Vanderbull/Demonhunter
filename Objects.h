#pragma once
#include "SDL.h"
#include <list>

// Fredik Zaar SP6 Demon Hunter

class Object
{
public:
	float xPos, yPos;
	int Width, Height;
	int surface;
	int Frame;
	int radius;

	SDL_Rect Clips[ 10 ];
	SDL_Rect SingleClip;
	
private:
};

class ThingsToDemon : public Object
{
public:
	ThingsToDemon();
	void SetClips();
	SDL_Rect HealthClips[ 6 ];
	int SurfaceHealth;

private:

};

class PowerUp : public Object
{
public:
	PowerUp( int xpos, int ypos, int Surface );
	void SetClips();
	void SetFrame();
	bool Left, Right;

private:
};

class Tree : public Object
{
public:
	Tree();
	
private:
};

class FireBall : public Object
{
public:
	FireBall();
	void SetClips();
	int FrameRight, FrameLeft;
	bool FireRight, FireLeft;

	int FireWidth, FireHeight;

private:

};

class Coffin : public Object
{
public:
	Coffin();
	void SetClips();
	void SetFrames();
	
};

class Control_Objects
{
public:
	Control_Objects();
	void DrawObjects();
	void CreateObjects();

	
	int WhichLifeToShow;
	SDL_Rect destHealth;
	int FrameHealth;

	int Zombie, Skeleton, Skull;

	bool PowerUpMan;
	
	FireBall * CreateFireBall( int xpos, int ypos, int Surface, bool right, bool left );
	Coffin * CreateCoffin( int xPos, int yPos, int Surface );

	PowerUp * WereWolf;
	
	std::list< PowerUp * > List_PowerUps;
	std::list< Tree * > List_Trees;
	std::list< FireBall * > List_FireBalls;
	std::list< Coffin * > List_Coffins;

	ThingsToDemon * DemonLife;

private:
};

extern Control_Objects Control_OBJ;