#pragma once
#include "SDL.h"

// Fredik Zaar SP6 Demon Hunter

class Outro
{
public:
	Outro();
	int surface;

	int Height, Width;
	int xPos, yPos;
	
	SDL_Rect ClipsOutro[ 2 ];
	
};