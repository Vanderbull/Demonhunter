#pragma once
#include <SDL.h>

#include <list>

class NotEnemies
{
public:
	SDL_Point Position;
	SDL_Point Size;
	
	//float xPos, yPos;
	int Frame, State;
	//int Height, Width;
	int radius;
	int surface;
};

#define NUMBER_OF_CLIPS 17
class Animal : public NotEnemies
{
public:
	Animal();
	SDL_Rect Clips[ NUMBER_OF_CLIPS ];
	void Setframe();
	int PrevFrameCrow;
};

// the class that controls the animals
class Control_Animals
{
public:
	Control_Animals();
	void Draw_Animals();
	void Create_Animals();

	int CrowTurf;

	Animal * CreateAnimal( SDL_POint iPosition, int surface );
	//Animal * CreateAnimal( int xPos, int yPos, int surface );

private:
	std::list< Animal* > My_Animals;
};

extern Control_Animals Control_Anim;
