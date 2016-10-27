#include "Intro.h"
#include <SDL.h>
#include "Game.h"

// Fredik Zaar SP6 Demon Hunter

void DancingDragon::SetFrame()
{
	if( Frame == 21 )
	{
		Frame = 0;
	}
	else
	{
		Frame++;
	}
}

void DancingDragon::SetClips()
{
	for( int i = 0; i < 23; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].h = Height;
		Clips[ i ].w = Width;
	}

}

DancingDragon::DancingDragon( int Surface )
{
	Frame = 0;
	PrevFrame = 0;
	StateCounter = 0;

	xPos = 300;
	yPos = 300;
	surface = Surface;
	Width = 185;
	//184
	Height = 119;
	SetClips();
}

// sets up the intro where the dudes talk
IntroTalk::IntroTalk( int Surface )
{
	xPos = 100;
	yPos = 200;
	Height = 210;
	Width = 100;
	surface = Surface;
	Frame = 0;
	for( int i = 0; i < 3; i++ )
	{
		srcClips[ i ].x = i * Width;
		srcClips[ i ].y = 0;
		srcClips[ i ].w = Width;
		srcClips[ i ].h = Height;
	}

	My_DudeTalks[ 0 ] = " My Life is ruined, my sisterhas been kidnapped and my   mom and dad slaughtered by  one of the devils henchemen ";
	My_DudeTalks[ 1 ] = "I wonder if there is anything i can do, i would do      anything to avenge my family and rescue my sister";
	My_FatherTalks[ 0 ] = " My son, I hear your prayers. I have been given the power to fulfill your wishes, But this means that your humanity will be lost forever";
	My_DudeTalks[ 2 ] = " My humanity was lost the minute my family was butchered ill do anything";
	My_FatherTalks[ 1 ] = " OK, son you will get the powers of an ancient god, the possibility to transform into a creature that has the power to kill the devil ";
	My_FatherTalks[ 2 ] = " I will follow you troughout your journey and give you the powerup thats needed when evil draws near ";
	My_FatherTalks[ 3 ] = " Now go my son and give the devil a new definition of the word REVENGE!!!!";
	My_DudeTalks[ 3 ] = " I wont let you down father, I will avenge my family, i just hope that my courage stands me by ";

	CounterWords = 0;
	CounterNextTalker = 0;
	Counter = 0;

	MyDude = true;
	Father = false;
	MyDude_Demon = false;
	FirstLine = true;
	SecondLine = false;
	ThirdLine = false;
	Fifth = false;
	Sixth = false;
	Seventh = false;

	Letter = 0;
	LetterHeight = 30;
	LetterWidth = 0;
	y = 20;
	Line = 0;
}

// draws a black background
void IntroTalk::DrawBackground()
{
	ParallaxLayer  * MyParaBackGround;
	MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

	SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
								600 };

	SDL_Rect dtRect = {	0, 0, MyParaBackGround->m_width, 600 };

	SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect ); 

}

// all the talking
void IntroTalk::DoTalk()
{
	int IntroState = 0;

	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Event input;
	
	while( IntroState < 4 )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				IntroState = 5;
				break;
			}
		}

		int SpeedOfWords = 50.0f * ( gamestate.dt / 1000 ) ;
		Counter += SpeedOfWords;
		
		DrawBackground();
		gamestate.DrawAllText();

		if( Counter > 400 )
		{
			Counter = 0;
			switch( IntroState )
			{
			case 0:
				{
					if( FirstLine )
					{
						if( Letter < My_DudeTalks[ 0 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							FirstLine = false;
							SecondLine = true;
						}
					}
					else
					{
						if( Letter < My_DudeTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							IntroState = 1;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							SecondLine = false;
							ThirdLine = true;
							Father = true;
						}
					}

					
					if( FirstLine )
					{
						My_DudeTalksSlow[ Line ] += My_DudeTalks[ 0 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}
					else
					{
						My_DudeTalksSlow2[ Line ] += My_DudeTalks[ 1 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow2[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}

					LetterWidth++;
			
					break;

		
				}
			case 1:
				{
					if( ThirdLine )
					{
						if( Letter < My_FatherTalks[ 0 ].length() )
						{
							Letter++;
						}
						else
						{
							
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							ThirdLine = false;
							FourthLine = true;
						}
					}
					else
					{
						if( Letter < My_DudeTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							FourthLine = false;
							LetterWidth = 0;
							Fifth = true;
							IntroState = 2;
						}
					}
					
					if( ThirdLine )
					{
						My_FatherTalksSlow[ Line ] += My_FatherTalks[ 0 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}
					else
					{
						My_DudeTalksSlow3[ Line ] += My_DudeTalks[ 2 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow3[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}

					LetterWidth++;
			
					break;

				}
			case 2:
				{
					if( Fifth )
					{
						if( Letter < My_FatherTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							MyDude_Demon = true;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Fifth = false;
							Sixth = true;
						}
					}
					else
					{
						if( Letter < My_FatherTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							Sixth = false;
							Seventh = true;
							IntroState = 3;
						}
					}
					
					if( Fifth )
					{
						My_FatherTalksSlow2[ Line ] += My_FatherTalks[ 1 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow2[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}
					else
					{
						My_FatherTalksSlow3[ Line ] += My_FatherTalks[ 2 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow3[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}

					LetterWidth++;
			
					break;



				}
			case 3:
				{
					if( Seventh )
					{
						if( Letter < My_FatherTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Seventh = false;
							Eight = true;
						}
					}
					else
					{
						if( Letter < My_DudeTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							IntroState = 5;
							
								
						}
					}
					
					if( Seventh )
					{
						My_FatherTalksSlow4[ Line ] += My_FatherTalks[ 3 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow4[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}
					else
					{
						My_DudeTalksSlow4[ Line ] += My_DudeTalks[ 3 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow4[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
					}

					LetterWidth++;
			
					
					break;



				}
			}

			if( LetterWidth > 27 )
			{
				y += 100;
				LetterWidth = 0;
				Line++;
			}
		}
		else
		{
			if( FirstLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( SecondLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow2[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( ThirdLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( FourthLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow3[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}

			}
			else if( Fifth )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow2[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Sixth )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow3[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Seventh )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_FatherTalksSlow4[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Eight )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, My_DudeTalksSlow4[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}

	
		}

		if( MyDude )
		{
			SDL_Rect destRect = { 0, 0, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ MYDUDE ], 
								gamestate.BackBuffer, &destRect );

		}
		if( MyDude_Demon )
		{
			SDL_Rect destRect = { 620, 0, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ MYDUDE_DEMON ], 
								gamestate.BackBuffer, &destRect );
		}

		if( Father )
		{
			SDL_Rect destRect = { 550, 300, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ FATHER ], 
								gamestate.BackBuffer, &destRect );

		}

		gamestate.FLIP();
	}

	gamestate.GameCondition = GS_LEVEL1;
}
	

	

