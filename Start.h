#pragma once
#include <SDL.h>

class FirstScreen
{
public:
	FirstScreen( int ButtonX, int Surface, int SurfaceButtons );

	int xPos, yPos;
	int Width, Height;
	int surface;
	int SurfaceButt;
	SDL_Rect ButtonClips[ 9 ];
	SDL_Rect DestClips[ 10 ];

	bool	Button_Options, Button_Newgame, Button_Quit, Button_Back, 
			Button_Sound, Button_Credits, Button_HighScore;

	int ButtonXpos;
	int Button_Width, Button_Height;
	int Button_Small_Width,	Button_Small_Height;

};
