#include "SDL.h"
#include "Game.h"
#include "characters.h"
#include <cmath>
#include "time.h"
#include "Timers.h"

const int FRAMES_PER_SECOND = 30;
using namespace std;

SDL_Event event;
bool Quit = false;


int main( int argc, char * arg[] )
{
	srand( time( 0 ) );
	DWORD	PrevTick, CurTick;

	Game New_Game;

	PrevTick = SDL_GetTicks();

	Timer fps;
	
	while( Quit == false )
	{	
		fps.start();

		if( gamestate.GameOK == false )
		{
			Quit = true;
		}

		while( SDL_PollEvent( &event ) )
		{		
		

			if( event.type == SDL_QUIT  )
			{
				Quit = true;
			}
			else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) )
			{
				//quit the program
				gamestate.GameCondition = GS_INTRO;
			}
		}		
		
		CurTick = SDL_GetTicks();
		gamestate.dt = float(CurTick - PrevTick);
		PrevTick = CurTick;

		
		New_Game.upDate( event );

	      //Cap the frame rate
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait    
        }
				
		gamestate.AddTick();
		
	}

	New_Game.cleanUp();
	gamestate.EndAll();

	return 0;

}
