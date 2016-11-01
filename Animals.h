#pragma once
#include <list>
#include <SDL.h>

class NotEnemies
{
public:
	float xPos, yPos;
	int Frame, State;
	int Height, Width;
	int radius;
	int surface;
};

class Animal : public NotEnemies
{
public:
	Animal();
	SDL_Rect Clips[ 17 ];
	

	void Setframe();
	int PrevFrameCrow;
	

private:
};

// the class that controls the animals
class Control_Animals
{
public:
	Control_Animals();
	void Draw_Animals();
	void Create_Animals();

	int CrowTurf;

	Animal * CreateAnimal( int xPos, int yPos, int surface );

	
private:
	std::list< Animal* > My_Animals;

};

extern Control_Animals Control_Anim;
