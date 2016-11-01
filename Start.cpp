#include "Start.h"
#include <SDL.h>

FirstScreen::FirstScreen( int ButtonX, int Surface, int SurfaceButtons )							
{
	xPos = 0;
	yPos = 0;
	Width = 800;
	Height = 600;
	surface = Surface;
	SurfaceButt = SurfaceButtons;

	ButtonXpos = ButtonX;
	Button_Width = 250;
	Button_Height = 70;
	Button_Small_Width = 200;
	Button_Small_Height = 50;

	Button_Options = false;
	Button_Back = false; 
	Button_Sound = false;
	Button_Credits = false;
	Button_HighScore = false;

	Button_Newgame = false;
	Button_Quit = false;

	for( int i = 0; i < 3; i++ )
	{
		ButtonClips[ i ].x = 0;
		ButtonClips[ i ].y = i * Button_Height;
		ButtonClips[ i ].w = Button_Width;
		ButtonClips[ i ].h = Button_Height;
	}
		ButtonClips[ 0 ].y = 10;
		ButtonClips[ 0 ].h = Button_Height-10;

		ButtonClips[ 3 ].x = 0;
		ButtonClips[ 3 ].y = 200;
		ButtonClips[ 3 ].w = 390;
		ButtonClips[ 3 ].h = 150;

	int j = 0;
	for( int i = 4; i < 8; i++, j++)
	{
		ButtonClips[ i ].x = 410;
		ButtonClips[ i ].y = j * 50;
		ButtonClips[ i ].w = Button_Small_Width;
		ButtonClips[ i ].h = Button_Small_Height;
	}

		ButtonClips[ 8 ].x = 410;
		ButtonClips[ 8 ].y = 55;
		ButtonClips[ 8 ].w = Button_Small_Width;
		ButtonClips[ 8 ].h = Button_Small_Height - 5;

	for( int i = 0; i < 3; i++ )
	{
		DestClips[ i ].x = ButtonXpos * i;
		DestClips[ i ].y = 515;
		DestClips[ i ].w = Button_Width;
		DestClips[ i ].h = Button_Height;

	}

		DestClips[ 3 ].x = 0;
		DestClips[ 3 ].y = 0;
		DestClips[ 3 ].w = 390;
		DestClips[ 3 ].h = 130;

	for( int i = 4; i < 8; i++ )
	{
		DestClips[ i ].x = 470;
		DestClips[ i ].y = 80 + i * 60;
		DestClips[ i ].w = Button_Small_Width;
		DestClips[ i ].h = Button_Small_Height;
	}

	DestClips[ 8 ].x = 40;
	DestClips[ 8 ].y = 20;
	DestClips[ 8 ].w = Button_Small_Width;
	DestClips[ 8 ].h = Button_Small_Height;

	DestClips[ 9 ].x = 40;
	DestClips[ 9 ].y = 20;
	DestClips[ 9 ].w = Button_Small_Width;
	DestClips[ 9 ].h = Button_Small_Height;
}


